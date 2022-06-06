/**************************************************************************//**
 * @file     system_CMS32L051.c
 * @brief    CMSIS Cortex-M0+ Device Peripheral Access Layer Source File for
 *           Device CMS32L051
 * @version  1.0.0
 * @date     2019/12/24
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

#include <stdint.h>
#include "CMS32L051.h"


/** @addtogroup Configuration_of_User_Option_Byte
  * @{
  */

typedef enum {
  HOCO_FREQ_64MHZ = 0xE8, 	/*!< fHOCO = 64MHz, fIH = 64MHz  	*/
  HOCO_FREQ_48MHZ = 0xE0, 	/*!< fHOCO = 48MHz, fIH = 48MHz  	*/
  HOCO_FREQ_32MHZ = 0xE9, 	/*!< fHOCO = 64MHz, fIH = 32MHz  	*/
  HOCO_FREQ_24MHZ = 0xE1, 	/*!< fHOCO = 48MHz, fIH = 24MHz  	*/
  HOCO_FREQ_16MHZ = 0xEA, 	/*!< fHOCO = 64MHz, fIH = 16MHz  	*/
  HOCO_FREQ_12MHZ = 0xE2, 	/*!< fHOCO = 48MHz, fIH = 12MHz  	*/
  HOCO_FREQ_8MHZ  = 0xEB, 	/*!< fHOCO = 64MHz, fIH =  8MHz  	*/
  HOCO_FREQ_6MHZ  = 0xE3, 	/*!< fHOCO = 48MHz, fIH =  6MHz  	*/
  HOCO_FREQ_4MHZ  = 0xEC, 	/*!< fHOCO = 64MHz, fIH =  4MHz  	*/
  HOCO_FREQ_3MHZ  = 0xE4, 	/*!< fHOCO = 48MHz, fIH =  3MHz  	*/
  HOCO_FREQ_2MHZ  = 0xED, 	/*!< fHOCO = 64MHz, fIH =  2MHz  	*/
} hoco_freq_t;

/*----------------------------------------------------------------------------
  User Option Byte 
 *----------------------------------------------------------------------------*/
/* ToDo: add here your necessary defines for device initialization
         following is an example for different system frequencies */

//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------
const uint8_t user_opt_data[4] __attribute__((used)) __attribute__((section(".ARM.__AT_0x000000C0"))) =
{

/**
 * @brief WDT Control BYTE
 * Please refer to the user manual for details.
 *     7   |    6    |    5    |   4   |   3   |   2   |   1   |   0
 * --------|---------|---------|-------|-------|-------|-------|----------
 *  WDTINT | WINDOW1 | WINDOW0 | WDTON | WDCS2 | WDCS1 | WDCS0 | WDSTBYON
 * --------|---------|---------|-------|-------|-------|-------|----------
 */
// <h> WDT Control Option Byte (C0H)
//   <e.4> Enable WDT (WDTON)
//     <o.5..6> Watchdog timer window open period setting      <2=> 75%        <3=> 100%
//     <o.1..3> Watchdog timer overflow time setting           <0=> 2^6/fIL    <1=> 2^7/fIL
//                                                             <2=> 2^8/fIL    <3=> 2^9/fIL
//                                                             <4=> 2^11/fIL   <5=> 2^13/fIL
//                                                             <6=> 2^14/fIL   <7=> 2^16/fIL
//     <e.0>    Operation in Standby mode setting (WDSTBYON)
//              <i> WDT Operaton in SLEEP/DEEPSLEEP mode.
//     </e>
//     <e.7>    interrupt enable
//              <i> interval interrupt is generated when 75% + 1/2 fIL of the overflow time is reached.
//     </e>
//   </e>
// </h>
    0xEF,

/**
 * @brief LVD Control BYTE (C1H)
 * Please refer to the user manual for details.
 *    7   |   6   |   5   |   4   |   3   |   2   |    1    |    0     
 * -------|-------|-------|-------|-------|-------|---------|----------
 *  VPOC2 | VPOC1 | VPOC0 |   1   | LVIS1 | LVIS0 | LVIMDS1 | LVIMDS0
 * -------|-------|-------|-------|-------|-------|---------|----------
 */
// <h> LVD Control Option Byte (C1H)
//     <o.0..7> Voltage detection setting (VLVD)              <0xFF=> ( LVD OFF )
//                                                            <0x3D=> VLVD = 1.88V/1.84V    ( interrupt mode )         
//                                                            <0x39=> VLVD = 1.98V/1.94V    ( interrupt mode )         
//                                                            <0x35=> VLVD = 2.09V/2.04V    ( interrupt mode )         
//                                                            <0x5D=> VLVD = 2.50V/2.45V    ( interrupt mode )         
//                                                            <0x59=> VLVD = 2.61V/2.55V    ( interrupt mode )         
//                                                            <0x55=> VLVD = 2.71V/2.65V    ( interrupt mode )         
//                                                            <0x7D=> VLVD = 2.81V/2.75V    ( interrupt mode )         
//                                                            <0x79=> VLVD = 2.92V/2.86V    ( interrupt mode )         
//                                                            <0x75=> VLVD = 3.02V/2.96V    ( interrupt mode )         
//                                                            <0x3F=> VLVD = 1.88V/1.84V    ( reset mode )             
//                                                            <0x3B=> VLVD = 1.98V/1.94V    ( reset mode )             
//                                                            <0x37=> VLVD = 2.09V/2.04V    ( reset mode )             
//                                                            <0x5F=> VLVD = 2.50V/2.45V    ( reset mode )             
//                                                            <0x5B=> VLVD = 2.61V/2.55V    ( reset mode )             
//                                                            <0x57=> VLVD = 2.71V/2.65V    ( reset mode )             
//                                                            <0x7F=> VLVD = 2.81V/2.75V    ( reset mode )             
//                                                            <0x7B=> VLVD = 2.92V/2.86V    ( reset mode )             
//                                                            <0x77=> VLVD = 3.02V/2.96V    ( reset mode )             
//                                                            <0x3A=> VLVDH = 1.98V/1.94V, VLVDL = 1.84V    ( interrupt & reset mode ) 
//                                                            <0x36=> VLVDH = 2.09V/2.04V, VLVDL = 1.84V    ( interrupt & reset mode ) 
//                                                            <0x32=> VLVDH = 3.13V/3.06V, VLVDL = 1.84V    ( interrupt & reset mode ) 
//                                                            <0x5A=> VLVDH = 2.61V/2.55V, VLVDL = 2.45V    ( interrupt & reset mode ) 
//                                                            <0x56=> VLVDH = 2.71V/2.65V, VLVDL = 2.45V    ( interrupt & reset mode ) 
//                                                            <0x52=> VLVDH = 3.75V/3.67V, VLVDL = 2.45V    ( interrupt & reset mode ) 
//                                                            <0x7A=> VLVDH = 2.92V/2.86V, VLVDL = 2.75V    ( interrupt & reset mode ) 
//                                                            <0x76=> VLVDH = 3.02V/2.96V, VLVDL = 2.75V    ( interrupt & reset mode ) 
//                                                            <0x72=> VLVDH = 4.06V/3.98V, VLVDL = 2.75V    ( interrupt & reset mode ) 
//              <i> Please setting the item for interrupt & reset mode
// </h>
    0xFF,

/**
 * @brief HOCO Control BYTE (FRQSEL)
 * Please refer to the user manual for details.
 *    7   |   6   |   5   |    4    |    3    |    2    |    1    |    0    
 * -------|-------|-------|---------|---------|---------|---------|---------
 *    1   |   1   |   1   | FRQSEL4 | FRQSEL3 | FRQSEL2 | FRQSEL1 | FRQSEL0 
 * -------|-------|-------|---------|---------|---------|---------|---------
 */
// <h> HOCO Control Option Byte (C2H)
//   <o.0..4> High-speed OCO clock setting                  <0xE8=> fHOCO = 64MHz, fIH = 64MHz
//                                                          <0xE0=> fHOCO = 48MHz, fIH = 48MHz
//                                                          <0xE9=> fHOCO = 64MHz, fIH = 32MHz
//                                                          <0xE1=> fHOCO = 48MHz, fIH = 24MHz
//                                                          <0xEA=> fHOCO = 64MHz, fIH = 16MHz
//                                                          <0xE2=> fHOCO = 48MHz, fIH = 12MHz
//                                                          <0xEB=> fHOCO = 64MHz, fIH =  8MHz
//                                                          <0xE3=> fHOCO = 48MHz, fIH =  6MHz
//                                                          <0xEC=> fHOCO = 64MHz, fIH =  4MHz
//                                                          <0xE4=> fHOCO = 48MHz, fIH =  3MHz
//                                                          <0xED=> fHOCO = 64MHz, fIH =  2MHz
// </h>
    0xEA, 

/**
 * @brief Flash Protect Control BYTE
 * Please refer to the user manual for details.
 */
// <h> OCD Control Option Byte (C3H)
//   <o.0..7> On-chip debug setting (OCDEN)                 <0xFF=> Enable  <0xC3=> Disable
//            <i> OCDM(500004H) == 0x3C && OCDEN == 0xC3: Debugger can not erease/write/read Flash.
//            <i> OCDM(500004H) != 0x3C && OCDEN == 0xC3: Debugger can only chip erease Flash but cannot write/read Flash.
// </h>
    0xFF

};

//-------- <<< end of configuration section >>> ------------------
/** @} */ /* End of group Configuration_of_User_Option_Byte */

/*----------------------------------------------------------------------------
  System Core Clock Variable
 *----------------------------------------------------------------------------*/
/* ToDo: initialize SystemCoreClock with the system core clock frequency value
         achieved after system intitialization.
         This means system core clock frequency after call to SystemInit() */
uint32_t SystemCoreClock;  		/* System Clock Frequency (Core Clock)*/



/*----------------------------------------------------------------------------
  Clock functions
 *----------------------------------------------------------------------------*/
uint32_t CLK_GetHocoFreq(void)
{

  uint32_t freq;
  uint8_t  frqsel  = (*(uint8_t *)0x000000C2U);
           frqsel &= 0xF8;  	/* Mask the lower 3 bits */
           frqsel |= CGC->HOCODIV;	/* Refer the value of HOCODIV */ 
		   
  freq = 1000000U;  /* fIH = 1MHz except for the following cases */
		
  switch(frqsel)
  {
      case HOCO_FREQ_64MHZ: 
          freq = 64000000U; 	/* fIH = 64MHz 	*/
          break;
      case HOCO_FREQ_48MHZ: 
          freq = 48000000U; 	/* fIH = 48MHz 	*/
          break;
      case HOCO_FREQ_32MHZ: 
          freq = 32000000U; 	/* fIH = 32MHz 	*/
          break;
      case HOCO_FREQ_24MHZ: 
          freq = 24000000U; 	/* fIH = 24MHz 	*/
          break;
      case HOCO_FREQ_16MHZ: 
          freq = 16000000U; 	/* fIH = 16MHz 	*/
          break;
      case HOCO_FREQ_12MHZ: 
          freq = 12000000U; 	/* fIH = 12MHz 	*/
          break;
      case HOCO_FREQ_8MHZ: 
          freq = 8000000U; 	/* fIH = 8MHz 	*/
          break;
      case HOCO_FREQ_6MHZ: 
          freq = 6000000U; 	/* fIH = 6MHz 	*/
          break;
      case HOCO_FREQ_4MHZ: 
          freq = 4000000U; 	/* fIH = 4MHz 	*/
          break;
      case HOCO_FREQ_3MHZ: 
          freq = 3000000U; 	/* fIH = 3MHz 	*/
          break;
      case HOCO_FREQ_2MHZ: 
          freq = 2000000U; 	/* fIH = 2MHz 	*/
          break;
  }

  return(freq);
}

void SystemCoreClockUpdate (void)            /* Get Core Clock Frequency      */
{
/* ToDo: add code to calculate the system frequency based upon the current
         register settings.
         This function can be used to retrieve the system core clock frequeny
         after user changed register sittings. */
  SystemCoreClock = CLK_GetHocoFreq();
}

void SystemInit (void)
{
/* ToDo: add code to initialize the system
         do not use global variables because this function is called before
         reaching pre-main. RW section maybe overwritten afterwards. */

  /* RAM Parity Error Reset Disable */
  SAF->RPECTL = 0x80U;

  CGC->WDTCFG0 = 0x1A;
  CGC->WDTCFG1 = 0x2B;
  CGC->WDTCFG2 = 0x3C;
  CGC->WDTCFG3 = 0x4D;
  DBG->DBGSTOPCR = 0;

  SystemCoreClock = CLK_GetHocoFreq();

  /* NVIC Clear Pending IRQ */
  NVIC->ICPR[0U] = 0xFFFFFFFF;

  /* NVIC Enable IRQs */
  NVIC->ISER[0U] = 0xFFFFFFFF;

  /* NVIC Lower Priority */
  NVIC->IP[0U] = 0xC0C0C0C0;
  NVIC->IP[1U] = 0xC0C0C0C0;
  NVIC->IP[2U] = 0xC0C0C0C0;
  NVIC->IP[3U] = 0xC0C0C0C0;
  NVIC->IP[4U] = 0xC0C0C0C0;
  NVIC->IP[5U] = 0xC0C0C0C0;
  NVIC->IP[6U] = 0xC0C0C0C0;
  NVIC->IP[7U] = 0xC0C0C0C0;

  /* restart watchdog timer */
  WDT->WDTE = 0xACU;   
}
