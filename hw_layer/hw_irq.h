/*!****************************************************************************
 * @file
 * hw_irq.h
 * 
 * @brief
 * Hardware Layer - Interrupts
 * 
 * @date  21.09.2023
 ******************************************************************************/

#ifndef HW_IRQ_H_
#define HW_IRQ_H_

/*- Header files -------------------------------------------------------------*/
#include <stdbool.h>


/*- Exported functions -------------------------------------------------------*/
void vHW_IrqInit(void);

void vHW_IrqSetUsb(bool bEnable);

#endif /* HW_IRQ_H_ */