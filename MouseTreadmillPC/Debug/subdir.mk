################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../mouseControl.cpp 

OBJS += \
./mouseControl.o 

CPP_DEPS += \
./mouseControl.d 


# Each subdirectory must supply rules for building sources it contributes
mouseControl.o: /Users/Didier/Desktop/EPFL/Secondo\ master/SemesterProject2019/GITRepository/3DMouseTreadmill/MouseTreadmillPC/mouseControl.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I"/Users/Didier/Desktop/EPFL/Secondo master/SemesterProject2019/GITRepository/3DMouseTreadmill/MAVLink Library/mouse" -I"/Users/Didier/Desktop/EPFL/Secondo master/SemesterProject2019/GITRepository/3DMouseTreadmill/MAVLink Library" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"mouseControl.d" -MT"mouseControl.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


