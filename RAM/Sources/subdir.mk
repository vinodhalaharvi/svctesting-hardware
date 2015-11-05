################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../Sources/main.o \

C_SRCS_QUOTED += \
"../Sources/delay.c" \
"../Sources/led.c" \
"../Sources/main.c" \
"../Sources/svc.c" \

O_SRCS_QUOTED += \
"../Sources/main.o" \

C_SRCS += \
../Sources/delay.c \
../Sources/led.c \
../Sources/main.c \
../Sources/svc.c \

OBJS += \
./Sources/delay.o \
./Sources/led.o \
./Sources/main.o \
./Sources/svc.o \

C_DEPS += \
./Sources/delay.d \
./Sources/led.d \
./Sources/main.d \
./Sources/svc.d \

OBJS_QUOTED += \
"./Sources/delay.o" \
"./Sources/led.o" \
"./Sources/main.o" \
"./Sources/svc.o" \

C_DEPS_QUOTED += \
"./Sources/delay.d" \
"./Sources/led.d" \
"./Sources/main.d" \
"./Sources/svc.d" \

OBJS_OS_FORMAT += \
./Sources/delay.o \
./Sources/led.o \
./Sources/main.o \
./Sources/svc.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/delay.o: ../Sources/delay.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/delay.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/delay.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/led.o: ../Sources/led.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/led.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/led.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/main.o: ../Sources/main.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/main.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/main.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/svc.o: ../Sources/svc.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/svc.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/svc.o"
	@echo 'Finished building: $<'
	@echo ' '


