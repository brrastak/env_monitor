// Independent Watchdog (IWDG)
#pragma once

#include "stm32f4xx_hal.h"
#include "etl/chrono.h"

namespace bsp {

class Iwdg
{
public:
    Iwdg(etl::chrono::milliseconds timeout);
    void feed();

private:
    IWDG_HandleTypeDef hiwdg;
};

}
