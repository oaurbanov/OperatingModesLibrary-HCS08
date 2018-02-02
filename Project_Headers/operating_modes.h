/*
 * operating_modes.h
 *
 *  Created on: Feb 1, 2018
 *      Author: oskra
 */

#ifndef OPERATING_MODES_H_
#define OPERATING_MODES_H_

/* Include shared modules, which are used for whole project */

void opModes_setRunMode(void);
/*
** ===================================================================
**     Method      :  opModes_setRunMode
**
**     Description :
**         Device initialization code for setting run mode.
**         Maximum performance and power consumption
**         3V , 3.7 mA
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
**         3V , 0.2 mA
** ===================================================================
*/

void opModes_setStop3Mode(void);
/*
** ===================================================================
**     Method      :  opModes_setStop3Mode
**
**     Description :
**         Device initialization code for setting stop3mode.
**         Low power consumption
**         3V , 0.05 mA
** ===================================================================
*/

void opModes_enableRTI(void);
/*
** ===================================================================
**     Method      :  opModes_enableRTI (bean MC9S08QG8_16)
**
**     Description :
**         Device initialization code for selected peripherals.
** ===================================================================
*/

void opModes_disableRTI(void);
/*
** ===================================================================
**     Method      :  opModes_disableRTI (bean MC9S08QG8_16)
**
**     Description :
**         Disables the RTI interruption
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


/********************************************************************************************************/
/******************************** High Level Implementation functions ***********************************/
/********************************************************************************************************/


void runMode_mSleep(unsigned int msecs);
/*
** ===================================================================
**     Method      :  runMode_mSleep
**
**     Description :
**         miliSeconds sleep function for runMode.
**         WARNING: runMode must be set before!
** ===================================================================
*/

void waitMode_sSleep(unsigned int secs);
/*
** ===================================================================
**     Method      :  waitMode_sSleep
**
**     Description :
**         Seconds sleep function for waitMode.
**         WARNING: waitMode must be set before!
** ===================================================================
*/

void stopMode_sSleep(unsigned int secs);
/*
** ===================================================================
**     Method      :  stopMode_sSleep
**
**     Description :
**     Description :
**         Seconds sleep function for stopMode.
**         WARNING: stopMode is set inside (Do NOT do it before). 
** ===================================================================
*/


#endif /* OPERATING_MODES_H_ */
