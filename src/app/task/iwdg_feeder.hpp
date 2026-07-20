// Task to blink the LED to indicate that the system is alive.
#pragma once

#include "bsp/board.hpp"
#include "bsp/iwdg.hpp"
#include "rtos/rtos.hpp"
#include "rtos/task.hpp"


namespace task {

class IwdgFeeder : public rtos::Task {
public:
    IwdgFeeder(bsp::Iwdg& iwdg, rtos::TaskPriority priority, size_t stackSize = rtos::MIN_STACK_SIZE)
        : Task{priority, stackSize}, m_iwdg{iwdg} {}

protected:
    void runner() override {
        while (true) {
            m_iwdg.feed();
            rtos::yield();
        }
    }

    rtos::TaskName name() const override {
        return "IWDG_FEEDER";
    }

private:
    bsp::Iwdg& m_iwdg;
};

}
