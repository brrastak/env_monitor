// Task to monitor the heap usage of tasks in the system
#pragma once

#include "rtos/rtos.hpp"
#include "rtos/task.hpp"
#include "log/log.hpp"
#include "etl/chrono.h"
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "lvgl.h"


using namespace etl::chrono_literals;

namespace task {

class HeapMonitor : public rtos::Task {
public:
    static void create(rtos::TaskPriority priority, size_t stack_size = rtos::MIN_STACK_SIZE) {
        static HeapMonitor instance{};
        instance.init(priority, stack_size);
    }

protected:
    void runner() override {
        while (true) {

            HeapStats_t heap_stats;
            vPortGetHeapStats(&heap_stats);

            lv_mem_monitor_t mem_monitor;
            lv_mem_monitor(&mem_monitor);

            logging::debug("FreeRTOS: free {}/{} bytes, fragmentation {}%\n"
                           "LVGL: free {}/{} bytes, fragmentation {}%",
                heap_stats.xAvailableHeapSpaceInBytes,
                configTOTAL_HEAP_SIZE,
                100 - (heap_stats.xSizeOfLargestFreeBlockInBytes * 100 / heap_stats.xAvailableHeapSpaceInBytes),
                mem_monitor.free_size,
                mem_monitor.total_size,
                static_cast<int>(mem_monitor.frag_pct)
            );

            rtos::delay(20_s);
        }
    }

    rtos::TaskName name() const override {
        return "HEAP_MONITOR";
    }

private:
    HeapMonitor() : rtos::Task{} {}
};

}
