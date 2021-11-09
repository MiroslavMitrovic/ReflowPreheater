################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Drivers/CMSIS-master/Device/_Template_Flash/Test/startup_stm32f10x_md.s 

C_SRCS += \
../Drivers/CMSIS-master/Device/_Template_Flash/Test/FlashDev.c \
../Drivers/CMSIS-master/Device/_Template_Flash/Test/FlashPrg.c \
../Drivers/CMSIS-master/Device/_Template_Flash/Test/FlashTest.c \
../Drivers/CMSIS-master/Device/_Template_Flash/Test/system_stm32f10x.c 

OBJS += \
./Drivers/CMSIS-master/Device/_Template_Flash/Test/FlashDev.o \
./Drivers/CMSIS-master/Device/_Template_Flash/Test/FlashPrg.o \
./Drivers/CMSIS-master/Device/_Template_Flash/Test/FlashTest.o \
./Drivers/CMSIS-master/Device/_Template_Flash/Test/startup_stm32f10x_md.o \
./Drivers/CMSIS-master/Device/_Template_Flash/Test/system_stm32f10x.o 

S_DEPS += \
./Drivers/CMSIS-master/Device/_Template_Flash/Test/startup_stm32f10x_md.d 

C_DEPS += \
./Drivers/CMSIS-master/Device/_Template_Flash/Test/FlashDev.d \
./Drivers/CMSIS-master/Device/_Template_Flash/Test/FlashPrg.d \
./Drivers/CMSIS-master/Device/_Template_Flash/Test/FlashTest.d \
./Drivers/CMSIS-master/Device/_Template_Flash/Test/system_stm32f10x.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS-master/Device/_Template_Flash/Test/%.o: ../Drivers/CMSIS-master/Device/_Template_Flash/Test/%.c Drivers/CMSIS-master/Device/_Template_Flash/Test/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -DARM_MATH_CM4 -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/CMSIS-master/Device/_Template_Flash/Test/%.o: ../Drivers/CMSIS-master/Device/_Template_Flash/Test/%.s Drivers/CMSIS-master/Device/_Template_Flash/Test/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DDEBUG -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

