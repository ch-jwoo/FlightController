################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CPP/Lib/MatlabAttitudeController/Second_att_control_codeblock_fly.cpp \
../CPP/Lib/MatlabAttitudeController/Second_att_control_codeblock_fly_data.cpp 

OBJS += \
./CPP/Lib/MatlabAttitudeController/Second_att_control_codeblock_fly.o \
./CPP/Lib/MatlabAttitudeController/Second_att_control_codeblock_fly_data.o 

CPP_DEPS += \
./CPP/Lib/MatlabAttitudeController/Second_att_control_codeblock_fly.d \
./CPP/Lib/MatlabAttitudeController/Second_att_control_codeblock_fly_data.d 


# Each subdirectory must supply rules for building sources it contributes
CPP/Lib/MatlabAttitudeController/Second_att_control_codeblock_fly.o: ../CPP/Lib/MatlabAttitudeController/Second_att_control_codeblock_fly.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -DSTM32H743xx -DDEBUG -c -I../FATFS/Target -I../FATFS/App -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FatFs/src -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"C:/git/pwmTest/CPP" -I"C:/git/pwmTest/CPP/Lib" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-threadsafe-statics -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"CPP/Lib/MatlabAttitudeController/Second_att_control_codeblock_fly.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
CPP/Lib/MatlabAttitudeController/Second_att_control_codeblock_fly_data.o: ../CPP/Lib/MatlabAttitudeController/Second_att_control_codeblock_fly_data.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -DSTM32H743xx -DDEBUG -c -I../FATFS/Target -I../FATFS/App -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FatFs/src -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"C:/git/pwmTest/CPP" -I"C:/git/pwmTest/CPP/Lib" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-threadsafe-statics -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"CPP/Lib/MatlabAttitudeController/Second_att_control_codeblock_fly_data.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

