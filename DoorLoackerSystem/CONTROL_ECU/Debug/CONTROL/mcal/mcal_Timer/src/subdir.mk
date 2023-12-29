################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CONTROL/mcal/mcal_Timer/src/mcal_Timer.c 

OBJS += \
./CONTROL/mcal/mcal_Timer/src/mcal_Timer.o 

C_DEPS += \
./CONTROL/mcal/mcal_Timer/src/mcal_Timer.d 


# Each subdirectory must supply rules for building sources it contributes
CONTROL/mcal/mcal_Timer/src/%.o: ../CONTROL/mcal/mcal_Timer/src/%.c CONTROL/mcal/mcal_Timer/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


