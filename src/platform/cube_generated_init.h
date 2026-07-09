#pragma once

#include "stm32f4xx_hal.h"

#ifdef __cplusplus
extern "C" {
#endif
    void Error_Handler(void);
    void MX_I2C1_Init(void);
    void MX_GPIO_Init(void);
    void MX_SPI2_Init(void);
    void MX_TIM3_Init(void);
    void MX_IWDG_Init(void);
    void SystemClock_Config(void);
#ifdef __cplusplus
}
#endif
