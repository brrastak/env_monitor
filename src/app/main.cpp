#include "bsp/board.hpp"
#include "log/log.hpp"
#include "rtos/rtos.hpp"
#include "task/heartbit.hpp"
#include "task/iwdg_feeder.hpp"
#include "task/sensor_reader.hpp"


int main() {

    logging::init();

    static auto board = bsp::Board();
    static auto led = board.led();
    static auto sensor = board.sensor();
    static auto iwdg = board.iwdg();

    logging::info("Initialization completed");

    static auto heartbit = task::Heartbit{led, rtos::TaskPriority::Normal};
    static auto sensor_reader = task::SensorReader{sensor, rtos::TaskPriority::Normal, 500};
    static auto iwdgFeeder = task::IwdgFeeder{iwdg, rtos::TaskPriority::Iwdg};

    rtos::scheduler::start();

    while (true) {

    }
}
