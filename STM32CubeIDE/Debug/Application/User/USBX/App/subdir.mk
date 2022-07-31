################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/wayp/STM32CubeIDE/workspace_1.10.0/Ux_Device_HID_Bidir/USBX/App/app_usbx_device.c \
C:/Users/wayp/STM32CubeIDE/workspace_1.10.0/Ux_Device_HID_Bidir/USBX/App/ux_device_descriptors.c \
C:/Users/wayp/STM32CubeIDE/workspace_1.10.0/Ux_Device_HID_Bidir/USBX/App/ux_device_mouse.c 

OBJS += \
./Application/User/USBX/App/app_usbx_device.o \
./Application/User/USBX/App/ux_device_descriptors.o \
./Application/User/USBX/App/ux_device_mouse.o 

C_DEPS += \
./Application/User/USBX/App/app_usbx_device.d \
./Application/User/USBX/App/ux_device_descriptors.d \
./Application/User/USBX/App/ux_device_mouse.d 


# Each subdirectory must supply rules for building sources it contributes
Application/User/USBX/App/app_usbx_device.o: C:/Users/wayp/STM32CubeIDE/workspace_1.10.0/Ux_Device_HID_Bidir/USBX/App/app_usbx_device.c Application/User/USBX/App/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DTX_INCLUDE_USER_DEFINE_FILE -DUX_INCLUDE_USER_DEFINE_FILE -DUSE_HAL_DRIVER -DSTM32F767xx -c -I../../Core/Inc -I../../AZURE_RTOS/App -I../../USBX/App -I../../USBX/Target -I../../Drivers/STM32F7xx_HAL_Driver/Inc -I../../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../../Drivers/CMSIS/Include -I../../Middlewares/ST/usbx/common/core/inc/ -I../../Middlewares/ST/usbx/ports/generic/inc/ -I../../Middlewares/ST/usbx/common/usbx_device_classes/inc/ -I../../Middlewares/ST/usbx/common/usbx_stm32_device_controllers/ -I../../Middlewares/ST/threadx/common/inc/ -I../../Middlewares/ST/threadx/ports/cortex_m7/gnu/inc/ -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/User/USBX/App/ux_device_descriptors.o: C:/Users/wayp/STM32CubeIDE/workspace_1.10.0/Ux_Device_HID_Bidir/USBX/App/ux_device_descriptors.c Application/User/USBX/App/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DTX_INCLUDE_USER_DEFINE_FILE -DUX_INCLUDE_USER_DEFINE_FILE -DUSE_HAL_DRIVER -DSTM32F767xx -c -I../../Core/Inc -I../../AZURE_RTOS/App -I../../USBX/App -I../../USBX/Target -I../../Drivers/STM32F7xx_HAL_Driver/Inc -I../../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../../Drivers/CMSIS/Include -I../../Middlewares/ST/usbx/common/core/inc/ -I../../Middlewares/ST/usbx/ports/generic/inc/ -I../../Middlewares/ST/usbx/common/usbx_device_classes/inc/ -I../../Middlewares/ST/usbx/common/usbx_stm32_device_controllers/ -I../../Middlewares/ST/threadx/common/inc/ -I../../Middlewares/ST/threadx/ports/cortex_m7/gnu/inc/ -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/User/USBX/App/ux_device_mouse.o: C:/Users/wayp/STM32CubeIDE/workspace_1.10.0/Ux_Device_HID_Bidir/USBX/App/ux_device_mouse.c Application/User/USBX/App/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DTX_INCLUDE_USER_DEFINE_FILE -DUX_INCLUDE_USER_DEFINE_FILE -DUSE_HAL_DRIVER -DSTM32F767xx -c -I../../Core/Inc -I../../AZURE_RTOS/App -I../../USBX/App -I../../USBX/Target -I../../Drivers/STM32F7xx_HAL_Driver/Inc -I../../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../../Drivers/CMSIS/Include -I../../Middlewares/ST/usbx/common/core/inc/ -I../../Middlewares/ST/usbx/ports/generic/inc/ -I../../Middlewares/ST/usbx/common/usbx_device_classes/inc/ -I../../Middlewares/ST/usbx/common/usbx_stm32_device_controllers/ -I../../Middlewares/ST/threadx/common/inc/ -I../../Middlewares/ST/threadx/ports/cortex_m7/gnu/inc/ -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Application-2f-User-2f-USBX-2f-App

clean-Application-2f-User-2f-USBX-2f-App:
	-$(RM) ./Application/User/USBX/App/app_usbx_device.d ./Application/User/USBX/App/app_usbx_device.o ./Application/User/USBX/App/app_usbx_device.su ./Application/User/USBX/App/ux_device_descriptors.d ./Application/User/USBX/App/ux_device_descriptors.o ./Application/User/USBX/App/ux_device_descriptors.su ./Application/User/USBX/App/ux_device_mouse.d ./Application/User/USBX/App/ux_device_mouse.o ./Application/User/USBX/App/ux_device_mouse.su

.PHONY: clean-Application-2f-User-2f-USBX-2f-App

