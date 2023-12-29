################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CONTROL/app/callback/appcb_Timer/src/appcb_Timer.c 

OBJS += \
./CONTROL/app/callback/appcb_Timer/src/appcb_Timer.o 

C_DEPS += \
./CONTROL/app/callback/appcb_Timer/src/appcb_Timer.d 


# Each subdirectory must supply rules for building sources it contributes
CONTROL/app/callback/appcb_Timer/src/%.o: ../CONTROL/app/callback/appcb_Timer/src/%.c CONTROL/app/callback/appcb_Timer/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


