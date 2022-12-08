#ifndef _APP_LCD_H
#define _APP_LCD_H

#include "drv_lcd.h"

typedef void (*lcd_show_callback_t)(void );

#define PIC_MAX_READ_BUF                512
#define PIC_SHOW_SPEED                  50

#define PIC_EARBUD_CHG_L_START_INDEX    0
#define PIC_EARBUD_CHG_R_START_INDEX    5
#define PIC_EARBUD_CHG_LR_START_INDEX   10
#define PIC_EARBUD_CHG_L_DONE_INDEX     4
#define PIC_EARBUD_CHG_R_DONE_INDEX     9
#define PIC_EARBUD_CHG_LR_DONE_INDEX    14

typedef enum
{
    PIC_EARBUD_CHG_NULL = 0,
    PIC_EARBUD_CHG_L,
    PIC_EARBUD_CHG_R,
    PIC_EARBUD_CHG_LR,
    PIC_EARBUD_CHG_LR_DONE
}pic_earbud_chg_state_t;

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
    pic_earbud_chg_state_t picEarbudChgState;
}pic_para_t;

typedef struct _lcd_para_t
{
    lcd_show_callback_t battery_level_show_callback;
    lcd_show_callback_t earbud_chg_show_callback; 
    
    uint8_t r_earbudFlashStep;
    char battLevelStr[5];

    uint16_t battLeveColor;
    
    uint16_t startX;
    uint16_t startY;
    uint8_t  flashCharIndex;
    uint8_t  flashCharLength;
}lcd_para_t;

void App_Lcd_Init(void );
void App_Lcd_Clr(void );
void App_Lcd_Show_Logo(void );
void App_Lcd_Show_Battery_Level(uint8_t battLevel, uint16_t color );
void App_Lcd_Show_Earbud_Chg_Enable(pic_earbud_chg_state_t picEarbudChgState );
void App_Lcd_Background_Led_On(void );
void App_Lcd_Background_Led_Off(void );
void App_Lcd_Set_Pic_Enable(uint8_t *buf, uint16_t length );
void App_Lcd_Set_Pic_Data(uint8_t *buf, uint16_t length );
void App_Lcd_Show_Logo_Handler(void );
void App_Lcd_Show_Logo_Enable(void );
void App_Lcd_Show_Logo_Disable(void );

void App_Lcd_Task_Sleep(void );
void App_Lcd_Task_Wakeup(void );

pic_state_t App_Lcd_Get_Logo_Show_State(void );
pic_state_t App_Lcd_Get_Earbud_Show_State(void );
void App_Lcd_Init_Earbud_Chg_Show_State(void );

#endif 

