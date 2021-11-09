################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Source/rtx_delay.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Source/rtx_evflags.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Source/rtx_evr.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Source/rtx_kernel.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Source/rtx_lib.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Source/rtx_memory.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Source/rtx_mempool.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Source/rtx_msgqueue.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Source/rtx_mutex.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Source/rtx_semaphore.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Source/rtx_system.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Source/rtx_thread.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Source/rtx_timer.c 

OBJS += \
./Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Source/rtx_delay.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Source/rtx_evflags.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Source/rtx_evr.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Source/rtx_kernel.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Source/rtx_lib.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Source/rtx_memory.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Source/rtx_mempool.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Source/rtx_msgqueue.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Source/rtx_mutex.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Source/rtx_semaphore.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Source/rtx_system.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Source/rtx_thread.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Source/rtx_timer.o 

C_DEPS += \
./Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Source/rtx_delay.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Source/rtx_evflags.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Source/rtx_evr.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Source/rtx_kernel.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Source/rtx_lib.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Source/rtx_memory.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Source/rtx_mempool.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Source/rtx_msgqueue.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Source/rtx_mutex.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Source/rtx_semaphore.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Source/rtx_system.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Source/rtx_thread.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Source/rtx_timer.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Source/%.o: ../Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Source/%.c Drivers/CMSIS_5-5.8.0/CMSIS/RTOS2/RTX/Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -DARM_MATH_CM4 -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

