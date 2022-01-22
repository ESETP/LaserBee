################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.2.3/kits/common/drivers/efm8_joystick/joystick.c 

OBJS += \
./lib/bsp/efm8_joystick/joystick.OBJ 


# Each subdirectory must supply rules for building sources it contributes
lib/bsp/efm8_joystick/joystick.OBJ: C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.2.3/kits/common/drivers/efm8_joystick/joystick.c
	@echo 'Building file: $<'
	@echo 'Invoking: Keil 8051 Compiler'
	C51 "@$(patsubst %.OBJ,%.__i,$@)" || $(RC)
	@echo 'Finished building: $<'
	@echo ' '

lib/bsp/efm8_joystick/joystick.OBJ: C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.2.3/kits/common/bsp/bsp.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.2.3/kits/common/drivers/efm8_joystick/joystick.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.2.3/kits/EFM8LB1_SLSTK2030A/config/bsp_config.h C:/Users/markh/OneDrive/Documents/Uni/4th\ Year/Eng/EE4/LaserBee/LaserBeeAudio/inc/config/joystick_config.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.2.3/Device/EFM8LB1/inc/SI_EFM8LB1_Register_Enums.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.2.3/Device/EFM8LB1/inc/SI_EFM8LB1_Defs.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.2.3/Device/shared/si8051Base/si_toolchain.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.2.3/Device/shared/si8051Base/stdint.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.2.3/Device/shared/si8051Base/stdbool.h


