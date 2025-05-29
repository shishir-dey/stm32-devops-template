#!/bin/bash

# Define the name of the build directories for host and target builds
HOST_BUILD_DIR="cmake-host-build-debug"
TARGET_BUILD_DIR="cmake-target-build-debug"

# Check if the host build directory exists and remove it
if [ -d "$HOST_BUILD_DIR" ]; then
    echo "Emptying existing host build directory: $HOST_BUILD_DIR"
    rm -rf "$HOST_BUILD_DIR"
fi

# Create the host build directory
mkdir "$HOST_BUILD_DIR"
cd "$HOST_BUILD_DIR"

# Run CMake to configure the build for the host environment
cmake .. -DHOST=True

# Execute the make command to build the project
make

# Change back to the previous directory
cd ..

# Run tests using CTest in the host build directory
ctest --test-dir "$HOST_BUILD_DIR"

# Check if the target build directory exists and remove it
if [ -d "$TARGET_BUILD_DIR" ]; then
    echo "Emptying existing target build directory: $TARGET_BUILD_DIR"
    rm -rf "$TARGET_BUILD_DIR"
fi

# Create the target build directory
mkdir "$TARGET_BUILD_DIR"
cd "$TARGET_BUILD_DIR"

# Run CMake to configure the build for the target environment
cmake .. -DCMAKE_TOOLCHAIN_FILE=../cmake/arm-none-eabi-gcc.cmake

# Execute the make command to build the project for the target architecture
make

# Change back to the previous directory
cd ..
