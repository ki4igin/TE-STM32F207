#ifndef __DEBUG_H
#define __DEBUG_H

#include "stdint.h"

#define error_handler() _error_handler(__FILE__, __LINE__)

void debug_printf(const char *fmt, ...);
void _error_handler(const char *file, uint32_t line);
void delay_ms(uint64_t delay);


#endif
