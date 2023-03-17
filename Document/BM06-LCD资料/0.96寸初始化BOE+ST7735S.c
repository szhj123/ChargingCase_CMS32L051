// N096-1608TBBIG11-H13  //
//Newvision  //
//ST7735S       //

/*====================================================*/
void Initial_ST7735(void)
{
	IOSET = nRESB;	
	Delay(10000);
	IOCLR = nRESB;
	Delay(10000);	
	IOSET = nRESB;	
	Delay(1000);

WriteCom(0x11); 
Delay(1000);	

WriteCom(0xB1);     //------------------------------------ST7735S Frame Rate-----------------------------------------//
WriteData(0x05);   
WriteData(0x3C);   
WriteData(0x3C);   

WriteCom(0xB2);     
WriteData(0x05);   
WriteData(0x3C);   
WriteData(0x3C);   

WriteCom(0xB3);     
WriteData(0x05);   
WriteData(0x3C);   
WriteData(0x3C);   
WriteData(0x05);   
WriteData(0x3C);   
WriteData(0x3C);   //------------------------------------End ST7735S Frame Rate-----------------------------------------//

WriteCom(0xB4);     //Dot inversion
WriteData(0x03);   

WriteCom(0xC0);     //------------------------------------ST7735S Power Sequence-----------------------------------------//
WriteData(0x0E);   
WriteData(0x0E);   
WriteData(0x04);   

WriteCom(0xC1);     
WriteData(0xC0);   

WriteCom(0xC2);     
WriteData(0x0D);   
WriteData(0x00);   

WriteCom(0xC3);     
WriteData(0x8D);   
WriteData(0x2A);   

WriteCom(0xC4);     
WriteData(0x8D);   
WriteData(0xEE);   //---------------------------------End ST7735S Power Sequence-------------------------------------//

WriteCom(0xC5);     //VCOM
WriteData(0x04);   

WriteCom(0x36);     //MX, MY, RGB mode
WriteData(0x08);   

WriteCom(0x3a);  
WriteData(0x05);  


WriteCom(0xE0);     
WriteData(0x05);   
WriteData(0x1A);   
WriteData(0x0B);   
WriteData(0x15);   
WriteData(0x3D);   
WriteData(0x38);   
WriteData(0x2E);   
WriteData(0x30);   
WriteData(0x2D);   
WriteData(0x28);   
WriteData(0x30);   
WriteData(0x3B);   
WriteData(0x00);   
WriteData(0x01);   
WriteData(0x02);   
WriteData(0x10);   

WriteCom(0xE1);     
WriteData(0x05);   
WriteData(0x1A);   
WriteData(0x0B);   
WriteData(0x15);   
WriteData(0x36);   
WriteData(0x2E);   
WriteData(0x28);   
WriteData(0x2B);   
WriteData(0x2B);   
WriteData(0x28);   
WriteData(0x30);   
WriteData(0x3B);   
WriteData(0x00);   
WriteData(0x01);   
WriteData(0x02);   
WriteData(0x10);   
WriteCom(0x29); 

}


/*====================================================*/
void address(void)
{             
	WriteCom(0x2A);       
	WriteData(0x00);  
	WriteData(0x18);  
	WriteData(0x00);
	WriteData(0x67);  

	WriteCom(0x2B);       
	WriteData(0x00);
	WriteData(0x00);  
	WriteData(0x00);
	WriteData(0x9F); 
				   
	WriteCom(0x2C);
 }	
 
