################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/COMPONENT/BME680/bme680.c 

OBJS += \
./Drivers/BSP/COMPONENT/BME680/bme680.o 

C_DEPS += \
./Drivers/BSP/COMPONENT/BME680/bme680.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/COMPONENT/BME680/%.o Drivers/BSP/COMPONENT/BME680/%.su Drivers/BSP/COMPONENT/BME680/%.cyclo: ../Drivers/BSP/COMPONENT/BME680/%.c Drivers/BSP/COMPONENT/BME680/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Core/Inc -I"D:/STM32/WorkSpace/6.2_I2C_BME680/Drivers/BSP/COMPONENT/BME680" -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-COMPONENT-2f-BME680

clean-Drivers-2f-BSP-2f-COMPONENT-2f-BME680:
	-$(RM) ./Drivers/BSP/COMPONENT/BME680/bme680.cyclo ./Drivers/BSP/COMPONENT/BME680/bme680.d ./Drivers/BSP/COMPONENT/BME680/bme680.o ./Drivers/BSP/COMPONENT/BME680/bme680.su

.PHONY: clean-Drivers-2f-BSP-2f-COMPONENT-2f-BME680

