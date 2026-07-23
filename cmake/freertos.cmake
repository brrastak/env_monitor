add_library(freertos_config INTERFACE)
target_include_directories(freertos_config SYSTEM
    INTERFACE
        ${PROJECT_SOURCE_DIR}/config
)

set( FREERTOS_HEAP "4" CACHE STRING "" FORCE)

# Select the native compile PORT
set( FREERTOS_PORT "GCC_ARM_CM4F" CACHE STRING "" FORCE)

add_subdirectory(${PROJECT_SOURCE_DIR}/external/freertos/FreeRTOS/Source)
