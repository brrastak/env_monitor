cmake_minimum_required(VERSION 3.22)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
project(env_monitor)

enable_language(CXX C ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(MCU_OPTIONS
    -mcpu=cortex-m4
    -mthumb
)

add_compile_options(
    ${MCU_OPTIONS}
    -MMD -MP
    -Wall -Wextra -Wpedantic
    -g
    -ffunction-sections -fdata-sections
)

add_link_options(
    ${MCU_OPTIONS}
    -T${CMAKE_SOURCE_DIR}/STM32F401XX_FLASH.ld
    -Wl,--gc-sections
    --specs=nano.specs
    --specs=nosys.specs
    -Wl,--cref,-Map=${PROJECT_NAME}.map
)

set(EXECUTABLE ${PROJECT_NAME}.elf)

add_executable(${EXECUTABLE}
    src/app/main.cpp
    src/bsp/board.cpp
    src/bsp/led.cpp

    src/platform/syscalls.c
    src/platform/cube_generated_init.c
    src/platform/startup_stm32f401xc.s
    src/platform/stm32f4xx_hal_msp.c
    src/log/print_rtt.cpp
)

# C++ only options
target_compile_options(${EXECUTABLE} PRIVATE
    $<$<COMPILE_LANGUAGE:CXX>:
        -fno-use-cxa-atexit
        -fno-exceptions
        -fno-unwind-tables
    >
)

target_include_directories(${EXECUTABLE}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/config
)

set(HAL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/stm32f4xx-hal-driver)
include(cmake/stm32_hal.cmake)
target_link_libraries(${EXECUTABLE}
    PRIVATE
        hal
)

set(RTT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/rtt)
include(cmake/rtt.cmake)
target_link_libraries(${EXECUTABLE}
    PRIVATE
        rtt
)

add_subdirectory(external/etl)
target_link_libraries(${EXECUTABLE}
    PRIVATE
        etl::etl
)

find_program(CMAKE_SIZE_UTIL arm-none-eabi-size)
find_program(CMAKE_OBJCOPY arm-none-eabi-objcopy)
# message(STATUS "CMAKE_SIZE_UTIL='${CMAKE_SIZE_UTIL}'")
# message(STATUS "CMAKE_OBJCOPY='${CMAKE_OBJCOPY}'")

add_custom_command(TARGET ${EXECUTABLE}
    POST_BUILD
    COMMAND ${CMAKE_SIZE_UTIL} ${EXECUTABLE}
)

add_custom_command(TARGET ${EXECUTABLE}
    POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex ${EXECUTABLE} ${PROJECT_NAME}.hex
    COMMAND ${CMAKE_OBJCOPY} -O binary ${EXECUTABLE} ${PROJECT_NAME}.bin
)


# # Specify source files
# set(SOURCES
#     src/main.c
#     src/stm32f4xx_hal.c
#     src/system_stm32f4xx.c
# )

# # Include directories
# include_directories(
#     ${CMAKE_SOURCE_DIR}/include
#     ${CMAKE_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Inc
# )

# # Create the executable
# add_executable(${PROJECT_NAME}.elf ${SOURCES})

# # Linker options for embedded
# target_link_options(${PROJECT_NAME}.elf PRIVATE
#     "-T${CMAKE_SOURCE_DIR}/STM32F407VG_FLASH.ld"
# )

# # Compiler options for embedded
# target_compile_options(${PROJECT_NAME}.elf PRIVATE
#     -mcpu=${TARGET_ARM_MCU}
#     -mthumb
#     -O2
# )

# # Include FreeRTOS headers
# include_directories(${CMAKE_SOURCE_DIR}/FreeRTOS/Source/include)

# # Add FreeRTOS source files
# set(FREERTOS_SOURCES
#     FreeRTOS/Source/portable/MemMang/heap_4.c
#     FreeRTOS/Source/portable/GCC/ARM_CM4F/port.c
#     FreeRTOS/Source/tasks.c
# )

# # Add FreeRTOS to your target
# target_sources(${PROJECT_NAME}.elf PRIVATE ${FREERTOS_SOURCES})

# add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
#  COMMAND ${CMAKE_OBJCOPY} -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.bin
#  COMMENT "Generating binary file"
# )
