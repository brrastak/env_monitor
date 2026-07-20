#include "board.hpp" 
#include "iwdg.hpp"
#include "platform/cube_generated_init.h"

namespace bsp {

using namespace etl::chrono_literals;

Board::Board()
    : led{GPIOC, GPIO_PIN_13}, iwdg{500_ms} {

    HAL_Init();

    SystemClock_Config();

    MX_GPIO_Init();
    MX_I2C1_Init();
    MX_SPI2_Init();
    MX_TIM3_Init();
}

}
