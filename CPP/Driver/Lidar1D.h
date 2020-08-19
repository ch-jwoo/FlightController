/*
 * Lidar1D.h
 *
 *  Created on: Aug 5, 2020
 *      Author: cjb88
 */

#ifndef DRIVER_LIDAR1D_H_
#define DRIVER_LIDAR1D_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "tim.h"

typedef struct{
	TIM_HandleTypeDef *htim;
	uint32_t directChannel;
	uint32_t indirectChannel;
	HAL_TIM_ActiveChannel activeChannel1;
	HAL_TIM_ActiveChannel activeChannel2;

	/* output */
	uint32_t distance_mm;
} Lidar1D_t;

extern Lidar1D_t lidar1D;

/*
 *  set timer, channel
 *  timer count 1 microsecond
 *  ex) system clock 168Mhz
 *  	Prescaler : 168-1
 *  	Period : max
 */
void Lidar1D_init(TIM_HandleTypeDef *htim, uint32_t directChannel, uint32_t indirectChannel);

/*
 *  start interrupt
 */
HAL_StatusTypeDef Lidar1D_run();

/*
 *  callback on
 *  void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
 */
void Lidar1D_CaptureCallback(TIM_HandleTypeDef *htim);


#ifdef __cplusplus
}
#endif

#endif /* DRIVER_LIDAR1D_H_ */
