#ifndef _DRV_LCD_H
#define _DRV_LCD_H

#include "hal_lcd.h"

void Drv_Lcd_Init(void );
void Drv_Lcd_Clr(uint16_t color );
void Drv_Lcd_Show_Picture(const uint8_t *buf, uint32_t length, Hal_Isr_Callback_t callback );
void Drv_Lcd_Set_Position(uint16_t startX, uint16_t startY, uint16_t endX, uint16_t endY );
void Drv_Lcd_Wr_Cmd(uint8_t cmd );
void Drv_Lcd_Wr_Data(uint8_t dat );
void Drv_LCD_BackLed_On(void );
void Drv_LCD_BackLed_Off(void );
void Drv_Lcd_Delay_Us(uint16_t us );

void Drv_Lcd_Wr_Color(uint16_t dat);
void Drv_Lcd_Fill(uint16_t xsta,uint16_t ysta,uint16_t xend,uint16_t yend,uint16_t color);
void Drv_Lcd_Draw_Point(uint16_t x,uint16_t y,uint16_t color);
void Drv_Lcd_Draw_Line(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t color);
void Drv_Lcd_Draw_Rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,uint16_t color);
void Drv_Lcd_Show_String(uint16_t x,uint16_t y,const uint8_t *p,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode);
void Drv_Lcd_Show_IntNum(uint16_t x,uint16_t y,uint16_t num,uint8_t len,uint16_t fc,uint16_t bc,uint8_t sizey );

#endif 


