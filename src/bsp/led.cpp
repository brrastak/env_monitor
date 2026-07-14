#include "led.hpp"

namespace bsp {

Led::Led(GPIO_TypeDef* port, uint16_t pin)
    : m_port{port}, m_pin{pin} {
    // Initialize the GPIO pin for the LED
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin = m_pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(m_port, &GPIO_InitStruct);

    off();
}

void Led::on() {
    HAL_GPIO_WritePin(m_port, m_pin, GPIO_PIN_RESET);
}

void Led::off() {
    HAL_GPIO_WritePin(m_port, m_pin, GPIO_PIN_SET);
}

void Led::blink() {
    HAL_GPIO_TogglePin(m_port, m_pin);
}

}
