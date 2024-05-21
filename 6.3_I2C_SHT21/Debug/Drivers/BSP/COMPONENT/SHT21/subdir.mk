################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/COMPONENT/SHT21/sht2x_for_stm32_hal.c 

OBJS += \
./Drivers/BSP/COMPONENT/SHT21/sht2x_for_stm32_hal.o 

C_DEPS += \
./Drivers/BSP/COMPONENT/SHT21/sht2x_for_stm32_hal.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/COMPONENT/SHT21/%.o Drivers/BSP/COMPONENT/SHT21/%.su Drivers/BSP/COMPONENT/SHT21/%.cyclo: ../Drivers/BSP/COMPONENT/SHT21/%.c Drivers/BSP/COMPONENT/SHT21/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Core/Inc -I"D:/STM32/WorkSpace/6.3_I2C_SHT21/Drivers/BSP/COMPONENT/SHT21" -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-COMPONENT-2f-SHT21

clean-Drivers-2f-BSP-2f-COMPONENT-2f-SHT21:
	-$(RM) ./Drivers/BSP/COMPONENT/SHT21/sht2x_for_stm32_hal.cyclo ./Drivers/BSP/COMPONENT/SHT21/sht2x_for_stm32_hal.d ./Drivers/BSP/COMPONENT/SHT21/sht2x_for_stm32_hal.o ./Drivers/BSP/COMPONENT/SHT21/sht2x_for_stm32_hal.su

.PHONY: clean-Drivers-2f-BSP-2f-COMPONENT-2f-SHT21

