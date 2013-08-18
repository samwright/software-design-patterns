################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Creational/Factory.cpp \
../Creational/Prototype.cpp \
../Creational/Singleton.cpp \
../Creational/builder.cpp 

OBJS += \
./Creational/Factory.o \
./Creational/Prototype.o \
./Creational/Singleton.o \
./Creational/builder.o 

CPP_DEPS += \
./Creational/Factory.d \
./Creational/Prototype.d \
./Creational/Singleton.d \
./Creational/builder.d 


# Each subdirectory must supply rules for building sources it contributes
Creational/%.o: ../Creational/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


