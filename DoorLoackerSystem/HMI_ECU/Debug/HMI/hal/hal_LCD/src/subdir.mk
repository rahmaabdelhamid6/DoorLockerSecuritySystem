################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HMI/hal/hal_LCD/src/hal_LCD.c 

OBJS += \
./HMI/hal/hal_LCD/src/hal_LCD.o 

C_DEPS += \
./HMI/hal/hal_LCD/src/hal_LCD.d 


# Each subdirectory must supply rules for building sources it contributes
HMI/hal/hal_LCD/src/%.o: ../HMI/hal/hal_LCD/src/%.c HMI/hal/hal_LCD/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


