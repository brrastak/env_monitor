// Task to control display.
#pragma once

#include "rtos/rtos.hpp"
#include "rtos/task.hpp"

namespace task {

class Gui : public rtos::Task {
public:
    static void create(rtos::TaskPriority priority, size_t stackSize = rtos::MIN_STACK_SIZE) {
        static Gui instance{priority, stackSize};
    }
    
protected:
    void runner() override;

    rtos::TaskName name() const override {
        return "GUI";
    }

private:
    Gui(rtos::TaskPriority priority, size_t stackSize);
};

}
