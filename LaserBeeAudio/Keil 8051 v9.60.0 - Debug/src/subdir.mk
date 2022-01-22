################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
A51_UPPER_SRCS += \
C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.2.3/Device/shared/si8051Base/SILABS_STARTUP.A51 

C_SRCS += \
../src/InitDevice.c \
../src/function_generator.c \
../src/main.c 

OBJS += \
./src/InitDevice.OBJ \
./src/SILABS_STARTUP.OBJ \
./src/function_generator.OBJ \
./src/main.OBJ 


# Each subdirectory must supply rules for building sources it contributes
src/%.OBJ: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Keil 8051 Compiler'
	C51 "@$(patsubst %.OBJ,%.__i,$@)" || $(RC)
	@echo 'Finished building: $<'
	@echo ' '

src/InitDevice.OBJ: C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.2.3/Device/EFM8LB1/inc/SI_EFM8LB1_Register_Enums.h C:/Users/markh/OneDrive/Documents/Uni/4th\ Year/Eng/EE4/LaserBee/LaserBeeAudio/inc/InitDevice.h C:/Users/markh/OneDrive/Documents/Uni/4th\ Year/Eng/EE4/LaserBee/LaserBeeAudio/inc/function_generator.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.2.3/Device/EFM8LB1/inc/SI_EFM8LB1_Defs.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.2.3/Device/shared/si8051Base/si_toolchain.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.2.3/Device/shared/si8051Base/stdint.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.2.3/Device/shared/si8051Base/stdbool.h

src/SILABS_STARTUP.OBJ: C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.2.3/Device/shared/si8051Base/SILABS_STARTUP.A51
	@echo 'Building file: $<'
	@echo 'Invoking: Keil 8051 Assembler'
	AX51 "@$(patsubst %.OBJ,%.__ia,$@)" || $(RC)
	@echo 'Finished building: $<'
	@echo ' '

src/function_generator.OBJ: C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.2.3/kits/common/bsp/bsp.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.2.3/kits/common/drivers/efm8_memory_lcd/inc/tick.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.2.3/kits/common/drivers/efm8_memory_lcd/inc/render.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.2.3/kits/common/drivers/efm8_joystick/joystick.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.2.3/kits/common/drivers/efm8_memory_lcd/inc/graphics/thinfont.h C:/Users/markh/OneDrive/Documents/Uni/4th\ Year/Eng/EE4/LaserBee/LaserBeeAudio/inc/function_generator.h C:/Users/markh/OneDrive/Documents/Uni/4th\ Year/Eng/EE4/LaserBee/LaserBeeAudio/inc/graphics/sine.h C:/Users/markh/OneDrive/Documents/Uni/4th\ Year/Eng/EE4/LaserBee/LaserBeeAudio/inc/graphics/square.h C:/Users/markh/OneDrive/Documents/Uni/4th\ Year/Eng/EE4/LaserBee/LaserBeeAudio/inc/graphics/triangle.h C:/Users/markh/OneDrive/Documents/Uni/4th\ Year/Eng/EE4/LaserBee/LaserBeeAudio/inc/graphics/sawtooth.h C:/Users/markh/OneDrive/Documents/Uni/4th\ Year/Eng/EE4/LaserBee/LaserBeeAudio/inc/graphics/windowed_sine.h C:/Users/markh/OneDrive/Documents/Uni/4th\ Year/Eng/EE4/LaserBee/LaserBeeAudio/inc/graphics/nav_up.h C:/Users/markh/OneDrive/Documents/Uni/4th\ Year/Eng/EE4/LaserBee/LaserBeeAudio/inc/graphics/nav_down.h C:/Users/markh/OneDrive/Documents/Uni/4th\ Year/Eng/EE4/LaserBee/LaserBeeAudio/inc/graphics/nav_left.h C:/Users/markh/OneDrive/Documents/Uni/4th\ Year/Eng/EE4/LaserBee/LaserBeeAudio/inc/graphics/nav_right.h C:/Users/markh/OneDrive/Documents/Uni/4th\ Year/Eng/EE4/LaserBee/LaserBeeAudio/inc/waveform_tables.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.2.3/kits/common/drivers/efm8_retargetserial/retargetserial.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.2.3/kits/EFM8LB1_SLSTK2030A/config/bsp_config.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.2.3/kits/common/drivers/efm8_memory_lcd/inc/config/render_config.h C:/Users/markh/OneDrive/Documents/Uni/4th\ Year/Eng/EE4/LaserBee/LaserBeeAudio/inc/config/joystick_config.h C:/SiliconLabs/SimplicityStudio/v5/developer/toolchains/keil_8051/9.60/INC/STDIO.H C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.2.3/Device/EFM8LB1/inc/SI_EFM8LB1_Register_Enums.h C:/Users/markh/OneDrive/Documents/Uni/4th\ Year/Eng/EE4/LaserBee/LaserBeeAudio/inc/config/memory_lcd_config.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.2.3/Device/EFM8LB1/inc/SI_EFM8LB1_Defs.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.2.3/Device/shared/si8051Base/si_toolchain.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.2.3/Device/shared/si8051Base/stdint.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.2.3/Device/shared/si8051Base/stdbool.h

src/main.OBJ: C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.2.3/kits/common/bsp/bsp.h C:/Users/markh/OneDrive/Documents/Uni/4th\ Year/Eng/EE4/LaserBee/LaserBeeAudio/inc/InitDevice.h C:/Users/markh/OneDrive/Documents/Uni/4th\ Year/Eng/EE4/LaserBee/LaserBeeAudio/inc/function_generator.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.2.3/kits/EFM8LB1_SLSTK2030A/config/bsp_config.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.2.3/Device/EFM8LB1/inc/SI_EFM8LB1_Register_Enums.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.2.3/Device/EFM8LB1/inc/SI_EFM8LB1_Defs.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.2.3/Device/shared/si8051Base/si_toolchain.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.2.3/Device/shared/si8051Base/stdint.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.2.3/Device/shared/si8051Base/stdbool.h


