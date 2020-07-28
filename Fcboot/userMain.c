/*
 * userMain.c
 *
 *  Created on: Jul 14, 2020
 *      Author: cjb88
 */

//essential
#include "main.h"
#include "usart.h"
#include "i2c.h"
#include "tim.h"
#include "cmsis_os.h"

//additional
#include "stdio.h"
#include "stdlib.h"

//selfmade
#include "MPU9250.h"
#include "sbus.h"
#include "tm_stm32_gps.h"
#include "IST8310.h"
#include "bme280.h"

//TM_GPS_t gps;
//uint8_t tempBuf;

#define USE_IST8310
#define USE_GPS
#define USE_MPU9250
#define USE_BME280
#define USE_SBUS

//we can use printf
int _write(int file, unsigned char* p, int len) // for debug through uart3
{
	HAL_UART_Transmit(&huart3, p, len, 10);
	return len;
}

#ifdef USE_GPS
void GPS_main(){
    TM_GPS_Init(&huart5);
//	HAL_UART_Receive_DMA(&huart4, &gps.dmaBuf, 1);
	while(1){
//		printf("run\r\n");
		GPS_calHz();
		printf("%u\r\n", gps.hz);
		osDelay(1000);
	}
}
#endif


#ifdef USE_IST8310
void IST8310_main(){
	taskENTER_CRITICAL();
	IST8310(&hi2c2);
	taskEXIT_CRITICAL();

//	IST8310_tempBuf tempBuffer;
//	IST8310_raw rawBuf;
	while(1){

		IST8310_updataIT();

		osDelay(10);
	}
}
#endif

float globalT, globalP, globalH;

void BME280_main(){
	taskENTER_CRITICAL();
	BME280(&hi2c2);

	/*
	 * recommended mode : gaming
	 * Sensor mode : normal mode, standby = 0.5ms
	 * oversampling : pressureX4, temperatureX1, humidityX0
	 * IIR filter coefficient : 16
	 * RMS Noise : 0.3Pa/2.5cm
	 * Data output rate : 83hz
	 * Filter bandwidth : 1.75 Hz
	 * response time : 0.3s
	 */
	BME280_init(P_OSR_04, H_OSR_00, T_OSR_01, normal, BW0_021ODR,t_00_5ms);
	taskEXIT_CRITICAL();
//	osDelay(100);
	while(1){
//		uint8_t id = 0;
//		id = BME280_getChipID();
//		printf("%u\r\n", id);
//		int32_t t = 0, p = 0, h = 0;
//		t = BME280_readTemperature();
//		p = BME280_readPressure();
//		h = BME280_readHumidity();
//
//		uint32_t comP, comH;
//		int32_t comT;
//		comT = BME280_compensate_T(t);
//		comP = BME280_compensate_P(p);
//		comH = BME280_compensate_H(h);
//		printf("%d %u %u\r\n", comT, comP, comH);

		BME280_updateIT();
//		printf("%d\r\n", bme280.countP);
//
//		globalT = comT/100.0;
//		globalP = comP/256.0/100.0;
//		globalH = comH/1024.0;
		osDelay(20);
	}
}

void userMain(){
    setvbuf(stdout, NULL, _IONBF, 0);

    printf("boot complete\r\n");

#ifdef USE_SBUS
	sbus_start(&huart7);
#endif

#ifdef USE_BME280
	xTaskCreate(BME280_main,
				"BME280_main",
				configMINIMAL_STACK_SIZE,
				NULL,
				4,
				NULL);
#endif

#ifdef USE_IST8310
	xTaskCreate(IST8310_main,
				"IST8310_main",
				configMINIMAL_STACK_SIZE,
				NULL,
				4,
				NULL);
#endif

#ifdef USE_GPS
	xTaskCreate(GPS_main,
				"GPS_main",
				configMINIMAL_STACK_SIZE,
				NULL,
				4,
				NULL);
#endif

#ifdef USE_MPU9250
    xTaskCreate(MPU9250_main,
    		    "MPU9250_main",
				configMINIMAL_STACK_SIZE,
				NULL,
				4,
				NULL);
#endif
}



//callback
void HAL_I2C_MemRxCpltCallback(I2C_HandleTypeDef *hi2c){
#ifdef USE_MPU9250
	MPU9250_rxCpltCallback(hi2c);
#endif

#ifdef USE_IST8310
	IST8310_rxCpltCallback(hi2c);
#endif

#ifdef USE_BME280
	BME280_rxCpltCallback(hi2c);
#endif
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
#ifdef USE_SBUS
	if(huart->Instance == UART7){
		sbus_callback();
	}
#endif
	if(huart->Instance == USART2){
		// telemetry
	}
#ifdef USE_GPS
	if(huart->Instance == UART5){
		TM_GPS_Update();
	}
#endif
}
