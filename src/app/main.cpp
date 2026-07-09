#include "bsp/board.hpp"
#include "stm32f4xx_hal.h"


int main() {

    auto board = bsp::Board();
    auto led = board.led;

    while (true) {
        HAL_Delay(1000);
        led.blink();
    }
}
