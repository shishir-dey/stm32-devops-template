@echo off
REM Turn off command echoing to make the output cleaner.

REM Define the name of the build directories for host and target builds.
set HOST_BUILD_DIR=cmake-host-build-debug
set TARGET_BUILD_DIR=cmake-target-build-debug

REM Check if the host build directory exists.
IF EXIST %HOST_BUILD_DIR% (
    REM If it exists, remove all files and subdirectories inside it.
    echo "Emptying existing host build directory: %HOST_BUILD_DIR%"
    rd /s /q %HOST_BUILD_DIR%
)

REM Create the host build directory (it will be empty after this).
mkdir %HOST_BUILD_DIR%
REM Change the current directory to the host build directory.
cd %HOST_BUILD_DIR%

REM Run CMake to configure the build for the host environment.
cmake .. -DHOST=True -G "MinGW Makefiles" 

REM Execute the make command to build the project using the generated makefiles.
mingw32-make

REM Change back to the previous directory (the original directory where the script was run).
cd ..

REM Run tests using CTest in the host build directory.
ctest --test-dir %HOST_BUILD_DIR%

REM Check if the target build directory exists.
IF EXIST %TARGET_BUILD_DIR% (
    REM If it exists, remove all files and subdirectories inside it.
    echo "Emptying existing target build directory: %TARGET_BUILD_DIR%"
    rd /s /q %TARGET_BUILD_DIR%
)

REM Create the target build directory for the target architecture.
mkdir %TARGET_BUILD_DIR%
REM Change the current directory to the target build directory.
cd %TARGET_BUILD_DIR%

REM Run CMake to configure the build for the target environment.
cmake .. -DCMAKE_TOOLCHAIN_FILE=../cmake/arm-none-eabi-gcc.cmake -G "MinGW Makefiles" 

REM Execute the make command to build the project for the target architecture.
mingw32-make

REM Change back to the previous directory after the target build is complete.
cd ..
