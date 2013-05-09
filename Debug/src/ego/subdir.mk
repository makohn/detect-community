################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ego/cluster.cpp \
../src/ego/ego_ml_algo.cpp \
../src/ego/egograph.cpp \
../src/ego/graph_match.cpp \
../src/ego/util.cpp 

OBJS += \
./src/ego/cluster.o \
./src/ego/ego_ml_algo.o \
./src/ego/egograph.o \
./src/ego/graph_match.o \
./src/ego/util.o 

CPP_DEPS += \
./src/ego/cluster.d \
./src/ego/ego_ml_algo.d \
./src/ego/egograph.d \
./src/ego/graph_match.d \
./src/ego/util.d 


# Each subdirectory must supply rules for building sources it contributes
src/ego/%.o: ../src/ego/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++0x -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


