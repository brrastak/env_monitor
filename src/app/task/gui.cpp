#include "log/log.hpp"
#include "log/log_lvgl.hpp" 
#include "lvgl.h"

#include "gui.hpp"

namespace task {

void Gui::runner() {
    // while (true) {
    //     rtos::yield();
    // }
}

Gui::Gui(rtos::TaskPriority priority, size_t stackSize)
    : Task{priority, stackSize} {

    // Register LVGL log callback
    lv_log_register_print_cb(log_lvgl);

    lv_init();
    logging::info("LVGL initialization completed");
}

}
