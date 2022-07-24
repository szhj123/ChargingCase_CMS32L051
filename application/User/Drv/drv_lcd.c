/********************************************************
* @file       drv_lcd.c
* @author     szhj13
* @version    V1.0
* @date       2022-06-06
* @brief      the start address of program
**********************************************************
* @Modify

**********************************************************/

/* Includes ---------------------------------------------*/
#include "drv_lcd.h"
#include "drv_timer.h"
/* Private typedef --------------------------------------*/
/* Private define ------------------ ------------------- -*/
/* Private macro ---------------------------------------*/
/* Private function ---------------------------------- --*/
/* Private variables ------------------------------------*/

void Drv_Lcd_Init(void )
{
    Hal_Lcd_Init();

    LCD_RST_HIGH();
    Drv_Lcd_Delay_Us(120);
    LCD_RST_LOW();
    Drv_Lcd_Delay_Us(100);
    LCD_RST_HIGH();
    Drv_Lcd_Delay_Us(120);

    Drv_Lcd_Wr_Cmd(0xff);
    Drv_Lcd_Wr_Data(0xa5);
    Drv_Lcd_Wr_Cmd(0x3a);
    Drv_Lcd_Wr_Data(0x55); //65
    Drv_Lcd_Wr_Cmd(0x51);
    Drv_Lcd_Wr_Data(0x14);
    Drv_Lcd_Wr_Cmd(0x53);
    Drv_Lcd_Wr_Data(0x11);
    Drv_Lcd_Wr_Cmd(0x62);
    Drv_Lcd_Wr_Data(0x20);
    Drv_Lcd_Wr_Cmd(0x86);
    Drv_Lcd_Wr_Data(0x00);
    Drv_Lcd_Wr_Cmd(0x87);
    Drv_Lcd_Wr_Data(0x1a);
    Drv_Lcd_Wr_Cmd(0x88);
    Drv_Lcd_Wr_Data(0x11);//vcomh0
    Drv_Lcd_Wr_Cmd(0x89);
    Drv_Lcd_Wr_Data(0x1c);//vcoml
    Drv_Lcd_Wr_Cmd(0x61);
    Drv_Lcd_Wr_Data(0x16);
    Drv_Lcd_Wr_Cmd(0x93);
    Drv_Lcd_Wr_Data(0x12); // 13--line inversion 12--frame inversion
    Drv_Lcd_Wr_Cmd(0x95);
    Drv_Lcd_Wr_Data(0x10);
    Drv_Lcd_Wr_Cmd(0x96);
    Drv_Lcd_Wr_Data(0x0e);
    Drv_Lcd_Wr_Cmd(0xb4);
    Drv_Lcd_Wr_Data(0x60);
    Drv_Lcd_Wr_Cmd(0x91);
    Drv_Lcd_Wr_Data(0x10);
    Drv_Lcd_Wr_Cmd(0xC1);
    Drv_Lcd_Wr_Data(0xF1);
    Drv_Lcd_Wr_Cmd(0xC5);
    Drv_Lcd_Wr_Data(0xF8);
    Drv_Lcd_Wr_Cmd(0xb5);
    Drv_Lcd_Wr_Data(0x20);
    Drv_Lcd_Wr_Cmd(0xc3);
    Drv_Lcd_Wr_Data(0x11);//ss/gs
    Drv_Lcd_Wr_Cmd(0x83);
    Drv_Lcd_Wr_Data(0x10);
    //////////////////////gamma_set//////////////////////////////////////
    Drv_Lcd_Wr_Cmd(0x2a); // Set col address
    Drv_Lcd_Wr_Data(0x00);
    Drv_Lcd_Wr_Data(0x84); // Start col address
    Drv_Lcd_Wr_Data(0x00);
    Drv_Lcd_Wr_Data(0x84); // End col address

    Drv_Lcd_Wr_Cmd(0x2b); // Set page address
    Drv_Lcd_Wr_Data(0x00);
    Drv_Lcd_Wr_Data(0x00); // Start col address
    Drv_Lcd_Wr_Data(0x00);
    Drv_Lcd_Wr_Data(0x1f); // End col address

    Drv_Lcd_Wr_Cmd(0x2c); // Write Display Data
    Drv_Lcd_Wr_Data(0x00);
    Drv_Lcd_Wr_Data(0x00);
    Drv_Lcd_Wr_Data(0x00);
    Drv_Lcd_Wr_Data(0x00);
    Drv_Lcd_Wr_Data(0x00);
    Drv_Lcd_Wr_Data(0x00);
    Drv_Lcd_Wr_Data(0x00);
    Drv_Lcd_Wr_Data(0x00);
    Drv_Lcd_Wr_Data(0x00);
    Drv_Lcd_Wr_Data(0x00);
    Drv_Lcd_Wr_Data(0x00);
    Drv_Lcd_Wr_Data(0x13);//VPMIDP G[0] 15/16
    Drv_Lcd_Wr_Data(0x00);
    Drv_Lcd_Wr_Data(0x11);//VRP1 G[1] 10
    Drv_Lcd_Wr_Data(0x00);
    Drv_Lcd_Wr_Data(0x16);//VRP0 G[2] 21
    Drv_Lcd_Wr_Data(0x00);
    Drv_Lcd_Wr_Data(0x05);//KP7 G[3] 0
    Drv_Lcd_Wr_Data(0x00);
    Drv_Lcd_Wr_Data(0x0d);//KP6 G[4] 1
    Drv_Lcd_Wr_Data(0x00);
    Drv_Lcd_Wr_Data(0x0c);//KP5 G[5] 2
    Drv_Lcd_Wr_Data(0x00);
    Drv_Lcd_Wr_Data(0x0d);//KP4 G[6] 6
    Drv_Lcd_Wr_Data(0x00);
    Drv_Lcd_Wr_Data(0x1e);//KP3 G[7] 25
    Drv_Lcd_Wr_Data(0x00);
    Drv_Lcd_Wr_Data(0x1b);//KP2 G[8] 29
    Drv_Lcd_Wr_Data(0x00);
    Drv_Lcd_Wr_Data(0x1b);//KP1 G[9] 30
    Drv_Lcd_Wr_Data(0x00);
    Drv_Lcd_Wr_Data(0x1f);//KP0 G[10] 31
    Drv_Lcd_Wr_Data(0x00);
    Drv_Lcd_Wr_Data(0x00);
    Drv_Lcd_Wr_Data(0x00);
    Drv_Lcd_Wr_Data(0x00);
    Drv_Lcd_Wr_Data(0x00);
    Drv_Lcd_Wr_Data(0x00);
    Drv_Lcd_Wr_Data(0x00);
    Drv_Lcd_Wr_Data(0x00);
    Drv_Lcd_Wr_Data(0x00);
    Drv_Lcd_Wr_Data(0x00);
    Drv_Lcd_Wr_Data(0x00);
    Drv_Lcd_Wr_Data(31-0x13);//VPMIDN G[11] 15/16
    Drv_Lcd_Wr_Data(0x00);
    Drv_Lcd_Wr_Data(31-0x16); //VRN0 G[13] 21
    Drv_Lcd_Wr_Data(0x00);
    Drv_Lcd_Wr_Data(31-0x11);//VRN1 G[12] 10
    Drv_Lcd_Wr_Data(0x00);
    Drv_Lcd_Wr_Data(31-0x1f);//KN0 G[21] 31
    Drv_Lcd_Wr_Data(0x00);
    Drv_Lcd_Wr_Data(31-0x1b);//KN1 G[20] 30
    Drv_Lcd_Wr_Data(0x00);
    Drv_Lcd_Wr_Data(31-0x1b);//KN2 G[19] 29
    Drv_Lcd_Wr_Data(0x00);
    Drv_Lcd_Wr_Data(31-0x1e);//KN3 G[18] 25
    Drv_Lcd_Wr_Data(0x00);
    Drv_Lcd_Wr_Data(31-0x0d);//KN4 G[17] 6
    Drv_Lcd_Wr_Data(0x00);
    Drv_Lcd_Wr_Data(31-0x0c);//KN5 G[16] 2
    Drv_Lcd_Wr_Data(0X00);
    Drv_Lcd_Wr_Data(31-0x13);//KN6 G[15] 1
    Drv_Lcd_Wr_Data(0x00);
    Drv_Lcd_Wr_Data(31-0x05);//KN7 G[14] 0

    Drv_Lcd_Wr_Cmd(0x2a); // Set col address
    Drv_Lcd_Wr_Data(0); // Start col address
    Drv_Lcd_Wr_Data(0);
    Drv_Lcd_Wr_Data(0);
    Drv_Lcd_Wr_Data(120); // End col address

    Drv_Lcd_Wr_Cmd(0x2b); // Set page address
    Drv_Lcd_Wr_Data(0); // Start col address
    Drv_Lcd_Wr_Data(0);
    Drv_Lcd_Wr_Data(0);
    Drv_Lcd_Wr_Data(160); //159 End col address

    Drv_Lcd_Wr_Cmd(0x83);
    Drv_Lcd_Wr_Data(0x00);
    Drv_Lcd_Wr_Cmd(0xff);
    Drv_Lcd_Wr_Data(0x00);

    Drv_Lcd_Wr_Cmd(0x11);
    Drv_Lcd_Delay_Us(200);
    Drv_Lcd_Wr_Cmd(0x21);
    Drv_Lcd_Wr_Cmd(0x36);
    Drv_Lcd_Wr_Data(0x00);
    Drv_Lcd_Wr_Cmd(0x29);
    
    Drv_Lcd_Clr(0x0000);
    
    Drv_LCD_BackLed_On();
}
void Drv_Lcd_Clr(uint16_t color)
{
	uint16_t i,j;

	Drv_Lcd_Set_Position(0,0, LCD_W-1,LCD_H-1);

    LCD_CS_LOW();

	LCD_RS_HIGH();

	for(i=0;i<LCD_W;i++)
	{
	    for(j=0;j<LCD_H;j++)
		{    
			Hal_Lcd_Spi_Send_One_Byte(color>>8);
			Hal_Lcd_Spi_Send_One_Byte(color);
		}
	}

    LCD_CS_HIGH();
}


void Drv_Lcd_Show_Picture(const uint8_t *buf, uint32_t length, Hal_Isr_Callback_t callback )
{
    Drv_Lcd_Set_Position(0,0, LCD_W-1,LCD_H-1);

    Hal_Lcd_Spi_Send_With_DMA(buf, length, callback);
}


void Drv_Lcd_Set_Position(uint16_t startX, uint16_t startY, uint16_t endX, uint16_t endY )
{
	Drv_Lcd_Wr_Cmd(0x2A);
	Drv_Lcd_Wr_Data(startX>>8);
	Drv_Lcd_Wr_Data(startX&0xff);
	Drv_Lcd_Wr_Data(endX>>8);
	Drv_Lcd_Wr_Data(endX&0xff);
    
	Drv_Lcd_Wr_Cmd(0x2B);
	Drv_Lcd_Wr_Data(startY>>8);
	Drv_Lcd_Wr_Data(startY&0xff);
	Drv_Lcd_Wr_Data(endY>>8);
	Drv_Lcd_Wr_Data(endY&0xff);

    Drv_Lcd_Wr_Cmd(0x2c);
}


void Drv_Lcd_Wr_Cmd(uint8_t cmd )
{
    LCD_CS_LOW();

    LCD_RS_LOW();

    Hal_Lcd_Spi_Send_One_Byte(cmd);

    LCD_CS_HIGH();
    
}

void Drv_Lcd_Wr_Data(uint8_t dat )
{
    LCD_CS_LOW();

    LCD_RS_HIGH();

    Hal_Lcd_Spi_Send_One_Byte(dat);

    LCD_CS_HIGH();
}


void Drv_LCD_BackLed_On(void )
{
    LCD_BACK_LED_LOW();
}

void Drv_LCD_BackLed_Off(void )
{
    LCD_BACK_LED_HIGH();
}

void Drv_Lcd_Delay_Us(uint16_t us )
{
    uint16_t i;

    while(us--)
    {
        for(i=0;i<48;i++);
    }
}

