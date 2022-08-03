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
}

uint8_t Drv_Batt_Get_Usb_State(void )
{
    if(Hal_Batt_Get_Usb_State())
    {
        return USB_PLUG_IN;
    }
    else
    {
        return USB_PLUG_OUT;
    }
}

uint8_t Drv_Batt_Get_Charing_State(void )
{
    return Hal_Batt_Get_Charging_State();
} 

uint16_t Drv_Batt_Get_BatVol(void )
{
    uint16_t batVol;
    
    batVol = (INTER_REF_VOL * 4096) / Hal_Batt_Get_AdcVal(ADC_INTERREFVOLT);

    return batVol;
}

uint16_t Drv_Earbud_Get_Cur_L(void )
{
    uint16_t earbudCur;
    
    earbudCur = (INTER_REF_VOL * Hal_Batt_Get_AdcVal(ADC_CHANNEL_32)) / Hal_Batt_Get_AdcVal(ADC_INTERREFVOLT);
	
    return earbudCur;
}

uint16_t Drv_Earbud_Get_Cur_R(void )
{
    uint16_t earbudCur;
    
    earbudCur = (INTER_REF_VOL * Hal_Batt_Get_AdcVal(ADC_CHANNEL_33)) / Hal_Batt_Get_AdcVal(ADC_INTERREFVOLT);
	
    return earbudCur;
}



