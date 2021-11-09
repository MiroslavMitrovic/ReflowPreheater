################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Platforms/MPS3/ARMCM33/Startup/AC6/startup_ARMCM33.s 

OBJS += \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Platforms/MPS3/ARMCM33/Startup/AC6/startup_ARMCM33.o 

S_DEPS += \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Platforms/MPS3/ARMCM33/Startup/AC6/startup_ARMCM33.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Platforms/MPS3/ARMCM33/Startup/AC6/%.o: ../Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Platforms/MPS3/ARMCM33/Startup/AC6/%.s Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Platforms/MPS3/ARMCM33/Startup/AC6/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DDEBUG -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

