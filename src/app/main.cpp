#include "bsp/board.hpp"
#include "stm32f4xx_hal.h"
#include "log/log.hpp"


int main() {

    logging::init();

    auto board = bsp::Board();
    auto led = board.led;
    auto iwdg = board.iwdg;

    logging::info("Initialization completed");

    while (true) {
        HAL_Delay(1000);
        iwdg.feed();
        led.blink();
        logging::info("Blink!");
    }
}
