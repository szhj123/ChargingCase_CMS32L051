/********************************************************
* @file       drv_battery.c
* @author     szhj13
* @version    V1.0
* @date       2022-06-06
* @brief      the start address of program
**********************************************************
* @Modify

**********************************************************/

/* Includes ---------------------------------------------*/
#include "drv_battery.h"

/* Private typedef --------------------------------------*/
/* Private define ---------------------------------------*/
/* Private macro ----------------------------------------*/
/* Private function -------------------------------------*/
/* Private variables ------------------------------------*/
uint16_t battVol;

void Drv_Batt_Init(void )
{
    Hal_Batt_Init();    

    battVol = Drv_Batt_Get_BatVol();
}

uint16_t Drv_Batt_Get_BatVol(void )
{
    uint16_t batVol;
    
    batVol = (INTER_REF_VOL * 4096) / Hal_Batt_Get_AdcVal(ADC_INTERREFVOLT);

    return batVol;
}


