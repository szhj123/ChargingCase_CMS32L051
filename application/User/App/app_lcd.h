#ifndef _APP_LCD_H
#define _APP_LCD_H

#include "drv_lcd.h"

typedef void (*lcd_show_callback_t)(void );

#define PIC_MAX_READ_BUF                512
#define PIC_SHOW_SPEED                  50

typedef enum 
{
    PIC_STATE_GET_INFO = 0,
    PIC_STATE_GET_DATA,
    PIC_STATE_WAIT_GET_END,
    PIC_STATE_IDLE
}pic_state_t;

typedef struct _pic_para_t
{
    pic_state_t picState;
    uint32_t    picTotalData;
    uint32_t    picDataOffset;
    uint32_t    picFlashAddr;
    uint16_t    picWidth;
    uint16_t    picHeight;
    uint8_t     picIndex;
    uint8_t     picTotalNum;
    uint8_t     picCnt;
    uint8_t     picSwitchTimerId;
    uint8_t     picShowEndFlag;
    uint8_t     picWrEndFlag;
    uint8_t     picDataBuf[PIC_MAX_READ_BUF];
}pic_para_t;

typedef struct _lcd_para_t
{
    lcd_show_callback_t show_battLevel_callback;
    lcd_show_callback_t l_show_earbudChg_callback; 
    lcd_show_callback_t r_show_earbudChg_callback;
    
    uint8_t r_earbudFlashStep;
    char battLevelStr[5];

    uint16_t battLeveColor;
    
    uint16_t startX;
    uint16_t startY;
    uint8_t  flashCharIndex;
    uint8_t  flashCharLength;

    uint16_t showBattLevelDelayCnt;
    uint16_t r_showEarbudChgDelayCnt;
}lcd_para_t;

void App_Lcd_Init(void );
void App_Lcd_Clr(void );
void App_Lcd_Show_Pic(void );
void App_Lcd_Set_BattLevel_Solid(uint8_t battLevel, uint16_t color );
void App_Lcd_Set_BattLevel_Flash(uint8_t battLevel, uint16_t color );
void App_Lcd_Set_EarbudChg_L_Flash(void );
void App_Lcd_Set_EarbudChg_R_Flash(void );
void App_Lcd_Ui_Init(uint8_t battLevel );
void App_Lcd_Set_Earbud_L_Solid(void );
void App_Lcd_Set_Earbud_R_Solid(void );
void App_Lcd_Background_Led_On(void );
void App_Lcd_Background_Led_Off(void );
void App_Lcd_Set_Pic_Enable(uint8_t *buf, uint16_t length );
void App_Lcd_Set_Pic_Data(uint8_t *buf, uint16_t length );
void App_Lcd_Show_Picture_Handler(void );
void App_Lcd_Show_Pic_Enable(void );
void App_Lcd_Show_Pic_Disable(void );

void App_Lcd_Task_Sleep(void );
void App_Lcd_Task_Wakeup(void );

pic_state_t App_Lcd_Get_Show_Pic_State(void );

#endif 

