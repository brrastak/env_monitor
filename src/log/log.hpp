#pragma once

#include "etl/print.h"
#include "etl/string.h"
#include "SEGGER_RTT.h"
#include "level.hpp"

namespace logging {

inline void init() {
    SEGGER_RTT_Init();
}

}

namespace {

constexpr etl::string<5> level_name(logging::Level level)
{
    switch (level) {
        case logging::Level::Error: return "ERROR";
        case logging::Level::Warn:  return "WARN";
        case logging::Level::Info:  return "INFO";
        case logging::Level::Debug: return "DEBUG";
        case logging::Level::Trace: return "TRACE";
        default: return "";
    }
}

template <logging::Level MessageLevel, class... Args>
void log(etl::format_string<Args...> fmt, Args&&... args)
{
    if (MessageLevel < logging::get_level()) {
        return;
    }

    etl::print("[{}]: ", level_name(MessageLevel));
    etl::println(etl::move(fmt), etl::forward<Args>(args)...);
}

}

namespace logging {

template <class... Args>
void error(etl::format_string<Args...> fmt, Args&&... args)
{
    log<Level::Error>(etl::move(fmt), etl::forward<Args>(args)...);
}

template <class... Args>
void warn(etl::format_string<Args...> fmt, Args&&... args)
{
    log<Level::Warn>(etl::move(fmt), etl::forward<Args>(args)...);
}

template <class... Args>
void info(etl::format_string<Args...> fmt, Args&&... args)
{
    log<Level::Info>(etl::move(fmt), etl::forward<Args>(args)...);
}

template <class... Args>
void debug(etl::format_string<Args...> fmt, Args&&... args)
{
    log<Level::Debug>(etl::move(fmt), etl::forward<Args>(args)...);
}

template <class... Args>
void trace(etl::format_string<Args...> fmt, Args&&... args)
{
    log<Level::Trace>(etl::move(fmt), etl::forward<Args>(args)...);
}

}
