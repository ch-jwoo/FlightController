/*
 * ModuleSD.h
 *
 *  Created on: Aug 9, 2020
 *      Author: cjb88
 */

#ifndef MODULE_MODULESD_H_
#define MODULE_MODULESD_H_

#include "main.h"
#include "fatfs.h"
#include "cstdio"
#include <cstring>

#include "printf.h"

//#include "MsgBus/MsgType.h"
#include "MsgBus/MsgBus.h"

namespace FC {

class ModuleSD {
public:
	ModuleSD() = default;

	static void main(){
		uint8_t writeBuf[256];
		uint32_t bytesWritten = 0;
		uint8_t writeLen = 0;

		FRESULT res;
//		uint32_t bytesWritten = 0;
//		uint32_t bytesRead;
//		uint8_t writeBuffer[100];
	//	uint8_t readBuffer[100];

		/*
		 *  TODO
		 *  FR_DISK_ERR		hardware layer error.
		 *  				retry after circuit
		 */
		uint8_t wtext[] = "Hello from SDIO DMA RTOS\n";
		/* 1. Mount - 0 */
		f_mount(&SDFatFS, (TCHAR const*)SDPath, 0);
		osDelay(1000);
		printf("try to open file\r\n");
		if((res = f_open(&SDFile, "0:/test.txt", FA_CREATE_ALWAYS | FA_WRITE)) != FR_OK){
			/* fail to open file */
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
			printf("fail to open file %d\r\n", res);
		}
		else{
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
			res = f_write(&SDFile, wtext, strlen((char*)wtext), (UINT*)bytesWritten);
			if((bytesWritten == 0) || (res != FR_OK)){
				/* fail to write file */
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
				printf("fail to write %d\r\n", res);
			}
			else{
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
				printf("success write\r\n");
			}

			f_close(&SDFile);
		}

		while(1){
			/* sdopen */
			if(f_open(&SDFile,"0:/log.txt", FA_CREATE_ALWAYS | FA_WRITE ) != FR_OK){
				/* fail to open file */
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
			}
			else{
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
//				struct Attitude attitude;
//				struct NedAccel nedAccel;
//				struct GPS gps;
//				struct Barometer baro;
//				struct BodyAngularVelocity gyro;
//
//				if(msgBus.getAttitude(&attitude)){
//					writeLen = sprintf((char*)writeBuf, "att %u %d %d %d\n", (uint)attitude.timestamp, (int)(attitude.roll*1000000),
//															(int)(attitude.pitch*1000000),
//															(int)(attitude.yaw*1000000));
//					res = f_write(&SDFile, (void const*)writeBuf, writeLen, (UINT*)&bytesWritten);
//					if((bytesWritten == 0) || (res != FR_OK)){
//						/* fail to write file */
//						HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
//					}
//					else{
//						HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
//					}
//				}
//				if(msgBus.getNedAccel(&nedAccel)){
//					writeLen=sprintf((char*)writeBuf,"accNED %u %d %d %d\n",(uint)nedAccel.timestamp,(int)(nedAccel.xyz[0]*1000000),
//																			(int)(nedAccel.xyz[1]*1000000),
//																			(int)(nedAccel.xyz[2]*1000000));
//					res = f_write(&SDFile, (void const*)writeBuf, writeLen, (UINT*)&bytesWritten);
//					if((bytesWritten == 0) || (res != FR_OK)){
//						/* fail to write file */
//						HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
//					}
//					else{
//						HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
//					}
//				}
//				if(msgBus.getBodyAngularVelocity(&gyro)){
//					writeLen = sprintf((char*)writeBuf,"gyro %u %d\n",(uint)gyro.timestamp,(int)(gyro.xyz[2]*1000000));
//					res = f_write(&SDFile, writeBuf, writeLen, (UINT*)&bytesWritten);
//					if((bytesWritten == 0) || (res != FR_OK)){
//						/* fail to write file */
//						HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
//					}
//					else{
//						HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
//					}
//				}
//				if(msgBus.getGPS(&gps)){
//					int32_t latDecimal = (int32_t)gps.lat;
//					int32_t latFraction = (int32_t)((gps.lat-latDecimal)*100000000);
//					int32_t lonDecimal = (int32_t)gps.lon;
//					int32_t lonFraction = (int32_t)((gps.lon-lonDecimal)*100000000);
//					writeLen=std::sprintf((char*)writeBuf,"GPS %u %d.%d %d.%d %d %d %d %d\n", gps.timestamp,
//																	  latDecimal, latFraction,
//																	  lonDecimal, lonFraction,
//																	  (int)(gps.alt*1000000),
//																	  (int)(gps.velN*1000000),
//																	  (int)(gps.velE*1000000),
//																	  (int)(gps.velD*1000000));
//					res = f_write(&SDFile, writeBuf, writeLen, (UINT*)&bytesWritten);
//					if((bytesWritten == 0) || (res != FR_OK)){
//						/* fail to write file */
//						HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
//					}
//					else{
//						HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
//					}
//				}   // Lat Lon Alt velN velE velD
//				if(msgBus.getBarometer(&baro)){
//					writeLen=sprintf((char*)writeBuf,"Baro %u %d\n",(uint)baro.timestamp,(int)(baro.pressure*1000000));
//					f_write(&SDFile, writeBuf, writeLen, (UINT*)&bytesWritten);
//					if((bytesWritten == 0) || (res != FR_OK)){
//						/* fail to write file */
//						HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
//					}
//					else{
//						HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
//					}
//				}
				writeLen = sprintf((char*)writeBuf,"hello fucking world\n");
				res = f_write(&SDFile, writeBuf, writeLen, (UINT*)&bytesWritten);
				if((bytesWritten == 0) || (res != FR_OK)){
					/* fail to write file */
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
				}
				else{
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
				}

				if(f_close(&SDFile) != FR_OK){
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
				}
				else{
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
				}
			}

			osDelay(5);			/* 10hz */
		}
	}

	~ModuleSD() = default;
	ModuleSD(const ModuleSD &other) = delete;
	ModuleSD(ModuleSD &&other) = delete;
	ModuleSD& operator=(const ModuleSD &other) = delete;
	ModuleSD& operator=(ModuleSD &&other) = delete;
private:
};

} /* namespace FC */

#endif /* MODULE_MODULESD_H_ */
