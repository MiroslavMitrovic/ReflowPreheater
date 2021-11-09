################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Drivers/CMSIS_5-5.8.0/Device/ARM/ARMCM3/Source/IAR/startup_ARMCM3.s 

OBJS += \
./Drivers/CMSIS_5-5.8.0/Device/ARM/ARMCM3/Source/IAR/startup_ARMCM3.o 

S_DEPS += \
./Drivers/CMSIS_5-5.8.0/Device/ARM/ARMCM3/Source/IAR/startup_ARMCM3.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS_5-5.8.0/Device/ARM/ARMCM3/Source/IAR/%.o: ../Drivers/CMSIS_5-5.8.0/Device/ARM/ARMCM3/Source/IAR/%.s Drivers/CMSIS_5-5.8.0/Device/ARM/ARMCM3/Source/IAR/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DDEBUG -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

