/*
 * ModuleSD.h
 *
 *  Created on: Aug 9, 2020
 *      Author: cjb88
 */

#ifndef MODULE_MODULESD_H_
#define MODULE_MODULESD_H_

#include "MsgBus/MsgBus.h"
#include "freertosVariable.h"
#include "fatfs.h"
#include "Peripherals/Etc/LED.h"

namespace FC {

enum SdSignal{
	SD_saveParam = 0x01,
	SD_saveWP = 0x02
};

class ModuleSD {
public:
   ModuleSD(LED* led);

   static void main();

   static void saveParam(){
	   osThreadFlagsSet(SD_TaskHandle, SD_saveParam);
   }

   static void saveWP(){
	   osThreadFlagsSet(SD_TaskHandle, SD_saveWP);
   }

   static inline FRESULT mount(){
	   return f_mount(&SDFatFS, (TCHAR const*)SDPath, 0);
   }

   void _saveParam();

   void _saveWP();

   void _saveLog();

   void _loadParm();

   void _loadWP();

   void _saveTest();

private:
   /* sd status led */
   LED* led;

   uint8_t writeBuf[256];
   uint32_t bytesWritten = 0;
   uint8_t writeLen = 0;
   FRESULT res;

   bool _openFile(const char* file, BYTE mode);
   bool _closeFile();

   uint32_t _write(const void* writeBuf, uint32_t writeLen);
   char _readByte();

public:
   ~ModuleSD() = default;
   ModuleSD(const ModuleSD &other) = delete;
   ModuleSD(ModuleSD &&other) = delete;
   ModuleSD& operator=(const ModuleSD &other) = delete;
   ModuleSD& operator=(ModuleSD &&other) = delete;
};

} /* namespace FC */

#endif /* MODULE_MODULESD_H_ */
