#include "bsp/board.hpp"
#include "log/log.hpp"
#include "rtos/rtos.hpp"
#include "task/heartbit.hpp"
#include "task/iwdg_feeder.hpp"
#include "task/sensor_reader.hpp"
#include "task/gui.hpp"


int main() {

    logging::init();

    static auto board = bsp::Board();
    static auto led = board.led();
    static auto sensor = board.sensor();
    static auto iwdg = board.iwdg();

    logging::info("HAL initialization completed");

    task::Heartbit::create(led, rtos::TaskPriority::Normal);
    task::SensorReader::create(sensor, rtos::TaskPriority::Normal, 500);
    task::IwdgFeeder::create(iwdg, rtos::TaskPriority::Iwdg);
    task::Gui::create(rtos::TaskPriority::Normal);

    rtos::scheduler::start();

    while (true) {

    }
}
