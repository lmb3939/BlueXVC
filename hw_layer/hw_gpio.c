/*!****************************************************************************
 * @file
 * hw_gpio.c
 * 
 * @brief
 * Hardware Layer - General Purpose I/O
 * 
 * @date  21.09.2023
 ******************************************************************************/

/*- Header files -------------------------------------------------------------*/
#include "hw_gpio.h"
#include "hw_iodef.h"


/*!****************************************************************************
 * @brief
 * Initialise GPIO
 * 
 * @date  21.09.2023
*******************************************************************************/
void vHW_GpioInit(void)
{
  /* Enable GPIOx peripheral clocks                       */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();

  /* LED                                                  */
  GPIO_InitTypeDef sInitLed = {
    .Mode = GPIO_MODE_OUTPUT_OD,
    .Pin = LED_PIN,
    .Pull = GPIO_NOPULL,
    .Speed = GPIO_SPEED_LOW
  };
  HAL_GPIO_Init(LED_PORT, &sInitLed);

  /* USB                                                  */
  GPIO_InitTypeDef sInitUsbData = {
    .Mode = GPIO_MODE_INPUT,
    .Pin = USB_DP_PIN | USB_DM_PIN,
    .Pull = GPIO_NOPULL,
    .Speed = GPIO_SPEED_LOW
  };
  HAL_GPIO_Init(USB_Dx_PORT, &sInitUsbData);
  GPIO_InitTypeDef sInitUsbPull = {
    .Mode = GPIO_MODE_OUTPUT_PP,
    .Pin = USB_PU_PIN,
    .Pull = GPIO_NOPULL,
    .Speed = GPIO_SPEED_LOW
  };
  HAL_GPIO_Init(USB_PU_PORT, &sInitUsbPull);
}

/*!****************************************************************************
 * @brief
 * Set LED state
 * 
 * @param[in] bEnable     LED state
 * @date  21.09.2023
 ******************************************************************************/
void vHW_GpioSetLed(bool bEnable)
{
  HAL_GPIO_WritePin(LED_PORT, LED_PIN, bEnable ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

/*!****************************************************************************
 * @brief
 * Toggle LED state 
 * 
 * @date  21.09.2023
 ******************************************************************************/
void vHW_GpioToggleLed(void)
{
  HAL_GPIO_TogglePin(LED_PORT, LED_PIN);
}

/*!****************************************************************************
 * @brief
 * Set USB Data Lines and D+ Pull-Up Resistor state
 * 
 * @param[in] bEnable     USB activation state
 * @date  21.09.2023
 ******************************************************************************/
void vHW_GpioSetUsb(bool bEnable)
{
  /* Configure data lines                                 */
  if (bEnable)
  {
    GPIO_InitTypeDef sUsbDataActive = {
      .Mode = GPIO_MODE_AF_PP,
      .Pin = USB_DP_PIN | USB_DM_PIN,
      .Pull = GPIO_NOPULL,
      .Speed = GPIO_SPEED_HIGH
    };
    HAL_GPIO_Init(USB_Dx_PORT, &sUsbDataActive);
  }
  else
  {
    HAL_GPIO_DeInit(USB_Dx_PORT, USB_DP_PIN | USB_DM_PIN);
  }

  /* Set Pull-up resistor state                           */
  HAL_GPIO_WritePin(USB_PU_PORT, USB_PU_PIN, bEnable ? GPIO_PIN_SET : GPIO_PIN_RESET);
}