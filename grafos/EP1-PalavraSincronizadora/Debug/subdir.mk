################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Digrafo.cpp \
../EP1.cpp \
../Visitados.cpp \
../verificador.cpp 

OBJS += \
./Digrafo.o \
./EP1.o \
./Visitados.o \
./verificador.o 

CPP_DEPS += \
./Digrafo.d \
./EP1.d \
./Visitados.d \
./verificador.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


