// Includes --------------------------------------------------------------------
#include "debug.h"
#include "leds.h"
#include "usart.h"
#include "stm32f2xx.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#define DEBUG_UART     USART2
#define DEBUG_BUF_SIZE 100

#ifdef DEBUG

char debug_buf[DEBUG_BUF_SIZE];

void debug_printf(const char *fmt, ...)
{
    va_list argp;
    va_start(argp, fmt);

    vsprintf(debug_buf, fmt, argp);
    uart_send_str(DEBUG_UART, (uint8_t *)debug_buf);

    va_end(argp);
}

#else
void debug_printf(const char *fmt, ...)
{
}

void DebugSendMessage(char *str)
{
    (void)str;
}

void DebugSendArray(void *pbuf, int len)
{
    (void)pbuf;
    (void)len;
}

void DebugSendWord(int data)
{
    (void)data;
}
#endif

void _error_handler(const char *file, uint32_t line)
{
    __disable_irq();
    debug_printf("Error: %s, %d", file, line);
    while (1) {
        delay_ms(300);
        led_toggle();
    }
}

void delay_ms(uint64_t delay)
{
    // __IO uint32_t temp = SysTick->CTRL;
    delay++;
    while (delay) {
        if (SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) {
            delay--;
        }
    }
}
