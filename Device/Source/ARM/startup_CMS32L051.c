/**************************************************************************//**
 * @file     startup_CMS32L051.c
 * @brief    CMSIS Cortex-M ARMv7-M based Core Device Startup File for
 *           Device <Device>
 * @version  1.0.0
 * @date     2019/12/24
 ******************************************************************************/
/*
 * Copyright (c) 2009-2016 ARM Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ******************************************************************************/
#define STACK_TOP  (0x20002000U)  /*!< Stack is placed on RAM TOP  */

#include <stdio.h>
#include <rt_misc.h>
#include <stdint.h>

//
// Build a stand-alone image
//

#pragma import(__use_no_semihosting)


//
// Dummy Interrupt Handlers
//
// The following functions are defined weakly to allow the user
// to override them at link time simply by declaring their own
// function of the same name.
//
// If no user function is provided, the weak function is used.
//

__WEAK void NMI_Handler(void)
{
  while(1);
}

__WEAK void HardFault_Handler(void)
{
  while(1);
}

__WEAK void SVC_Handler(void)
{
  while(1);
}

__WEAK void PendSV_Handler(void)
{
  while(1);
}

__WEAK void SysTick_Handler(void)
{
  while(1);
}

__WEAK void IRQ00_Handler(void)
{
   while(1);
}

__WEAK void IRQ01_Handler(void)
{
   while(1);
}

__WEAK void IRQ02_Handler(void)
{
   while(1);
}

__WEAK void IRQ03_Handler(void)
{
   while(1);
}

__WEAK void IRQ04_Handler(void)
{
   while(1);
}

__WEAK void IRQ05_Handler(void)
{
   while(1);
}

__WEAK void IRQ06_Handler(void)
{
   while(1);
}

__WEAK void IRQ07_Handler(void)
{
   while(1);
}

__WEAK void IRQ08_Handler(void)
{
   while(1);
}

__WEAK void IRQ09_Handler(void)
{
   while(1);
}

__WEAK void IRQ10_Handler(void)
{
   while(1);
}

__WEAK void IRQ11_Handler(void)
{
   while(1);
}

__WEAK void IRQ12_Handler(void)
{
   while(1);
}

__WEAK void IRQ13_Handler(void)
{
   while(1);
}

__WEAK void IRQ14_Handler(void)
{
   while(1);
}

__WEAK void IRQ15_Handler(void)
{
   while(1);
}

__WEAK void IRQ16_Handler(void)
{
   while(1);
}

__WEAK void IRQ17_Handler(void)
{
   while(1);
}

__WEAK void IRQ18_Handler(void)
{
   while(1);
}

__WEAK void IRQ19_Handler(void)
{
   while(1);
}

__WEAK void IRQ20_Handler(void)
{
   while(1);
}

__WEAK void IRQ21_Handler(void)
{
   while(1);
}

__WEAK void IRQ22_Handler(void)
{
   while(1);
}

__WEAK void IRQ23_Handler(void)
{
   while(1);
}

__WEAK void IRQ24_Handler(void)
{
   while(1);
}

__WEAK void IRQ25_Handler(void)
{
   while(1);
}

__WEAK void IRQ26_Handler(void)
{
   while(1);
}

__WEAK void IRQ27_Handler(void)
{
   while(1);
}

__WEAK void IRQ28_Handler(void)
{
   while(1);
}

__WEAK void IRQ29_Handler(void)
{
   while(1);
}

__WEAK void IRQ30_Handler(void)
{
   while(1);
}

__WEAK void IRQ31_Handler(void)
{
   while(1);
}

//
// Reset Handler
//

extern void SystemInit(void); 
extern void __main(void);

//#pragma arm section code = "sec_resethandler"
void Reset_Handler(void)
{
  SystemInit();
  __main();
}
//#pragma arm section code


//
// Set up Vector Table
//

typedef void (*const vect_t)(void) __irq;

vect_t __Vectors[]
__attribute__ ((section("vectors"))) = {
  (vect_t)(STACK_TOP),      // Top of Stack
  (vect_t)Reset_Handler,    // Reset Handler
  (vect_t)NMI_Handler,      // NMI Handler
  (vect_t)HardFault_Handler,// Hard Fault Handler
  0,                        // Reserved
  0,                        // Reserved
  0,                        // Reserved
  0,                        // Reserved
  0,                        // Reserved
  0,                        // Reserved
  0,                        // Reserved
  (vect_t)SVC_Handler,      // SVCall Handler
  0,                        // Reserved
  0,                        // Reserved
  (vect_t)PendSV_Handler,   // PendSV Handler
  (vect_t)SysTick_Handler,  // SysTick Handler

  (vect_t)IRQ00_Handler,
  (vect_t)IRQ01_Handler,
  (vect_t)IRQ02_Handler,
  (vect_t)IRQ03_Handler,
  (vect_t)IRQ04_Handler,
  (vect_t)IRQ05_Handler,
  (vect_t)IRQ06_Handler,
  (vect_t)IRQ07_Handler,
  (vect_t)IRQ08_Handler,
  (vect_t)IRQ09_Handler,
  (vect_t)IRQ10_Handler,
  (vect_t)IRQ11_Handler,
  (vect_t)IRQ12_Handler,
  (vect_t)IRQ13_Handler,
  (vect_t)IRQ14_Handler,
  (vect_t)IRQ15_Handler,
  (vect_t)IRQ16_Handler,
  (vect_t)IRQ17_Handler,
  (vect_t)IRQ18_Handler,
  (vect_t)IRQ19_Handler,
  (vect_t)IRQ20_Handler,
  (vect_t)IRQ21_Handler,
  (vect_t)IRQ22_Handler,
  (vect_t)IRQ23_Handler,
  (vect_t)IRQ24_Handler,
  (vect_t)IRQ25_Handler,
  (vect_t)IRQ26_Handler,
  (vect_t)IRQ27_Handler,
  (vect_t)IRQ28_Handler,
  (vect_t)IRQ29_Handler,
  (vect_t)IRQ30_Handler,
  (vect_t)IRQ31_Handler,
};


//
// Set up initial stack and heap
//

__value_in_regs struct __initial_stackheap
__user_initial_stackheap(unsigned hb, unsigned sb, unsigned hl, unsigned sl)
{
  struct __initial_stackheap s;

  s.heap_base   = hb;
  s.stack_base  = sb;
  s.heap_limit  = s.stack_base;
  s.stack_limit = s.heap_base;
  return s;
}


//
// Default exit function
//

__WEAK void _sys_exit(int return_code)
{
  while(1);
}
