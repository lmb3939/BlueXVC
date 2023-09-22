/*!****************************************************************************
 * @file
 * hw_iodef.h
 * 
 * @brief
 * Hardware Layer - I/O Definitions
 * 
 * @date  21.09.2023
 ******************************************************************************/

#ifndef HW_IODEF_H_
#define HW_IODEF_H_

/*- Header files -------------------------------------------------------------*/
#include "stm32f1xx_hal.h"


/*- Macros -------------------------------------------------------------------*/
/*! @brief LED
 *  @{                                                                        */
#define LED_PIN                       GPIO_PIN_13
#define LED_PORT                      GPIOC
/*! @}                                                                        */

/*! @brief USB DM/DP, Pull-Up Resistor
 *  @{                                                                        */
#define USB_DP_PIN                    GPIO_PIN_12
#define USB_DM_PIN                    GPIO_PIN_11
#define USB_Dx_PORT                   GPIOA
#define USB_PU_PIN                    GPIO_PIN_4
#define USB_PU_PORT                   GPIOA
/*! @}                                                                        */

#endif /* HW_IODEF_H_ */