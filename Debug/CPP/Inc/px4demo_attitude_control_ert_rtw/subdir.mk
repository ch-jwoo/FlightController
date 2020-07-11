################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CPP/Inc/px4demo_attitude_control_ert_rtw/px4demo_attitude_control.c \
../CPP/Inc/px4demo_attitude_control_ert_rtw/px4demo_attitude_control_data.c 

OBJS += \
./CPP/Inc/px4demo_attitude_control_ert_rtw/px4demo_attitude_control.o \
./CPP/Inc/px4demo_attitude_control_ert_rtw/px4demo_attitude_control_data.o 

C_DEPS += \
./CPP/Inc/px4demo_attitude_control_ert_rtw/px4demo_attitude_control.d \
./CPP/Inc/px4demo_attitude_control_ert_rtw/px4demo_attitude_control_data.d 


# Each subdirectory must supply rules for building sources it contributes
CPP/Inc/px4demo_attitude_control_ert_rtw/px4demo_attitude_control.o: ../CPP/Inc/px4demo_attitude_control_ert_rtw/px4demo_attitude_control.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F429xx -c -I../Drivers/CMSIS/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Core/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"CPP/Inc/px4demo_attitude_control_ert_rtw/px4demo_attitude_control.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
CPP/Inc/px4demo_attitude_control_ert_rtw/px4demo_attitude_control_data.o: ../CPP/Inc/px4demo_attitude_control_ert_rtw/px4demo_attitude_control_data.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F429xx -c -I../Drivers/CMSIS/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Core/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"CPP/Inc/px4demo_attitude_control_ert_rtw/px4demo_attitude_control_data.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

