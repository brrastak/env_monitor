#include "board.hpp" 
#include "platform/cube_generated_init.h"

namespace bsp {

Board::Board()
    : led{GPIOC, GPIO_PIN_13} {

    HAL_Init();

    SystemClock_Config();

    MX_GPIO_Init();
    MX_I2C1_Init();
    MX_SPI2_Init();
    MX_TIM3_Init();
    MX_IWDG_Init();
}

}
