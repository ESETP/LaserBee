################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.2.3/Device/EFM8LB1/bsp/efm8_memory_lcd/spi.c \
C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.2.3/Device/EFM8LB1/bsp/efm8_memory_lcd/tick.c 

OBJS += \
./lib/efm8lb1/bsp/efm8_memory_lcd/src/spi.OBJ \
./lib/efm8lb1/bsp/efm8_memory_lcd/src/tick.OBJ 


# Each subdirectory must supply rules for building sources it contributes
lib/efm8lb1/bsp/efm8_memory_lcd/src/spi.OBJ: C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.2.3/Device/EFM8LB1/bsp/efm8_memory_lcd/spi.c
	@echo 'Building file: $<'
	@echo 'Invoking: Keil 8051 Compiler'
	C51 "@$(patsubst %.OBJ,%.__i,$@)" || $(RC)
	@echo 'Finished building: $<'
	@echo ' '

lib/efm8lb1/bsp/efm8_memory_lcd/src/spi.OBJ: C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.2.3/kits/common/bsp/bsp.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.2.3/kits/common/drivers/efm8_memory_lcd/inc/spi.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.2.3/Device/EFM8LB1/peripheral_driver/inc/spi_0.h C:/SiliconLabs/SimplicityStudio/v5/developer/toolchains/keil_8051/9.60/INC/STRING.H C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.2.3/kits/EFM8LB1_SLSTK2030A/config/bsp_config.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.2.3/kits/common/drivers/efm8_memory_lcd/inc/config/spi_config.h C:/Users/markh/OneDrive/Documents/Uni/4th\ Year/Eng/EE4/LaserBee/LaserBeeAudio/inc/config/efm8_config.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.2.3/Device/EFM8LB1/inc/SI_EFM8LB1_Register_Enums.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.2.3/kits/common/drivers/efm8_memory_lcd/inc/disp.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.2.3/Device/EFM8LB1/inc/SI_EFM8LB1_Defs.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.2.3/Device/shared/si8051Base/si_toolchain.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.2.3/Device/shared/si8051Base/stdint.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.2.3/Device/shared/si8051Base/stdbool.h

lib/efm8lb1/bsp/efm8_memory_lcd/src/tick.OBJ: C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.2.3/Device/EFM8LB1/bsp/efm8_memory_lcd/tick.c
	@echo 'Building file: $<'
	@echo 'Invoking: Keil 8051 Compiler'
	C51 "@$(patsubst %.OBJ,%.__i,$@)" || $(RC)
	@echo 'Finished building: $<'
	@echo ' '

lib/efm8lb1/bsp/efm8_memory_lcd/src/tick.OBJ: C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.2.3/kits/common/bsp/bsp.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.2.3/kits/common/drivers/efm8_memory_lcd/inc/tick.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.2.3/kits/EFM8LB1_SLSTK2030A/config/bsp_config.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.2.3/Device/EFM8LB1/inc/SI_EFM8LB1_Register_Enums.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.2.3/Device/EFM8LB1/inc/SI_EFM8LB1_Defs.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.2.3/Device/shared/si8051Base/si_toolchain.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.2.3/Device/shared/si8051Base/stdint.h C:/SiliconLabs/SimplicityStudio/v5/developer/sdks/8051/v4.2.3/Device/shared/si8051Base/stdbool.h


