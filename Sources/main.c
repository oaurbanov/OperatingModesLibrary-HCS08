/**
* Copyright (c) 2005, Freescale Semiconductor
* Freescale Willy Note
*
* File name : main.c
* Project name: Stop_Mode_QG.mcp
*
* Author : Gabriel Sanchez Barba
*          Gonzalo Delgado Huitron
* Department : RTAC Americas
*
* Description : This example illustrates the use of the Stop modes in 
*               the MC9S08QG8 microcontroller. This example will show
*               the 3 diferent Stop modes available.LEDs will flash 
*               according to the Stop modeThis project was made with 
*               the Device Initialization tool which sets the module, 
*               according to the user's needs. For this example, the 
*               Stop modes need to be configured to comply with the 
*               following requirements:
*                       + IRQ in PTA5 enabled used to exit stop modes
*                       + Stop modes enabled  
*                       + LVD disabled  
*                       + COP is disabled 
*                       + LEDs are controlled by PTB6 and PTB7 
*
*                            
* (Refer to AN3136 for more information about Device Initialization)
*
* History :   
* 10/08/2005  : Release (rgd04c)
*/
#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include "operating_modes.h"

#define LED2    PTBD_PTBD4		 /*Define LED 0 position in port B*/
#define LED1    PTBD_PTBD5		 /*Define LED 1 position in port B*/

void blinkLeds(unsigned int count){
	unsigned char a;
	opModes_setRunMode();

	LED1 = 0;  PTBDD_PTBDD5 = 1; //1==out,0==in
	LED2 = 0;  PTBDD_PTBDD4 = 1; //1==out,0==in
	
	for(a=0; a<(count<<1); a++){
	    LED1 = ~LED1;			 /*Blink leds*/
	    LED2 = ~LED2;
	    runMode_mSleep(400);
	}
}

void main(void) {

	for(;;){	

		//runMode:
		blinkLeds(3);
		opModes_setRunMode();
		runMode_mSleep(10000);// running 10 secs in runMode.  I = 3.7 mA
		
		//waitMode:
		blinkLeds(2);
		opModes_setWaitMode();
		waitMode_sSleep(10);// running 10 secs in waitMode.  I = 0.2 mA

		//stopMode:
		blinkLeds(1);
		stopMode_sSleep(10);// running 10 secs in stopMode.  I = 0.05 mA

	}


}
