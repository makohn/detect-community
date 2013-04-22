################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ego/EgoGraph.cpp 

OBJS += \
./src/ego/EgoGraph.o 

CPP_DEPS += \
./src/ego/EgoGraph.d 


# Each subdirectory must supply rules for building sources it contributes
src/ego/%.o: ../src/ego/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++0x -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


