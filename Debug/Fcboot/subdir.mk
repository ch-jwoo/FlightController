################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Fcboot/MPU9250.c \
../Fcboot/State.c \
../Fcboot/estimate.c \
../Fcboot/userMain.c 

OBJS += \
./Fcboot/MPU9250.o \
./Fcboot/State.o \
./Fcboot/estimate.o \
./Fcboot/userMain.o 

C_DEPS += \
./Fcboot/MPU9250.d \
./Fcboot/State.d \
./Fcboot/estimate.d \
./Fcboot/userMain.d 


# Each subdirectory must supply rules for building sources it contributes
Fcboot/MPU9250.o: ../Fcboot/MPU9250.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F429xx -c -I"D:/OneDrive - inha.edu/2020_Robot_Aircraft/CPPTEST/C" -I"D:/OneDrive - inha.edu/2020_Robot_Aircraft/CPPTEST/Fcboot" -I../Drivers/CMSIS/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Core/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I"D:/OneDrive - inha.edu/2020_Robot_Aircraft/RobotAircraft/Second_attitude_control_worked/Second_att_control_codeblock_ert_rtw" -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Fcboot/MPU9250.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Fcboot/State.o: ../Fcboot/State.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F429xx -c -I"D:/OneDrive - inha.edu/2020_Robot_Aircraft/CPPTEST/C" -I"D:/OneDrive - inha.edu/2020_Robot_Aircraft/CPPTEST/Fcboot" -I../Drivers/CMSIS/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Core/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I"D:/OneDrive - inha.edu/2020_Robot_Aircraft/RobotAircraft/Second_attitude_control_worked/Second_att_control_codeblock_ert_rtw" -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Fcboot/State.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Fcboot/estimate.o: ../Fcboot/estimate.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F429xx -c -I"D:/OneDrive - inha.edu/2020_Robot_Aircraft/CPPTEST/C" -I"D:/OneDrive - inha.edu/2020_Robot_Aircraft/CPPTEST/Fcboot" -I../Drivers/CMSIS/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Core/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I"D:/OneDrive - inha.edu/2020_Robot_Aircraft/RobotAircraft/Second_attitude_control_worked/Second_att_control_codeblock_ert_rtw" -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Fcboot/estimate.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Fcboot/userMain.o: ../Fcboot/userMain.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F429xx -c -I"D:/OneDrive - inha.edu/2020_Robot_Aircraft/CPPTEST/C" -I"D:/OneDrive - inha.edu/2020_Robot_Aircraft/CPPTEST/Fcboot" -I../Drivers/CMSIS/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Core/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I"D:/OneDrive - inha.edu/2020_Robot_Aircraft/RobotAircraft/Second_attitude_control_worked/Second_att_control_codeblock_ert_rtw" -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Fcboot/userMain.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

