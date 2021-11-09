################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Drivers/CMSIS-master/Device/ARM/ARMSC300/Source/IAR/startup_ARMSC300.s 

OBJS += \
./Drivers/CMSIS-master/Device/ARM/ARMSC300/Source/IAR/startup_ARMSC300.o 

S_DEPS += \
./Drivers/CMSIS-master/Device/ARM/ARMSC300/Source/IAR/startup_ARMSC300.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS-master/Device/ARM/ARMSC300/Source/IAR/%.o: ../Drivers/CMSIS-master/Device/ARM/ARMSC300/Source/IAR/%.s Drivers/CMSIS-master/Device/ARM/ARMSC300/Source/IAR/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DDEBUG -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

