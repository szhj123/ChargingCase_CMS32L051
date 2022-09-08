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
#include "drv_lcd_font.h"
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
    Drv_Lcd_Wr_Data(132); // End col address

    Drv_Lcd_Wr_Cmd(0x2b); // Set page address
    Drv_Lcd_Wr_Data(0); // Start col address
    Drv_Lcd_Wr_Data(0);
    Drv_Lcd_Wr_Data(0);
    Drv_Lcd_Wr_Data(162); //159 End col address

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

    Drv_Lcd_Wr_Cmd(0x36);
    Drv_Lcd_Wr_Data(0xc0);
    
    Drv_Lcd_Clr(0x0000);
    
    Drv_Lcd_Background_Led_On();

    #if 0

    Drv_Lcd_Show_String(32, 10, "100%", WHITE, BLACK, 32, 0);

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
    #endif 
}

void Drv_Lcd_Clr(uint16_t color)
{
	uint16_t i,j;

	Drv_Lcd_Set_Position(0, 0, LCD_W-1,LCD_H-1);

    LCD_CS_LOW();

	LCD_RS_HIGH();

	for(i=0;i<LCD_H;i++)
	{
	    for(j=0;j<LCD_W;j++)
		{    
			Hal_Lcd_Spi_Send_One_Byte(color>>8);
			Hal_Lcd_Spi_Send_One_Byte(color);
		}
	}
    
    LCD_CS_HIGH();
}

void Drv_Lcd_Wr_Color(uint16_t dat)
{
    LCD_CS_LOW();

	LCD_RS_HIGH();

    Hal_Lcd_Spi_Send_One_Byte(dat>>8);
    Hal_Lcd_Spi_Send_One_Byte(dat);

    LCD_CS_HIGH();
}


void Drv_Lcd_Show_Picture(const uint8_t *buf, uint32_t length, Hal_Isr_Callback_t callback )
{
    #if 1

    Drv_Lcd_Set_Position(0,0, 131-1, 162-1);

    Hal_Lcd_Spi_Send_With_DMA(buf, length, callback);
    
    #else
    Hal_Lcd_Spi_Send_With_DMA(buf, length, callback);
    #endif 
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


void Drv_Lcd_Background_Led_On(void )
{
    LCD_BACK_LED_LOW();
}

void Drv_Lcd_Background_Led_Off(void )
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

void Drv_Lcd_Fill(uint16_t xsta,uint16_t ysta,uint16_t xend,uint16_t yend,uint16_t color)
{          
	uint16_t i,j; 
    
	Drv_Lcd_Set_Position(xsta,ysta,xend-1,yend-1);
    
	for(i=ysta;i<yend;i++)
	{													   	 	
		for(j=xsta;j<xend;j++)
		{
			Drv_Lcd_Wr_Color(color);
		}
	} 					  	    
}

void Drv_Lcd_Draw_Point(uint16_t x,uint16_t y,uint16_t color)
{
	Drv_Lcd_Set_Position(x,y,x,y);
	
	Drv_Lcd_Wr_Color(color);
} 

void Drv_Lcd_Draw_Line(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t color)
{
	uint16_t t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance;
	int incx,incy,uRow,uCol;
	delta_x=x2-x1; 
	delta_y=y2-y1;
	uRow=x1;
	uCol=y1;
	if(delta_x>0)incx=1; 
	else if (delta_x==0)incx=0;
	else {incx=-1;delta_x=-delta_x;}
	if(delta_y>0)incy=1;
	else if (delta_y==0)incy=0;
	else {incy=-1;delta_y=-delta_y;}
	if(delta_x>delta_y)distance=delta_x; 
	else distance=delta_y;
	for(t=0;t<distance+1;t++)
	{
		Drv_Lcd_Draw_Point(uRow,uCol,color);
		xerr+=delta_x;
		yerr+=delta_y;
		if(xerr>distance)
		{
			xerr-=distance;
			uRow+=incx;
		}
		if(yerr>distance)
		{
			yerr-=distance;
			uCol+=incy;
		}
	}
}

void Drv_Lcd_Draw_Rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,uint16_t color)
{
	Drv_Lcd_Draw_Line(x1,y1,x2,y1,color);
	Drv_Lcd_Draw_Line(x1,y1,x1,y2,color);
	Drv_Lcd_Draw_Line(x1,y2,x2,y2,color);
	Drv_Lcd_Draw_Line(x2,y1,x2,y2,color);
}

void Drv_Lcd_Show_Char(uint16_t x,uint16_t y,uint8_t num,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode)
{
	uint8_t temp,sizex,t,m=0;
	uint16_t i,TypefaceNum;//Ò»¸ö×Ö·ûËùÕ¼×Ö½Ú´óÐ¡
	uint16_t x0=x;
	sizex=sizey/2;
	TypefaceNum=(sizex/8+((sizex%8)?1:0))*sizey;
	num=num-' ';    //µÃµ½Æ«ÒÆºóµÄÖµ
	Drv_Lcd_Set_Position(x,y,x+sizex-1,y+sizey-1);  //ÉèÖÃ¹â±êÎ»ÖÃ 
	for(i=0;i<TypefaceNum;i++)
	{ 
		temp=ascii_3216[num][i];		 //µ÷ÓÃ16x32×ÖÌå

		for(t=0;t<8;t++)
		{
			if(!mode)//·Çµþ¼ÓÄ£Ê½
			{
				if(temp&(0x01<<t))Drv_Lcd_Wr_Color(fc);
				else Drv_Lcd_Wr_Color(bc);
				m++;
				if(m%sizex==0)
				{
					m=0;
					break;
				}
			}
			else//µþ¼ÓÄ£Ê½
			{
				if(temp&(0x01<<t))Drv_Lcd_Draw_Point(x,y,fc);
				x++;
				if((x-x0)==sizex)
				{
					x=x0;
					y++;
					break;
				}
			}
		}
	}   	 	  
}

uint32_t mypow(uint8_t m,uint8_t n)
{
	uint32_t result=1;	 
	while(n--)result*=m;
	return result;
}

void Drv_Lcd_Show_String(uint16_t x,uint16_t y,const uint8_t *p,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode)
{         
	while(*p!='\0')
	{       
		Drv_Lcd_Show_Char(x,y,*p,fc,bc,sizey,mode);
		x+=sizey/2;
		p++;
	}  
}

void Drv_Lcd_Show_IntNum(uint16_t x,uint16_t y,uint16_t num,uint8_t len,uint16_t fc,uint16_t bc,uint8_t sizey )
{         	
	uint8_t t,temp;
	uint8_t enshow=0;
	uint8_t sizex=sizey/2;
	for(t=0;t<len;t++)
	{
		temp=(num/mypow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				Drv_Lcd_Show_Char(x+t*sizex,y,' ',fc,bc,sizey,0);
				continue;
			}else enshow=1; 
		 	 
		}
        
	 	Drv_Lcd_Show_Char(x+t*sizex,y,temp+48,fc,bc,sizey,0);
	}
} 


