/* ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : TI1.c
**     Project     : Proyecto2
**     Processor   : MC9S08QE128CLK
**     Component   : TimerInt
**     Version     : Component 02.161, Driver 01.23, CPU db: 3.00.067
**     Compiler    : CodeWarrior HCS08 C Compiler
**     Date/Time   : 2019-12-05, 00:09, # CodeGen: 1
**     Abstract    :
**         This component "TimerInt" implements a periodic interrupt.
**         When the component and its events are enabled, the "OnInterrupt"
**         event is called periodically with the period that you specify.
**         TimerInt supports also changing the period in runtime.
**         The source of periodic interrupt can be timer compare or reload
**         register or timer-overflow interrupt (of free running counter).
**     Settings    :
**         Timer name                  : RTC (8-bit)
**         Compare name                : RTCmod
**         Counter shared              : No
**
**         High speed mode
**             Prescaler               : divide-by-1
**             Clock                   : 4096 Hz
**           Initial period/frequency
**             Xtal ticks              : 2954102
**             microseconds            : 59082
**             milliseconds            : 59
**             seconds (real)          : 0.05908203125
**             Hz                      : 17
**
**         Runtime setting             : none
**
**         Initialization:
**              Timer                  : Enabled
**              Events                 : Enabled
**
**         Timer registers
**              Counter                : RTCCNT    [$1831]
**              Mode                   : RTCSC     [$1830]
**              Run                    : RTCSC     [$1830]
**              Prescaler              : RTCSC     [$1830]
**
**         Compare registers
**              Compare                : RTCMOD    [$1832]
**
**         Flip-flop registers
**     Contents    :
**         No public methods
**
**     Copyright : 1997 - 2014 Freescale Semiconductor, Inc. 
**     All Rights Reserved.
**     
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**     
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**     
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**     
**     o Neither the name of Freescale Semiconductor, Inc. nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**     
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**     
**     http: www.freescale.com
**     mail: support@freescale.com
** ###################################################################*/
/*!
** @file TI1.c
** @version 01.23
** @brief
**         This component "TimerInt" implements a periodic interrupt.
**         When the component and its events are enabled, the "OnInterrupt"
**         event is called periodically with the period that you specify.
**         TimerInt supports also changing the period in runtime.
**         The source of periodic interrupt can be timer compare or reload
**         register or timer-overflow interrupt (of free running counter).
*/         
/*!
**  @addtogroup TI1_module TI1 module documentation
**  @{
*/         

/* MODULE TI1. */

#include "Events.h"
#include "PE_Error.h"
#include "TI1.h"
#pragma MESSAGE DISABLE C2705          /* WARNING C2705: Possible loss of data */
#pragma MESSAGE DISABLE C5919          /* WARNING C5919: Conversion of floating to unsigned integral */
#pragma MESSAGE DISABLE C5703          /* WARNING C5703: Parameter X declared in function F but not referenced */
#pragma CODE_SEG TI1_CODE

/*** Internal macros and method prototypes ***/

/*
** ===================================================================
**     Method      :  SetCV (component TimerInt)
**
**     Description :
**         The method computes and sets compare eventually modulo value 
**         for time measuring.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
#define TI1_SetCV(_Val) \
  (RTCMOD = (byte)(_Val))


/*** End of internal method prototypes ***/

/*
** ===================================================================
**     Method      :  TI1_Init (component TimerInt)
**
**     Description :
**         Initializes the associated peripheral(s) and the component 
**         internal variables. The method is called automatically as a 
**         part of the application initialization code.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void TI1_Init(void)
{
  /* RTCSC: RTIF=0,RTCLKS=0,RTIE=0,RTCPS=0 */
  setReg8(RTCSC, 0x00U);               /* Stop HW */ 
  TI1_SetCV(0xF1U);                    /* Initialize appropriate value to the compare/modulo/reload register */
  RTCMOD = RTCMOD;                     /* Reset HW counter */
  /* RTCSC: RTIF=1,RTCLKS=2,RTIE=1,RTCPS=1 */
  setReg8(RTCSC, 0xD1U);               /* Run RTC (select clock source, set frequency and enable interrupt) */ 
}


/*
** ===================================================================
**     Method      :  TI1_Interrupt (component TimerInt)
**
**     Description :
**         The method services the interrupt of the selected peripheral(s)
**         and eventually invokes the component event(s).
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
#pragma CODE_SEG __NEAR_SEG NON_BANKED
ISR(TI1_Interrupt)
{
  /* RTCSC: RTIF=1 */
  setReg8Bits(RTCSC, 0x80U);           /* Reset real-time counter request flag */ 
  TI1_OnInterrupt();                   /* Invoke user event */
}

#pragma CODE_SEG TI1_CODE


/* END TI1. */

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
