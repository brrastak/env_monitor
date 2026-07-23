set(SENSIRION_DIR ${PROJECT_SOURCE_DIR}/lib/sensirion-i2c)

add_library(sensirion STATIC
    ${SENSIRION_DIR}/src/sensirion_i2c.c
    ${SENSIRION_DIR}/src/scd4x_i2c.c
    ${SENSIRION_DIR}/src/sensirion_common.c

    ${SENSIRION_DIR}/port/sensirion_i2c_hal.c
)

target_include_directories(sensirion SYSTEM PUBLIC
    ${SENSIRION_DIR}/src
    ${SENSIRION_DIR}/port
)

# Access to ST HAL functions to work with I2C
target_link_libraries(sensirion
    PRIVATE
        hal
)
