################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CONTROL/app/app_ECU/src/app_ECU.c 

OBJS += \
./CONTROL/app/app_ECU/src/app_ECU.o 

C_DEPS += \
./CONTROL/app/app_ECU/src/app_ECU.d 


# Each subdirectory must supply rules for building sources it contributes
CONTROL/app/app_ECU/src/%.o: ../CONTROL/app/app_ECU/src/%.c CONTROL/app/app_ECU/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


