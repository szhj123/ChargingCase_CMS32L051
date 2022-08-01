/********************************************************
* @file       app_battery.c
* @author     szhj13
* @version    V1.0
* @date       2022-06-06
* @brief      the start address of program
**********************************************************
* @Modify

**********************************************************/

/* Includes ---------------------------------------------*/
#include "app_battery.h"
#include "drv_task.h"
/* Private typedef --------------------------------------*/
/* Private define ------------------ --------------------*/
#define ADC_DET_COUNT                100  
/* Private macro ---------------------------------------*/
/* Private function ---------------------------------- --*/
/* Private variables ------------------------------------*/
batt_para_t battPara;

void App_Batt_Init(void )
{
    Drv_Batt_Init();

    Drv_Task_Regist_Period(App_Batt_Handler, 0, 100, NULL);
}

static void App_Batt_Handler(void *arg )
{
    static uint8_t battSampleEndFlag;
    
    Drv_Batt_Adc_Sample(&battSampleEndFlag);

    if(!battSampleEndFlag)
    {
        return ;
    }

    if(Drv_Batt_Get_Usb_State() == USB_PLUG_OUT)
    {
        battPara.chgState = CHG_STATE_INIT;
        
        App_Batt_Discharging_Handler();
    }
    else
    {
        battPara.dischgState = DISCHG_STATE_INIT;
        
        App_Batt_Charging_Handler();
    }
}

static void Drv_Batt_Adc_Sample(uint8_t *battSampleEndFlag )
{
    static uint16_t adcSampleCnt;
    static uint32_t batVolSum;
    static uint32_t earbudCurSum_l;
    static uint32_t earbudCurSum_r;

    uint16_t tmpBatVol;
    uint16_t tmpEarbudCur_l;
    uint16_t tmpEarbudCur_r;
	    
    tmpBatVol = Drv_Batt_Get_BatVol();
        
    tmpEarbudCur_l = Drv_Earbud_Get_Cur_L();
    
    tmpEarbudCur_r = Drv_Earbud_Get_Cur_R();

    *battSampleEndFlag = 0;

    if(adcSampleCnt < ADC_DET_COUNT)
    {            
        
        batVolSum += tmpBatVol;
        earbudCurSum_l += tmpEarbudCur_l;
        earbudCurSum_r += tmpEarbudCur_r;
        
        adcSampleCnt++;
    }
    else
    {
        App_Batt_Set_BatVol(batVolSum / ADC_DET_COUNT);
        App_Earbud_Set_Cur_L(earbudCurSum_l / ADC_DET_COUNT);
        App_Earbud_Set_Cur_R(earbudCurSum_r / ADC_DET_COUNT);
     
        *battSampleEndFlag = 1;

        adcSampleCnt = 0;
        batVolSum = 0;
        earbudCurSum_l = 0;
        earbudCurSum_r = 0;
    } 
}

static void App_Batt_Discharging_Handler(void )
{
    static batt_level_state_t saveBattLevel;
    static earbud_chg_state_t saveEarbudChg_l;
    static earbud_chg_state_t saveEarbudChg_r;
    
    switch(battPara.dischgState)
    {
        case DISCHG_STATE_INIT:
        {
            saveBattLevel = App_Batt_Get_Level();

            saveEarbudChg_l = App_Earbud_Get_Chg_State_L();

            saveEarbudChg_r = App_Earbud_Get_Chg_State_R();
            
            break;
        }
        case DISCH_STATE_HANDLER:
        {
            break;
        }
        default: break;
    }
}

static void App_Batt_Charging_Handler(void )
{
    
}

uint16_t App_Batt_Get_Level(void )
{
    static const uint8_t battErrVol = 25; //ms
    
    if(battPara.battLevel == 0)
    {
        if(battPara.battVol >= BATT_VOL_90)
        {
            battPara.battLevel = BATT_LEVEL_90;
        }
        else if(battPara.battVol >=BATT_VOL_80 && battPara.battVol < BATT_VOL_90)
        {
            battPara.battLevel = BATT_LEVEL_80;
        }
        else if(battPara.battVol >=BATT_VOL_70 && battPara.battVol < BATT_VOL_80)
        {
            battPara.battLevel = BATT_LEVEL70;
        }
        else if(battPara.battVol >=BATT_VOL_60 && battPara.battVol < BATT_VOL_70)
        {
            battPara.battLevel = BATT_LEVEL_60;
        }
        else if(battPara.battVol >=BATT_VOL_50 && battPara.battVol < BATT_VOL_60)
        {
            battPara.battLevel = BATT_LEVEL_50;
        }
        else if(battPara.battVol >=BATT_VOL_40 && battPara.battVol < BATT_VOL_50)
        {
            battPara.battLevel = BATT_LEVEL_40;
        }
        else if(battPara.battVol >=BATT_VOL_30 && battPara.battVol < BATT_VOL_40)
        {
            battPara.battLevel = BATT_LEVEL_30;
        }
        else if(battPara.battVol >=BATT_VOL_20 && battPara.battVol < BATT_VOL_30)
        {
            battPara.battLevel = BATT_LEVEL_20;
        }
        else if(battPara.battVol >=BATT_VOL_10 && battPara.battVol < BATT_VOL_20)
        {
            battPara.battLevel = BATT_LEVEL_10;
        }
        else if(battPara.battVol >=BATT_VOL_5 && battPara.battVol < BATT_VOL_10)
        {
            battPara.battLevel = BATT_LEVEL_5;
        }
        else
        {
            if(battPara.battVol < BATT_VOL_0)
            {
                battPara.battLevel = BATT_LEVEL_0;
            }
            else
            {
                battPara.battLevel = BATT_LEVEL_5;
            }
        }
    }
    else
    {
        if(battPara.battLevel == BATT_LEVEL_100)
        {
            if(battPara.battVol < (BATT_VOL_100 - battErrVol))
            {
                battPara.battLevel = BATT_LEVEL_90;
            }
        }
        else if(battPara.battLevel == BATT_LEVEL_90)
        {
            
        }
    }
}

void App_Batt_Set_BatVol(uint16_t battVol )
{
    battPara.battVol = battVol;
}

uint16_t App_Batt_Get_BatVol(void )
{
    return battPara.battVol;
}

void App_Earbud_Set_Cur_L(uint16_t earbudCur )
{
    battPara.earbudCur_l = earbudCur;
}

uint16_t App_Earbud_Get_Cur_L(void )
{
    return battPara.earbudCur_l;
}

void App_Earbud_Set_Cur_R(uint16_t earbudCur )
{
    battPara.earbudCur_r = earbudCur;
}

uint16_t App_Earbud_Get_Cur_R(void )
{
    return battPara.earbudCur_r;
}


