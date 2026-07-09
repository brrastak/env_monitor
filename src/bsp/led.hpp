#pragma once

#include "stm32f4xx_hal.h"

namespace bsp
{

class Led
{
public:
    Led(GPIO_TypeDef* port, uint16_t pin);
    void on();
    void off();
    void blink();

private:
    GPIO_TypeDef* m_port;
    uint16_t m_pin;
};

}
