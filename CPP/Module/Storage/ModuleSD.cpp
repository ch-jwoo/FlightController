/*
 * ModuleSD.cpp
 *
 *  Created on: Aug 9, 2020
 *      Author: cjb88
 */

#include "ModuleSD.h"
#include "fatfs.h"
#include "printf.h"

namespace FC {

void ModuleSD::main(){
   uint8_t writeBuf[256];
   uint32_t bytesWritten = 0;
   uint8_t writeLen = 0;
   FRESULT res;

   /* 1. Mount - 0 */
   res=f_mount(&SDFatFS, (TCHAR const*)SDPath, 0);
   osDelay(1000);

   while(1){
      /* sdopen */
      res=f_open(&SDFile,"0:/log.txt", FA_OPEN_APPEND | FA_WRITE );
      if(res != FR_OK){
         /* fail to open file */
			 HAL_GPIO_WritePin(GPIOF, GPIO_PIN_4, GPIO_PIN_SET);
      }
      else{
     	 HAL_GPIO_WritePin(GPIOF, GPIO_PIN_4, GPIO_PIN_RESET);
			struct Attitude attitude;
			struct NedAccel nedAccel;
			struct GPS gps;
			struct Barometer baro;
			struct BodyAngularVelocity gyro;

         if(msgBus.getAttitude(&attitude)){
            writeLen = sprintf((char*)writeBuf, "att %u %d %d %d\n", (unsigned int)attitude.timestamp, (int)(attitude.roll*1000000),
                                          (int)(attitude.pitch*1000000),
                                          (int)(attitude.yaw*1000000));
            res = f_write(&SDFile, (void const*)writeBuf, writeLen, (UINT*)&bytesWritten);
            if((bytesWritten == 0) || (res != FR_OK)){
         	   /* fail to write file */
         	   HAL_GPIO_WritePin(GPIOF, GPIO_PIN_4, GPIO_PIN_SET);
            }
            else{
         	   HAL_GPIO_WritePin(GPIOF, GPIO_PIN_4, GPIO_PIN_RESET);
            }
         }
         if(msgBus.getNedAccel(&nedAccel)){
            writeLen=sprintf((char*)writeBuf,"accNED %u %d %d %d\n",(unsigned int)nedAccel.timestamp,(int)(nedAccel.xyz[0]*1000000),
                                                      (int)(nedAccel.xyz[1]*1000000),
                                                      (int)(nedAccel.xyz[2]*1000000));
            res = f_write(&SDFile, (void const*)writeBuf, writeLen, (UINT*)&bytesWritten);
            if((bytesWritten == 0) || (res != FR_OK)){
                /* fail to write file */
         	   HAL_GPIO_WritePin(GPIOF, GPIO_PIN_4, GPIO_PIN_SET);
            }
            else{
         	   HAL_GPIO_WritePin(GPIOF, GPIO_PIN_4, GPIO_PIN_RESET);
            }
         }
         if(msgBus.getBodyAngularVelocity(&gyro)){
            writeLen = sprintf((char*)writeBuf,"gyro %u %d\n",(unsigned int)gyro.timestamp,(int)(gyro.xyz[2]*1000000));
            res = f_write(&SDFile, writeBuf, writeLen, (UINT*)&bytesWritten);
            if((bytesWritten == 0) || (res != FR_OK)){
                /* fail to write file */
         	   HAL_GPIO_WritePin(GPIOF, GPIO_PIN_4, GPIO_PIN_SET);
            }
            else{
         	   HAL_GPIO_WritePin(GPIOF, GPIO_PIN_4, GPIO_PIN_RESET);
            }
         }
         if(msgBus.getGPS(&gps)){
            int32_t latDecimal = (int32_t)gps.lat;
            int32_t latFraction = (int32_t)((gps.lat-latDecimal)*100000000);
            int32_t lonDecimal = (int32_t)gps.lon;
            int32_t lonFraction = (int32_t)((gps.lon-lonDecimal)*100000000);
            writeLen=sprintf((char*)writeBuf,"GPS %u %d.%d %d.%d %d %d %d %d\n", gps.timestamp,
                                                  latDecimal, latFraction,
                                                  lonDecimal, lonFraction,
                                                  (int)(gps.alt*1000000),
                                                  (int)(gps.velN*1000000),
                                                  (int)(gps.velE*1000000),
                                                  (int)(gps.velD*1000000));
            res = f_write(&SDFile, writeBuf, writeLen, (UINT*)&bytesWritten);
            if((bytesWritten == 0) || (res != FR_OK)){
                /* fail to write file */
         	   HAL_GPIO_WritePin(GPIOF, GPIO_PIN_4, GPIO_PIN_SET);
            }
            else{
         	   HAL_GPIO_WritePin(GPIOF, GPIO_PIN_4, GPIO_PIN_RESET);
            }
         }   // Lat Lon Alt velN velE velD
         if(msgBus.getBarometer(&baro)){
            writeLen=sprintf((char*)writeBuf,"Baro %u %d\n",(unsigned int)baro.timestamp,(int)(baro.pressure*1000000));
            f_write(&SDFile, writeBuf, writeLen, (UINT*)&bytesWritten);
            if((bytesWritten == 0) || (res != FR_OK)){
                /* fail to write file */
         	   HAL_GPIO_WritePin(GPIOF, GPIO_PIN_4, GPIO_PIN_SET);
            }
            else{
         	   HAL_GPIO_WritePin(GPIOF, GPIO_PIN_4, GPIO_PIN_RESET);
            }
         }
         res=f_close(&SDFile);
      }
      osDelay(5);         /* 10hz */
   }
}
} /* namespace FC */
