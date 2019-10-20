/* ###################################################################
**     Filename    : main.c
**     Project     : SOLINDAR
**     Processor   : MC9S08QE128CLK
**     Version     : Driver 01.12
**     Compiler    : CodeWarrior HCS08 C Compiler
**     Date/Time   : 2019-10-07, 12:49, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.12
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "AD1.h"
#include "Bit1.h"
#include "Bit2.h"
#include "Bit3.h"
#include "Bit4.h"
#include "Bit5.h"
#include "PPG1.h"
#include "TI1.h"
#include "Bit6.h"
#include "Cap1.h"
/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
char f=0;
char x=1;
char pasos=0;
bool reverse=0;
int dato=0;
bool q0=0;
bool q1=0;
bool q2=1;
bool q3=0;
signed char y[4] = {0,0,0,0};

void main(void)
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  /* For example: for(;;) { } */
  
  for(;;){
	  if(f){
		  if (x==1){
			  Bit1_NegVal();
			  x++;
					//pasos++;
		  }
		  else if (x==2){
			  Bit3_NegVal();
			  x++;
					//pasos++;
		  }
		  else if (x==3){
			  Bit4_NegVal();
			  x++;
					//pasos++;
		  }
		  else if (x==4){
			  Bit1_NegVal();
			  x++;
					//pasos++;
		  }
		  else if (x==5){
			  Bit2_NegVal();
			  x++;
					//pasos++;
		  }
		  else if (x==6){
			  Bit4_NegVal(); 
			  x++;
					//pasos++;
		  }
		  else if (x==7){
			  Bit3_NegVal();
			  x++;
					//pasos++;
		  }
		  else {
			  Bit2_NegVal();
			  x=1;
					//pasos++;
		  }
		  
	  
		//reverse=~reverse;
		
	  //AD1_GetValue(&dato);
		//Bit5_SetVal();
		//Bit5_PutVal(FALSE);
		  f=0;
	  }
  }


  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.09]
**     for the Freescale HCS08 series of microcontrollers.
**
** ###################################################################
*/
