#Generated by VisualGDB (http://visualgdb.com)
#DO NOT EDIT THIS FILE MANUALLY UNLESS YOU ABSOLUTELY NEED TO
#USE VISUALGDB PROJECT PROPERTIES DIALOG INSTEAD

BINARYDIR := Release

#Additional flags
PREPROCESSOR_MACROS := NDEBUG=1 RELEASE=1 flash_layout STM32F103xE USE_FREERTOS
INCLUDE_DIRS := Inc Drivers\CMSIS\Device\ST\STM32F1xx\Include Drivers\STM32F1xx_HAL_Driver\Inc Middlewares\Third_Party\FreeRTOS\Source\include Middlewares\Third_Party\FreeRTOS\Source\CMSIS_RTOS Middlewares\Third_Party\FreeRTOS\Source\portable\GCC\ARM_CM3 Drivers\STM32F1xx_HAL_Driver\Inc\Legacy Drivers\STM32F1xx_HAL_Driver\Src Drivers/CMSIS/Device/ST/STM32F1xx/Include Drivers/CMSIS/Include Drivers/CMSIS/RTOS/Template Drivers/STM32F1xx_HAL_Driver/Inc Drivers/CMSIS/Include App ../delay ../sys
LIBRARY_DIRS := 
LIBRARY_NAMES := 
ADDITIONAL_LINKER_INPUTS := 
MACOS_FRAMEWORKS := 
LINUX_PACKAGES := 

CFLAGS := -ggdb -ffunction-sections -O3
CXXFLAGS := -ggdb -ffunction-sections -fno-exceptions -fno-rtti -O3
ASFLAGS := 
LDFLAGS := -Wl,-gc-sections
COMMONFLAGS := 
LINKER_SCRIPT := 

START_GROUP := -Wl,--start-group
END_GROUP := -Wl,--end-group

#Additional options detected from testing the toolchain
USE_DEL_TO_CLEAN := 1
CP_NOT_AVAILABLE := 1

ADDITIONAL_MAKE_FILES := stm32.mak
GENERATE_BIN_FILE := 1
GENERATE_IHEX_FILE := 1
GENERATE_MAP_FILE :=0
