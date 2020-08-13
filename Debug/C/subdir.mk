################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../C/algorithmCollection.c 

OBJS += \
./C/algorithmCollection.o 

C_DEPS += \
./C/algorithmCollection.d 


# Each subdirectory must supply rules for building sources it contributes
C/algorithmCollection.o: ../C/algorithmCollection.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F429xx -c -I"D:/OneDrive - inha.edu/2020_Robot_Aircraft/CPPTEST/C" -I"D:/OneDrive - inha.edu/2020_Robot_Aircraft/CPPTEST/Fcboot" -I../Drivers/CMSIS/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Core/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I"D:/OneDrive - inha.edu/2020_Robot_Aircraft/RobotAircraft/Second_attitude_control_worked/Second_att_control_codeblock_ert_rtw" -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"C/algorithmCollection.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

