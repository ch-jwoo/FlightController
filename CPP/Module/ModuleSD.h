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

//#include "MsgBus/MsgType.h"
#include "MsgBus/MsgBus.h"

namespace FC {

class ModuleSD {
public:
	ModuleSD() = default;

	static void main(){
		BSP_SD_Init();
		char buf[256];
		uint32_t bw;
		int len = 0;
		f_mount(&SDFatFS ,&SDPath[0],1);
		printf("f_mount result: %d",retSD);
//		if(retSD==FR_OK){
//			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
//		}
//		else HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);

		while(1){
			/* sdopen */
			f_open(&SDFile,"log.txt", FA_OPEN_EXISTING | FA_WRITE );
			printf("f_open result: %d",retSD);

//			if(retSD==FR_OK){
//				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
//			}
//			else HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);

			/* data read */
			struct Attitude attitude;
			struct NedAccel nedAccel;
			struct GPS gps;
			struct Barometer baro;
			struct BodyAngularVelocity gyro;

//			if(msgBus.getAttitude(&attitude)){
//			msgBus.getAttitude(&attitude);
//				len = sprintf(buf, "att %u %d %d %d\n", (uint)attitude.timestamp, (int)(attitude.roll*1000000),
//														(int)(attitude.pitch*1000000),
//														(int)(attitude.yaw*1000000));
//				f_write(&SDFile, buf, len, (UINT*)&bw);
//			}
//			if(msgBus.getNedAccel(&nedAccel)){
//				len=sprintf(buf,"accNED %u %d %d %d\n",(uint)nedAccel.timestamp,(int)(nedAccel.xyz[0]*1000000),
//																		(int)(nedAccel.xyz[1]*1000000),
//																		(int)(nedAccel.xyz[2]*1000000));
//				f_write(&SDFile, buf, len, (UINT*)&bw);
//			}
//			if(msgBus.getBodyAngularVelocity(&gyro)){
//				len=sprintf(buf,"gyro %u %d\n",(uint)gyro.timestamp,(int)(gyro.xyz[2]*1000000));
//				f_write(&SDFile, buf, len, (UINT*)&bw);
//			}
//			if(msgBus.getGPS(&gps)){
//				int32_t latDecimal = (int32_t)gps.lat;
//				int32_t latFraction = (int32_t)((gps.lat-latDecimal)*100000000);
//				int32_t lonDecimal = (int32_t)gps.lon;
//				int32_t lonFraction = (int32_t)((gps.lon-lonDecimal)*100000000);
//				len=std::sprintf(buf,"GPS %u %d.%d %d.%d %d %d %d %d\n",(uint)gps.timestamp,
//																  latDecimal, latFraction,
//																  lonDecimal, lonFraction,
//																  (int)(gps.alt*1000000),
//																  (int)(gps.velN*1000000),
//																  (int)(gps.velE*1000000),
//																  (int)(gps.velD*1000000));
//				f_write(&SDFile, buf, len, (UINT*)&bw);
//			}   // Lat Lon Alt velN velE velD
//			if(msgBus.getBarometer(&baro)){
//				len=sprintf(buf,"Baro %u %d\n",(uint)baro.timestamp,(int)(baro.pressure*1000000));
//				f_write(&SDFile, buf, len, (UINT*)&bw);
//			}
//
//			if(retSD==FR_OK){
//				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
//			}
//			else HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
			len=sprintf(buf,"hello fucking world\n");
			retSD=f_write(&SDFile, buf, len, (UINT*)&bw);

			printf("f_close result: %d",retSD);
			printf("f_write result: %d",retSD);
			f_close(&SDFile);


			osDelay(5);			/* 10hz */
		}
	}

	~ModuleSD() = default;
	ModuleSD(const ModuleSD &other) = delete;
	ModuleSD(ModuleSD &&other) = delete;
	ModuleSD& operator=(const ModuleSD &other) = delete;
	ModuleSD& operator=(ModuleSD &&other) = delete;
};

} /* namespace FC */

#endif /* MODULE_MODULESD_H_ */
