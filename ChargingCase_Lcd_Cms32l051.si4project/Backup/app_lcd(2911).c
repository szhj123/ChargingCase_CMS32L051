/********************************************************
* @file       app_lcd.c
* @author     szhj13
* @version    V1.0
* @date       2022-06-06
* @brief      the start address of program
**********************************************************
* @Modify

**********************************************************/

/* Includes ---------------------------------------------*/
#include "stdio.h"

#include "drv_task.h"
#include "drv_timer.h"
#include "app_lcd.h"
#include "drv_flash.h"
#include "drv_lcd_picture.h"

#include "app_battery.h"

/* Private typedef --------------------------------------*/
/* Private define ------------------ ------------------- -*/
/* Private macro ---------------------------------------*/
/* Private function ---------------------------------- --*/
static void App_Lcd_Display_Handler(void *arg );
static void App_Lcd_Show_Picture_End_Callback(void );
static void App_Lcd_Show_Earbud_Picture_End_Callback(void );
static void App_Lcd_BattLevel_Flash(void );
static void App_Lcd_Show_Earbud_Chg(void );
static void App_Lcd_Show_Logo_Switch(void *arg );
static void App_Lcd_Earbud_Pic_Switch(void * arg);
/* Private variables ------------------------------------*/
static task_block_t *lcdTask = NULL;
static lcd_para_t lcdPara;
static pic_para_t logoPara;
static pic_para_t earBudPicPara;

void App_Lcd_Init(void )
{
    Drv_Lcd_Init();

    lcdTask = Drv_Task_Regist_Period(App_Lcd_Display_Handler, 0, 1, NULL);    

    App_Lcd_Show_Logo_Disable();
}

static void App_Lcd_Delay_Count(void )
{
    if(lcdPara.showBattLevelDelayCnt < 0xffff)
    {
        lcdPara.showBattLevelDelayCnt++;
    }

    if(lcdPara.r_showEarbudChgDelayCnt < 0xffff)
    {
        lcdPara.r_showEarbudChgDelayCnt++;
    }
}

static void App_Lcd_Display_Handler(void *arg )
{
    App_Lcd_Delay_Count();
    
    if(lcdPara.battery_level_show_callback != NULL)
    {
        lcdPara.battery_level_show_callback();
    }

    if(lcdPara.earbud_chg_show_callback != NULL)
    {
        lcdPara.earbud_chg_show_callback();
    }
}

void App_Lcd_Background_Led_On(void )
{
    Drv_Lcd_Background_Led_On();
}

void App_Lcd_Background_Led_Off(void )
{
    Drv_Lcd_Background_Led_Off();
}

void App_Lcd_Clr(void )
{
    lcdPara.battery_level_show_callback = NULL;
    lcdPara.earbud_chg_show_callback = NULL;
    
    Drv_Lcd_Clr(BLACK);
}

void App_Lcd_Show_Logo(void )
{
    lcdPara.battery_level_show_callback = NULL;
    lcdPara.earbud_chg_show_callback = NULL;
    
    //Drv_Lcd_Show_Picture(gImage_pic, sizeof(gImage_pic), App_Lcd_Show_Picture_End_Callback);
    App_Lcd_Show_Logo_Enable();
    
    App_Lcd_Background_Led_On();
}

void App_Lcd_Show_Logo_Handler(void )
{    
    switch(logoPara.picState)
    {
        case PIC_STATE_GET_INFO:
        {
            uint8_t buf[6];
            
            //Drv_Flash_Read((logoPara.picIndex+logoPara.picCnt)*ERASE_64K_BLOCK_SIZE, buf, 6);
            Drv_Flash_Read((logoPara.picCnt+15)*ERASE_64K_BLOCK_SIZE, buf, 6);

            logoPara.picTotalNum = buf[0];
            logoPara.picIndex =  buf[1];
            logoPara.picWidth =  (uint16_t )buf[3] << 8 | buf[2];
            logoPara.picHeight = (uint16_t )buf[5] << 8 | buf[4];

            if(logoPara.picTotalNum != 0xff)
            {
                Drv_Lcd_Set_Position(0, 0, logoPara.picWidth-1, logoPara.picHeight-1);
                
                logoPara.picTotalData = logoPara.picWidth*logoPara.picHeight*2;
                
                logoPara.picFlashAddr = logoPara.picIndex*ERASE_64K_BLOCK_SIZE + 6;

                logoPara.picWrEndFlag = 0;
                
                logoPara.picState = PIC_STATE_GET_DATA;
            }
            break;
        }
        case PIC_STATE_GET_DATA:
        {
            if(logoPara.picTotalData > PIC_MAX_READ_BUF)
            {
                Drv_Flash_Read(logoPara.picFlashAddr, logoPara.picDataBuf, PIC_MAX_READ_BUF);

                logoPara.picTotalData -= PIC_MAX_READ_BUF;

                logoPara.picFlashAddr += PIC_MAX_READ_BUF;

                Drv_Lcd_Show_Picture(logoPara.picDataBuf, PIC_MAX_READ_BUF, App_Lcd_Show_Picture_End_Callback);
                
            }
            else
            {
                Drv_Flash_Read(logoPara.picFlashAddr, logoPara.picDataBuf, logoPara.picTotalData);

                Drv_Lcd_Show_Picture(logoPara.picDataBuf, logoPara.picTotalData, App_Lcd_Show_Picture_End_Callback);

                logoPara.picTotalData = 0;
            }
                

            logoPara.picState = PIC_STATE_WAIT_GET_END;

            break;
        }
        case PIC_STATE_WAIT_GET_END:
        {
            if(logoPara.picWrEndFlag)
            {
                logoPara.picWrEndFlag = 0;

                if(logoPara.picTotalData == 0)
                {
                    if(logoPara.picTotalNum == 1)
                    {
                        logoPara.picState = PIC_STATE_IDLE;
                    }
                    else
                    {
                        Drv_Timer_Regist_Oneshot(App_Lcd_Show_Logo_Switch, PIC_SHOW_SPEED, NULL);
                    }
                }
                else
                {
                    logoPara.picState = PIC_STATE_GET_DATA;
                }
            }

            break;
        }
        case PIC_STATE_IDLE:
        {
            break;
        }
        default: break;
    }

    if(logoPara.picShowEndFlag)
    {
        logoPara.picState = PIC_STATE_IDLE;
    }
}

static void App_Lcd_Show_Picture_End_Callback(void )
{
    logoPara.picWrEndFlag = 1;
}

static void App_Lcd_Show_Earbud_Picture_End_Callback(void )
{
    earBudPicPara.picWrEndFlag = 1;
}

static void App_Lcd_Show_Logo_Switch(void *arg )
{                      
    if(logoPara.picState != PIC_STATE_IDLE)
    {
        if(++logoPara.picCnt >= logoPara.picTotalNum)
        {
            logoPara.picCnt = 0;

            App_Lcd_Show_Logo_Disable();
    
            App_Lcd_Clr();

            App_Batt_Send_Batt_Level();

            App_Batt_Send_Earbud_Chg_State();

            return ;
        }
        
        logoPara.picState = PIC_STATE_GET_INFO;
    }
}

void App_Lcd_Show_Logo_Enable(void )
{
    if(App_Lcd_Get_Show_Logo_State() == PIC_STATE_IDLE)
    {
        logoPara.picCnt = 0;

        logoPara.picShowEndFlag = 0;
            
        logoPara.picState = PIC_STATE_GET_INFO;
    }
}

void App_Lcd_Show_Logo_Disable(void )
{
    logoPara.picCnt = 0;

    logoPara.picShowEndFlag = 1;
        
    logoPara.picState = PIC_STATE_IDLE;
}

pic_state_t App_Lcd_Get_Show_Logo_State(void )
{
    return logoPara.picState;
}


void App_Lcd_Set_BattLevel_Solid(uint8_t battLevel, uint16_t color )
{
    lcdPara.battery_level_show_callback = NULL;

    sprintf(lcdPara.battLevelStr, "%3d", battLevel);

    lcdPara.battLevelStr[3] = '%';
    lcdPara.battLevelStr[4] = '\0';

    if(battLevel >= 100)
    {
        lcdPara.startX = 35;
    }
    else if(battLevel >15 && battLevel < 100)
    {
        lcdPara.startX = 28;
    }
    else if(battLevel >= 10 && battLevel <= 15)
    {
        lcdPara.startX = 28;
    }
    else
    {
        lcdPara.startX = 20;
    }

    lcdPara.battLeveColor = color;

    lcdPara.showBattLevelDelayCnt = 0;

    App_Lcd_Background_Led_On();
    
    Drv_Lcd_Show_String(lcdPara.startX, 10, (const uint8_t *)lcdPara.battLevelStr, lcdPara.battLeveColor, BLACK, 32, 0);
}

void App_Lcd_Set_BattLevel_Flash(uint8_t battLevel, uint16_t color )
{
    char str[5];
    
    lcdPara.battery_level_show_callback = NULL;
    
    sprintf(str, "%3d", battLevel);

    str[3] = '%';
    str[4] = '\0';

    lcdPara.battLevelStr[0] = str[0];
    lcdPara.battLevelStr[1] = str[1];
    lcdPara.battLevelStr[2] = str[2];
    lcdPara.battLevelStr[3] = '\0';

    if(battLevel >= 100)
    {
        lcdPara.startX = 35;
    }
    else if(battLevel >15 && battLevel < 100)
    {
        lcdPara.startX = 28;
    }
    else if(battLevel >= 10 && battLevel <= 15)
    {
        lcdPara.startX = 28;
    }
    else
    {
        lcdPara.startX = 20;
    }

    Drv_Lcd_Show_String(lcdPara.startX, 10, (const uint8_t *)str, color, BLACK, 32, 0);

    App_Lcd_Background_Led_On();

    lcdPara.battLeveColor = color;
    
    lcdPara.showBattLevelDelayCnt = 0;

    lcdPara.battery_level_show_callback = App_Lcd_BattLevel_Flash;
}

static void App_Lcd_BattLevel_Flash(void )
{
    static uint16_t tmpColor = BLACK;

    if(lcdPara.showBattLevelDelayCnt > 500)
    {
        lcdPara.showBattLevelDelayCnt = 0;
        
        if(tmpColor == BLACK)
        {
            tmpColor = lcdPara.battLeveColor;
            Drv_Lcd_Show_String(lcdPara.startX, 10, (const uint8_t *)lcdPara.battLevelStr, tmpColor, BLACK, 32, 0);
        }
        else
        {
            tmpColor = BLACK;
            Drv_Lcd_Show_String(lcdPara.startX, 10, (const uint8_t *)lcdPara.battLevelStr, tmpColor, BLACK, 32, 0);
        }
    }
}


void App_Lcd_Show_Earbud_Chg_Enable(pic_earbud_chg_state_t picEarbudChgState )
{
    switch(picEarbudChgState)
    {
        case PIC_EARBUD_CHG_L:
        {
            earBudPicPara.picCnt = PIC_EARBUD_CHG_L_START_INDEX;
    
            earBudPicPara.picTotalNum = 5;
            break;
        }
        case PIC_EARBUD_CHG_R:
        {
            earBudPicPara.picCnt = PIC_EARBUD_CHG_R_START_INDEX;
    
            earBudPicPara.picTotalNum = 5;
            break;
        }
        case PIC_EARBUD_CHG_LR:
        {
            earBudPicPara.picCnt = PIC_EARBUD_CHG_LR_START_INDEX;
    
            earBudPicPara.picTotalNum = 5;
            break;
        }
        case PIC_EARBUD_CHG_LR_DONE:
        {
            earBudPicPara.picCnt = PIC_EARBUD_CHG_LR_DONE_INDEX;
    
            earBudPicPara.picTotalNum = 1;
            break;
        }
        default: break;
    }
    
    earBudPicPara.picState = PIC_STATE_GET_INFO;
    
    earBudPicPara.picEarbudChgState = picEarbudChgState;
    
    App_Lcd_Background_Led_On();

    lcdPara.earbud_chg_show_callback = App_Lcd_Show_Earbud_Chg;
}

static void App_Lcd_Show_Earbud_Chg(void )
{
    switch(earBudPicPara.picState)
    {
        case PIC_STATE_GET_INFO:
        {
            uint8_t buf[6];
            
            Drv_Flash_Read((earBudPicPara.picCnt)*ERASE_64K_BLOCK_SIZE, buf, 6);

            earBudPicPara.picIndex =  buf[1];
            earBudPicPara.picWidth =  (uint16_t )buf[3] << 8 | buf[2];
            earBudPicPara.picHeight = (uint16_t )buf[5] << 8 | buf[4];

            Drv_Lcd_Set_Position(25, 0, earBudPicPara.picWidth-1+25, earBudPicPara.picHeight-1);
               
            earBudPicPara.picTotalData = earBudPicPara.picWidth*earBudPicPara.picHeight*2;
                
            earBudPicPara.picFlashAddr = earBudPicPara.picCnt*ERASE_64K_BLOCK_SIZE + 6;

            earBudPicPara.picWrEndFlag = 0;
                
            earBudPicPara.picState = PIC_STATE_GET_DATA;
            break;
        }
        case PIC_STATE_GET_DATA:
        {
            if(earBudPicPara.picTotalData > PIC_MAX_READ_BUF)
            {
                Drv_Flash_Read(earBudPicPara.picFlashAddr, earBudPicPara.picDataBuf, PIC_MAX_READ_BUF);

                earBudPicPara.picTotalData -= PIC_MAX_READ_BUF;

                earBudPicPara.picFlashAddr += PIC_MAX_READ_BUF;

                Drv_Lcd_Show_Picture(earBudPicPara.picDataBuf, PIC_MAX_READ_BUF, App_Lcd_Show_Earbud_Picture_End_Callback);
                
            }
            else
            {
                Drv_Flash_Read(earBudPicPara.picFlashAddr, earBudPicPara.picDataBuf, earBudPicPara.picTotalData);

                Drv_Lcd_Show_Picture(earBudPicPara.picDataBuf, earBudPicPara.picTotalData, App_Lcd_Show_Earbud_Picture_End_Callback);

                earBudPicPara.picTotalData = 0;
            }
                

            earBudPicPara.picState = PIC_STATE_WAIT_GET_END;

            break;
        }
        case PIC_STATE_WAIT_GET_END:
        {
            if(earBudPicPara.picWrEndFlag)
            {
                earBudPicPara.picWrEndFlag = 0;

                if(earBudPicPara.picTotalData == 0)
                {
                    Drv_Timer_Regist_Oneshot(App_Lcd_Earbud_Pic_Switch, 500, NULL);
                }
                else
                {
                    earBudPicPara.picState = PIC_STATE_GET_DATA;
                }
            }

            break;
        }
        case PIC_STATE_IDLE:
        {
            break;
        }
        default: break;
    }
}

static void App_Lcd_Earbud_Pic_Switch(void *arg )
{
    if(earBudPicPara.picState != PIC_STATE_IDLE)
    {
        if(earBudPicPara.picTotalNum != 1)
        {
            if(earBudPicPara.picCnt >= 10)
            {
                if(++earBudPicPara.picCnt >= (earBudPicPara.picTotalNum+10))
                {
                    earBudPicPara.picCnt = 10;
                }
            }
            else if(earBudPicPara.picCnt >= 5)
            {
                if(++earBudPicPara.picCnt >= (earBudPicPara.picTotalNum+5))
                {
                    earBudPicPara.picCnt = 5;
                }
            }
            else
            {                
                if(++earBudPicPara.picCnt >= earBudPicPara.picTotalNum)
                {
                    earBudPicPara.picCnt = 0;
                }
            }
            
            earBudPicPara.picState = PIC_STATE_GET_INFO;
        }
        else
        {
            earBudPicPara.picState = PIC_STATE_IDLE;
        }
    }
}

void App_Lcd_Set_Pic_Enable(uint8_t *buf, uint16_t length )
{
    uint8_t  picTotalNum = buf[0];
    uint8_t  picIndex= buf[1];
    uint16_t picWidth = (uint16_t )buf[3] << 8 | buf[2];
    uint16_t picHeight = (uint16_t )buf[5] << 8 | buf[4];

    uint32_t falshAddr = picIndex * ERASE_64K_BLOCK_SIZE;

    logoPara.picState = PIC_STATE_IDLE;

    logoPara.picIndex = picIndex;

    logoPara.picTotalNum = picTotalNum;

    logoPara.picTotalData = (uint32_t )picWidth * (uint32_t )picHeight * 2;
    
    logoPara.picFlashAddr = falshAddr + 6;
    
    Drv_Flash_Block_64k_Erase(falshAddr);
    
    Drv_Flash_Write_With_Loop(falshAddr, (uint8_t *)&picTotalNum, 1);

    Drv_Flash_Write_With_Loop(falshAddr+1, (uint8_t *)&picIndex, 1);

    Drv_Flash_Write_With_Loop(falshAddr+2, (uint8_t *)&picWidth, 2);
    
    Drv_Flash_Write_With_Loop(falshAddr+4, (uint8_t *)&picHeight, 2);
}

void App_Lcd_Set_Pic_Data(uint8_t *buf, uint16_t length )
{
    uint16_t picDataLength = length - 4;
    uint8_t  *picDataPtr = (uint8_t *)&buf[4];
    
    logoPara.picDataOffset = ((uint32_t)buf[3] << 24) | ((uint32_t)buf[2] << 16) | ((uint32_t)buf[1] << 8) | (uint32_t)buf[0];

    Drv_Flash_Write(logoPara.picFlashAddr + logoPara.picDataOffset, picDataPtr, picDataLength);

    if((logoPara.picDataOffset + picDataLength) >= logoPara.picTotalData)
    {
        if(logoPara.picTotalNum == 1)
        {
            logoPara.picDataOffset = 0;

            logoPara.picFlashAddr = 0;
            
            //App_Lcd_Show_Logo_Enable();
        }
        else
        {
            if((logoPara.picIndex-14) == logoPara.picTotalNum)
            {
                logoPara.picDataOffset = 0;

                logoPara.picFlashAddr = 0;
                
                logoPara.picIndex = 15;

                //App_Lcd_Show_Logo_Enable();
            }
        }
    }
}

void App_Lcd_Task_Sleep(void )
{
    Drv_Task_Sleep(lcdTask);
}

void App_Lcd_Task_Wakeup(void )
{
    Drv_Task_Wakeup(lcdTask);
}


