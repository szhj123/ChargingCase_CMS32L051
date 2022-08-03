/********************************************************
* @file       hal_key.c
* @author     szhj13
* @version    V1.0
* @date       2022-06-06
* @brief      the start address of program
**********************************************************
* @Modify

**********************************************************/

/* Includes ---------------------------------------------*/
#include "hal_key.h"

/* Private typedef --------------------------------------*/
/* Private define ---------------------------------------*/
/* Private macro ----------------------------------------*/
/* Private function -------------------------------------*/
/* Private variables ------------------------------------*/
Hal_Isr_Callback_t tws_case_isr_callback = NULL;


void Hal_Key_Init(void )
{
    Cms32l051_Gpio_Init();
    
    Cms32l051_Intp_Init();
}

void Hal_Key_Regist_Isr_Callback(Hal_Isr_Callback_t callback )
{
    tws_case_isr_callback = callback;
}

void Hal_Key_Isr_Handler(void )
{
    if(tws_case_isr_callback != NULL)
    {
        tws_case_isr_callback();
    }
}

void Hal_Key_Tx_High(void )
{
    PORT_SetBit(PORT2, PIN0);
}

void Hal_Key_Tx_Low(void )
{
    PORT_ClrBit(PORT2, PIN0);
}

uint8_t Hal_Key_Get_Hall_State(void )
{
    return PORT_GetBit(PORT5, PIN0);
}

