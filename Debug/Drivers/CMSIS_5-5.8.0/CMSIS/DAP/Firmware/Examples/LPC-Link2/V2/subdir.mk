################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/CMSIS_5-5.8.0/CMSIS/DAP/Firmware/Examples/LPC-Link2/V2/USBD_User_CDC_ACM_UART_0.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/DAP/Firmware/Examples/LPC-Link2/V2/USBD_User_CustomClass_0.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/DAP/Firmware/Examples/LPC-Link2/V2/main.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/DAP/Firmware/Examples/LPC-Link2/V2/ser_num.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/DAP/Firmware/Examples/LPC-Link2/V2/target.c 

OBJS += \
./Drivers/CMSIS_5-5.8.0/CMSIS/DAP/Firmware/Examples/LPC-Link2/V2/USBD_User_CDC_ACM_UART_0.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/DAP/Firmware/Examples/LPC-Link2/V2/USBD_User_CustomClass_0.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/DAP/Firmware/Examples/LPC-Link2/V2/main.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/DAP/Firmware/Examples/LPC-Link2/V2/ser_num.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/DAP/Firmware/Examples/LPC-Link2/V2/target.o 

C_DEPS += \
./Drivers/CMSIS_5-5.8.0/CMSIS/DAP/Firmware/Examples/LPC-Link2/V2/USBD_User_CDC_ACM_UART_0.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/DAP/Firmware/Examples/LPC-Link2/V2/USBD_User_CustomClass_0.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/DAP/Firmware/Examples/LPC-Link2/V2/main.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/DAP/Firmware/Examples/LPC-Link2/V2/ser_num.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/DAP/Firmware/Examples/LPC-Link2/V2/target.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS_5-5.8.0/CMSIS/DAP/Firmware/Examples/LPC-Link2/V2/%.o: ../Drivers/CMSIS_5-5.8.0/CMSIS/DAP/Firmware/Examples/LPC-Link2/V2/%.c Drivers/CMSIS_5-5.8.0/CMSIS/DAP/Firmware/Examples/LPC-Link2/V2/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -DARM_MATH_CM4 -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

