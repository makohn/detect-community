################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ego/Cluster.cpp \
../src/ego/EgoGraph.cpp \
../src/ego/util.cpp 

OBJS += \
./src/ego/Cluster.o \
./src/ego/EgoGraph.o \
./src/ego/util.o 

CPP_DEPS += \
./src/ego/Cluster.d \
./src/ego/EgoGraph.d \
./src/ego/util.d 


# Each subdirectory must supply rules for building sources it contributes
src/ego/%.o: ../src/ego/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++0x -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


