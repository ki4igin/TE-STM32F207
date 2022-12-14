
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "lwip.h"
#include "tim.h"
#include "gpio.h"

#include "udp_c.h"
#include "tcp_server.h"
#include "leds.h"

/* Private includes ----------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/
struct pac {
    const uint32_t id;
    uint32_t cnt;
    uint32_t tmp;
    uint8_t data[60 * 8 * 3 / 4];
    uint32_t end;
};

struct pac pac_adc_vibr = {
    1,
    0,
    0,
    {0},
    0xFFFFFFFF};

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* Private user code ---------------------------------------------------------*/

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
    /* MCU Configuration--------------------------------------------------------*/

    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();

    /* Configure the system clock */
    SystemClock_Config();

    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    MX_LWIP_Init();
    MX_TIM6_Init();

    echo_init();

    // udp_client_connect();
    // LL_mDelay(1000);
    // uint8_t test_str[] = "Hello\n";
    // udp_client_send(test_str, sizeof(test_str));
    // LL_mDelay(1000);
    // led_off();
    // MX_LWIP_Process();
    // LL_mDelay(1000);
    LL_TIM_ClearFlag_UPDATE(TIM6);
    // // LL_TIM_EnableIT_UPDATE(TIM6);
    LL_TIM_EnableCounter(TIM6);

    /* Infinite loop */

    while (1) {
        static uint16_t cnt;
        if (LL_TIM_IsActiveFlag_UPDATE(TIM6)) {
            LL_TIM_ClearFlag_UPDATE(TIM6);
            pac_adc_vibr.cnt++;
            // udp_client_send(&pac_adc_vibr, sizeof(pac_adc_vibr));
            tcp_server_send(&pac_adc_vibr, sizeof(pac_adc_vibr));
        }

        MX_LWIP_Process();

        if (++cnt == 0) {
        }
    }
}

void tim6_update_callback(void)
{
    pac_adc_vibr.cnt++;
    udp_client_send(&pac_adc_vibr, sizeof(pac_adc_vibr));
    // MX_LWIP_Process();
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void)
{
    LL_FLASH_SetLatency(LL_FLASH_LATENCY_3);
    while (LL_FLASH_GetLatency() != LL_FLASH_LATENCY_3) {
    }
    LL_RCC_HSE_Enable();

    /* Wait till HSE is ready */
    while (LL_RCC_HSE_IsReady() != 1) {
    }
    LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_20, 192, LL_RCC_PLLP_DIV_2);
    LL_RCC_PLL_Enable();

    /* Wait till PLL is ready */
    while (LL_RCC_PLL_IsReady() != 1) {
    }
    LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
    LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_4);
    LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_2);
    LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);

    /* Wait till System clock is ready */
    while (LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL) {
    }
    LL_SetSystemCoreClock(120000000);

    /* Update the time base */
    if (HAL_InitTick(TICK_INT_PRIORITY) != HAL_OK) {
        Error_Handler();
    }
}

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{
    /* User can add his own implementation to report the HAL error return state */
    __disable_irq();
    while (1) {
    }
}

#ifdef USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
}
#endif /* USE_FULL_ASSERT */
