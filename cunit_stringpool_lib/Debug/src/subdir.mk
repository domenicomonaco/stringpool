################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/cunit_stringpool_lib.c 

OBJS += \
./src/cunit_stringpool_lib.o 

C_DEPS += \
./src/cunit_stringpool_lib.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"/Users/macbook/Documents/workspace-eclipse/Library" -I/opt/local/include -I/Users/macbook/Documents/workspace-eclipse/Library -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


