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
//#include "MCUinit.h"
#include "operating_modes.h"

#define LED2    PTBD_PTBD4		 /*Define LED 0 position in port B*/
#define LED1    PTBD_PTBD5		 /*Define LED 1 position in port B*/

//extern unsigned char hour;
//extern unsigned char min;
//extern unsigned char sec;


void activeMode_mSleep(unsigned int secs){
	unsigned int i, j;
	for (i=0;i<secs;i++){
		for(j=0;j<412;j++);
	}
}

void waitMode_sSleep(unsigned int secs){//TODO: fix it, it's not working
	unsigned int i, j;
	for (i=0; i<secs; i++){
		for (j=0;j<20;j++){}//720 //1430 valor en waitMode // 1 sec //debería ser 32000 porque el reloj interno corre a 32k, pero lo ajuste manualmente así
	}
}

void stopMode_4secs(unsigned int secs){
	unsigned int i;
	
	//opModes_setActiveMode();
	//activeMode_mSleep(1000);
	
	opModes_activateRTI();
	opModes_setStopMode();
	for(i=0;i<secs;i++){ // the RTI interrupts every 1 second
		//opModes_setStopMode();		
		SPMSC2 = 0x00;				 /*Stop mode 3 enabled*/
		asm stop;							 /*Stop instruction using Mode 3*/	
	}
	opModes_setActiveMode();		

}

void blinkingLeds(unsigned int count){
	unsigned char a;
	opModes_setActiveMode();
	LED1 = 0;  PTBDD_PTBDD5 = 1; //1==out,0==in
	LED2 = 0;  PTBDD_PTBDD4 = 1; //1==out,0==in
	
	for(a=0; a<(count<<1); a++){
	    LED1 = ~LED1;			 /*Blink leds*/
	    LED2 = ~LED2;
	    activeMode_mSleep(400);
	}
}

void main(void) {
	LED1 = 0;  PTBDD_PTBDD5 = 1; //1==out,0==in

	for(;;){	

		//activeMode:
		blinkingLeds(3);
		opModes_setActiveMode();
		activeMode_mSleep(10000);// running 10 secs in activeMode.  I = x mA
		
		//stopMode:
		blinkingLeds(2);
		stopMode_4secs(10);// running 10 secs in activeMode.  I = x uA
		
		//waitMode:
		//blinkingLeds(1);
		//opModes_setWaitMode();
		//waitMode_sSleep(10);// running 10 secs in waitMode.  I = x mA
		
	}


}
