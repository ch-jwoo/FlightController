/*
 * userMain.c
 *
 *  Created on: Jul 14, 2020
 *      Author: cjb88
 */

//essential
#include <fc_usec.h>
#include "main.h"
#include "usart.h"
#include "i2c.h"
#include "tim.h"
#include "cmsis_os.h"
#include "fatfs.h"

//additional
#include "stdio.h"
#include "stdlib.h"

//selfmade
#include "MPU9250.h"
#include "sbus.h"
#include "tm_stm32_gps.h"
#include "IST8310.h"
#include "bme280.h"

//#define USE_IST8310
//#define USE_GPS
//#define USE_MPU9250
//#define USE_BME280
//#define USE_SBUS

//we can use printf
int _write(int file, unsigned char* p, int len) // for debug through uart3
{
	HAL_UART_Transmit(&huart3, p, len, 10);
	return len;
}


#ifdef USE_GPS
void GPS_main(){
	taskENTER_CRITICAL();
    TM_GPS_Init(&huart8);
	taskEXIT_CRITICAL();

	while(1){
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

	while(1){

		IST8310_updataIT();

		osDelay(10);
	}
}
#endif


#ifdef USE_BME280
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

	while(1){
		BME280_updateIT();
		osDelay(20);
	}
}
#endif

#ifdef USE_MPU9250
void MPU9250_main(){
	TickType_t xLastWakeTime;
	const TickType_t xFrequency = 5;

	taskENTER_CRITICAL();
	MPU9250(&hi2c1);
	taskEXIT_CRITICAL();

	xLastWakeTime = xTaskGetTickCount();
	while(1){
		vTaskDelayUntil(&xLastWakeTime, xFrequency);
		MPU9250_updateDMA();
	}
}
#endif

uint32_t tim;
uint32_t temp;

void debug_main(){
//	BYTE buf[32] = "Hello world";
//	uint32_t bw, br;
//	uint8_t flag = 0;
//	if(flag == 0 && (retSD = f_mount(&SDFatFS, &SDPath[0], 1)) == FR_OK){
//		printf("f_mount OK %d\r\n", retSD);
//		printf("??\r\n");
//		flag = 1;
//	}
//	printf("Test %d\r\n", retSD);
	BYTE buf[32]="hello world";
	   uint32_t bw;

	   retSD=f_mount(&SDFatFS ,&SDPath[0],1);

//	   printf("f_mount OK %d \n \r",retSD);

	   if(retSD==FR_OK){
	      printf("f_mount OK %d \n \r",retSD);
	   }
	   else printf("f_mount Fail: %d \n \r",retSD);

	   retSD=f_open(&SDFile,"123.txt",FA_CREATE_NEW |FA_WRITE);
	   if(retSD==FR_OK){
	      printf("f_open OK &d \n \r",retSD);
	   }
	   else printf("f_open Fail: %d \n \r",retSD);
	   osDelay(10);

	   retSD=f_write(&SDFile,buf,sizeof(buf),&bw);
	      if(retSD==FR_OK){
	         printf("f_wirte OK &d \n \r",retSD);
	      }
	   else printf("f_write Fail: %d \n \r",retSD);

	   retSD=f_close(&SDFile);
	   if(retSD==FR_OK){
	      printf("f_close cplt: %d \n \r",retSD);
	   }
	   else printf("f_close fail: &d \n \r",retSD);

	   retSD=f_mount(NULL,"0:/",1);

	   printf("dismount result %d \r \n",retSD);
	osDelay(1000);
	while(1){
//		uint32_t last = (uint32_t)FC_usec();
//		temp = fcMicroSecond();
//		taskENTER_CRITICAL();



		osDelay(1000);
//		tim = (uint32_t)FC_usec() - last;
	}
}

void userMain(){
    setvbuf(stdout, NULL, _IONBF, 0);
	HAL_TIM_Base_Start_IT(&htim2);

    printf("boot complete\r\n");

	xTaskCreate(debug_main,
				"debug_main",
				configMINIMAL_STACK_SIZE,
				NULL,
				5,
				NULL);

#ifdef USE_SBUS
	SBUS_init(&huart7);
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
	MPU9250_i2cRxCpltCallback(hi2c);
#endif

#ifdef USE_IST8310
	IST8310_i2cRxCpltCallback(hi2c);
#endif

#ifdef USE_BME280
	BME280_i2cRxCpltCallback(hi2c);
#endif
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
#ifdef USE_SBUS
	SBUS_uartRxCpltCallback(huart);
#endif
#ifdef USE_GPS
	if(huart->Instance == UART5){
		TM_GPS_Update();
	}
#endif

	if(huart->Instance == USART2){
		// telemetry
	}
}
