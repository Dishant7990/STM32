################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/COMPONENT/SD\ CARD/fatfs_sd.c 

OBJS += \
./Drivers/BSP/COMPONENT/SD\ CARD/fatfs_sd.o 

C_DEPS += \
./Drivers/BSP/COMPONENT/SD\ CARD/fatfs_sd.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/COMPONENT/SD\ CARD/fatfs_sd.o: ../Drivers/BSP/COMPONENT/SD\ CARD/fatfs_sd.c Drivers/BSP/COMPONENT/SD\ CARD/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I"D:/STM32/WorkSpace/7.3-SPI-SD/Drivers/BSP/COMPONENT/SD CARD" -I"D:/STM32/WorkSpace/7.3-SPI-SD/Middlewares" -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"Drivers/BSP/COMPONENT/SD CARD/fatfs_sd.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-COMPONENT-2f-SD-20-CARD

clean-Drivers-2f-BSP-2f-COMPONENT-2f-SD-20-CARD:
	-$(RM) ./Drivers/BSP/COMPONENT/SD\ CARD/fatfs_sd.cyclo ./Drivers/BSP/COMPONENT/SD\ CARD/fatfs_sd.d ./Drivers/BSP/COMPONENT/SD\ CARD/fatfs_sd.o ./Drivers/BSP/COMPONENT/SD\ CARD/fatfs_sd.su

.PHONY: clean-Drivers-2f-BSP-2f-COMPONENT-2f-SD-20-CARD

