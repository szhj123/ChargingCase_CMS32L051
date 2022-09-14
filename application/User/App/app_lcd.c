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

/* Private typedef --------------------------------------*/
/* Private define ------------------ ------------------- -*/
/* Private macro ---------------------------------------*/
/* Private function ---------------------------------- --*/
static void App_Lcd_Display_Handler(void *arg );
static void App_Lcd_Show_Picture_End_Callback(void );
static void App_Lcd_BattLevel_Flash(void );
static void App_Lcd_EarbudChg_L_Flash(void );
static void App_Lcd_EarbudChg_R_Flash(void );
static void App_Lcd_Show_Picture_Switch(void *arg );
/* Private variables ------------------------------------*/
static task_block_t *lcdTask = NULL;
static lcd_para_t lcdPara;
static pic_para_t picPara;
static uint8_t lcdWrEndFlag;

void App_Lcd_Init(void )
{
    Drv_Lcd_Init();

    lcdTask = Drv_Task_Regist_Period(App_Lcd_Display_Handler, 0, 1, NULL);    

    App_Lcd_Show_Pic_Disable();
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
    Drv_Lcd_Clr(BLACK);
}

void App_Lcd_Show_Pic(void )
{
    lcdPara.show_battLevel_callback = NULL;
    lcdPara.l_show_earbudChg_callback = NULL;
    lcdPara.r_show_earbudChg_callback = NULL;
    
    //Drv_Lcd_Show_Picture(gImage_pic, sizeof(gImage_pic), App_Lcd_Show_Picture_End_Callback);
    App_Lcd_Show_Pic_Enable();
    
    App_Lcd_Background_Led_On();
}

void App_Lcd_Show_Picture_Handler(void )
{    
    switch(picPara.picState)
    {
        case PIC_STATE_GET_INFO:
        {
            uint8_t buf[6];
            
            //Drv_Flash_Read((picPara.picIndex+picPara.picCnt)*ERASE_64K_BLOCK_SIZE, buf, 6);
            Drv_Flash_Read((picPara.picCnt+5)*ERASE_64K_BLOCK_SIZE, buf, 6);

            picPara.picTotalNum = buf[0];
            picPara.picIndex =  buf[1];
            picPara.picWidth =  (uint16_t )buf[3] << 8 | buf[2];
            picPara.picHeight = (uint16_t )buf[5] << 8 | buf[4];

            if(picPara.picTotalNum != 0xff)
            {
                Drv_Lcd_Set_Position(0, 0, picPara.picWidth-1, picPara.picHeight-1);
                
                picPara.picTotalData = picPara.picWidth*picPara.picHeight*2;
                
                picPara.picFlashAddr = picPara.picIndex*ERASE_64K_BLOCK_SIZE + 6;

                lcdWrEndFlag = 0;
                
                picPara.picState = PIC_STATE_GET_DATA;
            }
            break;
        }
        case PIC_STATE_GET_DATA:
        {
            if(picPara.picTotalData > PIC_MAX_READ_BUF)
            {
                Drv_Flash_Read(picPara.picFlashAddr, picPara.picDataBuf, PIC_MAX_READ_BUF);

                picPara.picTotalData -= PIC_MAX_READ_BUF;

                picPara.picFlashAddr += PIC_MAX_READ_BUF;

                Drv_Lcd_Show_Picture(picPara.picDataBuf, PIC_MAX_READ_BUF, App_Lcd_Show_Picture_End_Callback);
                
            }
            else
            {
                Drv_Flash_Read(picPara.picFlashAddr, picPara.picDataBuf, picPara.picTotalData);

                Drv_Lcd_Show_Picture(picPara.picDataBuf, picPara.picTotalData, App_Lcd_Show_Picture_End_Callback);

                picPara.picTotalData = 0;
            }
                

            picPara.picState = PIC_STATE_WAIT_GET_END;

            break;
        }
        case PIC_STATE_WAIT_GET_END:
        {
            if(lcdWrEndFlag)
            {
                lcdWrEndFlag = 0;

                if(picPara.picTotalData == 0)
                {
                    if(picPara.picTotalNum == 1)
                    {
                        picPara.picState = PIC_STATE_IDLE;
                    }
                    else
                    {
                        Drv_Timer_Regist_Oneshot(App_Lcd_Show_Picture_Switch, PIC_SHOW_SPEED, NULL);
                    }
                }
                else
                {
                    picPara.picState = PIC_STATE_GET_DATA;
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

    if(picPara.picShowEndFlag)
    {
        picPara.picState = PIC_STATE_IDLE;
    }
}

static void App_Lcd_Show_Picture_End_Callback(void )
{
    lcdWrEndFlag = 1;
}

static void App_Lcd_Show_Picture_Switch(void *arg )
{                      
    if(picPara.picState != PIC_STATE_IDLE)
    {
        if(++picPara.picCnt >= picPara.picTotalNum)
        {
            picPara.picCnt = 0;
        }
        
        picPara.picState = PIC_STATE_GET_INFO;
    }
}

void App_Lcd_Show_Pic_Enable(void )
{
    picPara.picCnt = 0;

    picPara.picShowEndFlag = 0;
        
    picPara.picState = PIC_STATE_GET_INFO;
}

void App_Lcd_Show_Pic_Disable(void )
{
    picPara.picCnt = 0;

    picPara.picShowEndFlag = 1;
        
    picPara.picState = PIC_STATE_IDLE;
}

pic_state_t App_Lcd_Get_Show_Pic_State(void )
{
    return picPara.picState;
}


void App_Lcd_Set_BattLevel_Solid(uint8_t battLevel, uint16_t color )
{
    lcdPara.show_battLevel_callback = NULL;

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
    
    lcdPara.show_battLevel_callback = NULL;
    
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
            Drv_Lcd_Show_String(lcdPara.startX, 10, (const uint8_t *)lcdPara.battLevelStr, tmpColor, BLACK, 32, 0);
        }
        else
        {
            tmpColor = BLACK;
            Drv_Lcd_Show_String(lcdPara.startX, 10, (const uint8_t *)lcdPara.battLevelStr, tmpColor, BLACK, 32, 0);
        }
    }
}

void App_Lcd_Set_Earbud_L_Solid(void )
{    
    lcdPara.l_show_earbudChg_callback = NULL;

    Drv_Lcd_Draw_Rectangle(30, 55, 55, 115, WHITE);
    
    Drv_Lcd_Fill(35, 60, 51, 68, GREEN);
    Drv_Lcd_Fill(35, 71, 51, 79, GREEN);
    Drv_Lcd_Fill(35, 82, 51, 90, GREEN);
    Drv_Lcd_Fill(35, 93, 51, 101, YELLOW);
    Drv_Lcd_Fill(35, 104, 51, 112, RED);

    App_Lcd_Background_Led_On();
}

void App_Lcd_Set_EarbudChg_L_Flash(void )
{
    Drv_Lcd_Fill(35, 50, 50, 55, WHITE);
    
    Drv_Lcd_Draw_Rectangle(30, 55, 55, 115, WHITE);

    App_Lcd_Background_Led_On();

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

void App_Lcd_Set_Earbud_R_Solid(void )
{
    lcdPara.r_show_earbudChg_callback = NULL;

    Drv_Lcd_Draw_Rectangle(80, 55, 105, 115, WHITE);

    Drv_Lcd_Fill(85, 60, 101, 68, GREEN);
    Drv_Lcd_Fill(85, 71, 101, 79, GREEN);
    Drv_Lcd_Fill(85, 82, 101, 90, GREEN);
    Drv_Lcd_Fill(85, 93, 101, 101, YELLOW);
    Drv_Lcd_Fill(85, 104, 101, 112, RED);

    App_Lcd_Background_Led_On();
}

void App_Lcd_Set_EarbudChg_R_Flash(void )
{
    Drv_Lcd_Fill(85, 50, 100, 55, WHITE);
    
    Drv_Lcd_Draw_Rectangle(80, 55, 105, 115, WHITE);

    App_Lcd_Background_Led_On();
    
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

void App_Lcd_Show_Bt_Logo(void )
{
    Drv_Lcd_Show_String(32, 125, "L", WHITE, BLACK, 32, 0);
    Drv_Lcd_Draw_Rectangle(30, 125, 50, 156, WHITE);

    Drv_Lcd_Show_String(86, 125, "R", WHITE, BLACK, 32, 0);
    Drv_Lcd_Draw_Rectangle(84, 125, 104, 156, WHITE);

    Drv_Lcd_Draw_Line(60, 130, 75, 150, BLUE);
    Drv_Lcd_Draw_Line(60, 150, 75, 130, BLUE);
    Drv_Lcd_Draw_Line(68, 125, 68, 155, BLUE);
    Drv_Lcd_Draw_Line(68, 125, 75, 130, BLUE);
    Drv_Lcd_Draw_Line(68, 155, 75, 150, BLUE);

    App_Lcd_Background_Led_On();
}

void App_Lcd_Ui_Init(uint8_t battLevel )
{
    sprintf(lcdPara.battLevelStr, "%3d", battLevel);

    lcdPara.battLevelStr[3] = '%';
    lcdPara.battLevelStr[4] = '\0';


    if(battLevel >= 100)
    {
        lcdPara.startX = 35;
        lcdPara.battLeveColor = WHITE;
    }
    else if(battLevel >15 && battLevel < 100)
    {
        lcdPara.startX = 28;
        lcdPara.battLeveColor = WHITE;
    }
    else if(battLevel >= 10 && battLevel <= 15)
    {
        lcdPara.startX = 28;
        lcdPara.battLeveColor = YELLOW;
    }
    else
    {
        lcdPara.startX = 20;
        lcdPara.battLeveColor = RED;
    }

    Drv_Lcd_Show_String(lcdPara.startX, 10, (const uint8_t *)lcdPara.battLevelStr, lcdPara.battLeveColor, BLACK, 32, 0);

    Drv_Lcd_Fill(35, 50, 50, 55, WHITE);
    Drv_Lcd_Draw_Rectangle(30, 55, 55, 115, WHITE);

    Drv_Lcd_Fill(85, 50, 100, 55, WHITE);
    Drv_Lcd_Draw_Rectangle(80, 55, 105, 115, WHITE);

    Drv_Lcd_Fill(35, 60, 51, 68, GREEN);
    Drv_Lcd_Fill(35, 71, 51, 79, GREEN);
    Drv_Lcd_Fill(35, 82, 51, 90, GREEN);
    Drv_Lcd_Fill(35, 93, 51, 101, GREEN);
    Drv_Lcd_Fill(35, 104, 51, 112, RED);

    Drv_Lcd_Fill(85, 60, 101, 68, GREEN);
    Drv_Lcd_Fill(85, 71, 101, 79, GREEN);
    Drv_Lcd_Fill(85, 82, 101, 90, GREEN);
    Drv_Lcd_Fill(85, 93, 101, 101, GREEN);
    Drv_Lcd_Fill(85, 104, 101, 112, RED);

    Drv_Lcd_Show_String(32, 125, "L", WHITE, BLACK, 32, 0);
    Drv_Lcd_Draw_Rectangle(30, 125, 50, 156, WHITE);

    Drv_Lcd_Show_String(86, 125, "R", WHITE, BLACK, 32, 0);
    Drv_Lcd_Draw_Rectangle(84, 125, 104, 156, WHITE);

    Drv_Lcd_Draw_Line(60, 130, 75, 150, BLUE);
    Drv_Lcd_Draw_Line(60, 150, 75, 130, BLUE);
    Drv_Lcd_Draw_Line(68, 125, 68, 155, BLUE);
    Drv_Lcd_Draw_Line(68, 125, 75, 130, BLUE);
    Drv_Lcd_Draw_Line(68, 155, 75, 150, BLUE);

    App_Lcd_Background_Led_On();
}



void App_Lcd_Set_Pic_Enable(uint8_t *buf, uint16_t length )
{
    uint8_t  picTotalNum = buf[0];
    uint8_t  picIndex= buf[1];
    uint16_t picWidth = (uint16_t )buf[3] << 8 | buf[2];
    uint16_t picHeight = (uint16_t )buf[5] << 8 | buf[4];

    uint32_t falshAddr = picIndex * ERASE_64K_BLOCK_SIZE;

    picPara.picState = PIC_STATE_IDLE;

    picPara.picIndex = picIndex;

    picPara.picTotalNum = picTotalNum;

    picPara.picTotalData = (uint32_t )picWidth * (uint32_t )picHeight * 2;
    
    picPara.picFlashAddr = falshAddr + 6;
    
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
    
    picPara.picDataOffset = ((uint32_t)buf[3] << 24) | ((uint32_t)buf[2] << 16) | ((uint32_t)buf[1] << 8) | (uint32_t)buf[0];

    Drv_Flash_Write(picPara.picFlashAddr + picPara.picDataOffset, picDataPtr, picDataLength);

    if((picPara.picDataOffset + picDataLength) >= picPara.picTotalData)
    {
        if(picPara.picTotalNum == 1)
        {
            picPara.picDataOffset = 0;

            picPara.picFlashAddr = 0;
            
            //App_Lcd_Show_Pic_Enable();
        }
        else
        {
            if((picPara.picIndex-4) == picPara.picTotalNum)
            {
                picPara.picDataOffset = 0;

                picPara.picFlashAddr = 0;
                
                picPara.picIndex = 5;

                //App_Lcd_Show_Pic_Enable();
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


