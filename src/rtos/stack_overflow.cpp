#include "log/log.hpp"
#include "FreeRTOS.h"
#include "task.h"


extern "C" void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName ){
    
    logging::error("Stack overflow in task: {}", pcTaskName);

    while (true) {}
}
