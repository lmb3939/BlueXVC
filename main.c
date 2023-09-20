/*!****************************************************************************
 * @brief
 * main.c
 * 
 * @brief
 * Main program entry point
 * 
 * @date  20.09.2023
 ******************************************************************************/

/*- Header files -------------------------------------------------------------*/
#include "stm32f1xx_hal.h"


/*!****************************************************************************
 * @brief
 * Main program entry point
 * 
 * @date  20.09.2023
 ******************************************************************************/
int main(void)
{
  // Initialise STM32 HAL
  HAL_Init();

  // Enable GPIOC
  __HAL_RCC_GPIOC_CLK_ENABLE();

  // Configure GPIO: PC13 (LED) as output
  GPIO_InitTypeDef sLedConf = {
    .Mode = GPIO_MODE_OUTPUT_OD,
    .Pin = GPIO_PIN_13,
    .Pull = GPIO_NOPULL,
    .Speed = GPIO_SPEED_FREQ_LOW
  };
  HAL_GPIO_Init(GPIOC, &sLedConf);

  // Endless loop: Blink LED
  while (1)
  {
    HAL_Delay(500u);
    HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
  }
}