cmake_minimum_required(VERSION 3.15.3)

project(stm32-devops-template)

message("HOST=${HOST}")

enable_language(C ASM)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

set(COMMON_SOURCES
        lib/linked_list/linked_list.c
        lib/linked_list/linked_list.h
)

if( HOST )
        set(HOST_SOURCES
                test/test_linked_list.c
                lib/Unity/src/unity_internals.h
                lib/Unity/src/unity.h
                lib/Unity/src/unity.c
        )

        set(HOST_EXECUTABLE
                ${PROJECT_NAME}.out
        )

        add_executable(${HOST_EXECUTABLE}
                ${HOST_SOURCES}
                ${COMMON_SOURCES}
        )

        target_compile_definitions(${HOST_EXECUTABLE} PRIVATE
        )

        target_include_directories(${HOST_EXECUTABLE} PRIVATE
                lib/linked_list
                lib/Unity/src
        )

        target_compile_options(${HOST_EXECUTABLE} PRIVATE
                -Wall

                $<$<CONFIG:Debug>:-Og>
        )

        target_link_options(${HOST_EXECUTABLE} PRIVATE
        )
else() 
        set(TARGET_SOURCES
                src/main.c
                src/main.h
                src/startup_stm32f407xx.c
                src/syscalls.c
        )

        set(TARGET_EXECUTABLE
                ${PROJECT_NAME}.out
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
                -T${CMAKE_SOURCE_DIR}/src/linker_script.ld
                -mcpu=cortex-m4
                -mthumb
                -mfpu=fpv4-sp-d16
                -mfloat-abi=hard
                -specs=nano.specs
                -lc
                -lm
                # -lnosys
                -Wl,-Map=${PROJECT_NAME}.map,--cref
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
                COMMAND arm-none-eabi-objcopy -O ihex ${TARGET_EXECUTABLE} ${PROJECT_NAME}.hex
                COMMAND arm-none-eabi-objcopy -O binary ${TARGET_EXECUTABLE} ${PROJECT_NAME}.bin
        )
endif()