#include "bsp/board.hpp"
#include "log/log.hpp"
#include "rtos/rtos.hpp"
#include "task/heartbit.hpp"
#include "task/iwdg_feeder.hpp"
#include "task/sensor_reader.hpp"
#include "task/gui.hpp"
#include "task/heap_monitor.hpp"


int main() {

    logging::init();
    logging::set_level(logging::Level::Debug);

    static auto board = bsp::Board();
    auto& led = board.led();
    auto& sensor = board.sensor();
    auto& iwdg = board.iwdg();

    logging::debug("Initialization completed");

    task::Heartbit::create(led, rtos::TaskPriority::Normal, 1000);
    task::SensorReader::create(sensor, rtos::TaskPriority::Normal, 1000);
    task::HeapMonitor::create(rtos::TaskPriority::Normal, 1000);
    task::IwdgFeeder::create(iwdg, rtos::TaskPriority::Iwdg);
    // task::Gui::create(rtos::TaskPriority::Normal);

    rtos::scheduler::start();

    while (true) {

    }
}
