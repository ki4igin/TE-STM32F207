/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usart.h
  * @brief   This file contains all the function prototypes for
  *          the usart.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USART_H__
#define __USART_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f2xx.h"

void MX_USART2_Init(void);

#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)\\\

void uart_send_str(USART_TypeDef *USARTx, uint8_t *str);
void uart_send_array(USART_TypeDef *USARTx, uint8_t *pbuf, uint8_t len);
void uart_send_byte(USART_TypeDef *USARTx, uint8_t data);


#ifdef __cplusplus
}
#endif

#endif /* __USART_H__ */

