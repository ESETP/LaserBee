################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.2.3/Device/EFM8LB1/peripheral_driver/src/spi_0.c 

OBJS += \
./lib/efm8lb1/peripheralDrivers/src/spi_0.OBJ 


# Each subdirectory must supply rules for building sources it contributes
lib/efm8lb1/peripheralDrivers/src/spi_0.OBJ: C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.2.3/Device/EFM8LB1/peripheral_driver/src/spi_0.c
	@echo 'Building file: $<'
	@echo 'Invoking: Keil 8051 Compiler'
	C51 "@$(patsubst %.OBJ,%.__i,$@)" || $(RC)
	@echo 'Finished building: $<'
	@echo ' '

lib/efm8lb1/peripheralDrivers/src/spi_0.OBJ: C:/Users/markh/OneDrive/Documents/Uni/4th\ Year/Eng/EE4/LaserBee/LaserBeeAudio/inc/config/efm8_config.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.2.3/Device/EFM8LB1/inc/SI_EFM8LB1_Register_Enums.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.2.3/Device/EFM8LB1/peripheral_driver/inc/spi_0.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.2.3/Device/EFM8LB1/inc/SI_EFM8LB1_Defs.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.2.3/Device/shared/si8051Base/si_toolchain.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.2.3/Device/shared/si8051Base/stdint.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.2.3/Device/shared/si8051Base/stdbool.h


