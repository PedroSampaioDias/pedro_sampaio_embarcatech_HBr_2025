# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.1)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.1.1)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(arquitetura_modular C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(arquitetura_modular app/main.c hal/hal_led.c drivers/led_embutido.c)

pico_set_program_name(arquitetura_modular "arquitetura_modular")
pico_set_program_version(arquitetura_modular "0.1")

# Generate PIO header
pico_generate_pio_header(arquitetura_modular ${CMAKE_CURRENT_LIST_DIR}/blink.pio)

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(arquitetura_modular 0)
pico_enable_stdio_usb(arquitetura_modular 0)

# Add the standard library to the build
target_link_libraries(arquitetura_modular pico_stdlib pico_cyw43_arch_none)

# Add the standard include files to the build
target_include_directories(arquitetura_modular PRIVATE ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/drivers ${CMAKE_CURRENT_SOURCE_DIR}/hal ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Add any user requested libraries
target_link_libraries(arquitetura_modular 
        hardware_spi
        hardware_i2c
        hardware_dma
        hardware_pio
        hardware_interp
        hardware_timer
        hardware_watchdog
        hardware_clocks
        )

pico_add_extra_outputs(arquitetura_modular)

