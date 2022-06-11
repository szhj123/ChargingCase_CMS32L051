/********************************************************
* @file       hal_interrupt.c
* @author     szhj13
* @version    V1.0
* @date       2022-06-06
* @brief      the start address of program
**********************************************************
* @Modify

**********************************************************/

/* Includes ---------------------------------------------*/
#include "hal_task.h"
#include "hal_timer.h"
#include "hal_com.h"
/* Private typedef --------------------------------------*/
/* Private define ---------------------------------------*/
/* Private macro ----------------------------------------*/
/* Private function -------------------------------------*/
void IRQ17_Handler(void) __attribute__((alias("tm40_channel0_interrupt")));
void IRQ11_Handler(void) __attribute__((alias("uart0_interrupt_receive")));
void IRQ10_Handler(void) __attribute__((alias("uart0_interrupt_send")));
/* Private variables ------------------------------------*/

void SysTick_Handler(void )
{
    Hal_Task_Isr_Handler();
}

void tm40_channel0_interrupt(void )
{
    INTC_ClearPendingIRQ(TM00_IRQn);    /* clear INTTM00 interrupt flag */
    
    Hal_Timer_Isr_Handler();
}

void uart0_interrupt_receive(void )
{
    INTC_ClearPendingIRQ(SR0_IRQn);
    
    Hal_Com_Rx_Isr_Handler();
}

void uart0_interrupt_send(void )
{
    INTC_ClearPendingIRQ(ST0_IRQn);

    Hal_Com_Tx_Isr_Handler();
}

