// Task to blink the LED to indicate that the system is alive.
#pragma once

#include "bsp/board.hpp"
#include "bsp/led.hpp"
#include "rtos/rtos.hpp"
#include "rtos/task.hpp"
#include "log/log.hpp"
#include "etl/chrono.h"

using namespace etl::chrono_literals;


namespace task {

class Heartbit : public rtos::Task {
public:
    static void create(bsp::Led& led, rtos::TaskPriority priority, size_t stack_size = rtos::MIN_STACK_SIZE) {
        static Heartbit instance{led};
        instance.init(priority, stack_size);
    }
    
protected:
    void runner() override {
        while (true) {
            rtos::delay(1000_ms);
            m_led.blink();
            logging::trace("Blink!");
        }
    }

    rtos::TaskName name() const override {
        return "HEARTBIT";
    }

private:
    Heartbit(bsp::Led& led)
        : Task{}, m_led{led} {}

    bsp::Led& m_led;
};

}
