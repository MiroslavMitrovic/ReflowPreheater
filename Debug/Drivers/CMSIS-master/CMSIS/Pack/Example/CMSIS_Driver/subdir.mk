################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/CMSIS-master/CMSIS/Pack/Example/CMSIS_Driver/EMAC_LPC18xx.c \
../Drivers/CMSIS-master/CMSIS/Pack/Example/CMSIS_Driver/GPDMA_LPC18xx.c \
../Drivers/CMSIS-master/CMSIS/Pack/Example/CMSIS_Driver/GPIO_LPC18xx.c \
../Drivers/CMSIS-master/CMSIS/Pack/Example/CMSIS_Driver/I2C_LPC18xx.c \
../Drivers/CMSIS-master/CMSIS/Pack/Example/CMSIS_Driver/I2S_LPC18xx.c \
../Drivers/CMSIS-master/CMSIS/Pack/Example/CMSIS_Driver/MCI_LPC18xx.c \
../Drivers/CMSIS-master/CMSIS/Pack/Example/CMSIS_Driver/SCU_LPC18xx.c \
../Drivers/CMSIS-master/CMSIS/Pack/Example/CMSIS_Driver/SSP_LPC18xx.c \
../Drivers/CMSIS-master/CMSIS/Pack/Example/CMSIS_Driver/USART_LPC18xx.c \
../Drivers/CMSIS-master/CMSIS/Pack/Example/CMSIS_Driver/USB0_LPC18xx.c \
../Drivers/CMSIS-master/CMSIS/Pack/Example/CMSIS_Driver/USB1_LPC18xx.c \
../Drivers/CMSIS-master/CMSIS/Pack/Example/CMSIS_Driver/USBD0_LPC18xx.c \
../Drivers/CMSIS-master/CMSIS/Pack/Example/CMSIS_Driver/USBD1_LPC18xx.c \
../Drivers/CMSIS-master/CMSIS/Pack/Example/CMSIS_Driver/USBH0_LPC18xx.c \
../Drivers/CMSIS-master/CMSIS/Pack/Example/CMSIS_Driver/USBH1_LPC18xx.c 

OBJS += \
./Drivers/CMSIS-master/CMSIS/Pack/Example/CMSIS_Driver/EMAC_LPC18xx.o \
./Drivers/CMSIS-master/CMSIS/Pack/Example/CMSIS_Driver/GPDMA_LPC18xx.o \
./Drivers/CMSIS-master/CMSIS/Pack/Example/CMSIS_Driver/GPIO_LPC18xx.o \
./Drivers/CMSIS-master/CMSIS/Pack/Example/CMSIS_Driver/I2C_LPC18xx.o \
./Drivers/CMSIS-master/CMSIS/Pack/Example/CMSIS_Driver/I2S_LPC18xx.o \
./Drivers/CMSIS-master/CMSIS/Pack/Example/CMSIS_Driver/MCI_LPC18xx.o \
./Drivers/CMSIS-master/CMSIS/Pack/Example/CMSIS_Driver/SCU_LPC18xx.o \
./Drivers/CMSIS-master/CMSIS/Pack/Example/CMSIS_Driver/SSP_LPC18xx.o \
./Drivers/CMSIS-master/CMSIS/Pack/Example/CMSIS_Driver/USART_LPC18xx.o \
./Drivers/CMSIS-master/CMSIS/Pack/Example/CMSIS_Driver/USB0_LPC18xx.o \
./Drivers/CMSIS-master/CMSIS/Pack/Example/CMSIS_Driver/USB1_LPC18xx.o \
./Drivers/CMSIS-master/CMSIS/Pack/Example/CMSIS_Driver/USBD0_LPC18xx.o \
./Drivers/CMSIS-master/CMSIS/Pack/Example/CMSIS_Driver/USBD1_LPC18xx.o \
./Drivers/CMSIS-master/CMSIS/Pack/Example/CMSIS_Driver/USBH0_LPC18xx.o \
./Drivers/CMSIS-master/CMSIS/Pack/Example/CMSIS_Driver/USBH1_LPC18xx.o 

C_DEPS += \
./Drivers/CMSIS-master/CMSIS/Pack/Example/CMSIS_Driver/EMAC_LPC18xx.d \
./Drivers/CMSIS-master/CMSIS/Pack/Example/CMSIS_Driver/GPDMA_LPC18xx.d \
./Drivers/CMSIS-master/CMSIS/Pack/Example/CMSIS_Driver/GPIO_LPC18xx.d \
./Drivers/CMSIS-master/CMSIS/Pack/Example/CMSIS_Driver/I2C_LPC18xx.d \
./Drivers/CMSIS-master/CMSIS/Pack/Example/CMSIS_Driver/I2S_LPC18xx.d \
./Drivers/CMSIS-master/CMSIS/Pack/Example/CMSIS_Driver/MCI_LPC18xx.d \
./Drivers/CMSIS-master/CMSIS/Pack/Example/CMSIS_Driver/SCU_LPC18xx.d \
./Drivers/CMSIS-master/CMSIS/Pack/Example/CMSIS_Driver/SSP_LPC18xx.d \
./Drivers/CMSIS-master/CMSIS/Pack/Example/CMSIS_Driver/USART_LPC18xx.d \
./Drivers/CMSIS-master/CMSIS/Pack/Example/CMSIS_Driver/USB0_LPC18xx.d \
./Drivers/CMSIS-master/CMSIS/Pack/Example/CMSIS_Driver/USB1_LPC18xx.d \
./Drivers/CMSIS-master/CMSIS/Pack/Example/CMSIS_Driver/USBD0_LPC18xx.d \
./Drivers/CMSIS-master/CMSIS/Pack/Example/CMSIS_Driver/USBD1_LPC18xx.d \
./Drivers/CMSIS-master/CMSIS/Pack/Example/CMSIS_Driver/USBH0_LPC18xx.d \
./Drivers/CMSIS-master/CMSIS/Pack/Example/CMSIS_Driver/USBH1_LPC18xx.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS-master/CMSIS/Pack/Example/CMSIS_Driver/%.o: ../Drivers/CMSIS-master/CMSIS/Pack/Example/CMSIS_Driver/%.c Drivers/CMSIS-master/CMSIS/Pack/Example/CMSIS_Driver/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -DARM_MATH_CM4 -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

