#include "board.hpp" 
#include "etl/chrono.h"
#include "platform/cube_generated_init.h"

namespace bsp {

using namespace etl::chrono_literals;

Board::Board() {

    HAL_Init();

    SystemClock_Config();

    MX_GPIO_Init();
    // For SCD41 sensor
    MX_I2C1_Init();
    MX_SPI2_Init();
    MX_TIM3_Init();
}

Led Board::led() {
    return Led{GPIOC, GPIO_PIN_13};
}

Iwdg Board::iwdg() {
    return Iwdg{500_ms};
}

Sensor Board::sensor() {
    return Sensor{};
}

}
