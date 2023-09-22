/*!****************************************************************************
 * @file
 * hw_irq.c
 * 
 * @brief
 * Hardware Layer - Interrupts
 * 
 * @date  22.09.2023
 ******************************************************************************/

/*- Header files -------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include "hw_irq.h"


/*!****************************************************************************
 * @brief
 * Configure interrupt priorities
 * 
 * @date  22.09.2023
 ******************************************************************************/
void vHW_IrqInit(void)
{
  HAL_NVIC_SetPriority(USB_LP_IRQn, 1, 0);
}

/*!****************************************************************************
 * @brief
 * Set USB interrupt enable state
 *
 * @date  22.09.2023
 ******************************************************************************/
void vHW_IrqSetUsb(bool bEnable)
{
  if (bEnable) HAL_NVIC_EnableIRQ(USB_LP_IRQn);
  else         HAL_NVIC_DisableIRQ(USB_LP_IRQn);
}