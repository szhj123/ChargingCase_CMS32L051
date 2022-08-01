/********************************************************
* @file       hal_com.c
* @author     szhj13
* @version    V1.0
* @date       2022-06-06
* @brief      the start address of program
**********************************************************
* @Modify

**********************************************************/

/* Includes ---------------------------------------------*/
#include "hal_com.h"

/* Private typedef --------------------------------------*/
/* Private define ---------------------------------------*/
/* Private macro ----------------------------------------*/
/* Private function -------------------------------------*/
/* Private variables ------------------------------------*/
hal_com_tx_end_callback_t hal_com_tx_end_callback = NULL; 
hal_com_rx_end_callback_t hal_com_rx_end_callback = NULL;

static uint8_t *txPtr = NULL;
static uint16_t txCnt;
static uint16_t txLength;


void Hal_Com_Init(void )
{
    SystemCoreClockUpdate();

    UART0_Init(SystemCoreClock, 115200);

    INTC_EnableIRQ(SR0_IRQn);
}

void Hal_Com_Regist_Rx_Callback(hal_com_rx_end_callback_t callback )
{
    hal_com_rx_end_callback = callback;
}

void Hal_Com_Send_With_Interrupt(uint8_t *buf, uint16_t length, hal_com_tx_end_callback_t callback )
{
    if(buf == NULL || length <=0 )
    {
        return ;
    }
    
    INTC_ClearPendingIRQ(ST0_IRQn); /* clear INTST1 interrupt flag */
    NVIC_ClearPendingIRQ(ST0_IRQn); /* clear INTST1 interrupt flag */
    INTC_EnableIRQ(ST0_IRQn);       /* enable INTST1 interrupt */

    txPtr = buf;
    txLength = length;
    txCnt = 0;
    hal_com_tx_end_callback = callback;

    SCI0->TXD0 = buf[0];
    txPtr++;
    txCnt++;
}   

void Hal_Com_Tx_Isr_Handler(void )
{
    if(txCnt < txLength)
    {
        SCI0->TXD0 = *txPtr;
        txPtr++;
        txCnt++;
    }
    else
    {
        txPtr = NULL;
        txCnt = 0;
        txLength = 0;

        if(hal_com_tx_end_callback != NULL)
        {
            INTC_DisableIRQ(ST0_IRQn);
            hal_com_tx_end_callback();
        }
    }
}

void Hal_Com_Rx_Isr_Handler(void )
{
    volatile uint8_t rx_data;
    volatile uint8_t err_type;
    
    err_type = (uint8_t)(SCI0->SSR01 & 0x0007U);
    SCI0->SIR01 = (uint16_t)err_type;
    
    rx_data = SCI0->RXD0;

    if(hal_com_rx_end_callback != NULL)
    {
        hal_com_rx_end_callback(rx_data);
    }
    
}

