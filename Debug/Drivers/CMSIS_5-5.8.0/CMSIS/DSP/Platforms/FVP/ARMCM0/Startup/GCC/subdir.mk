################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Platforms/FVP/ARMCM0/Startup/GCC/startup_ARMCM0.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Platforms/FVP/ARMCM0/Startup/GCC/support.c 

S_UPPER_SRCS += \
../Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Platforms/FVP/ARMCM0/Startup/GCC/startup_ARMCM0.S 

OBJS += \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Platforms/FVP/ARMCM0/Startup/GCC/startup_ARMCM0.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Platforms/FVP/ARMCM0/Startup/GCC/support.o 

S_UPPER_DEPS += \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Platforms/FVP/ARMCM0/Startup/GCC/startup_ARMCM0.d 

C_DEPS += \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Platforms/FVP/ARMCM0/Startup/GCC/startup_ARMCM0.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Platforms/FVP/ARMCM0/Startup/GCC/support.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Platforms/FVP/ARMCM0/Startup/GCC/%.o: ../Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Platforms/FVP/ARMCM0/Startup/GCC/%.S Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Platforms/FVP/ARMCM0/Startup/GCC/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DDEBUG -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"
Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Platforms/FVP/ARMCM0/Startup/GCC/%.o: ../Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Platforms/FVP/ARMCM0/Startup/GCC/%.c Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Platforms/FVP/ARMCM0/Startup/GCC/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -DARM_MATH_CM4 -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

