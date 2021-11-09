################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Drivers/CMSIS-master/CMSIS/RTOS/RTX/SRC/IAR/HAL_CM0.s \
../Drivers/CMSIS-master/CMSIS/RTOS/RTX/SRC/IAR/HAL_CM3.s \
../Drivers/CMSIS-master/CMSIS/RTOS/RTX/SRC/IAR/HAL_CM4.s \
../Drivers/CMSIS-master/CMSIS/RTOS/RTX/SRC/IAR/SVC_Table.s 

OBJS += \
./Drivers/CMSIS-master/CMSIS/RTOS/RTX/SRC/IAR/HAL_CM0.o \
./Drivers/CMSIS-master/CMSIS/RTOS/RTX/SRC/IAR/HAL_CM3.o \
./Drivers/CMSIS-master/CMSIS/RTOS/RTX/SRC/IAR/HAL_CM4.o \
./Drivers/CMSIS-master/CMSIS/RTOS/RTX/SRC/IAR/SVC_Table.o 

S_DEPS += \
./Drivers/CMSIS-master/CMSIS/RTOS/RTX/SRC/IAR/HAL_CM0.d \
./Drivers/CMSIS-master/CMSIS/RTOS/RTX/SRC/IAR/HAL_CM3.d \
./Drivers/CMSIS-master/CMSIS/RTOS/RTX/SRC/IAR/HAL_CM4.d \
./Drivers/CMSIS-master/CMSIS/RTOS/RTX/SRC/IAR/SVC_Table.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS-master/CMSIS/RTOS/RTX/SRC/IAR/%.o: ../Drivers/CMSIS-master/CMSIS/RTOS/RTX/SRC/IAR/%.s Drivers/CMSIS-master/CMSIS/RTOS/RTX/SRC/IAR/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DDEBUG -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

