################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/LP_2.cpp \
../src/tempCodeRunnerFile.cpp 

CPP_DEPS += \
./src/LP_2.d \
./src/tempCodeRunnerFile.d 

OBJS += \
./src/LP_2.o \
./src/tempCodeRunnerFile.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/LP_2.d ./src/LP_2.o ./src/tempCodeRunnerFile.d ./src/tempCodeRunnerFile.o

.PHONY: clean-src

