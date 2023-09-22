/*!****************************************************************************
 * @file
 * hw_gpio.h
 * 
 * @brief
 * Hardware Layer - General Purpose I/O
 * 
 * @date  21.09.2023
 ******************************************************************************/

#ifndef HW_GPIO_H_
#define HW_GPIO_H_

/*- Header files -------------------------------------------------------------*/
#include <stdbool.h>


/*- Exported functions -------------------------------------------------------*/
void vHW_GpioInit(void);

void vHW_GpioSetLed(bool bEnable);
void vHW_GpioToggleLed(void);

void vHW_GpioSetUsb(bool bEnable);

#endif /* HW_GPIO_H_ */