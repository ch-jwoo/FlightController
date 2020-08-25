/*
 * ModuleSD.h
 *
 *  Created on: Aug 9, 2020
 *      Author: cjb88
 */

#ifndef MODULE_MODULESD_H_
#define MODULE_MODULESD_H_

#include "MsgBus/MsgBus.h"

namespace FC {

class ModuleSD {
public:
   static void main();

   ModuleSD() = default;
   ~ModuleSD() = default;
   ModuleSD(const ModuleSD &other) = delete;
   ModuleSD(ModuleSD &&other) = delete;
   ModuleSD& operator=(const ModuleSD &other) = delete;
   ModuleSD& operator=(ModuleSD &&other) = delete;
private:
};

} /* namespace FC */

#endif /* MODULE_MODULESD_H_ */
