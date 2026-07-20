// Task to blink the LED to indicate that the system is alive.
#pragma once

#include "bsp/board.hpp"
#include "bsp/led.hpp"
#include "rtos/rtos.hpp"
#include "rtos/task.hpp"
#include "log/log.hpp"

using namespace etl::chrono_literals;

namespace task {

class Heartbit : public rtos::Task {
public:
    Heartbit(bsp::Led& led, rtos::TaskPriority priority, size_t stackSize = rtos::MIN_STACK_SIZE)
        : Task{priority, stackSize}, m_led{led} {}

protected:
    void runner() override {
        while (true) {
            rtos::delay(1000_ms);
            m_led.blink();
            logging::info("Blink!");
        }
    }

    rtos::TaskName name() const override {
        return "HEARTBIT";
    }

private:
    bsp::Led& m_led;
};

}
