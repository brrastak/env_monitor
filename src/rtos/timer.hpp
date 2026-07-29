#pragma once

#include "etl/chrono.h"
#include "log/log.hpp"
#include "FreeRTOS.h"
#include "timers.h"

namespace rtos {

namespace timer {

inline void start(etl::chrono::milliseconds timeout, TimerCallbackFunction_t callback) {

    int id = 1;
    auto handle = xTimerCreate("TIMER", pdMS_TO_TICKS(timeout.count()), pdTRUE, &id, callback);
    if (handle == NULL) {
        logging::error("Timer wasn't created");
    }
}

}

}
