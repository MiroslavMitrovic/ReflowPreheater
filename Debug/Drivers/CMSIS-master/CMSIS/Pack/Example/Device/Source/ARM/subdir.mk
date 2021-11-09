################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Drivers/CMSIS-master/CMSIS/Pack/Example/Device/Source/ARM/startup_LPC18xx.s 

OBJS += \
./Drivers/CMSIS-master/CMSIS/Pack/Example/Device/Source/ARM/startup_LPC18xx.o 

S_DEPS += \
./Drivers/CMSIS-master/CMSIS/Pack/Example/Device/Source/ARM/startup_LPC18xx.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS-master/CMSIS/Pack/Example/Device/Source/ARM/%.o: ../Drivers/CMSIS-master/CMSIS/Pack/Example/Device/Source/ARM/%.s Drivers/CMSIS-master/CMSIS/Pack/Example/Device/Source/ARM/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DDEBUG -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

