################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/caoyuqian/STM32CubeIDE/workspace_1.8.0/MP1D/Common/System/system_stm32mp1xx.c 

OBJS += \
./Common/System/system_stm32mp1xx.o 

C_DEPS += \
./Common/System/system_stm32mp1xx.d 


# Each subdirectory must supply rules for building sources it contributes
Common/System/system_stm32mp1xx.o: C:/Users/caoyuqian/STM32CubeIDE/workspace_1.8.0/MP1D/Common/System/system_stm32mp1xx.c Common/System/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32MP157Axx -c -I../Core/Inc -I../module/Inc -IC:/Users/caoyuqian/STM32Cube/Repository/STM32Cube_FW_MP1_V1.5.0/Drivers/STM32MP1xx_HAL_Driver/Inc -IC:/Users/caoyuqian/STM32Cube/Repository/STM32Cube_FW_MP1_V1.5.0/Drivers/STM32MP1xx_HAL_Driver/Inc/Legacy -IC:/Users/caoyuqian/STM32Cube/Repository/STM32Cube_FW_MP1_V1.5.0/Drivers/CMSIS/Device/ST/STM32MP1xx/Include -IC:/Users/caoyuqian/STM32Cube/Repository/STM32Cube_FW_MP1_V1.5.0/Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Common-2f-System

clean-Common-2f-System:
	-$(RM) ./Common/System/system_stm32mp1xx.d ./Common/System/system_stm32mp1xx.o

.PHONY: clean-Common-2f-System

