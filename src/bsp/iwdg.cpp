#include "iwdg.hpp"

namespace bsp {

Iwdg::Iwdg(etl::chrono::milliseconds timeout) : hiwdg{} {

    hiwdg.Instance = IWDG;
    // f = 32kHz / 32 = 1kHz
    hiwdg.Init.Prescaler = IWDG_PRESCALER_32;
    hiwdg.Init.Reload = timeout.count();
    HAL_IWDG_Init(&hiwdg);
}

void Iwdg::feed() {
    HAL_IWDG_Refresh(&hiwdg);
}

}
