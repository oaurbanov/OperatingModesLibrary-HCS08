/*
** ###################################################################
**     Processor : MC9S08QG8
**     Date/Time : 1/02/2018
**     Abstract  :
**         This module manages MCU operating modes. ActiveMode,
**         WaitMode and StopMode(1,2,3)
**
**		Author: Oscar Urbano
**		Mail: oscarutkd@gmail.com
** ###################################################################
*/

#include "derivative.h" /* include peripheral declarations */
#include "operating_modes.h"


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
void opModes_setRunMode(void)
{

	/*  System clock initialization */
	/* SOPT1: COPE=0,COPT=0,STOPE=1,X,X,X,BKGDPE=1,RSTPE=0 */
	SOPT1 = 0x32;                                      
	/* SOPT2: COPCLKS=0,IICPS=0,ACIC=0 */
	SOPT2 = 0x00;     
	
	/*  Low voltage initialization */
	/* SPMSC1: LVDF=0,LVDACK=0,LVDIE=0,LVDRE=0,LVDSE=0,LVDE=0,BGBE=0 */
	SPMSC1 = 0x00;//0x18
	/* SPMSC2: PDF=0,PPDF=0,PPDACK=0,PDC=0,PPDC=0 */
	SPMSC2 = 0x00;        //-----------------------------------------stopMode3                                   
	/* SPMSC3: LVDV=0,LVWV=0 */
	SPMSC3 &= (unsigned char)~0x30;                              


	
    /*	FLL Engaged Internal (FEI)
		FLL engaged internal (FEI) is the default mode of operation out of any reset and is entered when all the
		following conditions occur:
		• CLKS bits are written to 00
		• IREFS bit is written to 1
		• RDIV bits are written to divide reference clock to be within the range of 31.25 kHz to 39.0625 kHz.
		In FLL engaged internal mode, the ICSOUT clock is derived from the FLL clock, which is controlled by
		the internal reference clock. The FLL loop will lock the frequency to 512 times the filter frequency, as
		selected by the RDIV bits. The ICSLCLK is available for BDC communications, and the internal reference
		clock is enabled.*/

		ICSC1_CLKS =0;	//Output of FLL is selected.
		ICSC1_IREFS = 1; //Internal reference clock selected
		ICSC1_RDIV = 0; //Divides reference clock by 1 (reset default)
	    ICSC2_BDIV   = 0;//divide internal clock by 1 (8MHz bus)
		//ICSC2_LP = 0;
	    
} /*opModes_setRunMode*/


/*
** ===================================================================
**     Method      :  opModes_setWaitMode
**
**     Description :
**         Device initialization code for setting wait mode.
**         Average performance and power consumption
**         WARNING: BKGD is disabled!
**         3V , 0.2 mA
** ===================================================================
*/
void opModes_setWaitMode(){

	/*  System clock initialization */
	/* SOPT1: COPE=0,COPT=0,STOPE=1,X,X,X,BKGDPE=1,RSTPE=0 */
	SOPT1 = 0x32;                                      
	/* SOPT2: COPCLKS=0,IICPS=0,ACIC=0 */
	SOPT2 = 0x00;     

	/*	FLL Bypassed Internal Low Power (FBILP)
	  	The FLL bypassed internal low power (FBILP) mode is entered when all the following conditions occur:
		• CLKS bits are written to 01
		• IREFS bit is written to 1.
		• BDM mode is not active and LP bit is written to 1
		In FLL bypassed internal low power mode, the ICSOUT clock is derived from the internal reference clock
		and the FLL is disabled. The ICSLCLK will be not be available for BDC communications, and the internal
		reference clock is enabled.*/
		
		ICSC1_CLKS =1; //Internal reference clock is selected.
		ICSC1_IREFS = 1; //Internal reference clock selected
		ICSC2_LP = 1; //FLL is disabled in bypass modes unless BDM is active
		//ICSC2_BDIV   = 3;//divide internal clock by 8 (8MHz bus)
		//ICSTRM = 0x00; //modificar los TRM no funcionó para ajustar frec reloj al maximo
		//ICSSC_FTRIM = 0; // The FTRIM bit controls the smallest adjustment of the internal reference clock frequency.
		
} /*opModes_setWaitMode*/

/*
** ===================================================================
**     Method      :  opModes_setStop3Mode
**
**     Description :
**         Device initialization code for setting stopMode3.
**         Low power consumption
**         WARNING: MCU is wake up just by interrupts
**         3V , 0.05 mA
** ===================================================================
*/
void opModes_setStop3Mode(){
	
	
	/*  System clock initialization */
	/* SOPT1: COPE=0,COPT=0,STOPE=1,X,X,X,BKGDPE=1,RSTPE=0 */
	SOPT1 = 0x32;                                      
	/* SOPT2: COPCLKS=0,IICPS=0,ACIC=0 */
	SOPT2 = 0x00;     
	
	/*  Low voltage initialization */
	/* SPMSC1: LVDF=0,LVDACK=0,LVDIE=0,LVDRE=0,LVDSE=0,LVDE=0,BGBE=0 */
	SPMSC1 = 0x00;//0x18
	/* SPMSC2: PDF=0,PPDF=0,PPDACK=0,PDC=0,PPDC=0 */
	SPMSC2 = 0x00;        //-----------------------------------------stopMode3                                   
	/* SPMSC3: LVDV=0,LVWV=0 */
	SPMSC3 &= (unsigned char)~0x30;                              
	  
	
	/* ICSC1: CLKS=0,RDIV=0,IREFS=1,IRCLKEN=0,IREFSTEN=0 */
	ICSC1 = 0x04;                        /* Initialization of the ICS control register 1 */ //Divides clock by 1, Internal reference clock selected
	/* ICSC2: BDIV=1,RANGE=0,HGO=0,LP=0,EREFS=0,ERCLKEN=0,EREFSTEN=0 */
	ICSC2 = 0x40;                        /* Initialization of the ICS control register 2 */ //divides selected clock by 8
	

	asm stop;							 /*Stop instruction using Mode 3*/	

} /*opModes_setStop3Mode*/


/*
** ===================================================================
**     Method      :  opModes_enableRTI (bean MC9S08QG8_16)
**
**     Description :
**         activates RTI every 1.024 seconds (internal oscillator selected, 
*          with a prescaler value of 32768 (RTIS = 7) )
** ===================================================================
*/
void opModes_enableRTI(){
  
  /*  System clock initialization */
  /* SOPT1: COPE=0,COPT=0,STOPE=1,X,X,X,BKGDPE=1,RSTPE=0 */
  SOPT1 = 0x32;                                      
  /* SOPT2: COPCLKS=0,IICPS=0,ACIC=0 */
  SOPT2 = 0x00;     
  
  /*  Low voltage initialization */
  /* SPMSC1: LVDF=0,LVDACK=0,LVDIE=0,LVDRE=0,LVDSE=0,LVDE=0,BGBE=0 */
  SPMSC1 = 0x00;//0x1C
  /* SPMSC2: PDF=0,PPDF=0,PPDACK=0,PDC=0,PPDC=0 */
  SPMSC2 = 0x00;        //-----------------------------------------stopMode3                                   
  /* SPMSC3: LVDV=0,LVWV=0 */
  SPMSC3 &= (unsigned char)~0x30;                              
  
  /* ICSC1: CLKS=0,RDIV=2,IREFS=1,IRCLKEN=0,IREFSTEN=0 */
  ICSC1 = 0x14;                        /* Initialization of the ICS control register 1 */ //Divides clock by 4, Internal reference clock selected
  /* ICSC2: BDIV=0,RANGE=0,HGO=0,LP=0,EREFS=0,ERCLKEN=0,EREFSTEN=0 */
  ICSC2 = 0x00;                        /* Initialization of the ICS control register 2 */ //divides selected clock by 1
  
  /* ### Init_RTI init code */
  /* SRTISC: RTIF=0,RTIACK=0,RTICLKS=0,RTIE=1,RTIS2=1,RTIS1=1,RTIS0=1 */
  SRTISC = 0x17;                                      
  
  asm CLI;                             /* Enable interrupts */
} /*opModes_enableRTI*/

/*
** ===================================================================
**     Method      :  opModes_disableRTI (bean MC9S08QG8_16)
**
**     Description :
**         disable the RTI interruption
** ===================================================================
*/
void opModes_disableRTI(){
  
  /* ### Init_RTI init code */
  /* SRTISC: RTIF=0,RTIACK=0,RTICLKS=0,RTIE=0,RTIS2=0,RTIS1=0,RTIS0=0 */
  SRTISC = 0x00;                                      
  
  asm CLI;                             /* Enable interrupts */
} /*opModes_disableRTI*/

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
__interrupt void Vrti_isr(void)
{
     SRTISC_RTIACK = 1;  /* Acknowledges RTI flag*/
}/* end of Vrti_isr */


extern void _Startup(void);

/* Interrupt vector table */
#define UNASSIGNED_ISR 0xFFFF          /* unassigned interrupt service routine */

void (* const _vect[])() @0xFFD0 = {   /* Interrupt vector table */
         Vrti_isr,                     /* Int.no.  0 Vrti (at FFD0)                  Used */
         UNASSIGNED_ISR,               /* Int.no.  1 Reserved2 (at FFD2)             Unassigned */
         UNASSIGNED_ISR,               /* Int.no.  2 Reserved3 (at FFD4)             Unassigned */
         UNASSIGNED_ISR,               /* Int.no.  3 Vacmp (at FFD6)                 Unassigned */
         UNASSIGNED_ISR,               /* Int.no.  4 Vadc (at FFD8)                  Unassigned */
         UNASSIGNED_ISR,               /* Int.no.  5 Vkeyboard (at FFDA)             Unassigned */
         UNASSIGNED_ISR,               /* Int.no.  6 Viic (at FFDC)                  Unassigned */
         UNASSIGNED_ISR,               /* Int.no.  7 Vscitx (at FFDE)                Unassigned */
         UNASSIGNED_ISR,               /* Int.no.  8 Vscirx (at FFE0)                Unassigned */
         UNASSIGNED_ISR,               /* Int.no.  9 Vscierr (at FFE2)               Unassigned */
         UNASSIGNED_ISR,               /* Int.no. 10 Vspi (at FFE4)                  Unassigned */
         UNASSIGNED_ISR,               /* Int.no. 11 Vmtim (at FFE6)                 Unassigned */
         UNASSIGNED_ISR,               /* Int.no. 12 Reserved13 (at FFE8)            Unassigned */
         UNASSIGNED_ISR,               /* Int.no. 13 Reserved14 (at FFEA)            Unassigned */
         UNASSIGNED_ISR,               /* Int.no. 14 Reserved15 (at FFEC)            Unassigned */
         UNASSIGNED_ISR,               /* Int.no. 15 Reserved16 (at FFEE)            Unassigned */
         UNASSIGNED_ISR,               /* Int.no. 16 Vtpmovf (at FFF0)               Unassigned */
         UNASSIGNED_ISR,               /* Int.no. 17 Vtpmch1 (at FFF2)               Unassigned */
         UNASSIGNED_ISR,               /* Int.no. 18 Vtpmch0 (at FFF4)               Unassigned */
         UNASSIGNED_ISR,               /* Int.no. 19 Reserved20 (at FFF6)            Unassigned */
         UNASSIGNED_ISR,               /* Int.no. 20 Vlvd (at FFF8)                  Unassigned */
         UNASSIGNED_ISR,                     /* Int.no. 21 Virq (at FFFA)                  Used */
         UNASSIGNED_ISR,               /* Int.no. 22 Vswi (at FFFC)                  Unassigned */
         //_Startup                      /* Int.no. 23 Vreset (at FFFE)                Reset vector */
 };



/********************************************************************************************************/
/******************************** High Level Implementation functions ***********************************/
/********************************************************************************************************/

/*
** ===================================================================
**     Method      :  runMode_mSleep
**
**     Description :
**         miliSeconds sleep function for runMode.
**         WARNING: runMode must be set before!
** ===================================================================
*/
void runMode_mSleep(unsigned int msecs){
	unsigned int i, j;
	for (i=0;i<msecs;i++){
		for(j=0;j<412;j++);// manually trimmed
	}
} /*runMode_mSleep*/

/*
** ===================================================================
**     Method      :  waitMode_sSleep
**
**     Description :
**         Seconds sleep function for waitMode.
**         WARNING: waitMode must be set before!
** ===================================================================
*/
void waitMode_sSleep(unsigned int secs){
	unsigned int i, j;
	for (i=0; i<secs; i++){
		for (j=0;j<750;j++);// manually trimmed
	}
} /*waitMode_sSleep*/

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
void stopMode_sSleep(unsigned int secs){
	unsigned int i;
	opModes_enableRTI();
	for(i=0;i<secs;i++){ // the RTI interrupts every 1 second
		opModes_setStop3Mode();		
	}
	opModes_disableRTI();
	opModes_setRunMode();		
} /*stopMode_sSleep*/
