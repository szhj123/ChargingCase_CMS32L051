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
    Cms32l051_Uart1_Init();
}

void Hal_Com_Regist_Rx_Callback(hal_com_rx_end_callback_t callback )
{
    hal_com_rx_end_callback = callback;
}

void Hal_Com_Tx_With_Interrupt(uint8_t *buf, uint16_t length, hal_com_tx_end_callback_t callback )
{
    if(buf == NULL || length <=0 )
    {
        return ;
    }
    
    INTC_ClearPendingIRQ(ST1_IRQn); /* clear INTST2 interrupt flag */
    NVIC_ClearPendingIRQ(ST1_IRQn); /* clear INTST2 interrupt flag */
    INTC_EnableIRQ(ST1_IRQn);       /* enable INTST2 interrupt */

    txPtr = buf;
    txLength = length;
    txCnt = 0;
    hal_com_tx_end_callback = callback;

    SCI0->TXD1 = buf[0];
    txPtr++;
    txCnt++;
}   

void Hal_Com_Tx_Isr_Handler(void )
{
    if(txCnt < txLength)
    {
        SCI0->TXD1 = *txPtr;
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
            INTC_DisableIRQ(ST1_IRQn);
            hal_com_tx_end_callback();
        }
    }
}

void Hal_Com_Rx_Isr_Handler(void )
{
    volatile uint8_t rx_data;
    
    rx_data = SCI0->RXD1;

    if(hal_com_rx_end_callback != NULL)
    {
        hal_com_rx_end_callback(rx_data);
    }
    
}

