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

void Drv_Batt_Boost_Enable(void )
{
    Hal_Batt_Boost_Enable();
}

void Drv_Batt_Boost_Disable(void )
{
    Hal_Batt_Boost_Disable();
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
    
    batVol = (EXTER_REF_VOL * Hal_Batt_Get_AdcVal(ADC_CHANNEL_10) * 3) >> 12;

    return batVol;
}

uint16_t Drv_Earbud_Get_Cur_L(void )
{
    uint16_t earbudCur;
    
    earbudCur = (EXTER_REF_VOL * Hal_Batt_Get_AdcVal(ADC_CHANNEL_32)) >> 13;

    return earbudCur;
}

uint16_t Drv_Earbud_Get_Cur_R(void )
{
    uint16_t earbudCur;
    	
    earbudCur = (EXTER_REF_VOL * Hal_Batt_Get_AdcVal(ADC_CHANNEL_33)) >> 13;

    return earbudCur;
}



