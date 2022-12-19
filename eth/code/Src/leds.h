#ifndef __LEDS_H
#define __LEDS_H

#include "stm32f2xx.h"
#include "gpio_def.h"
#include "stm32f2xx_ll_gpio.h"

__STATIC_INLINE void led_on(void)
{
    LL_GPIO_SetOutputPin(LED_GPIO_Port, LED_Pin);
}

__STATIC_INLINE void led_off(void)
{
    LL_GPIO_ResetOutputPin(LED_GPIO_Port, LED_Pin);
}

__STATIC_INLINE void led_toggle(void)
{
    LL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
}

#endif
