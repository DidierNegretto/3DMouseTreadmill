################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/Users/Didier/Desktop/EPFL/Secondo_master/SemesterProject2019/GITRepository/3DMouseTreadmill/Code\ STM32/mouseDriver.c \
/Users/Didier/Desktop/EPFL/Secondo_master/SemesterProject2019/GITRepository/3DMouseTreadmill/Code\ STM32/sensorDriver.c 

OBJS += \
./Code\ STM32/mouseDriver.o \
./Code\ STM32/sensorDriver.o 

C_DEPS += \
./Code\ STM32/mouseDriver.d \
./Code\ STM32/sensorDriver.d 


# Each subdirectory must supply rules for building sources it contributes
Code\ STM32/mouseDriver.o: /Users/Didier/Desktop/EPFL/Secondo_master/SemesterProject2019/GITRepository/3DMouseTreadmill/Code\ STM32/mouseDriver.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L476xx -DDEBUG -c -I../Drivers/CMSIS/Include -I"/Users/Didier/Desktop/EPFL/Secondo_master/SemesterProject2019/GITRepository/3DMouseTreadmill/MAVLink Library" -I../Core/Inc -I"/Users/Didier/Desktop/EPFL/Secondo_master/SemesterProject2019/GITRepository/3DMouseTreadmill/MAVLink Library/mouse" -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I"/Users/Didier/Desktop/EPFL/Secondo_master/SemesterProject2019/GITRepository/3DMouseTreadmill/Code STM32" -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -O1 -ffunction-sections -fdata-sections -Wall -Wextra -fstack-usage -MMD -MP -MF"Code STM32/mouseDriver.d" -MT"$@"  -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Code\ STM32/sensorDriver.o: /Users/Didier/Desktop/EPFL/Secondo_master/SemesterProject2019/GITRepository/3DMouseTreadmill/Code\ STM32/sensorDriver.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L476xx -DDEBUG -c -I../Drivers/CMSIS/Include -I"/Users/Didier/Desktop/EPFL/Secondo_master/SemesterProject2019/GITRepository/3DMouseTreadmill/MAVLink Library" -I../Core/Inc -I"/Users/Didier/Desktop/EPFL/Secondo_master/SemesterProject2019/GITRepository/3DMouseTreadmill/MAVLink Library/mouse" -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I"/Users/Didier/Desktop/EPFL/Secondo_master/SemesterProject2019/GITRepository/3DMouseTreadmill/Code STM32" -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -O1 -ffunction-sections -fdata-sections -Wall -Wextra -fstack-usage -MMD -MP -MF"Code STM32/sensorDriver.d" -MT"$@"  -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

