################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/CMSIS_5-5.8.0/CMSIS/CoreValidation/Source/CV_CAL1Cache.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/CoreValidation/Source/CV_CML1Cache.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/CoreValidation/Source/CV_CoreAFunc.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/CoreValidation/Source/CV_CoreFunc.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/CoreValidation/Source/CV_CoreInstr.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/CoreValidation/Source/CV_CoreSimd.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/CoreValidation/Source/CV_Framework.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/CoreValidation/Source/CV_GenTimer.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/CoreValidation/Source/CV_MPU_ARMv7.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/CoreValidation/Source/CV_MPU_ARMv8.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/CoreValidation/Source/CV_Report.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/CoreValidation/Source/cmsis_cv.c 

OBJS += \
./Drivers/CMSIS_5-5.8.0/CMSIS/CoreValidation/Source/CV_CAL1Cache.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/CoreValidation/Source/CV_CML1Cache.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/CoreValidation/Source/CV_CoreAFunc.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/CoreValidation/Source/CV_CoreFunc.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/CoreValidation/Source/CV_CoreInstr.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/CoreValidation/Source/CV_CoreSimd.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/CoreValidation/Source/CV_Framework.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/CoreValidation/Source/CV_GenTimer.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/CoreValidation/Source/CV_MPU_ARMv7.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/CoreValidation/Source/CV_MPU_ARMv8.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/CoreValidation/Source/CV_Report.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/CoreValidation/Source/cmsis_cv.o 

C_DEPS += \
./Drivers/CMSIS_5-5.8.0/CMSIS/CoreValidation/Source/CV_CAL1Cache.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/CoreValidation/Source/CV_CML1Cache.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/CoreValidation/Source/CV_CoreAFunc.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/CoreValidation/Source/CV_CoreFunc.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/CoreValidation/Source/CV_CoreInstr.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/CoreValidation/Source/CV_CoreSimd.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/CoreValidation/Source/CV_Framework.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/CoreValidation/Source/CV_GenTimer.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/CoreValidation/Source/CV_MPU_ARMv7.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/CoreValidation/Source/CV_MPU_ARMv8.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/CoreValidation/Source/CV_Report.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/CoreValidation/Source/cmsis_cv.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS_5-5.8.0/CMSIS/CoreValidation/Source/%.o: ../Drivers/CMSIS_5-5.8.0/CMSIS/CoreValidation/Source/%.c Drivers/CMSIS_5-5.8.0/CMSIS/CoreValidation/Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -DARM_MATH_CM4 -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

