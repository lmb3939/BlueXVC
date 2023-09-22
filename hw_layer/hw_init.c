/*!****************************************************************************
 * @file
 * hw_init.c
 * 
 * @brief
 * Hardware Layer - Initialisation
 * 
 * @date  21.09.2023
 ******************************************************************************/

/*- Header files -------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include "hw_clk.h"
#include "hw_gpio.h"
#include "hw_irq.h"
#include "hw_init.h"


/*!****************************************************************************
 * @brief
 * Hardware Layer initialisation
 * 
 * @date  21.09.2023
 ******************************************************************************/
void vHW_Init(void)
{
  vHW_ClkInit();
  vHW_GpioInit();
  vHW_IrqInit();

  /* Initialise STM32 HAL                                 */
  HAL_Init();
}