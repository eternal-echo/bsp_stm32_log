cmake_minimum_required(VERSION 3.22)

#
# This file is generated only once,
# and is not re-generated if converter is called multiple times.
#
# User is free to modify the file as much as necessary
#

# Setup compiler settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)


# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Set the project name
set(CMAKE_PROJECT_NAME mpu6050)

# Include toolchain file
include("cmake/gcc-arm-none-eabi.cmake")

# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Enable CMake support for ASM and C languages
enable_language(C ASM)

# Core project settings
project(${CMAKE_PROJECT_NAME})
message("Build type: " ${CMAKE_BUILD_TYPE})

# Create an executable object type
add_executable(${CMAKE_PROJECT_NAME})

# Add STM32CubeMX generated sources
add_subdirectory(cmake/stm32cubemx)

# Link directories setup
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined library search paths
)

# Add sources to executable
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user sources here

    # APP
    APP/imu_demo.c

    # BSP
    BSP/mpu6050/src/driver_mpu6050.c
    BSP/mpu6050/interface/driver_mpu6050_interface.c
    BSP/mpu6050/interface/iic.c
    BSP/mpu6050/example/driver_mpu6050_basic.c
    BSP/mpu6050/example/driver_mpu6050_dmp.c
    BSP/mpu6050/example/driver_mpu6050_fifo.c    

    # Middlewares
    ## easylogger
    Middlewares/easylogger/src/elog.c
    Middlewares/easylogger/src/elog_utils.c
    Middlewares/easylogger/port/elog_port.c

    # Utils
    Utils/delay.c
)

# Add include paths
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined include paths

    # BSP
    BSP/mpu6050/src
    BSP/mpu6050/interface
    BSP/mpu6050/example

    # Middlewares
    ## EasyLogger include paths
    Middlewares/easylogger/inc

    # Utils
    Utils
)

# Add project symbols (macros)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined symbols
)

# Add linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME}
    stm32cubemx

    # Add user defined libraries
)
