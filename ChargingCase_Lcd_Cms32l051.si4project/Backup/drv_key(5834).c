/********************************************************
* @file       drv_key.c
* @author     szhj13
* @version    V1.0
* @date       2022-06-06
* @brief      the start address of program
**********************************************************
* @Modify

**********************************************************/

/* Includes ---------------------------------------------*/
#include "drv_key.h"

/* Private typedef --------------------------------------*/
/* Private define ---------------------------------------*/
/* Private macro ----------------------------------------*/
/* Private function -------------------------------------*/
/* Private variables ------------------------------------*/

void Drv_Key_Init(void )
{
    Hal_Key_Init();
}

void Drv_Key_Regist_Isr_Callback(Hal_Isr_Callback_t callback )
{
    Hal_Key_Regist_Isr_Callback(callback);
}

void Drv_Key_Tx_High(void )
{
    Hal_Key_Tx_High();
}

void Drv_Key_Tx_Low(void )
{
    Hal_Key_Tx_Low();
}

uint8_t Drv_Key_Get_Hall_State(void )
{
    return Hal_Key_Get_Hall_State();
}

