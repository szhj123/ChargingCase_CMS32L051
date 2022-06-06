/**************************************************************************//**
 * @file     system_CMS32L051.h
 * @brief    CMSIS Cortex-M0+ Device Peripheral Access Layer Header File for
 *           Device CMS32L051
 * @version  V1.00
 * @date     2019/04/23
 ******************************************************************************/
/*
 * Copyright (c) 2009-2018 Arm Limited. All rights reserved.
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
 */

#ifndef SYSTEM_CMS32L051_H
#define SYSTEM_CMS32L051_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

extern uint32_t SystemCoreClock;     /*!< System Clock Frequency (Core Clock)  */


/**
  \brief Setup the microcontroller system.

   Initialize the System and update the SystemCoreClock variable.
 */
extern void SystemInit (void);


/**
  \brief  Update SystemCoreClock variable.

   Updates the SystemCoreClock with current core Clock retrieved from cpu registers.
 */
extern void SystemCoreClockUpdate (void);


/* =========================================================================================================================== */
/* ================                               INTC Function ProtoTypes                          	      ================ */
/* =========================================================================================================================== */

/** @addtogroup INTC_Function_ProtoTypes
  * @{
  */

typedef struct {
   __IO uint8_t  	IFL;
   __IO uint8_t  	RESERVED[3];
}  R_INT_IF_Type;

typedef struct {
   __IO uint8_t  	MKL;
   __IO uint8_t  	RESERVED[3];
}  R_INT_MK_Type;

typedef struct {
   R_INT_IF_Type     	IF[32];
   uint32_t   		RESERVED[32];
   R_INT_MK_Type     	MK[32];
}  R_INT_Type;

#define R_INT_BASE	(0x40006000UL)           /*!< (INTC     ) Base Address */
#define R_INT		((R_INT_Type            *) R_INT_BASE)
	
// __STATIC_INLINE void INTC_EnableIRQ(IRQn_Type IRQn)
// {
//   R_INT->MK[IRQn].MKL = 0;
// }
//#define INTC_EnableIRQ(IRQn) *((volatile uint8_t*)((volatile uint8_t*)(&R_INT->MK[0])+4*(IRQn % 32)+(IRQn / 32))) = 0;
#define INTC_EnableIRQ(IRQn) *((volatile uint8_t*)((volatile uint8_t*)(&R_INT->MK[0])+4*(IRQn))) = 0;

// __STATIC_INLINE void INTC_DisableIRQ(IRQn_Type IRQn)
// {
//   R_INT->MK[IRQn].MKL = 1;
// }
//#define INTC_DisableIRQ(IRQn) *((volatile uint8_t*)((volatile uint8_t*)(&R_INT->MK[0])+4*(IRQn % 32)+(IRQn / 32))) = 1;
#define INTC_DisableIRQ(IRQn) *((volatile uint8_t*)((volatile uint8_t*)(&R_INT->MK[0])+4*(IRQn))) = 1;

// __STATIC_INLINE void INTC_ClearPendingIRQ(IRQn_Type IRQn)
// {
//   R_INT->IF[IRQn].IFL = 0;
// }
//#define INTC_ClearPendingIRQ(IRQn) *((volatile uint8_t*)((volatile uint8_t*)(&R_INT->IF[0])+4*(IRQn % 32)+(IRQn / 32))) = 0;
#define INTC_ClearPendingIRQ(IRQn) *((volatile uint8_t*)((volatile uint8_t*)(&R_INT->IF[0])+4*(IRQn))) = 0;

// __STATIC_INLINE void INTC_SetPendingIRQ(IRQn_Type IRQn)
// {
//   R_INT->IF[IRQn].IFL = 1;
// }
//#define INTC_SetPendingIRQ(IRQn) *((volatile uint8_t*)((volatile uint8_t*)(&R_INT->IF[0])+4*(IRQn % 32)+(IRQn / 32))) = 1;
#define INTC_SetPendingIRQ(IRQn) *((volatile uint8_t*)((volatile uint8_t*)(&R_INT->IF[0])+4*(IRQn))) = 1;

// __STATIC_INLINE uint8_t INTC_GetPendingIRQ(IRQn_Type IRQn)
// {
//     return (R_INT->IF[IRQn].IFL);
// }
//#define INTC_GetPendingIRQ(IRQn) (*((volatile uint8_t*)((volatile uint8_t*)(&R_INT->IF[0])+4*(IRQn % 32)+(IRQn / 32))))
#define INTC_GetPendingIRQ(IRQn) (*((volatile uint8_t*)((volatile uint8_t*)(&R_INT->IF[0])+4*(IRQn))))

/* Enable Interrupt */
#define __EI  	__set_PRIMASK(0)
/* Disable Interrupt */
#define __DI  	__set_PRIMASK(1)

/* Enter sleep mode */
#define __HALT() 	do { \
						SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;\
						__WFI();\
					} while (0U)

#define __SLEEP    __HALT

/* Enter deep sleep mode */
#define __STOP() 	do { \
						SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;\
						__WFI();\
					} while (0U)

/** @} */ /* End of group INTC_Function_ProtoTypes */

#ifdef __cplusplus
}
#endif

#endif /* SYSTEM_CMS32L051_H */
