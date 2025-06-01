################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../TCP_App/Src/TCP_client.c \
../TCP_App/Src/app_ethernet.c \
../TCP_App/Src/uart_debug.c 

OBJS += \
./TCP_App/Src/TCP_client.o \
./TCP_App/Src/app_ethernet.o \
./TCP_App/Src/uart_debug.o 

C_DEPS += \
./TCP_App/Src/TCP_client.d \
./TCP_App/Src/app_ethernet.d \
./TCP_App/Src/uart_debug.d 


# Each subdirectory must supply rules for building sources it contributes
TCP_App/Src/%.o TCP_App/Src/%.su TCP_App/Src/%.cyclo: ../TCP_App/Src/%.c TCP_App/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F746xx -c -I../Core/Inc -I../TCP_App/Inc -I../LWIP/App -I../LWIP/Target -IC:/Users/batuh/STM32Cube/Repository/STM32Cube_FW_F7_V1.17.3/Middlewares/Third_Party/LwIP/src/include -IC:/Users/batuh/STM32Cube/Repository/STM32Cube_FW_F7_V1.17.3/Middlewares/Third_Party/LwIP/system -IC:/Users/batuh/STM32Cube/Repository/STM32Cube_FW_F7_V1.17.3/Drivers/STM32F7xx_HAL_Driver/Inc -IC:/Users/batuh/STM32Cube/Repository/STM32Cube_FW_F7_V1.17.3/Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -IC:/Users/batuh/STM32Cube/Repository/STM32Cube_FW_F7_V1.17.3/Drivers/BSP/Components/lan8742 -IC:/Users/batuh/STM32Cube/Repository/STM32Cube_FW_F7_V1.17.3/Middlewares/Third_Party/LwIP/src/include/netif/ppp -IC:/Users/batuh/STM32Cube/Repository/STM32Cube_FW_F7_V1.17.3/Drivers/CMSIS/Device/ST/STM32F7xx/Include -IC:/Users/batuh/STM32Cube/Repository/STM32Cube_FW_F7_V1.17.3/Middlewares/Third_Party/LwIP/src/include/lwip -IC:/Users/batuh/STM32Cube/Repository/STM32Cube_FW_F7_V1.17.3/Middlewares/Third_Party/LwIP/src/include/lwip/apps -IC:/Users/batuh/STM32Cube/Repository/STM32Cube_FW_F7_V1.17.3/Middlewares/Third_Party/LwIP/src/include/lwip/priv -IC:/Users/batuh/STM32Cube/Repository/STM32Cube_FW_F7_V1.17.3/Middlewares/Third_Party/LwIP/src/include/lwip/prot -IC:/Users/batuh/STM32Cube/Repository/STM32Cube_FW_F7_V1.17.3/Middlewares/Third_Party/LwIP/src/include/netif -IC:/Users/batuh/STM32Cube/Repository/STM32Cube_FW_F7_V1.17.3/Middlewares/Third_Party/LwIP/src/include/compat/posix -IC:/Users/batuh/STM32Cube/Repository/STM32Cube_FW_F7_V1.17.3/Middlewares/Third_Party/LwIP/src/include/compat/posix/arpa -IC:/Users/batuh/STM32Cube/Repository/STM32Cube_FW_F7_V1.17.3/Middlewares/Third_Party/LwIP/src/include/compat/posix/net -IC:/Users/batuh/STM32Cube/Repository/STM32Cube_FW_F7_V1.17.3/Middlewares/Third_Party/LwIP/src/include/compat/posix/sys -IC:/Users/batuh/STM32Cube/Repository/STM32Cube_FW_F7_V1.17.3/Middlewares/Third_Party/LwIP/src/include/compat/stdc -IC:/Users/batuh/STM32Cube/Repository/STM32Cube_FW_F7_V1.17.3/Middlewares/Third_Party/LwIP/system/arch -IC:/Users/batuh/STM32Cube/Repository/STM32Cube_FW_F7_V1.17.3/Drivers/CMSIS/Include -I"C:/Users/batuh/Desktop/Batuhan/Projects/f746g_TCP_basic/TCP_App" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-TCP_App-2f-Src

clean-TCP_App-2f-Src:
	-$(RM) ./TCP_App/Src/TCP_client.cyclo ./TCP_App/Src/TCP_client.d ./TCP_App/Src/TCP_client.o ./TCP_App/Src/TCP_client.su ./TCP_App/Src/app_ethernet.cyclo ./TCP_App/Src/app_ethernet.d ./TCP_App/Src/app_ethernet.o ./TCP_App/Src/app_ethernet.su ./TCP_App/Src/uart_debug.cyclo ./TCP_App/Src/uart_debug.d ./TCP_App/Src/uart_debug.o ./TCP_App/Src/uart_debug.su

.PHONY: clean-TCP_App-2f-Src

