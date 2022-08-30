/********************************************************
* @file       hal_battery.c
* @author     szhj13
* @version    V1.0
* @date       2022-06-06
* @brief      the start address of program
**********************************************************
* @Modify

**********************************************************/

/* Includes ---------------------------------------------*/
#include "hal_battery.h"

/* Private typedef --------------------------------------*/
/* Private define ---------------------------------------*/
/* Private macro ----------------------------------------*/
/* Private function -------------------------------------*/
/* Private variables ------------------------------------*/

void Hal_Batt_Init(void )
{
    Cms32l051_Gpio_Init();

    Cms32l051_Intp_Init();

    Cms32l051_Adc_Init();
}

void Hal_Batt_Boost_Enable(void )
{
    PORT_SetBit(PORT2, PIN0);
}

void Hal_Batt_Boost_Disable(void )
{
    PORT_ClrBit(PORT2, PIN0);
}

uint8_t Hal_Batt_Get_Usb_State(void )
{
    return PORT_GetBit(PORT3, PIN0);
}

uint8_t Hal_Batt_Get_Charging_State(void )
{
    return PORT_GetBit(PORT2, PIN1);
}

uint16_t Hal_Batt_Get_AdcVal(adc_channel_t adcChannel)
{
    uint16_t tmpBuf[16];
    
    ADC_Converse(adcChannel, sizeof(tmpBuf)/sizeof(tmpBuf[0]), tmpBuf);

    return ADC_MidAvg_Filter(tmpBuf, sizeof(tmpBuf)/sizeof(tmpBuf[0]));
}


