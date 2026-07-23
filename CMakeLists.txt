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
    -mfpu=fpv4-sp-d16
    -mfloat-abi=hard
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
    -Wl,--print-memory-usage
)

set(EXECUTABLE ${PROJECT_NAME}.elf)

add_executable(${EXECUTABLE}
    src/app/main.cpp

    src/bsp/board.cpp
    src/bsp/led.cpp
    src/bsp/iwdg.cpp
    src/bsp/sensor.cpp

    src/log/print_rtt.cpp

    src/platform/syscalls.c
    src/platform/cube_generated_init.c
    src/platform/startup_stm32f401xc.s
    src/platform/stm32f4xx_hal_msp.c
    src/platform/stm32f4xx_hal_timebase_tim.c
    src/platform/system_stm32f4xx.c
    src/platform/stm32f4xx_it.c
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
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/config
        ${PROJECT_SOURCE_DIR}/rtos
)

include(cmake/dependencies.cmake)
target_link_libraries(${EXECUTABLE}
    PRIVATE
        hal
        rtt
        etl::etl
        freertos_kernel
        sensirion
        lvgl
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
