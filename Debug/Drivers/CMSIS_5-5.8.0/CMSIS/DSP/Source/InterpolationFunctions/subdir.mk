################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/InterpolationFunctions/InterpolationFunctions.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/InterpolationFunctions/InterpolationFunctionsF16.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/InterpolationFunctions/arm_bilinear_interp_f16.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/InterpolationFunctions/arm_bilinear_interp_f32.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/InterpolationFunctions/arm_bilinear_interp_q15.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/InterpolationFunctions/arm_bilinear_interp_q31.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/InterpolationFunctions/arm_bilinear_interp_q7.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/InterpolationFunctions/arm_linear_interp_f16.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/InterpolationFunctions/arm_linear_interp_f32.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/InterpolationFunctions/arm_linear_interp_q15.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/InterpolationFunctions/arm_linear_interp_q31.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/InterpolationFunctions/arm_linear_interp_q7.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/InterpolationFunctions/arm_spline_interp_f32.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/InterpolationFunctions/arm_spline_interp_init_f32.c 

OBJS += \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/InterpolationFunctions/InterpolationFunctions.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/InterpolationFunctions/InterpolationFunctionsF16.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/InterpolationFunctions/arm_bilinear_interp_f16.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/InterpolationFunctions/arm_bilinear_interp_f32.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/InterpolationFunctions/arm_bilinear_interp_q15.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/InterpolationFunctions/arm_bilinear_interp_q31.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/InterpolationFunctions/arm_bilinear_interp_q7.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/InterpolationFunctions/arm_linear_interp_f16.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/InterpolationFunctions/arm_linear_interp_f32.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/InterpolationFunctions/arm_linear_interp_q15.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/InterpolationFunctions/arm_linear_interp_q31.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/InterpolationFunctions/arm_linear_interp_q7.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/InterpolationFunctions/arm_spline_interp_f32.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/InterpolationFunctions/arm_spline_interp_init_f32.o 

C_DEPS += \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/InterpolationFunctions/InterpolationFunctions.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/InterpolationFunctions/InterpolationFunctionsF16.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/InterpolationFunctions/arm_bilinear_interp_f16.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/InterpolationFunctions/arm_bilinear_interp_f32.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/InterpolationFunctions/arm_bilinear_interp_q15.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/InterpolationFunctions/arm_bilinear_interp_q31.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/InterpolationFunctions/arm_bilinear_interp_q7.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/InterpolationFunctions/arm_linear_interp_f16.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/InterpolationFunctions/arm_linear_interp_f32.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/InterpolationFunctions/arm_linear_interp_q15.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/InterpolationFunctions/arm_linear_interp_q31.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/InterpolationFunctions/arm_linear_interp_q7.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/InterpolationFunctions/arm_spline_interp_f32.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/InterpolationFunctions/arm_spline_interp_init_f32.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/InterpolationFunctions/%.o: ../Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/InterpolationFunctions/%.c Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/InterpolationFunctions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -DARM_MATH_CM4 -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

