################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/StatisticsFunctions.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/StatisticsFunctionsF16.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_absmax_f16.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_absmax_f32.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_absmax_q15.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_absmax_q31.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_absmax_q7.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_absmin_f16.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_absmin_f32.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_absmin_q15.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_absmin_q31.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_absmin_q7.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_entropy_f16.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_entropy_f32.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_entropy_f64.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_kullback_leibler_f16.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_kullback_leibler_f32.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_kullback_leibler_f64.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_logsumexp_dot_prod_f16.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_logsumexp_dot_prod_f32.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_logsumexp_f16.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_logsumexp_f32.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_max_f16.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_max_f32.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_max_no_idx_f16.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_max_no_idx_f32.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_max_q15.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_max_q31.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_max_q7.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_mean_f16.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_mean_f32.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_mean_q15.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_mean_q31.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_mean_q7.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_min_f16.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_min_f32.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_min_q15.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_min_q31.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_min_q7.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_power_f16.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_power_f32.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_power_q15.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_power_q31.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_power_q7.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_rms_f16.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_rms_f32.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_rms_q15.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_rms_q31.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_std_f16.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_std_f32.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_std_q15.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_std_q31.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_var_f16.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_var_f32.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_var_q15.c \
../Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_var_q31.c 

OBJS += \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/StatisticsFunctions.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/StatisticsFunctionsF16.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_absmax_f16.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_absmax_f32.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_absmax_q15.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_absmax_q31.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_absmax_q7.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_absmin_f16.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_absmin_f32.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_absmin_q15.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_absmin_q31.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_absmin_q7.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_entropy_f16.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_entropy_f32.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_entropy_f64.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_kullback_leibler_f16.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_kullback_leibler_f32.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_kullback_leibler_f64.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_logsumexp_dot_prod_f16.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_logsumexp_dot_prod_f32.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_logsumexp_f16.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_logsumexp_f32.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_max_f16.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_max_f32.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_max_no_idx_f16.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_max_no_idx_f32.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_max_q15.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_max_q31.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_max_q7.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_mean_f16.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_mean_f32.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_mean_q15.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_mean_q31.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_mean_q7.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_min_f16.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_min_f32.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_min_q15.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_min_q31.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_min_q7.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_power_f16.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_power_f32.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_power_q15.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_power_q31.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_power_q7.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_rms_f16.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_rms_f32.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_rms_q15.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_rms_q31.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_std_f16.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_std_f32.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_std_q15.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_std_q31.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_var_f16.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_var_f32.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_var_q15.o \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_var_q31.o 

C_DEPS += \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/StatisticsFunctions.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/StatisticsFunctionsF16.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_absmax_f16.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_absmax_f32.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_absmax_q15.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_absmax_q31.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_absmax_q7.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_absmin_f16.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_absmin_f32.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_absmin_q15.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_absmin_q31.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_absmin_q7.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_entropy_f16.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_entropy_f32.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_entropy_f64.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_kullback_leibler_f16.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_kullback_leibler_f32.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_kullback_leibler_f64.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_logsumexp_dot_prod_f16.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_logsumexp_dot_prod_f32.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_logsumexp_f16.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_logsumexp_f32.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_max_f16.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_max_f32.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_max_no_idx_f16.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_max_no_idx_f32.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_max_q15.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_max_q31.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_max_q7.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_mean_f16.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_mean_f32.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_mean_q15.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_mean_q31.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_mean_q7.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_min_f16.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_min_f32.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_min_q15.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_min_q31.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_min_q7.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_power_f16.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_power_f32.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_power_q15.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_power_q31.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_power_q7.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_rms_f16.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_rms_f32.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_rms_q15.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_rms_q31.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_std_f16.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_std_f32.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_std_q15.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_std_q31.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_var_f16.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_var_f32.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_var_q15.d \
./Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/arm_var_q31.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/%.o: ../Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/%.c Drivers/CMSIS_5-5.8.0/CMSIS/DSP/Source/StatisticsFunctions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -DARM_MATH_CM4 -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

