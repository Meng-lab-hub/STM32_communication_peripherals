################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/bsp_accelerometer.c \
../Core/Src/bsp_buttonsswitches.c \
../Core/Src/bsp_can.c \
../Core/Src/bsp_glcd.c \
../Core/Src/bsp_globalfunctions.c \
../Core/Src/bsp_i2c.c \
../Core/Src/bsp_spi.c \
../Core/Src/bsp_thermometer.c \
../Core/Src/bsp_uart.c \
../Core/Src/gpio.c \
../Core/Src/graphics.c \
../Core/Src/localsensorprocessing.c \
../Core/Src/log.c \
../Core/Src/main.c \
../Core/Src/mainloop.c \
../Core/Src/stm32f4xx_hal_msp.c \
../Core/Src/stm32f4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f4xx.c \
../Core/Src/tim.c \
../Core/Src/usart.c 

OBJS += \
./Core/Src/bsp_accelerometer.o \
./Core/Src/bsp_buttonsswitches.o \
./Core/Src/bsp_can.o \
./Core/Src/bsp_glcd.o \
./Core/Src/bsp_globalfunctions.o \
./Core/Src/bsp_i2c.o \
./Core/Src/bsp_spi.o \
./Core/Src/bsp_thermometer.o \
./Core/Src/bsp_uart.o \
./Core/Src/gpio.o \
./Core/Src/graphics.o \
./Core/Src/localsensorprocessing.o \
./Core/Src/log.o \
./Core/Src/main.o \
./Core/Src/mainloop.o \
./Core/Src/stm32f4xx_hal_msp.o \
./Core/Src/stm32f4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f4xx.o \
./Core/Src/tim.o \
./Core/Src/usart.o 

C_DEPS += \
./Core/Src/bsp_accelerometer.d \
./Core/Src/bsp_buttonsswitches.d \
./Core/Src/bsp_can.d \
./Core/Src/bsp_glcd.d \
./Core/Src/bsp_globalfunctions.d \
./Core/Src/bsp_i2c.d \
./Core/Src/bsp_spi.d \
./Core/Src/bsp_thermometer.d \
./Core/Src/bsp_uart.d \
./Core/Src/gpio.d \
./Core/Src/graphics.d \
./Core/Src/localsensorprocessing.d \
./Core/Src/log.d \
./Core/Src/main.d \
./Core/Src/mainloop.d \
./Core/Src/stm32f4xx_hal_msp.d \
./Core/Src/stm32f4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f4xx.d \
./Core/Src/tim.d \
./Core/Src/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I../Drivers/CMSIS/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Core/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/bsp_accelerometer.d ./Core/Src/bsp_accelerometer.o ./Core/Src/bsp_accelerometer.su ./Core/Src/bsp_buttonsswitches.d ./Core/Src/bsp_buttonsswitches.o ./Core/Src/bsp_buttonsswitches.su ./Core/Src/bsp_can.d ./Core/Src/bsp_can.o ./Core/Src/bsp_can.su ./Core/Src/bsp_glcd.d ./Core/Src/bsp_glcd.o ./Core/Src/bsp_glcd.su ./Core/Src/bsp_globalfunctions.d ./Core/Src/bsp_globalfunctions.o ./Core/Src/bsp_globalfunctions.su ./Core/Src/bsp_i2c.d ./Core/Src/bsp_i2c.o ./Core/Src/bsp_i2c.su ./Core/Src/bsp_spi.d ./Core/Src/bsp_spi.o ./Core/Src/bsp_spi.su ./Core/Src/bsp_thermometer.d ./Core/Src/bsp_thermometer.o ./Core/Src/bsp_thermometer.su ./Core/Src/bsp_uart.d ./Core/Src/bsp_uart.o ./Core/Src/bsp_uart.su ./Core/Src/gpio.d ./Core/Src/gpio.o ./Core/Src/gpio.su ./Core/Src/graphics.d ./Core/Src/graphics.o ./Core/Src/graphics.su ./Core/Src/localsensorprocessing.d ./Core/Src/localsensorprocessing.o ./Core/Src/localsensorprocessing.su ./Core/Src/log.d ./Core/Src/log.o ./Core/Src/log.su ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/mainloop.d ./Core/Src/mainloop.o ./Core/Src/mainloop.su ./Core/Src/stm32f4xx_hal_msp.d ./Core/Src/stm32f4xx_hal_msp.o ./Core/Src/stm32f4xx_hal_msp.su ./Core/Src/stm32f4xx_it.d ./Core/Src/stm32f4xx_it.o ./Core/Src/stm32f4xx_it.su ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f4xx.d ./Core/Src/system_stm32f4xx.o ./Core/Src/system_stm32f4xx.su ./Core/Src/tim.d ./Core/Src/tim.o ./Core/Src/tim.su ./Core/Src/usart.d ./Core/Src/usart.o ./Core/Src/usart.su

.PHONY: clean-Core-2f-Src

