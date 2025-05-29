cmake_minimum_required(VERSION 3.15.3)

project(stm32-devops-template)

message("HOST=${HOST}")

# Enable testing
enable_testing()

enable_language(C ASM)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

set(COMMON_SOURCES
        src/data/linked_list.c
        src/data/linked_list.h
        src/data/common_types.h
        src/data/queue.c
        src/data/queue.h
        src/data/circular_queue.c
        src/data/circular_queue.h
        src/data/priority_queue.c
        src/data/priority_queue.h
)

if( HOST )
        # Collect all test source files matching test/test_*.c
        file(GLOB TEST_SOURCES "test/test_*.c")

        # Loop over each test source file
        foreach(TEST_SOURCE ${TEST_SOURCES})

        # Get the file name without the directory and extension
        get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE)

        # Create an executable for each test
        add_executable(${TEST_NAME}
                ${TEST_SOURCE}
                ${COMMON_SOURCES}  # Common sources if needed
                lib/Unity/src/unity.c
        )

        # Set compile definitions if needed
        target_compile_definitions(${TEST_NAME} PRIVATE
        )

        # Include directories
        target_include_directories(${TEST_NAME} PRIVATE
                src/data
                lib/Unity/src
        )

        # Set compile options
        target_compile_options(${TEST_NAME} PRIVATE
                -Wall
                $<$<CONFIG:Debug>:-Og>
        )

        # Set link options if needed
        target_link_options(${TEST_NAME} PRIVATE
        )

        # Register the test with ctest
        add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})

        endforeach()
else() 
        set(TARGET_SOURCES
                src/main.c
                src/main.h
                src/autogen/startup_stm32f407xx.c
                src/autogen/syscalls.c
        )

        include(${CMAKE_SOURCE_DIR}/config/project_info.cmake)

        set(TARGET_EXECUTABLE
                ${PROJECT_NAME}_${ENVIRONMENT}_${CLIENT}_${FEATURE}_${FW_VERSION}.out
        )

        add_executable(${TARGET_EXECUTABLE}
                ${TARGET_SOURCES}
                ${COMMON_SOURCES}
        )

        target_compile_definitions(${TARGET_EXECUTABLE} PRIVATE
                -DSTM32F407xx
        )

        target_include_directories(${TARGET_EXECUTABLE} PRIVATE
                lib/linked_list
        )

        target_compile_options(${TARGET_EXECUTABLE} PRIVATE
                -mcpu=cortex-m4
                -mthumb
                -mfpu=fpv4-sp-d16
                -mfloat-abi=hard

                -fdata-sections
                -ffunction-sections

                -Wall

                $<$<CONFIG:Debug>:-Og>
        )

        target_link_options(${TARGET_EXECUTABLE} PRIVATE
                -T${CMAKE_SOURCE_DIR}/src/autogen/linker_script.ld
                -mcpu=cortex-m4
                -mthumb
                -mfpu=fpv4-sp-d16
                -mfloat-abi=hard
                -specs=nano.specs
                -lc
                -lm
                # -lnosys
                -Wl,-Map=${PROJECT_NAME}_${ENVIRONMENT}_${CLIENT}_${FEATURE}_${FW_VERSION}.map,--cref
                -Wl,--gc-sections
        )

        # Print executable size
        add_custom_command(TARGET ${TARGET_EXECUTABLE}
                POST_BUILD
                COMMAND arm-none-eabi-size ${TARGET_EXECUTABLE}
        )

        # Create hex file
        add_custom_command(TARGET ${TARGET_EXECUTABLE}
                POST_BUILD
                COMMAND arm-none-eabi-objcopy -O ihex ${TARGET_EXECUTABLE} ${PROJECT_NAME}_${ENVIRONMENT}_${CLIENT}_${FEATURE}_${FW_VERSION}.hex
                COMMAND arm-none-eabi-objcopy -O binary ${TARGET_EXECUTABLE} ${PROJECT_NAME}_${ENVIRONMENT}_${CLIENT}_${FEATURE}_${FW_VERSION}.bin
        )
endif()