################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/CMSIS_5-5.8.0/CMSIS/Driver/DriverTemplates/Driver_CAN.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/Driver/DriverTemplates/Driver_ETH_MAC.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/Driver/DriverTemplates/Driver_ETH_PHY.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/Driver/DriverTemplates/Driver_Flash.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/Driver/DriverTemplates/Driver_I2C.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/Driver/DriverTemplates/Driver_MCI.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/Driver/DriverTemplates/Driver_NAND.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/Driver/DriverTemplates/Driver_SAI.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/Driver/DriverTemplates/Driver_SPI.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/Driver/DriverTemplates/Driver_Storage.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/Driver/DriverTemplates/Driver_USART.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/Driver/DriverTemplates/Driver_USBD.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/Driver/DriverTemplates/Driver_USBH.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/Driver/DriverTemplates/Driver_WiFi.c 

OBJS += \
./Drivers/CMSIS_5-5.8.0/CMSIS/Driver/DriverTemplates/Driver_CAN.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/Driver/DriverTemplates/Driver_ETH_MAC.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/Driver/DriverTemplates/Driver_ETH_PHY.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/Driver/DriverTemplates/Driver_Flash.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/Driver/DriverTemplates/Driver_I2C.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/Driver/DriverTemplates/Driver_MCI.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/Driver/DriverTemplates/Driver_NAND.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/Driver/DriverTemplates/Driver_SAI.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/Driver/DriverTemplates/Driver_SPI.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/Driver/DriverTemplates/Driver_Storage.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/Driver/DriverTemplates/Driver_USART.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/Driver/DriverTemplates/Driver_USBD.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/Driver/DriverTemplates/Driver_USBH.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/Driver/DriverTemplates/Driver_WiFi.o 

C_DEPS += \
./Drivers/CMSIS_5-5.8.0/CMSIS/Driver/DriverTemplates/Driver_CAN.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/Driver/DriverTemplates/Driver_ETH_MAC.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/Driver/DriverTemplates/Driver_ETH_PHY.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/Driver/DriverTemplates/Driver_Flash.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/Driver/DriverTemplates/Driver_I2C.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/Driver/DriverTemplates/Driver_MCI.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/Driver/DriverTemplates/Driver_NAND.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/Driver/DriverTemplates/Driver_SAI.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/Driver/DriverTemplates/Driver_SPI.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/Driver/DriverTemplates/Driver_Storage.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/Driver/DriverTemplates/Driver_USART.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/Driver/DriverTemplates/Driver_USBD.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/Driver/DriverTemplates/Driver_USBH.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/Driver/DriverTemplates/Driver_WiFi.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS_5-5.8.0/CMSIS/Driver/DriverTemplates/%.o: ../Drivers/CMSIS_5-5.8.0/CMSIS/Driver/DriverTemplates/%.c Drivers/CMSIS_5-5.8.0/CMSIS/Driver/DriverTemplates/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -DARM_MATH_CM4 -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

