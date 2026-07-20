/// FreeRTOS wrapper functions
#pragma once

#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"

using namespace etl::chrono_literals;

namespace rtos {

    enum class TaskPriority : UBaseType_t {
        Idle = tskIDLE_PRIORITY,
        Iwdg,
        Normal
    };

    using TaskName = etl::string<configMAX_TASK_NAME_LEN>;

    constexpr size_t MIN_STACK_SIZE = configMINIMAL_STACK_SIZE;

    namespace scheduler {

        inline void start() {
            vTaskStartScheduler();
        }

    }

    inline void yield() {
        taskYIELD();
    }

    inline void delay(etl::chrono::milliseconds timeout) {
        vTaskDelay(pdMS_TO_TICKS(timeout.count()));
    }
}
