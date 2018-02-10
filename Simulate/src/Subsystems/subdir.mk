################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Subsystems/DriveBase.cpp \
../src/Subsystems/IntakeSub.cpp 

OBJS += \
./src/Subsystems/DriveBase.o \
./src/Subsystems/IntakeSub.o 

CPP_DEPS += \
./src/Subsystems/DriveBase.d \
./src/Subsystems/IntakeSub.d 


# Each subdirectory must supply rules for building sources it contributes
src/Subsystems/%.o: ../src/Subsystems/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"C:\Users\schen\eclipse-workspace/Roborioles2018/src" -IC:\Users\schen/wpilib/cpp/current/sim/include -I/usr/include -I/usr/include/gazebo-5.0 -I/usr/include/sdformat-2.3 -O0 -g3 -Wall -c -fmessage-length=0 -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


