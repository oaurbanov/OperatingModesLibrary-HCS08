/**
* Copyright (c) 2005, Freescale Semiconductor
* Freescale Willy Note
*
* File name : main.c
* Project name: RTI_QG8.mcp
*
* Author : Oscar Luna
* Department : RTAC Americas
*
* Description : This example illustrates the implementation of the real time  
*               interrupt (RTI). This example makes use of the Device Initialization 
*               tool for the RTI module set up. The RTI module will trigger  
*               a periodic hardware interrupt. 
*               
*               For this example, the RTI module is configured the following way:
*               
*                 + Time period of 1.024 seconds (internal oscillator selected, 
*                        with a prescaler value of 32768 (RTIS = 7) )
*
*                 + RTI interrupt enabled
*
*                 + COP watchdog disabled
*
*                 + RESET pin enabled
*
*                 + PTB7, PTB6 and PTB5 configured as outputs for LED display. 
*                                                       
*               The initialization of the module is the Device Initialization tool 
*               automatically generated MCUinit.c code, which was included in this 
*               project.
*
*               This example was explicitly made for the MC9S08QG8 microcontroller 
*               migrating may need some changes in the code.
*           
*               (Refer to AN3136 for more information about Device Initialization)
* History :   
* 28/010/2005  : Migration to CW 4.9 (r12370c)
*/

#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include "MCUinit.h"

void main(void) {

     MCU_init();
    
   for(;;) {

				/* Waits for RTI interrupts */
   }
  
 }
