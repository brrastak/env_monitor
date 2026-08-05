// Task to blink the LED to indicate that the system is alive.
#pragma once

#include "bsp/board.hpp"
#include "bsp/iwdg.hpp"
#include "rtos/rtos.hpp"
#include "rtos/task.hpp"


namespace task {

class IwdgFeeder : public rtos::Task {
public:
    static void create(bsp::Iwdg& iwdg, rtos::TaskPriority priority, size_t stack_size = rtos::MIN_STACK_SIZE) {
        static IwdgFeeder instance{iwdg};
        instance.init(priority, stack_size);
    }

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
    IwdgFeeder(bsp::Iwdg& iwdg)
        : Task{}, m_iwdg{iwdg} {}

    bsp::Iwdg& m_iwdg;
};

}
