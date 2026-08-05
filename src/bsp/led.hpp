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

    Led(const Led&) = delete;
    Led& operator=(const Led&) = delete;
    Led(Led&&) = delete;
    Led& operator=(Led&&) = delete;
};

}
