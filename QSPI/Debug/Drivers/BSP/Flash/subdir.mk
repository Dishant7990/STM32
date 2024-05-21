################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/Flash/FlashCircularBuffer.c \
../Drivers/BSP/Flash/flash.c 

OBJS += \
./Drivers/BSP/Flash/FlashCircularBuffer.o \
./Drivers/BSP/Flash/flash.o 

C_DEPS += \
./Drivers/BSP/Flash/FlashCircularBuffer.d \
./Drivers/BSP/Flash/flash.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/Flash/%.o Drivers/BSP/Flash/%.su Drivers/BSP/Flash/%.cyclo: ../Drivers/BSP/Flash/%.c Drivers/BSP/Flash/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -DCUSTOM_DEBUG=1 -c -I"D:/STM32/WorkSpace/QSPI/Drivers/BSP/Flash" -I"D:/STM32/WorkSpace/QSPI/Drivers/BSP/Refrance_drv" -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-Flash

clean-Drivers-2f-BSP-2f-Flash:
	-$(RM) ./Drivers/BSP/Flash/FlashCircularBuffer.cyclo ./Drivers/BSP/Flash/FlashCircularBuffer.d ./Drivers/BSP/Flash/FlashCircularBuffer.o ./Drivers/BSP/Flash/FlashCircularBuffer.su ./Drivers/BSP/Flash/flash.cyclo ./Drivers/BSP/Flash/flash.d ./Drivers/BSP/Flash/flash.o ./Drivers/BSP/Flash/flash.su

.PHONY: clean-Drivers-2f-BSP-2f-Flash

