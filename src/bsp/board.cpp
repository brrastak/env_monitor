#include "lvgl_init.hpp"
#include "board.hpp"
#include "etl/chrono.h"
#include "etl/singleton.h"
#include "platform/cube_generated_init.h"
#include "platform/mpu.hpp"

namespace bsp {

using namespace etl::chrono_literals;

Board::Board() {

    HAL_Init();

    SystemClock_Config();

    init_mpu();

    MX_GPIO_Init();
    // For SCD41 sensor
    MX_I2C1_Init();
    MX_SPI2_Init();
    MX_TIM3_Init();

    lvgl::init();
}

Led& Board::led() {
    etl::singleton<Led>::create(GPIOC, GPIO_PIN_13);
    return etl::singleton<Led>::instance();
}

Iwdg& Board::iwdg() {
    etl::singleton<Iwdg>::create(500_ms);
    return etl::singleton<Iwdg>::instance();
}

Sensor& Board::sensor() {
    etl::singleton<Sensor>::create();
    return etl::singleton<Sensor>::instance();
}

}
