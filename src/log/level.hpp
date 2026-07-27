#pragma once

namespace logging {

enum class Level {
    Trace,
    Debug,
    Info,
    Warn,
    Error,
    None,
    Default = Info
};

void set_level(Level new_level);
Level get_level();

}
