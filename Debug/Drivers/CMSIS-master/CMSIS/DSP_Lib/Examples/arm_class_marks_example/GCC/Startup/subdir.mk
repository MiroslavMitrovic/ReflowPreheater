################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/CMSIS-master/CMSIS/DSP_Lib/Examples/arm_class_marks_example/GCC/Startup/system_ARMCM0.c \
../Drivers/CMSIS-master/CMSIS/DSP_Lib/Examples/arm_class_marks_example/GCC/Startup/system_ARMCM3.c \
../Drivers/CMSIS-master/CMSIS/DSP_Lib/Examples/arm_class_marks_example/GCC/Startup/system_ARMCM4.c 

S_UPPER_SRCS += \
../Drivers/CMSIS-master/CMSIS/DSP_Lib/Examples/arm_class_marks_example/GCC/Startup/startup_ARMCM0.S \
../Drivers/CMSIS-master/CMSIS/DSP_Lib/Examples/arm_class_marks_example/GCC/Startup/startup_ARMCM3.S \
../Drivers/CMSIS-master/CMSIS/DSP_Lib/Examples/arm_class_marks_example/GCC/Startup/startup_ARMCM4.S 

OBJS += \
./Drivers/CMSIS-master/CMSIS/DSP_Lib/Examples/arm_class_marks_example/GCC/Startup/startup_ARMCM0.o \
./Drivers/CMSIS-master/CMSIS/DSP_Lib/Examples/arm_class_marks_example/GCC/Startup/startup_ARMCM3.o \
./Drivers/CMSIS-master/CMSIS/DSP_Lib/Examples/arm_class_marks_example/GCC/Startup/startup_ARMCM4.o \
./Drivers/CMSIS-master/CMSIS/DSP_Lib/Examples/arm_class_marks_example/GCC/Startup/system_ARMCM0.o \
./Drivers/CMSIS-master/CMSIS/DSP_Lib/Examples/arm_class_marks_example/GCC/Startup/system_ARMCM3.o \
./Drivers/CMSIS-master/CMSIS/DSP_Lib/Examples/arm_class_marks_example/GCC/Startup/system_ARMCM4.o 

S_UPPER_DEPS += \
./Drivers/CMSIS-master/CMSIS/DSP_Lib/Examples/arm_class_marks_example/GCC/Startup/startup_ARMCM0.d \
./Drivers/CMSIS-master/CMSIS/DSP_Lib/Examples/arm_class_marks_example/GCC/Startup/startup_ARMCM3.d \
./Drivers/CMSIS-master/CMSIS/DSP_Lib/Examples/arm_class_marks_example/GCC/Startup/startup_ARMCM4.d 

C_DEPS += \
./Drivers/CMSIS-master/CMSIS/DSP_Lib/Examples/arm_class_marks_example/GCC/Startup/system_ARMCM0.d \
./Drivers/CMSIS-master/CMSIS/DSP_Lib/Examples/arm_class_marks_example/GCC/Startup/system_ARMCM3.d \
./Drivers/CMSIS-master/CMSIS/DSP_Lib/Examples/arm_class_marks_example/GCC/Startup/system_ARMCM4.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS-master/CMSIS/DSP_Lib/Examples/arm_class_marks_example/GCC/Startup/%.o: ../Drivers/CMSIS-master/CMSIS/DSP_Lib/Examples/arm_class_marks_example/GCC/Startup/%.S Drivers/CMSIS-master/CMSIS/DSP_Lib/Examples/arm_class_marks_example/GCC/Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DDEBUG -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"
Drivers/CMSIS-master/CMSIS/DSP_Lib/Examples/arm_class_marks_example/GCC/Startup/%.o: ../Drivers/CMSIS-master/CMSIS/DSP_Lib/Examples/arm_class_marks_example/GCC/Startup/%.c Drivers/CMSIS-master/CMSIS/DSP_Lib/Examples/arm_class_marks_example/GCC/Startup/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -DARM_MATH_CM4 -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

