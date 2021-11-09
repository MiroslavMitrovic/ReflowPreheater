################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_UPPER_SRCS += \
../Drivers/CMSIS_5-5.8.0/CMSIS/RTOS/RTX/SRC/GCC/HAL_CM0.S \
../Drivers/CMSIS_5-5.8.0/CMSIS/RTOS/RTX/SRC/GCC/HAL_CM3.S \
../Drivers/CMSIS_5-5.8.0/CMSIS/RTOS/RTX/SRC/GCC/HAL_CM4.S \
../Drivers/CMSIS_5-5.8.0/CMSIS/RTOS/RTX/SRC/GCC/SVC_Table.S 

OBJS += \
./Drivers/CMSIS_5-5.8.0/CMSIS/RTOS/RTX/SRC/GCC/HAL_CM0.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/RTOS/RTX/SRC/GCC/HAL_CM3.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/RTOS/RTX/SRC/GCC/HAL_CM4.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/RTOS/RTX/SRC/GCC/SVC_Table.o 

S_UPPER_DEPS += \
./Drivers/CMSIS_5-5.8.0/CMSIS/RTOS/RTX/SRC/GCC/HAL_CM0.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/RTOS/RTX/SRC/GCC/HAL_CM3.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/RTOS/RTX/SRC/GCC/HAL_CM4.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/RTOS/RTX/SRC/GCC/SVC_Table.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS_5-5.8.0/CMSIS/RTOS/RTX/SRC/GCC/%.o: ../Drivers/CMSIS_5-5.8.0/CMSIS/RTOS/RTX/SRC/GCC/%.S Drivers/CMSIS_5-5.8.0/CMSIS/RTOS/RTX/SRC/GCC/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DDEBUG -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

