#pragma once

#include "led.hpp"
#include "iwdg.hpp"
#include "sensor.hpp"

namespace bsp {

class Board
{
public:
    Board();
    Led led();
    Iwdg iwdg();
    Sensor sensor();
};

}
