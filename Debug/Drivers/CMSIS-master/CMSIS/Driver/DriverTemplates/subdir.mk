################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/CMSIS-master/CMSIS/Driver/DriverTemplates/Driver_CAN.c \
../Drivers/CMSIS-master/CMSIS/Driver/DriverTemplates/Driver_ETH_MAC.c \
../Drivers/CMSIS-master/CMSIS/Driver/DriverTemplates/Driver_ETH_PHY.c \
../Drivers/CMSIS-master/CMSIS/Driver/DriverTemplates/Driver_Flash.c \
../Drivers/CMSIS-master/CMSIS/Driver/DriverTemplates/Driver_I2C.c \
../Drivers/CMSIS-master/CMSIS/Driver/DriverTemplates/Driver_MCI.c \
../Drivers/CMSIS-master/CMSIS/Driver/DriverTemplates/Driver_SAI.c \
../Drivers/CMSIS-master/CMSIS/Driver/DriverTemplates/Driver_SPI.c \
../Drivers/CMSIS-master/CMSIS/Driver/DriverTemplates/Driver_USART.c \
../Drivers/CMSIS-master/CMSIS/Driver/DriverTemplates/Driver_USBD.c \
../Drivers/CMSIS-master/CMSIS/Driver/DriverTemplates/Driver_USBH.c 

OBJS += \
./Drivers/CMSIS-master/CMSIS/Driver/DriverTemplates/Driver_CAN.o \
./Drivers/CMSIS-master/CMSIS/Driver/DriverTemplates/Driver_ETH_MAC.o \
./Drivers/CMSIS-master/CMSIS/Driver/DriverTemplates/Driver_ETH_PHY.o \
./Drivers/CMSIS-master/CMSIS/Driver/DriverTemplates/Driver_Flash.o \
./Drivers/CMSIS-master/CMSIS/Driver/DriverTemplates/Driver_I2C.o \
./Drivers/CMSIS-master/CMSIS/Driver/DriverTemplates/Driver_MCI.o \
./Drivers/CMSIS-master/CMSIS/Driver/DriverTemplates/Driver_SAI.o \
./Drivers/CMSIS-master/CMSIS/Driver/DriverTemplates/Driver_SPI.o \
./Drivers/CMSIS-master/CMSIS/Driver/DriverTemplates/Driver_USART.o \
./Drivers/CMSIS-master/CMSIS/Driver/DriverTemplates/Driver_USBD.o \
./Drivers/CMSIS-master/CMSIS/Driver/DriverTemplates/Driver_USBH.o 

C_DEPS += \
./Drivers/CMSIS-master/CMSIS/Driver/DriverTemplates/Driver_CAN.d \
./Drivers/CMSIS-master/CMSIS/Driver/DriverTemplates/Driver_ETH_MAC.d \
./Drivers/CMSIS-master/CMSIS/Driver/DriverTemplates/Driver_ETH_PHY.d \
./Drivers/CMSIS-master/CMSIS/Driver/DriverTemplates/Driver_Flash.d \
./Drivers/CMSIS-master/CMSIS/Driver/DriverTemplates/Driver_I2C.d \
./Drivers/CMSIS-master/CMSIS/Driver/DriverTemplates/Driver_MCI.d \
./Drivers/CMSIS-master/CMSIS/Driver/DriverTemplates/Driver_SAI.d \
./Drivers/CMSIS-master/CMSIS/Driver/DriverTemplates/Driver_SPI.d \
./Drivers/CMSIS-master/CMSIS/Driver/DriverTemplates/Driver_USART.d \
./Drivers/CMSIS-master/CMSIS/Driver/DriverTemplates/Driver_USBD.d \
./Drivers/CMSIS-master/CMSIS/Driver/DriverTemplates/Driver_USBH.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS-master/CMSIS/Driver/DriverTemplates/%.o: ../Drivers/CMSIS-master/CMSIS/Driver/DriverTemplates/%.c Drivers/CMSIS-master/CMSIS/Driver/DriverTemplates/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -DARM_MATH_CM4 -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

