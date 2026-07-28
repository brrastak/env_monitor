#pragma once

#include "lvgl.h"
#include "SEGGER_RTT.h"

inline void log_lvgl(lv_log_level_t level, const char* message)
{
    SEGGER_RTT_printf(0, "%s", message);
}
