/*
 * operating_modes.h
 *
 *  Created on: Feb 1, 2018
 *      Author: oskra
 */

#ifndef OPERATING_MODES_H_
#define OPERATING_MODES_H_

/* Include shared modules, which are used for whole project */

void opModes_setActiveMode(void);
/*
** ===================================================================
**     Method      :  opModes_setActiveMode
**
**     Description :
**         Device initialization code for setting active mode.
**         Maximum performance and power consumption
** ===================================================================
*/

void opModes_setWaitMode(void);
/*
** ===================================================================
**     Method      :  opModes_setWaitMode
**
**     Description :
**         Device initialization code for setting wait mode.
**         Average performance and power consumption
**         BKGD is disabled
** ===================================================================
*/

void opModes_setStopMode(void);
/*
** ===================================================================
**     Method      :  opModes_setStopMode
**
**     Description :
**         Device initialization code for setting stop mode.
**         Low power consumption
** ===================================================================
*/

void opModes_activateRTI(void);
/*
** ===================================================================
**     Method      :  MCU_init (bean MC9S08QG8_16)
**
**     Description :
**         Device initialization code for selected peripherals.
** ===================================================================
*/


__interrupt void Virq_isr(void);
/*
** ===================================================================
**     Interrupt handler : Virq_isr
**
**     Description :
**         User interrupt service routine. 
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/


__interrupt void Vrti_isr(void);
/*
** ===================================================================
**     Interrupt handler : Vrti_isr
**
**     Description :
**         User interrupt service routine. 
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

#endif /* OPERATING_MODES_H_ */
