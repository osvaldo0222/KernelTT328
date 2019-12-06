################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include Drivers/STM32F7xx_HAL_Driver/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
KernelItt328.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
KernelItt328.list \


# All Target
all: KernelItt328.elf secondary-outputs

# Tool invocations
KernelItt328.elf: $(OBJS) $(USER_OBJS) /home/osvaldofdez/10-DECIMO-CICLO/SistemasOperativos/KernelItt328/STM32F767ZITX_FLASH.ld
	arm-none-eabi-gcc -o "KernelItt328.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m7 -T"/home/osvaldofdez/10-DECIMO-CICLO/SistemasOperativos/KernelItt328/STM32F767ZITX_FLASH.ld" --specs=nosys.specs -Wl,-Map="KernelItt328.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

KernelItt328.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "KernelItt328.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
