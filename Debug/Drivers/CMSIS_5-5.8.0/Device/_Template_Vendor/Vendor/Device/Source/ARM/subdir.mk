################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Drivers/CMSIS_5-5.8.0/Device/_Template_Vendor/Vendor/Device/Source/ARM/startup_Device_ac5.s \
../Drivers/CMSIS_5-5.8.0/Device/_Template_Vendor/Vendor/Device/Source/ARM/startup_Device_ac5_noSct.s 

S_UPPER_SRCS += \
../Drivers/CMSIS_5-5.8.0/Device/_Template_Vendor/Vendor/Device/Source/ARM/startup_Device_ac6.S 

OBJS += \
./Drivers/CMSIS_5-5.8.0/Device/_Template_Vendor/Vendor/Device/Source/ARM/startup_Device_ac5.o \
./Drivers/CMSIS_5-5.8.0/Device/_Template_Vendor/Vendor/Device/Source/ARM/startup_Device_ac5_noSct.o \
./Drivers/CMSIS_5-5.8.0/Device/_Template_Vendor/Vendor/Device/Source/ARM/startup_Device_ac6.o 

S_DEPS += \
./Drivers/CMSIS_5-5.8.0/Device/_Template_Vendor/Vendor/Device/Source/ARM/startup_Device_ac5.d \
./Drivers/CMSIS_5-5.8.0/Device/_Template_Vendor/Vendor/Device/Source/ARM/startup_Device_ac5_noSct.d 

S_UPPER_DEPS += \
./Drivers/CMSIS_5-5.8.0/Device/_Template_Vendor/Vendor/Device/Source/ARM/startup_Device_ac6.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS_5-5.8.0/Device/_Template_Vendor/Vendor/Device/Source/ARM/%.o: ../Drivers/CMSIS_5-5.8.0/Device/_Template_Vendor/Vendor/Device/Source/ARM/%.s Drivers/CMSIS_5-5.8.0/Device/_Template_Vendor/Vendor/Device/Source/ARM/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DDEBUG -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"
Drivers/CMSIS_5-5.8.0/Device/_Template_Vendor/Vendor/Device/Source/ARM/%.o: ../Drivers/CMSIS_5-5.8.0/Device/_Template_Vendor/Vendor/Device/Source/ARM/%.S Drivers/CMSIS_5-5.8.0/Device/_Template_Vendor/Vendor/Device/Source/ARM/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DDEBUG -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

