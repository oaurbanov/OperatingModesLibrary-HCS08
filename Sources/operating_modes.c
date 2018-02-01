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
**     Method      :  opModes_setActiveMode
**
**     Description :
**         Device initialization code for setting active mode.
**         Maximum performance and power consumption
** ===================================================================
*/
void opModes_setActiveMode(void)
{
	
	/*  System clock initialization */
	/* SOPT1: COPE=0,COPT=0,STOPE=1,X,X,X,BKGDPE=1,RSTPE=0 */
	SOPT1 = 0x32;                                      
	/* SOPT2: COPCLKS=0,IICPS=0,ACIC=0 */
	SOPT2 = 0x00;  //siempre cero                                    

	
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
	
	    //TODO:SMPC for get out from stop modes
	    
} /*opModes_setActiveMode*/


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
void opModes_setWaitMode(){
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
		
		//lowPowerEnabled = 1;
} /*opModes_setWaitMode*/

/*
** ===================================================================
**     Method      :  opModes_setStopMode
**
**     Description :
**         Device initialization code for setting stop mode.
**         Low power consumption
** ===================================================================
*/
void opModes_setStopMode(){//TODO: unsigned char mode
	
	/*  System clock initialization */
	/* SOPT1: COPE=0,COPT=0,STOPE=1,X,X,X,BKGDPE=1,RSTPE=0 */
	SOPT1 = 0x32;//0x30                                      
	/* SPMSC1: LVDF=0,LVDACK=0,LVDIE=0,LVDRE=1,LVDSE=1,LVDE=0,BGBE=0 */
	SPMSC1 = 0x18;                                      
	/* SPMSC2: PDF=0,PPDF=0,PPDACK=0,PDC=0,PPDC=0 */
	SPMSC2 = 0x00;    //-----------------------------------------stopMode3                                  
	/* SPMSC3: LVDV=0,LVWV=0 */
	SPMSC3 &= (unsigned char)~0x30;                              
	/* ICSC1: CLKS=0,RDIV=0,IREFS=1,IRCLKEN=0,IREFSTEN=0 */
	ICSC1 = 0x04;                        /* Initialization of the ICS control register 1 */
	/* ICSC2: BDIV=1,RANGE=0,HGO=0,LP=0,EREFS=0,ERCLKEN=0,EREFSTEN=0 */
	ICSC2 = 0x40;                        /* Initialization of the ICS control register 2 */
	
	/* Common initialization of the write once registers */
	/* SOPT2: COPCLKS=0,IICPS=0,ACIC=0 */
	SOPT2 = 0x00;  //siempre cero                                    

	asm stop;							 /*Stop instruction using Mode 3*/	

} /*opModes_setStopMode*/

//void activateStop3Mode(void){
//	  SPMSC2 = 0x00;				 /*Stop mode 3 enabled*/
//		LED0 = 0;							 /* Turns off led 0*/
//		LED1 = 0;							 /* Turns off led 1*/
//		Delay();
//	  PTAD = 0x0E;
//	  asm stop;							 /*Stop instruction using Mode 3*/	
//}









/*
** ===================================================================
**     Method      :  MCU_init (bean MC9S08QG8_16)
**
**     Description :
**         Device initialization code for selected peripherals.
** ===================================================================
*/
void opModes_activateRTI(){
  /* ### MC9S08QG8_16 "Cpu" init code ... */
  /*  PE initialization code after reset */
  /*  System clock initialization */
  /* SOPT1: COPE=0,COPT=0,STOPE=1,X,X,X,BKGDPE=1,RSTPE=0 */
  SOPT1 = 0x32;                                      
  /* SPMSC1: LVDF=0,LVDACK=0,LVDIE=0,LVDRE=1,LVDSE=1,LVDE=1,BGBE=0 */
  SPMSC1 = 0x1C;                                      
  /* SPMSC2: PDF=0,PPDF=0,PPDACK=0,PDC=0,PPDC=0 */
  SPMSC2 = 0x00;        //-----------------------------------------stopMode3                                   
  /* SPMSC3: LVDV=0,LVWV=0 */
  SPMSC3 &= (unsigned char)~0x30;                              
  /* ICSC1: CLKS=0,RDIV=2,IREFS=1,IRCLKEN=0,IREFSTEN=0 */
  ICSC1 = 0x14;                        /* Initialization of the ICS control register 1 */
  /* ICSC2: BDIV=0,RANGE=0,HGO=0,LP=0,EREFS=0,ERCLKEN=0,EREFSTEN=0 */
  ICSC2 = 0x00;                        /* Initialization of the ICS control register 2 */
  /* Common initialization of the write once registers */
  /* SOPT2: COPCLKS=0,IICPS=0,ACIC=0 */
  SOPT2 = 0x00;     
  
  //TODO: clean other regs

  /* Common initialization of the CPU registers */
  /* PTASE: PTASE5=1,PTASE4=1,PTASE3=1,PTASE2=1,PTASE1=1,PTASE0=1 */
  //PTASE |= (unsigned char)0x3F;                               
  /* PTBSE: PTBSE7=1,PTBSE6=1,PTBSE5=1,PTBSE4=1,PTBSE3=1,PTBSE2=1,PTBSE1=1,PTBSE0=1 */
  //PTBSE = 0xFF;                                      
  /* PTADS: PTADS5=0,PTADS4=0,PTADS3=0,PTADS2=0,PTADS1=0,PTADS0=0 */
  //PTADS = 0x00;                                      
  /* PTBDS: PTBDS7=0,PTBDS6=0,PTBDS5=0,PTBDS4=0,PTBDS3=0,PTBDS2=0,PTBDS1=0,PTBDS0=0 */
  //PTBDS = 0x00;
  
  /* ### Init_RTI init code */
  /* SRTISC: RTIF=0,RTIACK=0,RTICLKS=0,RTIE=1,RTIS2=1,RTIS1=1,RTIS0=1 */
  SRTISC = 0x17;                                      
  
  /* ### Init_COP init code */
  //SRS = 0xFF;                          /* Clear WatchDog counter */

  /* ### Init_GPIO init code */
//  /* PTBD: PTBD7=1,PTBD6=1,PTBD5=1 */
//  PTBD |= (unsigned char)0xF0;                               
//  /* PTBPE: PTBPE7=0,PTBPE6=0,PTBPE5=0 */
//  PTBPE &= (unsigned char)~0xE0;                              
//  /* PTBDD: PTBDD7=1,PTBDD6=1,PTBDD5=1 */
//  PTBDD |= (unsigned char)0xF0;                               
  /* ### */
  asm CLI;                             /* Enable interrupts */
} /*MCU_init*/

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
__interrupt void Virq_isr(void)
{
    IRQSC_IRQACK=1;				/*Clears IRQ flag*/

}
/* end of Virq_isr */

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

//    if(hour == 24){
//    
//        hour = 0;                    /* Resets hour counter*/
//    
//    }if (min == 60){
//    
//        hour++;                      /* Increases hour counter*/
//        min = 0;                     /* Resets minute counter*/
//        //PTBD_PTBD6 = ~PTBD_PTBD6;    /* toggle hour LED */
//    
//    }if(sec == 60){
//    
//        min++;                       /* Increases minutes counter*/
//        sec = 0;                     /* Resets seconds counter*/
//        //PTBD_PTBD5 = ~PTBD_PTBD5;    /* toggle minute LED */
//                                     
//    }else{                           
//        
//        sec++;                       /* Increases seconds counter*/
//        //PTBD_PTBD4 = ~PTBD_PTBD4;    /* toggle seconds LED */ 
//                                      
//    }                                



}
/* end of Vrti_isr */

/* Initialization of the CPU registers in FLASH */

/* NVPROT: FPS=0x7F,FPDIS=1 */
//const volatile NVPROTSTR _NVPROT @0x0000FFBD = { 0xFF };

/* NVOPT: KEYEN=0,FNORED=1,SEC01=1,SEC00=0 */
//const volatile NVOPTSTR _NVOPT @0x0000FFBF = { 0x7E };



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
         Virq_isr,                     /* Int.no. 21 Virq (at FFFA)                  Used */
         UNASSIGNED_ISR,               /* Int.no. 22 Vswi (at FFFC)                  Unassigned */
         //_Startup                      /* Int.no. 23 Vreset (at FFFE)                Reset vector */
 };












///*
// * Delay:      This function is for delay purposes only
// *
// * Parameters: None
// *
// * Return : None
// */
//void Delay(void){
//  unsigned int b;
//  unsigned char a;
//  for(a=0;a<0x01;a++)
//  {
//      for(b=0;b<0xFFFF;b++)
//      {
//        ;
//      }
//  }
//}
//
//void activateStop3Mode(void){
//	  SPMSC2 = 0x00;				 /*Stop mode 3 enabled*/
//		LED0 = 0;							 /* Turns off led 0*/
//		LED1 = 0;							 /* Turns off led 1*/
//		Delay();
//	  PTAD = 0x0E;
//	  asm stop;							 /*Stop instruction using Mode 3*/	
//}
//
//void activateRTI(void){
//	MCU_init_RTI();
//	
//}
//
//void stopForSecs(unsigned int secs){
//	unsigned int i;
//	//Delay();Delay();Delay();Delay();Delay();Delay();
//	//Delay();Delay();Delay();Delay();Delay();Delay();
//	activateRTI();
//	for(i=0; i<secs ; i++){
//		activateStop3Mode();
//	}
//	MCU_init();	
//}
//
//void runForSecs(unsigned int secs){
//	unsigned int i;
//	//activateRunMode();//inialize clock regs for max freq
//	for(i=0; i<secs; i++){
//		//ssleep();//ssleep has to run on max freq
//	}
//	
//}


//void blinkingLeds(unsigned int count){
//	unsigned char a;
//	LED0 = 0;
//	LED1 = 0;
//	for(a=0; a<(count<<1); a++){
//	    LED0 = ~LED0;			 /*Blink leds*/
//	    LED1 = ~LED1;
//	    Delay();
//	}
