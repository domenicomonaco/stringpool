################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: cunit_stringpool_lib

dependents:
	-cd /Users/macbook/Documents/workspace-eclipse/Library/Debug && $(MAKE) clean all

# Tool invocations
cunit_stringpool_lib: $(OBJS) $(USER_OBJS) /Users/macbook/Documents/workspace-eclipse/Library/Debug/libLibrary.a
	@echo 'Building target: $@'
	@echo 'Invoking: MacOS X C Linker'
	gcc -L"/Users/macbook/Documents/workspace-eclipse/Library/Debug" -L/opt/local/lib -L/opt/local/bin -L/Users/macbook/Documents/workspace-eclipse/Library -L/Users/macbook/Documents/workspace-eclipse/Library/Release -o "cunit_stringpool_lib" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES) cunit_stringpool_lib
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:
/Users/macbook/Documents/workspace-eclipse/Library/Debug/libLibrary.a:

-include ../makefile.targets
