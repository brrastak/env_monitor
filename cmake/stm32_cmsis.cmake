add_library(cmsis STATIC
    ${CMSIS_DIR}/Source/Templates/system_stm32f4xx.c
)

target_include_directories(cmsis SYSTEM PUBLIC
    ${CMSIS_DIR}/Include
)

target_compile_definitions(cmsis PUBLIC
    STM32F401xC
)

set(CORE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/cmsis-core)
include(${CMAKE_CURRENT_LIST_DIR}/stm32_core.cmake)

target_link_libraries(cmsis
    PUBLIC
        core
)
