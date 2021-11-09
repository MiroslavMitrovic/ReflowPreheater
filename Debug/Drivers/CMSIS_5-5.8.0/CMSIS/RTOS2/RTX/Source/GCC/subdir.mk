################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_UPPER_SRCS += \
../Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Source/GCC/irq_armv6m.S \
../Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Source/GCC/irq_armv7a.S \
../Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Source/GCC/irq_armv7m.S \
../Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Source/GCC/irq_armv8mbl.S \
../Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Source/GCC/irq_armv8mml.S 

OBJS += \
./Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Source/GCC/irq_armv6m.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Source/GCC/irq_armv7a.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Source/GCC/irq_armv7m.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Source/GCC/irq_armv8mbl.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Source/GCC/irq_armv8mml.o 

S_UPPER_DEPS += \
./Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Source/GCC/irq_armv6m.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Source/GCC/irq_armv7a.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Source/GCC/irq_armv7m.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Source/GCC/irq_armv8mbl.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Source/GCC/irq_armv8mml.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Source/GCC/%.o: ../Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Source/GCC/%.S Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Source/GCC/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DDEBUG -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

