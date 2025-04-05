# Generated CMake Pico project file

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

# Project name changed to KyberCore
project(KyberCore C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add all source files in the 'src' directory
file(GLOB SOURCES 
    src/*.cpp
)

# Add executable, name it KyberCore and point to the source files
add_executable(KyberCore ${SOURCES})

# Set the program name and version
pico_set_program_name(KyberCore "KyberCore")
pico_set_program_version(KyberCore "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(KyberCore 0)
pico_enable_stdio_usb(KyberCore 0)

# Add the standard library to the build
target_link_libraries(KyberCore
        pico_stdlib)

# Add include directory for header files
target_include_directories(KyberCore PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/include
)

# Add any user requested libraries
target_link_libraries(KyberCore 
        pico_cyw43_arch_none
        )

# Generate UF2 etc.
pico_add_extra_outputs(KyberCore)
