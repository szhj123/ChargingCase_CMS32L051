;/**************************************************************************//**
; * @file     startup_CMS32L051.s
; * @brief    CMSIS Cortex-M0+ Core Device Startup File for
; *           Device CMS32L051
; * @version  V1.00
; * @date     2019/04/26
; ******************************************************************************/
;/*
; * Copyright (c) 2009-2016 ARM Limited. All rights reserved.
; *
; * SPDX-License-Identifier: Apache-2.0
; *
; * Licensed under the Apache License, Version 2.0 (the License); you may
; * not use this file except in compliance with the License.
; * You may obtain a copy of the License at
; *
; * www.apache.org/licenses/LICENSE-2.0
; *
; * Unless required by applicable law or agreed to in writing, software
; * distributed under the License is distributed on an AS IS BASIS, WITHOUT
; * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
; * See the License for the specific language governing permissions and
; * limitations under the License.
; */


;
; The modules in this file are included in the libraries, and may be replaced
; by any user-defined modules that define the PUBLIC symbol _program_start or
; a user defined start symbol.
; To override the cstartup defined in the library, simply add your modified
; version to the workbench project.
;
; The vector table is normally located at address 0.
; When debugging in RAM, it can be located in RAM, aligned to at least 2^6.
; The name "__vector_table" has special meaning for C-SPY:
; it is where the SP start value is found, and the NVIC vector
; table register (VTOR) is initialized to this address if != 0.
;
; Cortex-M version
;

        MODULE  ?cstartup

        ;; Forward declaration of sections.
        SECTION CSTACK:DATA:NOROOT(3)

        SECTION .intvec:CODE:NOROOT(2)

        EXTERN  __iar_program_start
        EXTERN  SystemInit
        PUBLIC  __vector_table
        PUBLIC  __vector_table_0x1c
        PUBLIC  __Vectors
        PUBLIC  __Vectors_End
        PUBLIC  __Vectors_Size

        DATA

__vector_table
        DCD     sfe(CSTACK)
        DCD     Reset_Handler

        DCD     NMI_Handler
        DCD     HardFault_Handler
        DCD     0
        DCD     0
        DCD     0
__vector_table_0x1c
        DCD     0
        DCD     0
        DCD     0
        DCD     0
        DCD     SVC_Handler
        DCD     0
        DCD     0
        DCD     PendSV_Handler
        DCD     SysTick_Handler

        ; External Interrupts
; ToDo:  Add here the vectors for the device specific external interrupts handler
        DCD     IRQ00_Handler            ;  IRQ00: Handler
        DCD     IRQ01_Handler            ;  IRQ01: Handler
        DCD     IRQ02_Handler            ;  IRQ02: Handler
        DCD     IRQ03_Handler            ;  IRQ03: Handler
        DCD     IRQ04_Handler            ;  IRQ04: Handler
        DCD     IRQ05_Handler            ;  IRQ05: Handler
        DCD     IRQ06_Handler            ;  IRQ06: Handler
        DCD     IRQ07_Handler            ;  IRQ07: Handler
        DCD     IRQ08_Handler            ;  IRQ08: Handler
        DCD     IRQ09_Handler            ;  IRQ09: Handler
        DCD     IRQ10_Handler            ;  IRQ10: Handler
        DCD     IRQ11_Handler            ;  IRQ11: Handler
        DCD     IRQ12_Handler            ;  IRQ12: Handler
        DCD     IRQ13_Handler            ;  IRQ13: Handler
        DCD     IRQ14_Handler            ;  IRQ14: Handler
        DCD     IRQ15_Handler            ;  IRQ15: Handler
        DCD     IRQ16_Handler            ;  IRQ16: Handler
        DCD     IRQ17_Handler            ;  IRQ17: Handler
        DCD     IRQ18_Handler            ;  IRQ18: Handler
        DCD     IRQ19_Handler            ;  IRQ19: Handler
        DCD     IRQ20_Handler            ;  IRQ20: Handler
        DCD     IRQ21_Handler            ;  IRQ21: Handler
        DCD     IRQ22_Handler            ;  IRQ22: Handler
        DCD     IRQ23_Handler            ;  IRQ23: Handler
        DCD     IRQ24_Handler            ;  IRQ24: Handler
        DCD     IRQ25_Handler            ;  IRQ25: Handler
        DCD     IRQ26_Handler            ;  IRQ26: Handler
        DCD     IRQ27_Handler            ;  IRQ27: Handler
        DCD     IRQ28_Handler            ;  IRQ28: Handler
        DCD     IRQ29_Handler            ;  IRQ29: Handler
        DCD     IRQ30_Handler            ;  IRQ30: Handler
        DCD     IRQ31_Handler            ;  IRQ31: Handler
__Vectors_End

__Vectors       EQU   __vector_table
__Vectors_Size  EQU   __Vectors_End - __Vectors


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Default interrupt handlers.
;;
        THUMB

        PUBWEAK Reset_Handler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reset_Handler
        LDR     R0, =SystemInit
        BLX     R0
        LDR     R0, =__iar_program_start
        BX      R0

        PUBWEAK NMI_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
NMI_Handler
        B NMI_Handler

        PUBWEAK HardFault_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
HardFault_Handler
        B HardFault_Handler

        PUBWEAK SVC_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
SVC_Handler
        B SVC_Handler

        PUBWEAK PendSV_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
PendSV_Handler
        B PendSV_Handler

        PUBWEAK SysTick_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
SysTick_Handler
        B SysTick_Handler

; ToDo:  Add here the export definition for the device specific external interrupts handler
; ToDo:  Add here the names for the device specific external interrupts handler
        PUBWEAK IRQ00_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
IRQ00_Handler
        B IRQ00_Handler

        PUBWEAK IRQ01_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
IRQ01_Handler
        B IRQ01_Handler

        PUBWEAK IRQ02_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
IRQ02_Handler
        B IRQ02_Handler

        PUBWEAK IRQ03_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
IRQ03_Handler
        B IRQ03_Handler

        PUBWEAK IRQ04_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
IRQ04_Handler
        B IRQ04_Handler

        PUBWEAK IRQ05_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
IRQ05_Handler
        B IRQ05_Handler

        PUBWEAK IRQ06_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
IRQ06_Handler
        B IRQ06_Handler

        PUBWEAK IRQ07_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
IRQ07_Handler
        B IRQ07_Handler

        PUBWEAK IRQ08_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
IRQ08_Handler
        B IRQ08_Handler

        PUBWEAK IRQ09_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
IRQ09_Handler
        B IRQ09_Handler

        PUBWEAK IRQ10_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
IRQ10_Handler
        B IRQ10_Handler

        PUBWEAK IRQ11_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
IRQ11_Handler
        B IRQ11_Handler

        PUBWEAK IRQ12_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
IRQ12_Handler
        B IRQ12_Handler

        PUBWEAK IRQ13_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
IRQ13_Handler
        B IRQ13_Handler

        PUBWEAK IRQ14_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
IRQ14_Handler
        B IRQ14_Handler

        PUBWEAK IRQ15_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
IRQ15_Handler
        B IRQ15_Handler

        PUBWEAK IRQ16_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
IRQ16_Handler
        B IRQ16_Handler

        PUBWEAK IRQ17_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
IRQ17_Handler
        B IRQ17_Handler

        PUBWEAK IRQ18_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
IRQ18_Handler
        B IRQ18_Handler

        PUBWEAK IRQ19_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
IRQ19_Handler
        B IRQ19_Handler

        PUBWEAK IRQ20_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
IRQ20_Handler
        B IRQ20_Handler

        PUBWEAK IRQ21_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
IRQ21_Handler
        B IRQ21_Handler

        PUBWEAK IRQ22_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
IRQ22_Handler
        B IRQ22_Handler

        PUBWEAK IRQ23_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
IRQ23_Handler
        B IRQ23_Handler

        PUBWEAK IRQ24_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
IRQ24_Handler
        B IRQ24_Handler

        PUBWEAK IRQ25_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
IRQ25_Handler
        B IRQ25_Handler

        PUBWEAK IRQ26_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
IRQ26_Handler
        B IRQ26_Handler

        PUBWEAK IRQ27_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
IRQ27_Handler
        B IRQ27_Handler

        PUBWEAK IRQ28_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
IRQ28_Handler
        B IRQ28_Handler

        PUBWEAK IRQ29_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
IRQ29_Handler
        B IRQ29_Handler

        PUBWEAK IRQ30_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
IRQ30_Handler
        B IRQ30_Handler

        PUBWEAK IRQ31_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
IRQ31_Handler
        B IRQ31_Handler

        END
