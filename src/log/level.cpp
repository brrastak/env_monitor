#include "level.hpp"

namespace {
    static logging::Level log_level = logging::Level::Default;
}

namespace logging {

void set_level(Level new_level){
    log_level = new_level;
}

Level get_level(){
    return log_level;
}

}
