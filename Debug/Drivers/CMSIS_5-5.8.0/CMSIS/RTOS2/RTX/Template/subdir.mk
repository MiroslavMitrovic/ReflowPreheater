################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Template/Events.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Template/MemPool.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Template/MsgQueue.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Template/Mutex.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Template/Semaphore.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Template/Thread.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Template/Timer.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Template/main.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Template/svc_user.c 

OBJS += \
./Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Template/Events.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Template/MemPool.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Template/MsgQueue.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Template/Mutex.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Template/Semaphore.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Template/Thread.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Template/Timer.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Template/main.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Template/svc_user.o 

C_DEPS += \
./Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Template/Events.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Template/MemPool.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Template/MsgQueue.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Template/Mutex.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Template/Semaphore.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Template/Thread.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Template/Timer.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Template/main.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Template/svc_user.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Template/%.o: ../Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Template/%.c Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Template/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -DARM_MATH_CM4 -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

