################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CPP/Lib/MatlabAttitudeController/Second_att_control_codeblock_fly.c \
../CPP/Lib/MatlabAttitudeController/Second_att_control_codeblock_fly_data.c 

C_DEPS += \
./CPP/Lib/MatlabAttitudeController/Second_att_control_codeblock_fly.d \
./CPP/Lib/MatlabAttitudeController/Second_att_control_codeblock_fly_data.d 

OBJS += \
./CPP/Lib/MatlabAttitudeController/Second_att_control_codeblock_fly.o \
./CPP/Lib/MatlabAttitudeController/Second_att_control_codeblock_fly_data.o 


# Each subdirectory must supply rules for building sources it contributes
CPP/Lib/MatlabAttitudeController/Second_att_control_codeblock_fly.o: ../CPP/Lib/MatlabAttitudeController/Second_att_control_codeblock_fly.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F429xx -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../FATFS/App -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"C:/STM/CPPTEST/Fcboot" -I../Drivers/CMSIS/Include -I../Core/Inc -I../FATFS/Target -I../Middlewares/Third_Party/FatFs/src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"CPP/Lib/MatlabAttitudeController/Second_att_control_codeblock_fly.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
CPP/Lib/MatlabAttitudeController/Second_att_control_codeblock_fly_data.o: ../CPP/Lib/MatlabAttitudeController/Second_att_control_codeblock_fly_data.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F429xx -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../FATFS/App -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"C:/STM/CPPTEST/Fcboot" -I../Drivers/CMSIS/Include -I../Core/Inc -I../FATFS/Target -I../Middlewares/Third_Party/FatFs/src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"CPP/Lib/MatlabAttitudeController/Second_att_control_codeblock_fly_data.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

