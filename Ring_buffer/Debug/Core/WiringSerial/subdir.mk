################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/WiringSerial/Serial.c 

OBJS += \
./Core/WiringSerial/Serial.o 

C_DEPS += \
./Core/WiringSerial/Serial.d 


# Each subdirectory must supply rules for building sources it contributes
Core/WiringSerial/%.o Core/WiringSerial/%.su Core/WiringSerial/%.cyclo: ../Core/WiringSerial/%.c Core/WiringSerial/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L496xx -c -I../Core/Inc -I"D:/STM32/WorkSpace/Ring_buffer/Core/WiringSerial" -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-WiringSerial

clean-Core-2f-WiringSerial:
	-$(RM) ./Core/WiringSerial/Serial.cyclo ./Core/WiringSerial/Serial.d ./Core/WiringSerial/Serial.o ./Core/WiringSerial/Serial.su

.PHONY: clean-Core-2f-WiringSerial

