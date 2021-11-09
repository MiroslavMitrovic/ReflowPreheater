################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Drivers/CMSIS-master/Device/_Template_Vendor/Vendor/Device/Source/IAR/startup_Device.s 

OBJS += \
./Drivers/CMSIS-master/Device/_Template_Vendor/Vendor/Device/Source/IAR/startup_Device.o 

S_DEPS += \
./Drivers/CMSIS-master/Device/_Template_Vendor/Vendor/Device/Source/IAR/startup_Device.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS-master/Device/_Template_Vendor/Vendor/Device/Source/IAR/%.o: ../Drivers/CMSIS-master/Device/_Template_Vendor/Vendor/Device/Source/IAR/%.s Drivers/CMSIS-master/Device/_Template_Vendor/Vendor/Device/Source/IAR/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DDEBUG -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

