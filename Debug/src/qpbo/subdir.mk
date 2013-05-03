################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/qpbo/QPBO.cpp \
../src/qpbo/QPBO_extra.cpp \
../src/qpbo/QPBO_maxflow.cpp \
../src/qpbo/QPBO_postprocessing.cpp 

OBJS += \
./src/qpbo/QPBO.o \
./src/qpbo/QPBO_extra.o \
./src/qpbo/QPBO_maxflow.o \
./src/qpbo/QPBO_postprocessing.o 

CPP_DEPS += \
./src/qpbo/QPBO.d \
./src/qpbo/QPBO_extra.d \
./src/qpbo/QPBO_maxflow.d \
./src/qpbo/QPBO_postprocessing.d 


# Each subdirectory must supply rules for building sources it contributes
src/qpbo/%.o: ../src/qpbo/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++0x -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


