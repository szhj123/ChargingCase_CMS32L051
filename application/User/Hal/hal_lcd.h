#ifndef _HAL_LCD_H
#define _HAL_LCD_H

#include "hal_cms32l051.h"

#define LCD_W 121u
#define LCD_H 161u

#define PIC_MAX_SIZE (LCD_W * LCD_H * 2)


#define LCD_CS_LOW() PORT_ClrBit(PORT12, PIN0)
#define LCD_CS_HIGH() PORT_SetBit(PORT12, PIN0)

#define LCD_RS_LOW() PORT_ClrBit(PORT3, PIN1)
#define LCD_RS_HIGH() PORT_SetBit(PORT3, PIN1)

#define LCD_RST_LOW() PORT_ClrBit(PORT13, PIN6)
#define LCD_RST_HIGH() PORT_SetBit(PORT13, PIN6)

#define LCD_BACK_LED_HIGH() PORT_SetBit(PORT14, PIN7)
#define LCD_BACK_LED_LOW() PORT_ClrBit(PORT14, PIN7)


void Hal_Lcd_Init(void );
void Hal_Lcd_Send_Single_Data(uint8_t dat );
void Hal_Lcd_Send_With_Loop(uint8_t *buf, uint16_t length );
void Hal_Lcd_Set_BgColor(uint8_t *pBuf, uint16_t length, Hal_Isr_Callback_t callback );
void Hal_Lcd_Isr_Handler(void );

#endif 

