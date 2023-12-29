################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HMI/mcal/mcal_Uart.h/src/mcal_Uart.c 

OBJS += \
./HMI/mcal/mcal_Uart.h/src/mcal_Uart.o 

C_DEPS += \
./HMI/mcal/mcal_Uart.h/src/mcal_Uart.d 


# Each subdirectory must supply rules for building sources it contributes
HMI/mcal/mcal_Uart.h/src/%.o: ../HMI/mcal/mcal_Uart.h/src/%.c HMI/mcal/mcal_Uart.h/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


