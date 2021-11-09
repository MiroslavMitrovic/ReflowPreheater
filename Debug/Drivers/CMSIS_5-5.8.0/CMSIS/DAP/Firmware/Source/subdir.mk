################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/CMSIS_5-5.8.0/CMSIS/DAP/Firmware/Source/DAP.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/DAP/Firmware/Source/DAP_vendor.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/DAP/Firmware/Source/JTAG_DP.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/DAP/Firmware/Source/SWO.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/DAP/Firmware/Source/SW_DP.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/DAP/Firmware/Source/UART.c 

OBJS += \
./Drivers/CMSIS_5-5.8.0/CMSIS/DAP/Firmware/Source/DAP.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/DAP/Firmware/Source/DAP_vendor.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/DAP/Firmware/Source/JTAG_DP.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/DAP/Firmware/Source/SWO.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/DAP/Firmware/Source/SW_DP.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/DAP/Firmware/Source/UART.o 

C_DEPS += \
./Drivers/CMSIS_5-5.8.0/CMSIS/DAP/Firmware/Source/DAP.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/DAP/Firmware/Source/DAP_vendor.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/DAP/Firmware/Source/JTAG_DP.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/DAP/Firmware/Source/SWO.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/DAP/Firmware/Source/SW_DP.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/DAP/Firmware/Source/UART.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS_5-5.8.0/CMSIS/DAP/Firmware/Source/%.o: ../Drivers/CMSIS_5-5.8.0/CMSIS/DAP/Firmware/Source/%.c Drivers/CMSIS_5-5.8.0/CMSIS/DAP/Firmware/Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -DARM_MATH_CM4 -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

