################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Drivers/CMSIS_5-5.8.0/CMSIS/RTOS/Template/startup_LPC177x_8x.s 

C_SRCS += \
../Drivers/CMSIS_5-5.8.0/CMSIS/RTOS/Template/os_sample.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/RTOS/Template/os_sample1.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/RTOS/Template/system_LPC177x_8x.c 

OBJS += \
./Drivers/CMSIS_5-5.8.0/CMSIS/RTOS/Template/os_sample.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/RTOS/Template/os_sample1.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/RTOS/Template/startup_LPC177x_8x.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/RTOS/Template/system_LPC177x_8x.o 

S_DEPS += \
./Drivers/CMSIS_5-5.8.0/CMSIS/RTOS/Template/startup_LPC177x_8x.d 

C_DEPS += \
./Drivers/CMSIS_5-5.8.0/CMSIS/RTOS/Template/os_sample.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/RTOS/Template/os_sample1.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/RTOS/Template/system_LPC177x_8x.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS_5-5.8.0/CMSIS/RTOS/Template/%.o: ../Drivers/CMSIS_5-5.8.0/CMSIS/RTOS/Template/%.c Drivers/CMSIS_5-5.8.0/CMSIS/RTOS/Template/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -DARM_MATH_CM4 -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/CMSIS_5-5.8.0/CMSIS/RTOS/Template/%.o: ../Drivers/CMSIS_5-5.8.0/CMSIS/RTOS/Template/%.s Drivers/CMSIS_5-5.8.0/CMSIS/RTOS/Template/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DDEBUG -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

