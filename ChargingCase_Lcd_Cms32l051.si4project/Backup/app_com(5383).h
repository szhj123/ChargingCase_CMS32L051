#ifndef _APP_COM_H
#define _APP_COM_H

#include "drv_com.h"

#define FW_VER_BUILD               0
#define FW_VER_MINOR               0
#define FW_VER_MAJOR               1

#define CMD_SET_LED                0x01
#define CMD_GET_LCD_ERASE          0x02
#define CMD_SET_LCD_DATA           0x03
#define CMD_SET_LCD_ACK            0x04

#define CMD_SET_FW_ERASE           0x05
#define CMD_SET_FW_DATA            0x06
#define CMD_SET_FW_CHECKSUM        0x07
#define CMD_SET_FW_ACK             0x08

#define CMD_GET_FW_VERSION         0x09
#define CMD_SET_FW_VERSION         (CMD_GET_FW_VERSION | 0x80)

#define CMD_LCD_ACK                1
#define CMD_LCD_NAK                0

#define CMD_FW_ACK                 1
#define CMD_FW_NAK                 0

typedef struct _fw_info_t
{
    uint32_t fwSize;
    uint32_t fwOffset;
}fw_info_t;


void App_Com_Init(void );
void App_Com_Tx_Lcd_Ack(uint8_t reply );
void App_Com_Tx_Version(void );

void App_Com_Tx_Fw_Ack(uint8_t reply );

#endif 

