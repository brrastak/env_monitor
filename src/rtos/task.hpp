#pragma once

#include "FreeRTOS.h"
#include "task.h"
#include "rtos.hpp"
#include "etl/string.h"

namespace rtos {

/// @brief Base class for tasks. Inherit from this class and implement the runner() method to create a task.
class Task {
public:
    Task(TaskPriority priority, size_t stackSize = MIN_STACK_SIZE) {

        // Scheduler will call TaskBase::entry(this) === this->runner() when the task is started.
        // All the task parameters should be passed to the constructor of the derived class
        // to be used in the runner() function.
        xTaskCreate(reinterpret_cast<TaskFunction_t>(entry), name().c_str(), stackSize, this, static_cast<UBaseType_t>(priority), nullptr);
    }

    virtual void runner() = 0;

    virtual TaskName name() const {
        return "TASK";
    }

private:
    static void entry(void* arg) {
        auto* task = static_cast<Task*>(arg);
        task->runner();

        // If runner() ever returns, delete the FreeRTOS task.
        vTaskDelete(nullptr);
    }
};

}
