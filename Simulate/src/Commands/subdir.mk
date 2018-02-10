################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Commands/AutonomousCommand.cpp \
../src/Commands/Drive.cpp \
../src/Commands/IntakeCmd.cpp 

OBJS += \
./src/Commands/AutonomousCommand.o \
./src/Commands/Drive.o \
./src/Commands/IntakeCmd.o 

CPP_DEPS += \
./src/Commands/AutonomousCommand.d \
./src/Commands/Drive.d \
./src/Commands/IntakeCmd.d 


# Each subdirectory must supply rules for building sources it contributes
src/Commands/%.o: ../src/Commands/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"C:\Users\schen\eclipse-workspace/Roborioles2018/src" -IC:\Users\schen/wpilib/cpp/current/sim/include -I/usr/include -I/usr/include/gazebo-5.0 -I/usr/include/sdformat-2.3 -O0 -g3 -Wall -c -fmessage-length=0 -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


