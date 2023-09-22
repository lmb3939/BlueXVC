/*!****************************************************************************
 * @file
 * hw_clk.c
 * 
 * @brief
 * Hardware Layer - System Clock
 * 
 * @date  21.09.2023
 ******************************************************************************/

/*- Header files -------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include "hw_clk.h"


/*!****************************************************************************
 * @brief
 * Initialise System clock and Peripheral clock supply
 * 
 *             /1    72 MHz    72 MHz        72 MHz
 *     8 MHz   *9   PLLCLK    SYSCLK   /1   HCLK
 * HSE ---->[ PLL ]--+-->[SW]--->[AHBPRE]--+------------------------------> CPU
 *                   |                     |       9 MHz
 *                   |                     |       STKCLK
 *                   |                     +-->[/8]-------------------> SysTick
 *                   |                     |             36 MHz
 *                   |                     |      /2     PCLK1
 *                   |                     +-->[APB1PRE]-----------------> APB1
 *                   |                     |             72 MHz
 *                   |                     |      /1     PCLK2
 *                   |                     +-->[APB2PRE]-----------------> APB2
 *                   |           48 MHz
 *                   |    /1.5   USBCLK
 *                   +-->[USBPRE]-----------------------------------------> USB
 * 
 * @date  21.09.2023
 ******************************************************************************/
void vHW_ClkInit(void)
{
  /* Enable HSE and configure PLL                         */
  RCC_OscInitTypeDef sOscInit = {
    .OscillatorType = RCC_OSCILLATORTYPE_HSE,
    .HSEState = RCC_HSE_ON,
    .PLL.PLLState = RCC_PLL_ON,
    .PLL.PLLSource = RCC_PLLSOURCE_HSE,
    .PLL.PLLMUL = RCC_PLL_MUL9
  };
  HAL_RCC_OscConfig(&sOscInit);

  /* Configure SYSCLK and AHB/APB clock sources           */
  RCC_ClkInitTypeDef sClkInit = {
    .ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | \
                 RCC_CLOCKTYPE_PCLK1  | RCC_CLOCKTYPE_PCLK2,
    .SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK,
    .AHBCLKDivider = RCC_SYSCLK_DIV1,
    .APB1CLKDivider = RCC_HCLK_DIV2,
    .APB2CLKDivider = RCC_HCLK_DIV1
  };
  HAL_RCC_ClockConfig(&sClkInit, FLASH_LATENCY_2);

  /* Configure peripherals clock sources                  */
  RCC_PeriphCLKInitTypeDef sPeriphInit = {
    .PeriphClockSelection = RCC_PERIPHCLK_USB,
    .UsbClockSelection = RCC_USBCLKSOURCE_PLL_DIV1_5
  };
  HAL_RCCEx_PeriphCLKConfig(&sPeriphInit);

  /* Disable HSI, LSI                                     */
  __HAL_RCC_HSI_DISABLE();
  __HAL_RCC_LSI_DISABLE();
}