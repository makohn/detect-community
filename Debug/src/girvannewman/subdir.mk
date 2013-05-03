################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/girvannewman/NewmanGraph.cpp \
../src/girvannewman/betweenness.cpp \
../src/girvannewman/connection.cpp \
../src/girvannewman/girvannewman.cpp 

OBJS += \
./src/girvannewman/NewmanGraph.o \
./src/girvannewman/betweenness.o \
./src/girvannewman/connection.o \
./src/girvannewman/girvannewman.o 

CPP_DEPS += \
./src/girvannewman/NewmanGraph.d \
./src/girvannewman/betweenness.d \
./src/girvannewman/connection.d \
./src/girvannewman/girvannewman.d 


# Each subdirectory must supply rules for building sources it contributes
src/girvannewman/%.o: ../src/girvannewman/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++0x -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


