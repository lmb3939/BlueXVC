cmake_minimum_required(VERSION 3.20)

# Toolchain configuration
set(CMAKE_TOOLCHAIN_FILE $ENV{CMAKE_CONFIGS_PATH}/gcc-arm-none-eabi.cmake)

# Project configuration
project(BlueXVC)
set(EXECUTABLE ${PROJECT_NAME}.elf)
set(LINKER_FILE ${CMAKE_SOURCE_DIR}/Controller/STM32F1xx/linker_script_stm32f103xb.ld)

enable_language(C ASM)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# List of source files
file(GLOB_RECURSE SRC_FILES *.c *.S)
list(FILTER SRC_FILES EXCLUDE REGEX "build\/.*")
list(FILTER SRC_FILES EXCLUDE REGEX "Controller\/.*\/Template\/.*\.c")

# Build the executable based on the source files
add_executable(${EXECUTABLE} ${SRC_FILES})

# List of compiler defines, prefix with -D compiler option
target_compile_definitions(${EXECUTABLE} PRIVATE
        -DSTM32F103xB
)

# List of includ directories
target_include_directories(${EXECUTABLE} PRIVATE
        hw_layer
        Controller
        Controller/STM32F1xx
        Controller/STM32F1xx/Core
        Controller/STM32F1xx/Peripheral/inc
)

# Compiler options
target_compile_options(${EXECUTABLE} PRIVATE
        -march=armv7-m
        -mcpu=cortex-m3
        -mthumb

        -fdata-sections
        -ffunction-sections
        -nostartfiles

        -Wall
        -Wextra
        
        -Og
        -g
)

# Linker options
cmake_path(GET LINKER_FILE FILENAME LINKER_FILE_FILENAME)
cmake_path(REMOVE_FILENAME LINKER_FILE OUTPUT_VARIABLE LINKER_FILE_FOLDER)
target_link_options(${EXECUTABLE} PRIVATE
        -L${LINKER_FILE_FOLDER}
        -T${LINKER_FILE_FILENAME}

        -march=armv7-m
        -mcpu=cortex-m3
        -mthumb
        
        -specs=nano.specs
        -nostartfiles
        
        -lc
        -lm
        -lnosys
        
        -Wl,-Map=${PROJECT_NAME}.map,--cref
        -Wl,--gc-sections
        -Xlinker -print-memory-usage -Xlinker
)

# Optional: Print executable size as part of the post build process
add_custom_command(TARGET ${EXECUTABLE}
        POST_BUILD
        COMMAND ${CMAKE_SIZE_UTIL} ${EXECUTABLE}
)

# Optional: Create hex after the build
add_custom_command(TARGET ${EXECUTABLE}
        POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -O ihex ${EXECUTABLE} ${PROJECT_NAME}.hex
)