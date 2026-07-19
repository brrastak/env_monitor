#include "bsp/board.hpp"
#include "stm32f4xx_hal.h"
#include "log/log.hpp"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "bsp/led.hpp"


static void heartbit_task(void* pvParameters);

int main() {

    logging::init();

    static auto board = bsp::Board();
    static auto led = board.led;
    static auto iwdg = board.iwdg;

    logging::info("Initialization completed");

    uint32_t sysClockFreq = HAL_RCC_GetSysClockFreq();
    logging::info("System clock frequency: {} Hz", sysClockFreq);

    xTaskCreate(heartbit_task, "Heartbit Task", 100, &led, 1, nullptr);

    vTaskStartScheduler();

    while (true) {
        
    }
}

static void heartbit_task(void* pvParameters) {
    
    bsp::Led* led = static_cast<bsp::Led*>(pvParameters);

    while (true) {
        vTaskDelay(pdMS_TO_TICKS(1000));
        led->blink();
        logging::info("Blink!");
    }
}
