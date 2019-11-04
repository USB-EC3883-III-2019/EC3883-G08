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
#include "TI1.h"
#include "AS1.h"
#include "PWM1.h"
#include "Cap1.h"
#include "TI2.h"
#include "Bit6.h"
#include "KB1.h"
#include "TI3.h"
#include "Bit5.h"
/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
char f=0;
char h=0;
char i;
unsigned int t;
unsigned int sonar;
char CodError;
char x=1;
char pasos=0;
int posicion;
bool reverse=0;
int lidar;
unsigned char block[4] = {0,0,0,0};
unsigned int a=0;
int auxs1=0;
int auxs2=0;
int auxs3=0;
int auxl1=0;
int auxl2 =0;
int auxl3=0;
char filtro=0;
char m=1;




void main(void)
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  /* For example: for(;;) { } */
  for(;;){
	  
	  if(h){
		  if(pasos>=52){
			  pasos=0;
			  reverse=!reverse;
		  }
		  if (reverse==0){
	  		  if (x==1){
	  			  Bit1_NegVal();
	  			  x++;
	  			  pasos++;
	  		  }
	  		  else if (x==2){
	  			  Bit3_NegVal();
	  			  x++;
	  			  pasos++;
	  		  }
	  		  else if (x==3){
	  			  Bit4_NegVal();
	  			  x++;
	  			  pasos++;
	  		  }
	  		  else if (x==4){
	  			  Bit1_NegVal();
	  			  x++;
	  			  pasos++;
	  		  }
	  		  else if (x==5){
	  			  Bit2_NegVal();
	  			  x++;
	  			  pasos++;
	  		  }
	  		  else if (x==6){
	  			  Bit4_NegVal(); 
	  			  x++;
	  			  pasos++;
	  		  }
	  		  else if (x==7){
	  			  Bit3_NegVal();
	  			  x++;
	  			  pasos++;
	  		  }
	  		  else {
	  			  Bit2_NegVal();
	  			  x=1;
	  			  pasos++;
	  		  }
	  	
		  }
	  	  else if(reverse==1){
	  		  if(x==1){
	  			  Bit2_NegVal();
	  			  x++;
	  			  pasos++;
	  		  }
	  		  else if(x==2){
	  			  Bit3_NegVal();
	  			  x++;
	  			  pasos++;
	  		  }
	  		  else if(x==3){
	  			  Bit4_NegVal();			  
	  			  x++;
	  			  pasos++;
	  		  }
	  		  else if(x==4){
	  			  Bit2_NegVal();			  
	  			  x++;
	  			  pasos++;
	  		  }
	  		  else if(x==5){
	  			  Bit1_NegVal();			  
	  			  x++;
	  			  pasos++;
	  		  }
	  		  else if(x==6){
	  			  Bit4_NegVal();			  
	  			  x++;
	  			  pasos++;
	  		  }
	  		  else if(x==7){
	  			  Bit3_NegVal();			  
	  			  x++;
	  			  pasos++;
	  		  }
	  		  else {
	  			  Bit1_NegVal();			  
	  			  x=1;
	  			  pasos++;
	  		  }
	  	  }
		  h=0;
	  }
  
	  if(f){
		  
		  AD1_Measure(TRUE);
		  AD1_GetValue(&lidar);
		  if(t<=0x80){
			  sonar=t;
		  }
		  //else{
		  //block[0]=lidar[0];
		  //block[1]=lidar[1];
		  //}
		  //posicion=pasos*4;
		  
		  /*block[0]= pasos&0x3F;
		  block[1]= block[1]|0x80;
		  block[2]= ((lidar&0xF80)>>7)|0x80;
		  block[3]= (lidar&0x7F)|0x80;
		  if(reverse){
			  block[0]=block[0]|0x40;
		  }*/
		  
		  if (filtro){
			  
			  if(m==1){
				  auxs1=sonar;
				  auxl1=lidar;
				  m++;
			  }
			  else if(m==2){
				  auxs2=sonar;
				  auxl2=lidar;
				  m++;
			  }
			  else if(m==3){
				  auxs3=sonar;
				  auxl3=lidar;
				  m++;
			  }
			  else if(m==4){
				  sonar=(sonar+auxs1+auxs2+auxs3)>>2;
				  lidar=(lidar+auxl1+auxl2+auxl3)>>2;
				  block[0]= pasos&0x3F;
				  block[1]= sonar|0x80;
				  block[2]= ((lidar&0xF80)>>7)|0xC0;
				  block[3]= (lidar&0x7F)|0x80;
				  m=1;
				  if(reverse){
					  block[0]=block[0]|0x40;
				  }
				  do{
					  CodError=AS1_SendBlock(block,4,&i);
				  	  //CodError =  AS1_SendChar(t);
				  } while (CodError != ERR_OK);
				  
			  }
		  }
		  else{
			  block[0]= pasos&0x3F;
			  block[1]= sonar|0x80;
			  block[2]= ((lidar&0xF80)>>7)|0x80;
			  block[3]= (lidar&0x7F)|0x80;
			  if(reverse){
			  	  block[0]=block[0]|0x40;
			  }
			  do{
				  CodError=AS1_SendBlock(block,4,&i);
			  //CodError =  AS1_SendChar(t);
			  } while (CodError != ERR_OK);
	  	  }
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
