################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/gpio.c \
../Core/Src/ipcc.c \
../Core/Src/lptim.c \
../Core/Src/main.c \
../Core/Src/stm32mp1xx_hal_msp.c \
../Core/Src/stm32mp1xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/tim.c \
../Core/Src/usart.c 

OBJS += \
./Core/Src/gpio.o \
./Core/Src/ipcc.o \
./Core/Src/lptim.o \
./Core/Src/main.o \
./Core/Src/stm32mp1xx_hal_msp.o \
./Core/Src/stm32mp1xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/tim.o \
./Core/Src/usart.o 

C_DEPS += \
./Core/Src/gpio.d \
./Core/Src/ipcc.d \
./Core/Src/lptim.d \
./Core/Src/main.d \
./Core/Src/stm32mp1xx_hal_msp.d \
./Core/Src/stm32mp1xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/tim.d \
./Core/Src/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32MP157Axx -c -I../Core/Inc -IC:/Users/caoyuqian/STM32Cube/Repository/STM32Cube_FW_MP1_V1.5.0/Drivers/STM32MP1xx_HAL_Driver/Inc -IC:/Users/caoyuqian/STM32Cube/Repository/STM32Cube_FW_MP1_V1.5.0/Drivers/STM32MP1xx_HAL_Driver/Inc/Legacy -IC:/Users/caoyuqian/STM32Cube/Repository/STM32Cube_FW_MP1_V1.5.0/Drivers/CMSIS/Device/ST/STM32MP1xx/Include -IC:/Users/caoyuqian/STM32Cube/Repository/STM32Cube_FW_MP1_V1.5.0/Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/gpio.d ./Core/Src/gpio.o ./Core/Src/ipcc.d ./Core/Src/ipcc.o ./Core/Src/lptim.d ./Core/Src/lptim.o ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/stm32mp1xx_hal_msp.d ./Core/Src/stm32mp1xx_hal_msp.o ./Core/Src/stm32mp1xx_it.d ./Core/Src/stm32mp1xx_it.o ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/tim.d ./Core/Src/tim.o ./Core/Src/usart.d ./Core/Src/usart.o

.PHONY: clean-Core-2f-Src

