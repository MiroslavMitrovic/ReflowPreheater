################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Drivers/CMSIS-master/Device/ARM/ARMCM0plus/Source/ARM/startup_ARMCM0plus.s 

OBJS += \
./Drivers/CMSIS-master/Device/ARM/ARMCM0plus/Source/ARM/startup_ARMCM0plus.o 

S_DEPS += \
./Drivers/CMSIS-master/Device/ARM/ARMCM0plus/Source/ARM/startup_ARMCM0plus.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS-master/Device/ARM/ARMCM0plus/Source/ARM/%.o: ../Drivers/CMSIS-master/Device/ARM/ARMCM0plus/Source/ARM/%.s Drivers/CMSIS-master/Device/ARM/ARMCM0plus/Source/ARM/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DDEBUG -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

