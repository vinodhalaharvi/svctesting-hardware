################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/main.c" \
"../Sources/svc.c" \

C_SRCS += \
../Sources/main.c \
../Sources/svc.c \

OBJS += \
./Sources/main.o \
./Sources/svc.o \

C_DEPS += \
./Sources/main.d \
./Sources/svc.d \

OBJS_QUOTED += \
"./Sources/main.o" \
"./Sources/svc.o" \

C_DEPS_QUOTED += \
"./Sources/main.d" \
"./Sources/svc.d" \

OBJS_OS_FORMAT += \
./Sources/main.o \
./Sources/svc.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/main.o: ../Sources/main.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/main.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/main.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/svc.o: ../Sources/svc.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/svc.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/svc.o"
	@echo 'Finished building: $<'
	@echo ' '


