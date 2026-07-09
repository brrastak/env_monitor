add_library(hal STATIC
    ${HAL_DIR}/Src/stm32f4xx_hal.c
    ${HAL_DIR}/Src/stm32f4xx_hal_gpio.c
    ${HAL_DIR}/Src/stm32f4xx_hal_rcc.c
    ${HAL_DIR}/Src/stm32f4xx_hal_uart.c
    ${HAL_DIR}/Src/stm32f4xx_hal_i2c.c
    ${HAL_DIR}/Src/stm32f4xx_hal_iwdg.c
    ${HAL_DIR}/Src/stm32f4xx_hal_spi.c
    ${HAL_DIR}/Src/stm32f4xx_hal_tim.c
    ${HAL_DIR}/Src/stm32f4xx_hal_tim_ex.c
    ${HAL_DIR}/Src/stm32f4xx_hal_cortex.c
)

target_include_directories(hal
    SYSTEM PUBLIC
        ${HAL_DIR}/Inc

    PRIVATE
        ${CMAKE_SOURCE_DIR}/config
)

target_compile_definitions(hal PUBLIC
    USE_HAL_DRIVER
)

set(CMSIS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/cmsis-device-f4)
include(cmake/stm32_cmsis.cmake)

target_link_libraries(hal
    PUBLIC
        cmsis
)
