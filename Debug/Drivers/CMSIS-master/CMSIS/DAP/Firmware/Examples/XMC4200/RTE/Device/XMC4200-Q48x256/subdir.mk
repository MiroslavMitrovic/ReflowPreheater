################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Drivers/CMSIS-master/CMSIS/DAP/Firmware/Examples/XMC4200/RTE/Device/XMC4200-Q48x256/startup_XMC4200.s 

C_SRCS += \
../Drivers/CMSIS-master/CMSIS/DAP/Firmware/Examples/XMC4200/RTE/Device/XMC4200-Q48x256/system_XMC4200.c 

OBJS += \
./Drivers/CMSIS-master/CMSIS/DAP/Firmware/Examples/XMC4200/RTE/Device/XMC4200-Q48x256/startup_XMC4200.o \
./Drivers/CMSIS-master/CMSIS/DAP/Firmware/Examples/XMC4200/RTE/Device/XMC4200-Q48x256/system_XMC4200.o 

S_DEPS += \
./Drivers/CMSIS-master/CMSIS/DAP/Firmware/Examples/XMC4200/RTE/Device/XMC4200-Q48x256/startup_XMC4200.d 

C_DEPS += \
./Drivers/CMSIS-master/CMSIS/DAP/Firmware/Examples/XMC4200/RTE/Device/XMC4200-Q48x256/system_XMC4200.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS-master/CMSIS/DAP/Firmware/Examples/XMC4200/RTE/Device/XMC4200-Q48x256/%.o: ../Drivers/CMSIS-master/CMSIS/DAP/Firmware/Examples/XMC4200/RTE/Device/XMC4200-Q48x256/%.s Drivers/CMSIS-master/CMSIS/DAP/Firmware/Examples/XMC4200/RTE/Device/XMC4200-Q48x256/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DDEBUG -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"
Drivers/CMSIS-master/CMSIS/DAP/Firmware/Examples/XMC4200/RTE/Device/XMC4200-Q48x256/%.o: ../Drivers/CMSIS-master/CMSIS/DAP/Firmware/Examples/XMC4200/RTE/Device/XMC4200-Q48x256/%.c Drivers/CMSIS-master/CMSIS/DAP/Firmware/Examples/XMC4200/RTE/Device/XMC4200-Q48x256/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -DARM_MATH_CM4 -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

