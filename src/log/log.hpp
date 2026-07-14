#pragma once

#include "etl/print.h"
#include "SEGGER_RTT.h"

namespace logging {

    inline void init() {
        SEGGER_RTT_Init();
    }

    template <class... Args>
    void info(etl::format_string<Args...> fmt, Args&&... args) {
        
        etl::print("[INFO]: ");
        etl::println(etl::move(fmt), etl::forward<Args>(args)...);
    }

    template <class... Args>
    void error(etl::format_string<Args...> fmt, Args&&... args) {
        
        etl::print("[ERROR]: ");
        etl::println(etl::move(fmt), etl::forward<Args>(args)...);
    }
}
