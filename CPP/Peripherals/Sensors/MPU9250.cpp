/*
 * MPU9250.cpp
 *
 *  Created on: 2020. 8. 23.
 *      Author: cjb88
 */

#include <Peripherals/Sensors/MPU9250.h>

namespace FC {

MPU9250::MPU9250(RtosI2C *i2c, MPU9250_Ascale_t Ascale, MPU9250_Gscale_t Gscale, MPU9250_Mscale_t Mscale, MPU9250_M_MODE_t Mmode)
: i2c(i2c)
, Ascale(Ascale)
, Gscale(Gscale)
, Mscale(Mscale)
, Mmode(Mmode)
{
	aRes = getAres(Ascale);
	gRes = getGres(Gscale);
	mRes = getGres(Gscale);
}

void MPU9250::init(){
	resetMPU9250();
	calibrateMPU9250();
	initMPU9250();
	initAK8963();
}

bool MPU9250::updateMPU9250(){
	i2c->read(MPU9250_ADDRESS, ACCEL_XOUT_H, buffer, 14);
	if(!calRawMPU9250()) return false;
	calCalibMPU9250();
}
bool MPU9250::updateAK8963(){
	i2c->read(AK8963_ADDRESS, AK8963_XOUT_L, buffer, 7);
	if(!calRawAK8963()) return false;
	calCalibAK8963();
}

void MPU9250::calibrateMPU9250(){
	  uint8_t data[12]; // data array to hold accelerometer and gyro x, y, z, data
	  uint16_t ii, packet_count, fifo_count;
	  int32_t gyro_bias[3] = {0, 0, 0}, accel_bias[3] = {0, 0, 0};

	// reset device, reset all registers, clear gyro and accelerometer bias registers
	  writeByte(MPU9250_ADDRESS, PWR_MGMT_1, 0x80); // Write a one to bit 7 reset bit; toggle reset device
	  osDelay(100);

	// get stable time source
	// Set clock source to be PLL with x-axis gyroscope reference, bits 2:0 = 001
	  writeByte(MPU9250_ADDRESS, PWR_MGMT_1, 0x01);
	  writeByte(MPU9250_ADDRESS, PWR_MGMT_2, 0x00);
	  osDelay(200);

	// Configure device for bias calculation
	  writeByte(MPU9250_ADDRESS, INT_ENABLE, 0x00);   // Disable all interrupts
	  writeByte(MPU9250_ADDRESS, FIFO_EN, 0x00);      // Disable FIFO
	  writeByte(MPU9250_ADDRESS, PWR_MGMT_1, 0x00);   // Turn on internal clock source
	  writeByte(MPU9250_ADDRESS, I2C_MST_CTRL, 0x00); // Disable I2C master
	  writeByte(MPU9250_ADDRESS, USER_CTRL, 0x00);    // Disable FIFO and I2C master modes
	  writeByte(MPU9250_ADDRESS, USER_CTRL, 0x0C);    // Reset FIFO and DMP
	  osDelay(15);

	// Configure MPU9250 gyro and accelerometer for bias calculation
	  writeByte(MPU9250_ADDRESS, CONFIG, 0x01);      // Set low-pass filter to 188 Hz
	  writeByte(MPU9250_ADDRESS, SMPLRT_DIV, 0x00);  // Set sample rate to 1 kHz
	  writeByte(MPU9250_ADDRESS, GYRO_CONFIG, 0x00);  // Set gyro full-scale to 250 degrees per second, maximum sensitivity
	  writeByte(MPU9250_ADDRESS, ACCEL_CONFIG, 0x00); // Set accelerometer full-scale to 2 g, maximum sensitivity

	// Configure FIFO to capture accelerometer and gyro data for bias calculation
	  writeByte(MPU9250_ADDRESS, USER_CTRL, 0x40);   // Enable FIFO
	  writeByte(MPU9250_ADDRESS, FIFO_EN, 0x78);     // Enable gyro and accelerometer sensors for FIFO (max size 512 bytes in MPU-9250)
	  osDelay(40); // accumulate 40 samples in 80 milliseconds = 480 bytes

	// At end of sample accumulation, turn off FIFO sensor read
	  writeByte(MPU9250_ADDRESS, FIFO_EN, 0x00);        // Disable gyro and accelerometer sensors for FIFO
	  readBytes(MPU9250_ADDRESS, FIFO_COUNTH, 2, &data[0]); // read FIFO sample count
	  fifo_count = ((uint16_t)data[0] << 8) | data[1];
	  packet_count = fifo_count/12;// How many sets of full gyro and accelerometer data for averaging

	  for (ii = 0; ii < packet_count; ii++) {
	    int16_t accel_temp[3] = {0, 0, 0}, gyro_temp[3] = {0, 0, 0};
	    readBytes(MPU9250_ADDRESS, FIFO_R_W, 12, &data[0]); // read data for averaging
	    accel_temp[0] = (int16_t) (((int16_t)data[0] << 8) | data[1]  ) ;  // Form signed 16-bit integer for each sample in FIFO
	    accel_temp[1] = (int16_t) (((int16_t)data[2] << 8) | data[3]  ) ;
	    accel_temp[2] = (int16_t) (((int16_t)data[4] << 8) | data[5]  ) ;
	    gyro_temp[0]  = (int16_t) (((int16_t)data[6] << 8) | data[7]  ) ;
	    gyro_temp[1]  = (int16_t) (((int16_t)data[8] << 8) | data[9]  ) ;
	    gyro_temp[2]  = (int16_t) (((int16_t)data[10] << 8) | data[11]) ;

	    accel_bias[0] += (int32_t) accel_temp[0]; // Sum individual signed 16-bit biases to get accumulated signed 32-bit biases
	    accel_bias[1] += (int32_t) accel_temp[1];
	    accel_bias[2] += (int32_t) accel_temp[2];
	    gyro_bias[0]  += (int32_t) gyro_temp[0];
	    gyro_bias[1]  += (int32_t) gyro_temp[1];
	    gyro_bias[2]  += (int32_t) gyro_temp[2];

	  }
	    accel_bias[0] /= (int32_t) packet_count; // Normalize sums to get average count biases
	    accel_bias[1] /= (int32_t) packet_count;
	    accel_bias[2] /= (int32_t) packet_count;
	    gyro_bias[0]  /= (int32_t) packet_count;
	    gyro_bias[1]  /= (int32_t) packet_count;
	    gyro_bias[2]  /= (int32_t) packet_count;

	    uint16_t accelsensitivity = (uint16_t)(1/aRes);
	//    uint16_t gyrosensitivity = (uint16_t)(1/gRes);
	//    printf("%u, %u", accelsensitivity, gyrosensitivity);

	  if(accel_bias[2] > 0L) {accel_bias[2] -= (int32_t) accelsensitivity;}  // Remove gravity from the z-axis accelerometer bias calculation
	  else {accel_bias[2] += (int32_t) accelsensitivity;}

	// Construct the gyro biases for push to the hardware gyro bias registers, which are reset to zero upon device startup
	  data[0] = (-gyro_bias[0]/4  >> 8) & 0xFF; // Divide by 4 to get 32.9 LSB per deg/s to conform to expected bias input format
	  data[1] = (-gyro_bias[0]/4)       & 0xFF; // Biases are additive, so change sign on calculated average gyro biases
	  data[2] = (-gyro_bias[1]/4  >> 8) & 0xFF;
	  data[3] = (-gyro_bias[1]/4)       & 0xFF;
	  data[4] = (-gyro_bias[2]/4  >> 8) & 0xFF;
	  data[5] = (-gyro_bias[2]/4)       & 0xFF;

	/// Push gyro biases to hardware registers
	  writeByte(MPU9250_ADDRESS, XG_OFFSET_H, data[0]);
	  writeByte(MPU9250_ADDRESS, XG_OFFSET_L, data[1]);
	  writeByte(MPU9250_ADDRESS, YG_OFFSET_H, data[2]);
	  writeByte(MPU9250_ADDRESS, YG_OFFSET_L, data[3]);
	  writeByte(MPU9250_ADDRESS, ZG_OFFSET_H, data[4]);
	  writeByte(MPU9250_ADDRESS, ZG_OFFSET_L, data[5]);


	//  MPU9250_gyroBias[0] = (float) gyro_bias[0]/(float) gyrosensitivity; // construct gyro bias in deg/s for later manual subtraction
	//  MPU9250_gyroBias[1] = (float) gyro_bias[1]/(float) gyrosensitivity;
	//  MPU9250_gyroBias[2] = (float) gyro_bias[2]/(float) gyrosensitivity;

	// Construct the accelerometer biases for push to the hardware accelerometer bias registers. These registers contain
	// factory trim values which must be added to the calculated accelerometer biases; on boot up these registers will hold
	// non-zero values. In addition, bit 0 of the lower byte must be preserved since it is used for temperature
	// compensation calculations. Accelerometer bias registers expect bias input as 2048 LSB per g, so that
	// the accelerometer biases calculated above must be divided by 8.

	  int32_t accel_bias_reg[3] = {0, 0, 0}; // A place to hold the factory accelerometer trim biases
	  readBytes(MPU9250_ADDRESS, XA_OFFSET_H, 2, &data[0]); // Read factory accelerometer trim values
	  accel_bias_reg[0] = (int16_t) ((int16_t)data[0] << 8) | data[1];
	  readBytes(MPU9250_ADDRESS, YA_OFFSET_H, 2, &data[0]);
	  accel_bias_reg[1] = (int16_t) ((int16_t)data[0] << 8) | data[1];
	  readBytes(MPU9250_ADDRESS, ZA_OFFSET_H, 2, &data[0]);
	  accel_bias_reg[2] = (int16_t) ((int16_t)data[0] << 8) | data[1];

	  uint32_t mask = 1uL; // Define mask for temperature compensation bit 0 of lower byte of accelerometer bias registers
	  uint8_t mask_bit[3] = {0, 0, 0}; // Define array to hold mask bit for each accelerometer bias axis

	  for(ii = 0; ii < 3; ii++) {
	    if(accel_bias_reg[ii] & mask) mask_bit[ii] = 0x01; // If temperature compensation bit is set, record that fact in mask_bit
	  }

	  // Construct total accelerometer bias, including calculated average accelerometer bias from above
	  accel_bias_reg[0] -= (accel_bias[0]/8); // Subtract calculated averaged accelerometer bias scaled to 2048 LSB/g (16 g full scale)
	  accel_bias_reg[1] -= (accel_bias[1]/8);
	  accel_bias_reg[2] -= (accel_bias[2]/8);

	  data[0] = (accel_bias_reg[0] >> 8) & 0xFF;
	  data[1] = (accel_bias_reg[0])      & 0xFF;
	  data[1] = data[1] | mask_bit[0]; // preserve temperature compensation bit when writing back to accelerometer bias registers
	  data[2] = (accel_bias_reg[1] >> 8) & 0xFF;
	  data[3] = (accel_bias_reg[1])      & 0xFF;
	  data[3] = data[3] | mask_bit[1]; // preserve temperature compensation bit when writing back to accelerometer bias registers
	  data[4] = (accel_bias_reg[2] >> 8) & 0xFF;
	  data[5] = (accel_bias_reg[2])      & 0xFF;
	  data[5] = data[5] | mask_bit[2]; // preserve temperature compensation bit when writing back to accelerometer bias registers

	// Apparently this is not working for the acceleration biases in the MPU-9250
	// Are we handling the temperature correction bit properly?
	// Push accelerometer biases to hardware registers
	//  writeByte(MPU9250_ADDRESS, XA_OFFSET_H, data[0]);
	//  writeByte(MPU9250_ADDRESS, XA_OFFSET_L, data[1]);
	//  writeByte(MPU9250_ADDRESS, YA_OFFSET_H, data[2]);
	//  writeByte(MPU9250_ADDRESS, YA_OFFSET_L, data[3]);
	//  writeByte(MPU9250_ADDRESS, ZA_OFFSET_H, data[4]);
	//  writeByte(MPU9250_ADDRESS, ZA_OFFSET_L, data[5]);

	// Output scaled accelerometer biases for manual subtraction in the main program
	//    MPU9250_accelBias[0] = (float)accel_bias[0]/(float)accelsensitivity;
	//    MPU9250_accelBias[1] = (float)accel_bias[1]/(float)accelsensitivity;
	//    MPU9250_accelBias[2] = (float)accel_bias[2]/(float)accelsensitivity;
}

void MPU9250::resetMPU9250(){
    writeByte(MPU9250_ADDRESS, PWR_MGMT_1, 0x80); // Write a one to bit 7 reset bit; toggle reset device
}

void MPU9250::initMPU9250()
{
 // Initialize MPU9250 device
 // wake up device
  writeByte(MPU9250_ADDRESS, PWR_MGMT_1, 0x00); // Clear sleep mode bit (6), enable all sensors
  osDelay(100); // Delay 100 ms for PLL to get established on x-axis gyro; should check for PLL ready interrupt

 // get stable time source
  writeByte(MPU9250_ADDRESS, PWR_MGMT_1, 0x01);  // Set clock source to be PLL with x-axis gyroscope reference, bits 2:0 = 001

 // Configure Gyro and Accelerometer
 // Disable FSYNC and set accelerometer and gyro bandwidth to 44 and 42 Hz, respectively;
 // DLPF_CFG = bits 2:0 = 010; this sets the sample rate at 1 kHz for both
 // Maximum delay is 4.9 ms which is just over a 200 Hz maximum rate
  writeByte(MPU9250_ADDRESS, CONFIG, 0x03);

 // Set sample rate = gyroscope output rate/(1 + SMPLRT_DIV)
  writeByte(MPU9250_ADDRESS, SMPLRT_DIV, 0x04);  // Use a 200 Hz rate; the same rate set in CONFIG above

 // Set gyroscope full scale range
 // Range selects FS_SEL and AFS_SEL are 0 - 3, so 2-bit values are left-shifted into positions 4:3
  uint8_t c = readByte(MPU9250_ADDRESS, GYRO_CONFIG); // get current GYRO_CONFIG register value
 // c = c & ~0xE0; // Clear self-test bits [7:5]
  c = c & ~0x02; // Clear Fchoice bits [1:0]
  c = c & ~0x18; // Clear AFS bits [4:3]
  c = c | Gscale << 3; // Set full scale range for the gyro
 // c =| 0x00; // Set Fchoice for the gyro to 11 by writing i
  writeByte(MPU9250_ADDRESS, GYRO_CONFIG, c ); // Write new GYRO_CONFIG value to regts inverse to bits 1:0 of GYRO_CONFIGister

 // Set accelerometer full-scale range configuration
  c = readByte(MPU9250_ADDRESS, ACCEL_CONFIG); // get current ACCEL_CONFIG register value
 // c = c & ~0xE0; // Clear self-test bits [7:5]
  c = c & ~0x18;  // Clear AFS bits [4:3]
  c = c | Ascale << 3; // Set full scale range for the accelerometer
  writeByte(MPU9250_ADDRESS, ACCEL_CONFIG, c); // Write new ACCEL_CONFIG register value

 // Set accelerometer sample rate configuration
 // It is possible to get a 4 kHz sample rate from the accelerometer by choosing 1 for
 // accel_fchoice_b bit [3]; in this case the bandwidth is 1.13 kHz
  c = readByte(MPU9250_ADDRESS, ACCEL_CONFIG2); // get current ACCEL_CONFIG2 register value
  c = c & ~0x0F; // Clear accel_fchoice_b (bit 3) and A_DLPFG (bits [2:0])
  c = c | 0x03;  // Set accelerometer rate to 1 kHz and bandwidth to 41 Hz
  writeByte(MPU9250_ADDRESS, ACCEL_CONFIG2, c); // Write new ACCEL_CONFIG2 register value

 // The accelerometer, gyro, and thermometer are set to 1 kHz sample rates,
 // but all these rates are further reduced by a factor of 5 to 200 Hz because of the SMPLRT_DIV setting

  // Configure Interrupts and Bypass Enable
  // Set interrupt pin active high, push-pull, and clear on read of INT_STATUS, enable I2C_BYPASS_EN so additional chips
  // can join the I2C bus and all can be controlled by the Arduino as master
  writeByte(MPU9250_ADDRESS, INT_PIN_CFG, 0x22);
  writeByte(MPU9250_ADDRESS, INT_ENABLE, 0x01);  // Enable data ready (bit 0) interrupt
}

void MPU9250::initAK8963()
{
	// First extract the factory calibration for each magnetometer axis
	uint8_t rawData[3];  // x/y/z gyro calibration data stored here
	writeByte(AK8963_ADDRESS, AK8963_CNTL, 0x00); // Power down magnetometer
	osDelay(10);
	writeByte(AK8963_ADDRESS, AK8963_CNTL, 0x0F); // Enter Fuse ROM access mode
	osDelay(10);
	readBytes(AK8963_ADDRESS, AK8963_ASAX, 3, &rawData[0]);  // Read the x-, y-, and z-axis calibration values

	// set axis to accel axis
	magCalibration[1] =  (float)(rawData[0] - 128)/256.0f + 1.0f;   // Return x-axis sensitivity adjustment values, etc.
	magCalibration[0] =  (float)(rawData[1] - 128)/256.0f + 1.0f;
	magCalibration[2] =  ((float)(rawData[2] - 128)/256.0f + 1.0f);
	writeByte(AK8963_ADDRESS, AK8963_CNTL, 0x00); // Power down magnetometer
	osDelay(10);
	// Configure the magnetometer for continuous read and highest resolution
	// set Mscale bit 4 to 1 (0) to enable 16 (14) bit resolution in CNTL register,
	// and enable continuous mode data acquisition Mmode (bits [3:0]), 0010 for 8 Hz and 0110 for 100 Hz sample rates
	writeByte(AK8963_ADDRESS, AK8963_CNTL, Mscale << 4 | Mmode); // Set magnetometer data resolution and sample ODR
	osDelay(10);
}

bool MPU9250::calRawMPU9250(){
	// accel axis reverse
	accelCount[0] = ((((int16_t)buffer[0]) << 8) | buffer[1]);
	accelCount[1] = ((((int16_t)buffer[2]) << 8) | buffer[3]);
	accelCount[2] = ((((int16_t)buffer[4]) << 8) | buffer[5]);
	tmpCount = (int16_t) (buffer[6] << 8 | buffer[7]);
	gyroCount[0] = (((int16_t)buffer[8]) << 8) | buffer[9];
	gyroCount[1] = (((int16_t)buffer[10]) << 8) | buffer[11];
	gyroCount[2] = (((int16_t)buffer[12]) << 8) | buffer[13];
	if(accelCount[0] == 0 && accelCount[1] == 0 && accelCount[2] == 0) return false;
	return true;
}

void MPU9250::calCalibMPU9250(){
	//	MPU9250_a[0] = ((float)MPU9250_accelCount[0]*MPU9250_aRes - MPU9250_accelBias[0]);  // get actual g value, this depends on scale being set
	//	MPU9250_a[1] = ((float)MPU9250_accelCount[1]*MPU9250_aRes - MPU9250_accelBias[1]);
	//	MPU9250_a[2] = ((float)MPU9250_accelCount[2]*MPU9250_aRes - MPU9250_accelBias[2]);
	//	// Calculate the gyro value into actual degrees per second
	//	MPU9250_g[0] = MPU9250_DEG2RAD*((float)MPU9250_gyroCount[0]*MPU9250_gRes - MPU9250_gyroBias[0]);  // get actual gyro value, this depends on scale being set
	//	MPU9250_g[1] = MPU9250_DEG2RAD*((float)MPU9250_gyroCount[1]*MPU9250_gRes - MPU9250_gyroBias[1]);
	//	MPU9250_g[2] = MPU9250_DEG2RAD*((float)MPU9250_gyroCount[2]*MPU9250_gRes - MPU9250_gyroBias[2]);

		accel[0] = ((float)accelCount[0]*aRes);  // get actual g value, this depends on scale being set
		accel[1] = ((float)accelCount[1]*aRes);
		accel[2] = ((float)accelCount[2]*aRes);
		// Calculate the gyro value into actual degrees per second
		gyro[0] = (float)gyroCount[0]*gRes;  // get actual gyro value, this depends on scale being set
		gyro[1] = (float)gyroCount[1]*gRes;
		gyro[2] = (float)gyroCount[2]*gRes;
}

bool MPU9250::calRawAK8963(){
	if(buffer[6] & 0x08) return false; // Check if magnetic sensor overflow set, if not then report data

	// mag have different axis with acc, gyr -> ax = my, ay = mx, az = -mz
	magCount[1] = (int16_t)(((int16_t)buffer[1] << 8) | buffer[0]);  // Turn the MSB and LSB into a signed 16-bit value
	magCount[0] = (int16_t)(((int16_t)buffer[3] << 8) | buffer[2]);  // Data stored as little Endian
	magCount[2] = -(int16_t)(((int16_t)buffer[5] << 8) | buffer[4]);
	return true;
}

void MPU9250::calCalibAK8963(){
    mag[0] = (float)magCount[0]*mRes*magCalibration[0];  // get actual magnetometer value, this depends on scale being set
    mag[1] = (float)magCount[1]*mRes*magCalibration[1];
    mag[2] = (float)magCount[2]*mRes*magCalibration[2];
}

float MPU9250::getAres(MPU9250_Ascale_t Ascale){
	switch (Ascale)
	{
	// Possible accelerometer scales (and their register bit settings) are:
	// 2 Gs (00), 4 Gs (01), 8 Gs (10), and 16 Gs  (11).
		// Here's a bit of an algorith to calculate DPS/(ADC tick) based on that 2-bit value:
	case MPU9250_AFS_2G:
		  return 2.0/32768.0;
	case MPU9250_AFS_4G:
		  return 4.0/32768.0;
	case MPU9250_AFS_8G:
		  return 8.0/32768.0;
	case MPU9250_AFS_16G:
		  return 16.0/32768.0;
	}
}
float MPU9250::getGres(MPU9250_Gscale_t Gscale){
	  switch (Gscale)
	  {
	    // Possible gyro scales (and their register bit settings) are:
	    // 250 DPS (00), 500 DPS (01), 1000 DPS (10), and 2000 DPS  (11).
	        // Here's a bit of an algorith to calculate DPS/(ADC tick) based on that 2-bit value:
	    case MPU9250_GFS_250DPS:
	    	  return 250.0/32768.0;
	    case MPU9250_GFS_500DPS:
	    	  return 500.0/32768.0;
	    case MPU9250_GFS_1000DPS:
	    	  return 1000.0/32768.0;
	    case MPU9250_GFS_2000DPS:
	    	  return 2000.0/32768.0;
	  }
}
float MPU9250::getMres(MPU9250_Mscale_t Mscale){
	switch (Mscale)
	{
	// Possible magnetometer scales (and their register bit settings) are:
	// 14 bit resolution (0) and 16 bit resolution (1)
	case MPU9250_MFS_14BITS:
		  return 10.0*4912.0/8190.0; // Proper scale to return milliGauss
	case MPU9250_MFS_16BITS:
		  return 10.0*4912.0/32760.0; // Proper scale to return milliGauss
	}
}

} /* namespace FC */
