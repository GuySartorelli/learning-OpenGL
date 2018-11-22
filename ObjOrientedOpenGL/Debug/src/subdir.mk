################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ShaderProgram.cpp \
../src/Util.cpp \
../src/VertexArray.cpp 

C_SRCS += \
../src/glad.c 

OBJS += \
./src/ShaderProgram.o \
./src/Util.o \
./src/VertexArray.o \
./src/glad.o 

CPP_DEPS += \
./src/ShaderProgram.d \
./src/Util.d \
./src/VertexArray.d 

C_DEPS += \
./src/glad.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I"/home/rallion/Documents/learnOpenGL/C++/OpenOOGL/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


