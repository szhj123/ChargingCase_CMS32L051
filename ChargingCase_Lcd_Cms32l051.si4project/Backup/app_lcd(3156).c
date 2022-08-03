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
#include "drv_lcd_picture.h"

/* Private typedef --------------------------------------*/
/* Private define ------------------ ------------------- -*/
/* Private macro ---------------------------------------*/
/* Private function ---------------------------------- --*/
static void App_Lcd_Display_Handler(void *arg );
static void App_Lcd_Show_Picture_End_Callback(void );
static void App_Lcd_BattLevel_Flash(void );
static void App_Lcd_EarbudChg_L_Flash(void );
static void App_Lcd_EarbudChg_R_Flash(void );
/* Private variables ------------------------------------*/
task_block_t *taskLcd = NULL;
lcd_para_t lcdPara;

void App_Lcd_Init(void )
{
    Drv_Lcd_Init();

    taskLcd = Drv_Task_Regist_Period(App_Lcd_Display_Handler, 0, 1, NULL);
}

static void App_Lcd_Delay_Count(void )
{
    if(lcdPara.showBattLevelDelayCnt < 0xffff)
    {
        lcdPara.showBattLevelDelayCnt++;
    }

    if(lcdPara.l_showEarbudChgDelayCnt < 0xffff)
    {
        lcdPara.l_showEarbudChgDelayCnt++;
    }

    if(lcdPara.r_showEarbudChgDelayCnt < 0xffff)
    {
        lcdPara.r_showEarbudChgDelayCnt++;
    }
}

static void App_Lcd_Display_Handler(void *arg )
{
    App_Lcd_Delay_Count();
    
    if(lcdPara.show_battLevel_callback != NULL)
    {
        lcdPara.show_battLevel_callback();
    }

    if(lcdPara.l_show_earbudChg_callback != NULL)
    {
        lcdPara.l_show_earbudChg_callback();
    }

    if(lcdPara.r_show_earbudChg_callback != NULL)
    {
        lcdPara.r_show_earbudChg_callback();
    }
    
}

void App_Lcd_Show_Picture(void )
{
    Drv_Lcd_Show_Picture(gImage_bt_logo, sizeof(gImage_bt_logo), App_Lcd_Show_Picture_End_Callback);
}

static void App_Lcd_Show_Picture_End_Callback(void )
{
    
}

void App_Lcd_Set_BattLevel_Solid(uint8_t battLevel )
{
    lcdPara.show_battLevel_callback = NULL;

    sprintf(lcdPara.battLevelStr, "%3d", battLevel);

    lcdPara.battLevelStr[3] = '%';
    lcdPara.battLevelStr[4] = '\0';

    lcdPara.showBattLevelDelayCnt = 0;
    
    Drv_Lcd_Show_String(32, 10, (const uint8_t *)lcdPara.battLevelStr, WHITE, BLACK, 32, 0);
}

void App_Lcd_Set_BattLevel_Flash(uint8_t battLevel, uint16_t color )
{
    lcdPara.show_battLevel_callback = NULL;

    sprintf(lcdPara.battLevelStr, "%3d", battLevel);

    lcdPara.battLevelStr[3] = '%';
    lcdPara.battLevelStr[4] = '\0';

    lcdPara.battLeveColor = color;
    
    lcdPara.showBattLevelDelayCnt = 0;

    lcdPara.show_battLevel_callback = App_Lcd_BattLevel_Flash;
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
            Drv_Lcd_Show_String(32, 10, (const uint8_t *)lcdPara.battLevelStr, tmpColor, BLACK, 32, 0);
        }
        else
        {
            tmpColor = BLACK;
            Drv_Lcd_Show_String(32, 10, (const uint8_t *)lcdPara.battLevelStr, tmpColor, BLACK, 32, 0);
        }
    }
}

void App_Lcd_Set_EarbudChg_L_Flash(void )
{
    Drv_Lcd_Fill(35, 50, 50, 55, WHITE);
    Drv_Lcd_Draw_Rectangle(30, 55, 55, 115, WHITE);

    lcdPara.l_earbudFlashStep = 0;

    lcdPara.l_showEarbudChgDelayCnt = 0;

    lcdPara.l_show_earbudChg_callback = App_Lcd_EarbudChg_L_Flash;
}

static void App_Lcd_EarbudChg_L_Flash(void )
{
    if(lcdPara.l_showEarbudChgDelayCnt > 250)
    {
        lcdPara.l_showEarbudChgDelayCnt = 0;
        
        switch(lcdPara.l_earbudFlashStep)
        {
            case 0:
            {
                Drv_Lcd_Fill(35, 104, 51, 112, RED);
                lcdPara.l_earbudFlashStep = 1;
                break;
            }
            case 1:
            {
                Drv_Lcd_Fill(35, 93, 51, 101, YELLOW);
                Drv_Lcd_Fill(35, 104, 51, 112, RED);
                lcdPara.l_earbudFlashStep = 2;
                break;
            }
            case 2: 
            {
                Drv_Lcd_Fill(35, 82, 51, 90, GREEN);
                Drv_Lcd_Fill(35, 93, 51, 101, YELLOW);
                Drv_Lcd_Fill(35, 104, 51, 112, RED);
                lcdPara.l_earbudFlashStep = 3;
                break;
            }
            case 3:
            {
                Drv_Lcd_Fill(35, 71, 51, 79, GREEN);
                Drv_Lcd_Fill(35, 82, 51, 90, GREEN);
                Drv_Lcd_Fill(35, 93, 51, 101, YELLOW);
                Drv_Lcd_Fill(35, 104, 51, 112, RED);
                lcdPara.l_earbudFlashStep = 4;
                break;
            }
            case 4:
            {
                Drv_Lcd_Fill(35, 60, 51, 68, GREEN);
                Drv_Lcd_Fill(35, 71, 51, 79, GREEN);
                Drv_Lcd_Fill(35, 82, 51, 90, GREEN);
                Drv_Lcd_Fill(35, 93, 51, 101, YELLOW);
                Drv_Lcd_Fill(35, 104, 51, 112, RED);
                lcdPara.l_earbudFlashStep = 5;
                break;
            }
            case 5:
            {
                Drv_Lcd_Fill(35, 60, 51, 68, BLACK);
                Drv_Lcd_Fill(35, 71, 51, 79, BLACK);
                Drv_Lcd_Fill(35, 82, 51, 90, BLACK);
                Drv_Lcd_Fill(35, 93, 51, 101, BLACK);
                Drv_Lcd_Fill(35, 104, 51, 112, BLACK);
                lcdPara.l_earbudFlashStep = 0;
                break;
            }
            default: break;
        }
    }
}

void App_Lcd_Set_EarbudChg_R_Flash(void )
{
    Drv_Lcd_Fill(85, 50, 100, 55, WHITE);
    Drv_Lcd_Draw_Rectangle(80, 55, 105, 115, WHITE);
    
    lcdPara.r_earbudFlashStep = 0;

    lcdPara.r_showEarbudChgDelayCnt = 0;

    lcdPara.r_show_earbudChg_callback = App_Lcd_EarbudChg_R_Flash;
}

static void App_Lcd_EarbudChg_R_Flash(void )
{
    if(lcdPara.r_showEarbudChgDelayCnt > 250)
    {
        lcdPara.r_showEarbudChgDelayCnt = 0;
        
        switch(lcdPara.r_earbudFlashStep)
        {
            case 0:
            {
                Drv_Lcd_Fill(85, 104, 101, 112, RED);
                lcdPara.r_earbudFlashStep = 1;
                break;
            }
            case 1:
            {
                Drv_Lcd_Fill(85, 93, 101, 101, YELLOW);
                Drv_Lcd_Fill(85, 104, 101, 112, RED);
                lcdPara.r_earbudFlashStep = 2;
                break;
            }
            case 2:
            {
                Drv_Lcd_Fill(85, 82, 101, 90, GREEN);
                Drv_Lcd_Fill(85, 93, 101, 101, YELLOW);
                Drv_Lcd_Fill(85, 104, 101, 112, RED);
                lcdPara.r_earbudFlashStep = 3;
                break;
            }
            case 3:
            {
                Drv_Lcd_Fill(85, 71, 101, 79, GREEN);
                Drv_Lcd_Fill(85, 82, 101, 90, GREEN);
                Drv_Lcd_Fill(85, 93, 101, 101, YELLOW);
                Drv_Lcd_Fill(85, 104, 101, 112, RED);
                lcdPara.r_earbudFlashStep = 4;
                break;
            }
            case 4:
            {
                Drv_Lcd_Fill(85, 60, 101, 68, GREEN);
                Drv_Lcd_Fill(85, 71, 101, 79, GREEN);
                Drv_Lcd_Fill(85, 82, 101, 90, GREEN);
                Drv_Lcd_Fill(85, 93, 101, 101, YELLOW);
                Drv_Lcd_Fill(85, 104, 101, 112, RED);
                lcdPara.r_earbudFlashStep = 5;
                break;
            }
            case 5:
            {
                Drv_Lcd_Fill(85, 60, 101, 68, BLACK);
                Drv_Lcd_Fill(85, 71, 101, 79, BLACK);
                Drv_Lcd_Fill(85, 82, 101, 90, BLACK);
                Drv_Lcd_Fill(85, 93, 101, 101, BLACK);
                Drv_Lcd_Fill(85, 104, 101, 112, BLACK);
                lcdPara.r_earbudFlashStep = 0;
                break;
            }
            default: break;
        }
    }
}

