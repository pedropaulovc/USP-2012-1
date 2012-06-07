################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Automato.cpp \
../Digrafo.cpp \
../EP1.cpp \
../Main.cpp \
../Visitados.cpp 

OBJS += \
./Automato.o \
./Digrafo.o \
./EP1.o \
./Main.o \
./Visitados.o 

CPP_DEPS += \
./Automato.d \
./Digrafo.d \
./EP1.d \
./Main.d \
./Visitados.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


