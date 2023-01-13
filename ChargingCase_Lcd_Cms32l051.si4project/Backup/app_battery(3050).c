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
#include "app_lcd.h"
#include "app_key.h"
#include "drv_task.h"
#include "drv_timer.h"
#include "drv_event.h"
/* Private typedef --------------------------------------*/
/* Private define ------------------ --------------------*/
#define ADC_DET_COUNT                100  
#define BATT_DETECT_TIME             100 //ms
#define BATT_ERROR_VOL_REDUCE_TIME   5000 //ms
#define BATT_ERROR_VOL_REDUCE_COUNT  (BATT_ERROR_VOL_REDUCE_TIME / BATT_DETECT_TIME)
#define BATT_CHARGING_STEADY_TIME    3000 //ms
#define BATT_CHARGING_STEADY_COUNT   (BATT_CHARGING_STEADY_TIME / BATT_DETECT_TIME)
#define BATT_CHARGING_FULL_TIME      1800000//ms
#define BATT_CHARGING_FULL_COUNT     (BATT_CHARGING_FULL_TIME / BATT_DETECT_TIME)

/* Private macro ---------------------------------------*/
/* Private function ---------------------------------- --*/
static void App_Batt_Handler(void *arg );
static void App_Batt_Discharging_Handler(void );
static void App_Batt_Charging_Handler(void );
static void App_Batt_Charging_Full_Detect(void );
static void Drv_Batt_Adc_Sample(uint8_t *battSampleEndFlag );
static void App_Batt_Event_Handler(void *arg );
static void App_Batt_Handler_End_Callback(void *arg );
/* Private variables ------------------------------------*/
static task_block_t *battTask = NULL;
static batt_para_t battPara;
static uint8_t standbyTimerId = TIMER_NULL;

void App_Batt_Init(void )
{
    uint8_t i;
    
    Drv_Batt_Init();

    battTask = Drv_Task_Regist_Period(App_Batt_Handler, 0, 1, NULL);

    for(i=0;i<100;i++)
    {
        Drv_Batt_Get_BatVol();
    }
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
        App_Batt_Discharging_Handler();
    }
    else
    {
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
    uint16_t tmpEarbud_L_Cur;
    uint16_t tmpEarbud_R_Cur;
	    
    tmpBatVol = Drv_Batt_Get_BatVol();
        
    tmpEarbud_L_Cur = Drv_Earbud_Get_Cur_L();
    
    tmpEarbud_R_Cur = Drv_Earbud_Get_Cur_R();

    *battSampleEndFlag = 0;

    if(adcSampleCnt < ADC_DET_COUNT)
    {            
        
        batVolSum += tmpBatVol;
        earbudCurSum_l += tmpEarbud_L_Cur;
        earbudCurSum_r += tmpEarbud_R_Cur;
        
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
    battPara.chgState = CHG_STATE_INIT;
    
    switch(battPara.dischgState)
    {
        case DISCHG_STATE_INIT:
        {
            if(battPara.preBattLevel == 0)
            {
                App_Batt_Cal_Level();

                battPara.preBattLevel = battPara.battLevel;
            }

            App_Earbud_Cal_L_Chg_State();

            App_Earbud_Cal_R_Chg_State();

            battPara.preEarbud_L_Chg_State = battPara.earbud_L_Chg_State;

            battPara.preEarbud_R_Chg_State = battPara.earbud_R_Chg_State;

            App_Batt_Send_Batt_Level();

            App_Batt_Send_Earbud_Chg_State();

            battPara.dischgState = DISCH_STATE_HANDLER;

            Drv_Task_Delay(battTask, 3000);
            
            break;
        }
        case DISCH_STATE_HANDLER:
        {
            battPara.battVolSave = battPara.battVol;
            
            App_Batt_Cal_Level();

            App_Earbud_Cal_L_Chg_State();

            App_Earbud_Cal_R_Chg_State();
            
            if(battPara.battLevel < battPara.preBattLevel)
            {
                battPara.preBattLevel = battPara.battLevel;

                App_Batt_Send_Batt_Level();
            }
            
            if(battPara.earbud_L_Chg_State != battPara.preEarbud_L_Chg_State)
            {
                battPara.earbud_L_Chg_State = battPara.preEarbud_L_Chg_State;
                
                App_Batt_Send_Earbud_Chg_State();
            }

            if(battPara.earbud_R_Chg_State != battPara.preEarbud_R_Chg_State)
            {
                battPara.earbud_R_Chg_State = battPara.preEarbud_R_Chg_State;
                
                App_Batt_Send_Earbud_Chg_State();
            }
            
            break;
        }
        default: break;
    }
}

static void App_Batt_Charging_Handler(void )
{
    battPara.dischgState = DISCHG_STATE_INIT;

    switch(battPara.chgState)
    {
        case CHG_STATE_INIT:
        {
            if(battPara.battVolSave == 0)
            {
                battPara.battVolSave = App_Batt_Get_BatVol();

                App_Batt_Cal_Level();
            }

            App_Earbud_Cal_L_Chg_State();

            App_Earbud_Cal_R_Chg_State();

            battPara.preBattLevel = battPara.battLevel;

            battPara.preEarbud_L_Chg_State = battPara.earbud_L_Chg_State;

            battPara.preEarbud_R_Chg_State = battPara.earbud_R_Chg_State;

            battPara.battVolErr = 0;

            App_Lcd_Init_Earbud_Chg_Show_State();
            
            App_Batt_Send_Batt_Level();

            App_Batt_Send_Earbud_Chg_State();

            battPara.delayCnt = 0;

            battPara.chgState = CHG_STATE_GET_BATT_ERR_VOL;

            break;
        }
        case CHG_STATE_GET_BATT_ERR_VOL:
        {
            if(++battPara.delayCnt > BATT_CHARGING_STEADY_COUNT)
            {
                battPara.delayCnt = 0;

                if(App_Batt_Get_BatVol() > battPara.battVolSave)
                {
                    battPara.battVolErr = App_Batt_Get_BatVol() - battPara.battVolSave;

                    battPara.chgState = CHG_STATE_HANDLER;
                }
            }
            break;
        }
        case CHG_STATE_HANDLER:
        {
            App_Batt_Charging_Full_Detect();

            battPara.battVol -= battPara.battVolErr;

            App_Batt_Cal_Level();

            App_Earbud_Cal_L_Chg_State();

            App_Earbud_Cal_R_Chg_State();
            
            if(battPara.battLevel > battPara.preBattLevel)
            {
                battPara.preBattLevel = battPara.battLevel;

                App_Batt_Send_Batt_Level();
            }

            if(battPara.earbud_L_Chg_State != battPara.preEarbud_L_Chg_State)
            {
                battPara.earbud_L_Chg_State = battPara.preEarbud_L_Chg_State;
                
                App_Batt_Send_Earbud_Chg_State();
            }

            if(battPara.earbud_R_Chg_State != battPara.preEarbud_R_Chg_State)
            {
                battPara.earbud_R_Chg_State = battPara.preEarbud_R_Chg_State;
                
                App_Batt_Send_Earbud_Chg_State();
            }
            
            break;
        }
    }
}

static void App_Batt_Charging_Full_Detect(void )
{
    static uint16_t battDelayCnt;
    static uint16_t battFullDelayCnt;
        
    if(battPara.battLevel != BATT_LEVEL_100)
    {
        if(Drv_Batt_Get_Charing_State())
        {
            if(++battFullDelayCnt > 50)
            {
                battDelayCnt = 0;

                battFullDelayCnt = 0;
                
                battPara.battLevel = BATT_LEVEL_100;
            }
        }

        if(battPara.battVol >= 4150)
        {
            if(battPara.battVolErr > 0)
            {
                if(++battDelayCnt > BATT_ERROR_VOL_REDUCE_COUNT)
                {
                    battDelayCnt = 0;

                    battPara.battVolErr--;
                }
            }
            else
            {
                if(++battDelayCnt > BATT_CHARGING_FULL_COUNT)
                {
                    battDelayCnt = 0;

                    battPara.battLevel = BATT_LEVEL_100;
                }
            }
        }
        else
        {
            battDelayCnt = 0;
        }
    }
}


batt_level_state_t App_Batt_Cal_Level(void )
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
            battPara.battLevel = BATT_LEVEL_70;
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
            if(Drv_Batt_Get_Usb_State() == USB_PLUG_OUT)
            {
                if(battPara.battVol < (BATT_VOL_100 - battErrVol))
                {
                    battPara.battLevel = BATT_LEVEL_90;
                }
            }
        }
        else if(battPara.battLevel == BATT_LEVEL_90)
        {
            if(battPara.battVol < (BATT_VOL_90 - battErrVol))
            {
                battPara.battLevel = BATT_LEVEL_80;
            }
        }
        else if(battPara.battLevel == BATT_LEVEL_80)
        {
            if(battPara.battVol < (BATT_VOL_80 - battErrVol))
            {
                battPara.battLevel = BATT_LEVEL_70;
            }
            else if(battPara.battVol > (BATT_VOL_90 + battErrVol))
            {
                battPara.battLevel = BATT_LEVEL_90;
            }
        }
        else if(battPara.battLevel == BATT_LEVEL_70)
        {
            if(battPara.battVol < (BATT_VOL_70 - battErrVol))
            {
                battPara.battLevel = BATT_LEVEL_60;
            }
            else if(battPara.battVol > (BATT_VOL_80 + battErrVol))
            {
                battPara.battLevel = BATT_LEVEL_80;
            }
        }
        else if(battPara.battLevel == BATT_LEVEL_60)
        {
            if(battPara.battVol < (BATT_VOL_60 - battErrVol))
            {
                battPara.battLevel = BATT_LEVEL_50;
            }
            else if(battPara.battVol > (BATT_VOL_70 + battErrVol))
            {
                battPara.battLevel = BATT_LEVEL_70;
            }
        }
        else if(battPara.battLevel == BATT_LEVEL_50)
        {
            if(battPara.battVol < (BATT_VOL_50 - battErrVol))
            {
                battPara.battLevel = BATT_LEVEL_40;
            }
            else if(battPara.battVol > (BATT_VOL_60 + battErrVol))
            {
                battPara.battLevel = BATT_LEVEL_60;
            }
        }
        else if(battPara.battLevel == BATT_LEVEL_40)
        {
            if(battPara.battVol < (BATT_VOL_40 - battErrVol))
            {
                battPara.battLevel = BATT_LEVEL_30;
            }
            else if(battPara.battVol > (BATT_VOL_50 + battErrVol))
            {
                battPara.battLevel = BATT_LEVEL_50;
            }
        }
        else if(battPara.battLevel == BATT_LEVEL_30)
        {
            if(battPara.battVol < (BATT_VOL_30 - battErrVol))
            {
                battPara.battLevel = BATT_LEVEL_20;
            }
            else if(battPara.battVol > (BATT_VOL_40 + battErrVol))
            {
                battPara.battLevel = BATT_LEVEL_40;
            }
        }
        else if(battPara.battLevel == BATT_LEVEL_20)
        {
            if(battPara.battVol < (BATT_VOL_20 - battErrVol))
            {
                battPara.battLevel = BATT_LEVEL_10;
            }
            else if(battPara.battVol > (BATT_VOL_30 + battErrVol))
            {
                battPara.battLevel = BATT_LEVEL_30;
            }
        }
        else if(battPara.battLevel == BATT_LEVEL_10)
        {
            if(battPara.battVol < (BATT_VOL_10 - battErrVol))
            {
                battPara.battLevel = BATT_LEVEL_5;
            }
            else if(battPara.battVol > (BATT_VOL_20 + battErrVol))
            {
                battPara.battLevel = BATT_LEVEL_20;
            }
        }
        else if(battPara.battLevel == BATT_LEVEL_5)
        {
            if(battPara.battVol < BATT_VOL_0)
            {
                battPara.battLevel = BATT_LEVEL_0;
            }
            else if(battPara.battVol > (BATT_VOL_10 + battErrVol))
            {
                battPara.battLevel = BATT_LEVEL_10;
            }
        }
        else if(battPara.battLevel == BATT_LEVEL_0)
        {
            if(battPara.battVol > (BATT_VOL_5 + battErrVol))
            {
                battPara.battLevel = BATT_LEVEL_5;
            }
        }
    }

    return battPara.battLevel;
}

earbud_chg_state_t App_Earbud_Cal_L_Chg_State(void )
{
    static const uint8_t curErr = 5;//ma
    
    if(battPara.earbud_L_Chg_State == EARBUD_CHG_PROCEE)
    {
        if(battPara.earbud_L_Cur < EARBUD_MIN_CUR)
        {
            battPara.earbud_L_Chg_State = EARBUD_CHG_DONE;
        }
    }
    else
    {
        if(battPara.earbud_L_Cur > (EARBUD_MIN_CUR + curErr))
        {
            battPara.earbud_L_Chg_State = EARBUD_CHG_PROCEE;
        }
    }

    
    return battPara.earbud_L_Chg_State;
}

earbud_chg_state_t App_Earbud_Cal_R_Chg_State(void )
{
    static const uint8_t curErr = 5;//ma
    
    if(battPara.earbud_R_Chg_State == EARBUD_CHG_PROCEE)
    {
        if(battPara.earbud_R_Cur < EARBUD_MIN_CUR)
        {
            battPara.earbud_R_Chg_State = EARBUD_CHG_DONE;
        }
    }
    else
    {
        if(battPara.earbud_R_Cur > (EARBUD_MIN_CUR + curErr))
        {
            battPara.earbud_R_Chg_State = EARBUD_CHG_PROCEE;
        }
    }
		
		return battPara.earbud_R_Chg_State;
}

batt_level_state_t App_Batt_Get_Level(void )
{
    return battPara.battLevel;
}

earbud_chg_state_t App_Earbud_Get_L_Chg_State(void )
{
    return battPara.earbud_L_Chg_State;
}

earbud_chg_state_t App_Earbud_Get_R_Chg_State(void )
{
    return battPara.earbud_R_Chg_State;
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
    battPara.earbud_L_Cur = earbudCur;
}

uint16_t App_Earbud_Get_Cur_L(void )
{
    return battPara.earbud_L_Cur;
}

void App_Earbud_Set_Cur_R(uint16_t earbudCur )
{
    battPara.earbud_R_Cur = earbudCur;
}

uint16_t App_Earbud_Get_Cur_R(void )
{
    return battPara.earbud_R_Cur;
}

uint8_t App_Batt_Get_Usb_State(void )
{
    return Drv_Batt_Get_Usb_State();
}

void App_Batt_Send_Batt_Level(void )
{
    uint8_t battLevel = (uint8_t )App_Batt_Get_Level();

    Drv_Msg_Queue_Put(App_Batt_Event_Handler, CMD_BATT_LEVEL, &battLevel, 1);
}

void App_Batt_Send_Earbud_Chg_State(void )
{
    uint8_t buf[2] = {0};

    buf[0] = (uint8_t )App_Earbud_Get_L_Chg_State();
    buf[1] = (uint8_t )App_Earbud_Get_R_Chg_State();

    Drv_Msg_Queue_Put(App_Batt_Event_Handler, CMD_BATT_EARBUD_CHG_STATE, buf, sizeof(buf));
}

static void App_Batt_Event_Handler(void *arg )
{    
    msg_t *msg = (msg_t *)arg; 

    if(msg->cmd == CMD_BATT_LEVEL)
    {
        uint8_t battLevel = msg->buf[0];

        if(battLevel == 0)
        {
            App_Batt_Handler_End_Callback(NULL);
        }
        else
        {
            if(App_Lcd_Get_Earbud_Show_State() == PIC_STATE_IDLE)
            {
                App_Lcd_Show_Battery_Level(battLevel, BLUE);
            }
        }
    }
    else if(msg->cmd == CMD_BATT_EARBUD_CHG_STATE)
    {
        earbud_chg_state_t earbudChgStateL= (earbud_chg_state_t )msg->buf[0];
        
        earbud_chg_state_t earbudChgStateR = (earbud_chg_state_t )msg->buf[1];

        App_Lcd_Show_Logo_Disable();   

        if(earbudChgStateL != EARBUD_CHG_DONE && earbudChgStateR != EARBUD_CHG_DONE)
        {
            App_Lcd_Show_Earbud_Chg_Enable(PIC_EARBUD_CHG_LR);
        }
        else if(earbudChgStateL != EARBUD_CHG_DONE)
        {
            App_Lcd_Show_Earbud_Chg_Enable(PIC_EARBUD_CHG_L);
        }
        else if(earbudChgStateR != EARBUD_CHG_DONE)
        {                
            App_Lcd_Show_Earbud_Chg_Enable(PIC_EARBUD_CHG_R);
        }
        else 
        {
            App_Lcd_Show_Earbud_Chg_Enable(PIC_EARBUD_CHG_LR_DONE);
        }

        if(Drv_Batt_Get_Usb_State() == USB_PLUG_OUT)
        {
            if(earbudChgStateL == EARBUD_CHG_DONE && earbudChgStateR == EARBUD_CHG_DONE)
            {
                Drv_Timer_Delete(standbyTimerId);
                
                standbyTimerId = Drv_Timer_Regist_Oneshot(App_Batt_Handler_End_Callback, 5000, NULL);
            }
        }
        else
        {
            Drv_Timer_Delete(standbyTimerId);
        }

    }
    else if(msg->cmd == CMD_BATT_SLEEP)
    {
        App_Sys_Sleep();
    }
}

static void App_Batt_Handler_End_Callback(void *arg )
{
    App_Lcd_Clr();

    App_Lcd_Background_Led_Off();

    if(App_Hall_Get_State() == 0)
    {
        Drv_Msg_Queue_Put(App_Batt_Event_Handler, CMD_BATT_SLEEP, NULL, 0);
    }
}


void App_Batt_Delete_Standby_Timer(void )
{
    Drv_Timer_Delete(standbyTimerId);

    standbyTimerId = TIMER_NULL;
}

void App_Batt_Task_Sleep(void )
{
    Drv_Task_Sleep(battTask);
}

void App_Batt_Task_Wakeup(void )
{
    Drv_Task_Wakeup(battTask);
}

void App_Sys_Sleep(void )
{
	  return ;
	
    uint16_t i;

    ADC_Stop();

    Drv_Batt_Boost_Vout_Disable();
        
    /*** enter power down ***/
	CGC->PMUKEY = 0x192A;
	CGC->PMUKEY = 0x3E4F;
	CGC->PMUCTL = 1;

	/* disable LVR */
	LVD->LVIM = 0x80;//disable LVR,option byte 0xC1 select interrupt&reset mode
	__STOP(); 		// DeepSleep
	/* enable LVR */
	LVD->LVIM = 0x00;

    for(i=0;i<250;i++) __NOP();
    
    App_Sys_Wakeup();
}

void App_Sys_Wakeup(void )
{
     Cms32l051_Systick_Init();
     
     Cms32l051_Tim40_Channel0_Interval_Init();
     
     Cms32l051_Uart1_Init();
     
     Cms32l051_Spi00_Init();
     
     Cms32l051_Spi20_Init();
     
     Cms32l051_Adc_Init();
	
		 Cms32l051_Gpio_Init();
	
		 Cms32l051_Intp_Init();
     
     Drv_Batt_Boost_Vout_Enable();
}

