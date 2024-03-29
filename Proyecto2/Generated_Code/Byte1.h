/* ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : Byte1.h
**     Project     : Proyecto2
**     Processor   : MC9S08QE128CLK
**     Component   : ByteIO
**     Version     : Component 02.063, Driver 03.26, CPU db: 3.00.067
**     Compiler    : CodeWarrior HCS08 C Compiler
**     Date/Time   : 2019-12-05, 00:09, # CodeGen: 1
**     Abstract    :
**         This component "ByteIO" implements an one-byte input/output.
**         It uses one 8-bit port.
**         Note: This component is set to work in Output direction only.
**         Methods of this component are mostly implemented as a macros 
**         (if supported by target langauage and compiler).
**     Settings    :
**         Port name                   : PTD
**
**         Initial direction           : Output (direction cannot be changed)
**         Initial output value        : 0 = 000H
**         Initial pull option         : off
**
**         8-bit data register         : PTDD      [$0006]
**         8-bit control register      : PTDDD     [$0007]
**
**             ----------------------------------------------------
**                   Bit     |   Pin   |   Name
**             ----------------------------------------------------
**                    0      |    2    |   PTD0_KBI2P0_SPSCK2
**                    1      |    1    |   PTD1_KBI2P1_MOSI2
**                    2      |    58   |   PTD2_KBI2P2_MISO2
**                    3      |    57   |   PTD3_KBI2P3_SS2
**                    4      |    56   |   PTD4_KBI2P4
**                    5      |    28   |   PTD5_KBI2P5
**                    6      |    27   |   PTD6_KBI2P6
**                    7      |    26   |   PTD7_KBI2P7
**             ----------------------------------------------------
**     Contents    :
**         GetDir - bool Byte1_GetDir(void);
**         GetVal - byte Byte1_GetVal(void);
**         PutVal - void Byte1_PutVal(byte Val);
**         GetBit - bool Byte1_GetBit(byte Bit);
**         PutBit - void Byte1_PutBit(byte Bit, bool Val);
**         SetBit - void Byte1_SetBit(byte Bit);
**         ClrBit - void Byte1_ClrBit(byte Bit);
**         NegBit - void Byte1_NegBit(byte Bit);
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
** @file Byte1.h
** @version 03.26
** @brief
**         This component "ByteIO" implements an one-byte input/output.
**         It uses one 8-bit port.
**         Note: This component is set to work in Output direction only.
**         Methods of this component are mostly implemented as a macros 
**         (if supported by target langauage and compiler).
*/         
/*!
**  @addtogroup Byte1_module Byte1 module documentation
**  @{
*/         

#ifndef Byte1_H_
#define Byte1_H_

/* MODULE Byte1. */

  /* Including shared modules, which are used in the whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "PE_Timer.h"
#include "Cpu.h"


/*
** ===================================================================
**     Method      :  Byte1_GetVal (component ByteIO)
**     Description :
**         This method returns an input value.
**           a) direction = Input  : reads the input value from the
**                                   pins and returns it
**           b) direction = Output : returns the last written value
**         Note: This component is set to work in Output direction only.
**     Parameters  : None
**     Returns     :
**         ---        - Input value (0 to 255)
** ===================================================================
*/
#define Byte1_GetVal() ( \
    getReg8(PTDD)                      /* Evaluate to port data */ \
  )

/*
** ===================================================================
**     Method      :  Byte1_PutVal (component ByteIO)
**     Description :
**         This method writes the new output value.
**     Parameters  :
**         NAME       - DESCRIPTION
**         Val        - Output value (0 to 255)
**     Returns     : Nothing
** ===================================================================
*/
#define Byte1_PutVal(Val) ( \
    (void)setReg8(PTDD, Val)           /* PTDD0-PTDD7=Val[bits 0-7] */ \
  )

/*
** ===================================================================
**     Method      :  Byte1_GetBit (component ByteIO)
**     Description :
**         This method returns the specified bit of the input value.
**           a) direction = Input  : reads the input value from pins
**                                   and returns the specified bit
**           b) direction = Output : returns the specified bit
**                                   of the last written value
**         Note: This component is set to work in Output direction only.
**     Parameters  :
**         NAME       - DESCRIPTION
**         Bit        - Number of the bit to read (0 to 7)
**     Returns     :
**         ---        - Value of the specified bit (FALSE or TRUE)
**                      FALSE = "0" or "Low", TRUE = "1" or "High"
** ===================================================================
*/
bool Byte1_GetBit(byte Bit);

/*
** ===================================================================
**     Method      :  Byte1_PutBit (component ByteIO)
**     Description :
**         This method writes the new value to the specified bit
**         of the output value.
**     Parameters  :
**         NAME       - DESCRIPTION
**         Bit        - Number of the bit (0 to 7)
**         Val        - New value of the bit (FALSE or TRUE)
**                      FALSE = "0" or "Low", TRUE = "1" or "High"
**     Returns     : Nothing
** ===================================================================
*/
void Byte1_PutBit(byte Bit, bool Val);

/*
** ===================================================================
**     Method      :  Byte1_SetBit (component ByteIO)
**     Description :
**         This method sets (sets to one) the specified bit of the
**         output value.
**         [ It is the same as "PutBit(Bit,TRUE);" ]
**     Parameters  :
**         NAME       - DESCRIPTION
**         Bit        - Number of the bit to set (0 to 7)
**     Returns     : Nothing
** ===================================================================
*/
void Byte1_SetBit(byte Bit);

/*
** ===================================================================
**     Method      :  Byte1_ClrBit (component ByteIO)
**     Description :
**         This method clears (sets to zero) the specified bit
**         of the output value.
**         [ It is the same as "PutBit(Bit,FALSE);" ]
**     Parameters  :
**         NAME       - DESCRIPTION
**         Bit        - Number of the bit to clear (0 to 7)
**     Returns     : Nothing
** ===================================================================
*/
void Byte1_ClrBit(byte Bit);

/*
** ===================================================================
**     Method      :  Byte1_NegBit (component ByteIO)
**     Description :
**         This method negates (inverts) the specified bit of the
**         output value.
**     Parameters  :
**         NAME       - DESCRIPTION
**         Bit        - Number of the bit to invert (0 to 7)
**     Returns     : Nothing
** ===================================================================
*/
void Byte1_NegBit(byte Bit);

/*
** ===================================================================
**     Method      :  Byte1_GetDir (component ByteIO)
**     Description :
**         This method returns direction of the component.
**     Parameters  : None
**     Returns     :
**         ---        - Direction of the component (always <true>, Output only)
**                      <false> = Input, <true> = Output
** ===================================================================
*/
#define Byte1_GetDir() ( \
    (bool)1U                           /* Port is fixed to GPO mode */ \
  )



/* END Byte1. */
#endif /* #ifndef __Byte1_H_ */
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
