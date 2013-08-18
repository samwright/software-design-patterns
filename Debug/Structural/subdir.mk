################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Structural/adapter.cpp \
../Structural/bridge.cpp \
../Structural/composite.cpp \
../Structural/curiously_recurring_template.cpp \
../Structural/decorator.cpp \
../Structural/facade.cpp \
../Structural/flyweight.cpp \
../Structural/interface_based_programming.cpp \
../Structural/proxy.cpp 

OBJS += \
./Structural/adapter.o \
./Structural/bridge.o \
./Structural/composite.o \
./Structural/curiously_recurring_template.o \
./Structural/decorator.o \
./Structural/facade.o \
./Structural/flyweight.o \
./Structural/interface_based_programming.o \
./Structural/proxy.o 

CPP_DEPS += \
./Structural/adapter.d \
./Structural/bridge.d \
./Structural/composite.d \
./Structural/curiously_recurring_template.d \
./Structural/decorator.d \
./Structural/facade.d \
./Structural/flyweight.d \
./Structural/interface_based_programming.d \
./Structural/proxy.d 


# Each subdirectory must supply rules for building sources it contributes
Structural/%.o: ../Structural/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


