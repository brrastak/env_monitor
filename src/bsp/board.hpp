#pragma once

#include "led.hpp"
#include "iwdg.hpp"


namespace bsp {

class Board
{
public:
    Board();
    Led led();
    Iwdg iwdg();
};

}
