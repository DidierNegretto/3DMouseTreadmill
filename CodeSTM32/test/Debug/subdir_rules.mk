################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: "$<"'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -DTEST -I"/Users/Didier/Desktop/EPFL/Secondo_master/SemesterProject2019/GITRepository/3DMouseTreadmill/MAVLink Library/mouse" -I"/Users/Didier/Desktop/EPFL/Secondo_master/SemesterProject2019/GITRepository/3DMouseTreadmill/MAVLink Library" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


