/*
 * Lidar1D.c
 *
 *  Created on: Aug 5, 2020
 *      Author: cjb88
 */

#include "Lidar1D.h"

Lidar1D_t lidar1D={0,};

void Lidar1D_init(TIM_HandleTypeDef *htim, uint32_t directChannel, uint32_t indirectChannel){
		lidar1D.htim = htim;
		lidar1D.directChannel = directChannel;
		lidar1D.indirectChannel = indirectChannel;
	  switch (directChannel)
	  {
	    case TIM_CHANNEL_1:
	    {
		  lidar1D.activeChannel1 = HAL_TIM_ACTIVE_CHANNEL_1;
	      break;
	    }

	    case TIM_CHANNEL_2:
	    {
		  lidar1D.activeChannel1 = HAL_TIM_ACTIVE_CHANNEL_2;
	      break;
	    }

	    case TIM_CHANNEL_3:
	    {
		  lidar1D.activeChannel1 = HAL_TIM_ACTIVE_CHANNEL_2;
	      break;
	    }

	    case TIM_CHANNEL_4:
	    {
		  lidar1D.activeChannel1 = HAL_TIM_ACTIVE_CHANNEL_2;
	      break;
	    }
	    default:
	      break;
	  }

	  switch (indirectChannel)
	  {
	    case TIM_CHANNEL_1:
	    {
		  lidar1D.activeChannel2 = HAL_TIM_ACTIVE_CHANNEL_1;
	      break;
	    }

	    case TIM_CHANNEL_2:
	    {
		  lidar1D.activeChannel2 = HAL_TIM_ACTIVE_CHANNEL_2;
	      break;
	    }

	    case TIM_CHANNEL_3:
	    {
		  lidar1D.activeChannel2 = HAL_TIM_ACTIVE_CHANNEL_2;
	      break;
	    }

	    case TIM_CHANNEL_4:
	    {
		  lidar1D.activeChannel2 = HAL_TIM_ACTIVE_CHANNEL_2;
	      break;
	    }
	    default:
	      break;
	  }
}

HAL_StatusTypeDef Lidar1D_run(){
	if(HAL_TIM_IC_Start_IT(lidar1D.htim, lidar1D.directChannel) != HAL_OK) Error_Handler();
	if(HAL_TIM_IC_Start_IT(lidar1D.htim, lidar1D.indirectChannel) != HAL_OK) Error_Handler();
	return HAL_OK;
}


uint8_t Lidar1D_CaptureCallback(TIM_HandleTypeDef *htim){
	if(htim->Instance != lidar1D.htim->Instance) return 0;	/* success */

	if(htim->Channel == lidar1D.activeChannel1){
//		IC1Value = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
		lidar1D.htim->Instance->CNT = 0;
	}
	if(htim->Channel == lidar1D.activeChannel2){
		lidar1D.distance_mm = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2);
	}
	return 1;
}
