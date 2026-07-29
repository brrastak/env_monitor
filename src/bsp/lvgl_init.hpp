#pragma once

#include "FreeRTOS.h"
#include "task.h"
#include "log/log.hpp"
#include "log/log_lvgl.hpp" 
#include "lvgl.h"
#include "rtos/timer.hpp"
#include "etl/chrono.h"

namespace {

uint32_t get_millis() {
    return pdTICKS_TO_MS(xTaskGetTickCount());
}

void timer_handler(TimerHandle_t) {
    lv_timer_handler();
}

}

namespace bsp::lvgl {

using namespace etl::chrono_literals;

void init() {

    // Register LVGL log callback
    lv_log_register_print_cb(log_lvgl);

    lv_init();

    // Register function to get ticks passed
    lv_tick_set_cb(get_millis);

    // Start periodical run of LVGL timer handler
    rtos::timer::start(5_ms, timer_handler);
}

}
