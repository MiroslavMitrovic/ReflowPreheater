################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Examples/MemPool/RTE/Device/ARMCM3/startup_ARMCM3.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Examples/MemPool/RTE/Device/ARMCM3/system_ARMCM3.c 

OBJS += \
./Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Examples/MemPool/RTE/Device/ARMCM3/startup_ARMCM3.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Examples/MemPool/RTE/Device/ARMCM3/system_ARMCM3.o 

C_DEPS += \
./Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Examples/MemPool/RTE/Device/ARMCM3/startup_ARMCM3.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Examples/MemPool/RTE/Device/ARMCM3/system_ARMCM3.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Examples/MemPool/RTE/Device/ARMCM3/%.o: ../Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Examples/MemPool/RTE/Device/ARMCM3/%.c Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Examples/MemPool/RTE/Device/ARMCM3/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -DARM_MATH_CM4 -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

