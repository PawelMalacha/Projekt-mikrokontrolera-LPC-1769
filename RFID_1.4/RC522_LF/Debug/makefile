################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include mbed/TARGET_LPC1768/TOOLCHAIN_GCC_CR/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: RC522_LF.axf

# Tool invocations
RC522_LF.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU C++ Linker'
	arm-none-eabi-c++ -nostdlib -L"C:\Users\pawel\Documents\LPCXpresso_8.2.2_650\RFID_1.4\RC522_LF" -L"C:\Users\pawel\Documents\LPCXpresso_8.2.2_650\RFID_1.4\RC522_LF\mbed" -L"C:\Users\pawel\Documents\LPCXpresso_8.2.2_650\RFID_1.4\RC522_LF\mbed\TARGET_LPC1768" -L"C:\Users\pawel\Documents\LPCXpresso_8.2.2_650\RFID_1.4\RC522_LF\mbed\TARGET_LPC1768\TARGET_NXP" -L"C:\Users\pawel\Documents\LPCXpresso_8.2.2_650\RFID_1.4\RC522_LF\mbed\TARGET_LPC1768\TARGET_NXP\TARGET_LPC176X" -L"C:\Users\pawel\Documents\LPCXpresso_8.2.2_650\RFID_1.4\RC522_LF\mbed\TARGET_LPC1768\TARGET_NXP\TARGET_LPC176X\TARGET_MBED_LPC1768" -L"C:\Users\pawel\Documents\LPCXpresso_8.2.2_650\RFID_1.4\RC522_LF\mbed\TARGET_LPC1768\TOOLCHAIN_GCC_CR" -Xlinker -Map="RC522_LF.map" -Xlinker --gc-sections -mcpu=cortex-m3 -mthumb -T "RC522_LF_Debug.ld" -o "RC522_LF.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(CC_DEPS)$(C++_DEPS)$(EXECUTABLES)$(C_UPPER_DEPS)$(CXX_DEPS)$(OBJS)$(CPP_DEPS)$(C_DEPS) RC522_LF.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "RC522_LF.axf"; arm-none-eabi-objcopy -O binary "RC522_LF.axf" "RC522_LF.bin" ; # checksum -p LPC1769 -d "RC522_LF.bin";
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
