################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Middlewares/USBX/USB/USBX/UX\ Device\ CoreStack/subdir.mk
-include Middlewares/USBX/USB/USBX/UX\ Device\ Controllers/subdir.mk
-include Middlewares/USBX/USB/USBX/UX\ Device\ Class\ HID/subdir.mk
-include Middlewares/USBX/USB/USBX/CoreSystem/subdir.mk
-include Middlewares/ThreadX/RTOS/ThreadX/Core/subdir.mk
-include Drivers/STM32F7xx_HAL_Driver/subdir.mk
-include Drivers/CMSIS/subdir.mk
-include Application/User/USBX/App/subdir.mk
-include Application/User/Startup/subdir.mk
-include Application/User/Core/subdir.mk
-include Application/User/AZURE_RTOS/App/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := Ux_Device_HID_Bidir
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
Ux_Device_HID_Bidir.elf \

MAP_FILES += \
Ux_Device_HID_Bidir.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
Ux_Device_HID_Bidir.list \


# All Target
all: main-build

# Main-build Target
main-build: Ux_Device_HID_Bidir.elf secondary-outputs

# Tool invocations
Ux_Device_HID_Bidir.elf Ux_Device_HID_Bidir.map: $(OBJS) $(USER_OBJS) C:\Users\wayp\STM32CubeIDE\workspace_1.10.0\Ux_Device_HID_Bidir\STM32CubeIDE\STM32F767ZITX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "Ux_Device_HID_Bidir.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m7 -T"C:\Users\wayp\STM32CubeIDE\workspace_1.10.0\Ux_Device_HID_Bidir\STM32CubeIDE\STM32F767ZITX_FLASH.ld" --specs=nosys.specs -Wl,-Map="Ux_Device_HID_Bidir.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

Ux_Device_HID_Bidir.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "Ux_Device_HID_Bidir.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) Ux_Device_HID_Bidir.elf Ux_Device_HID_Bidir.list Ux_Device_HID_Bidir.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
