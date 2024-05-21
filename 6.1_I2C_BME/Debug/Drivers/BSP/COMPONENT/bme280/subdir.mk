################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/COMPONENT/bme280/BME280_STM32.c 

OBJS += \
./Drivers/BSP/COMPONENT/bme280/BME280_STM32.o 

C_DEPS += \
./Drivers/BSP/COMPONENT/bme280/BME280_STM32.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/COMPONENT/bme280/%.o Drivers/BSP/COMPONENT/bme280/%.su Drivers/BSP/COMPONENT/bme280/%.cyclo: ../Drivers/BSP/COMPONENT/bme280/%.c Drivers/BSP/COMPONENT/bme280/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Core/Inc -I"D:/STM32/WorkSpace/6.1_I2C_BME/Drivers/BSP/COMPONENT/bme280" -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-COMPONENT-2f-bme280

clean-Drivers-2f-BSP-2f-COMPONENT-2f-bme280:
	-$(RM) ./Drivers/BSP/COMPONENT/bme280/BME280_STM32.cyclo ./Drivers/BSP/COMPONENT/bme280/BME280_STM32.d ./Drivers/BSP/COMPONENT/bme280/BME280_STM32.o ./Drivers/BSP/COMPONENT/bme280/BME280_STM32.su

.PHONY: clean-Drivers-2f-BSP-2f-COMPONENT-2f-bme280

