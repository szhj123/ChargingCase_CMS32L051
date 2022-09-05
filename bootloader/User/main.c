/********************************************************
* @file       main.c
* @author     szhj13
* @version    V1.0
* @date       2022-06-06
* @brief      the start address of program
**********************************************************
* @Modify

**********************************************************/

/* Includes ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CMS32L051.h"
#include "flash.h"
#include "userdefine.h"
/* Private typedef --------------------------------------*/
typedef void (*app_func_callback_t)(void );
/* Private define ------------------ --------------------*/
#define BLD_START_ADDR                0x0000
#define BLD_MAX_SIZE                  0x1800
#define APP1_START_ADDR               (BLD_START_ADDR + BLD_MAX_SIZE)
#define APP1_MAX_SIZE                 0x7400
#define APP2_START_ADDR               (APP1_START_ADDR + APP1_MAX_SIZE)
#define APP2_MAX_SIZE                 0x7400

#define FLASH_SECTOR_SIZE             0x200

#define USER_DATA_START_ADDR          0x500200

typedef struct _user_data_t
{
    uint8_t fwUpgFlag;
		uint32_t fwSize;
}user_data_t;

/* Private macro ----------------------------------------*/
/* Private function -------------------------------------*/
void Get_User_Data(uint8_t *buf, uint16_t length );
void App1_Erase(void );
void App1_ProgramPage(void );
void Set_User_Data(uint8_t *buf, uint16_t length );
uint16_t Get_Fw_Checksum(uint32_t flashAddr, uint32_t length );
void App_Run(void );
/* Private variables ------------------------------------*/
static user_data_t userData;
static app_func_callback_t application = NULL;

int main(void )
{
		__disable_irq();
	
		SystemCoreClockUpdate();
	
		Get_User_Data((uint8_t *)&userData, sizeof(user_data_t));
	
		if(userData.fwUpgFlag == 0x01)
		{
			  uint16_t app1Checksum = 0;
				uint16_t app2Checksum = 0;
			
	      App1_Erase();
			
				App1_ProgramPage();
			
				app1Checksum = Get_Fw_Checksum(APP1_START_ADDR, userData.fwSize);
			  
				app2Checksum = Get_Fw_Checksum(APP2_START_ADDR, userData.fwSize);
			
				if(app1Checksum == app2Checksum)
				{
					  userData.fwUpgFlag = 0x0;
					
						Set_User_Data((uint8_t *)&userData, sizeof(user_data_t));
					
				    App_Run();
				}
				else
				{
					  NVIC_SystemReset();
				}
		}
		else
		{
		    App_Run();
		}
	
    while(1)
		{
		}
}


void Get_User_Data(uint8_t *buf, uint16_t length )
{
    uint16_t i;
	
		for(i=0;i<length;i++)
		{
		    buf[i] = *((uint8_t *)USER_DATA_START_ADDR + i);
		}
}

void Set_User_Data(uint8_t *buf, uint16_t length )
{
	  EraseSector(USER_DATA_START_ADDR);
	
		ProgramPage(USER_DATA_START_ADDR, sizeof(user_data_t), (uint8_t *)&userData);
}

void App1_Erase(void )
{
	  uint32_t flashAddr = APP1_START_ADDR;
	
		do{
		    EraseSector(flashAddr);
				
			  flashAddr += FLASH_SECTOR_SIZE;
			
		}while(flashAddr < (APP1_START_ADDR + userData.fwSize));
}

void App1_ProgramPage(void )
{
	  uint8_t *pBuf = (uint8_t *)APP2_START_ADDR;
		uint32_t flashAddr = APP1_START_ADDR;

		 ProgramPage(flashAddr, userData.fwSize, pBuf);
}

void InvertUint16(uint16_t *poly )
{
    uint8_t i;
    uint16_t tmp = 0;
    uint16_t polyVal = *poly;

    for(i=0;i<16;i++)
    {
        if(polyVal & (1 << i))
            tmp |= 1 << (15-i);
    }
    *poly = tmp;
}

uint16_t Flash_Cal_Checksum(uint8_t *data, uint32_t length)
{
    uint16_t wCRCin = 0x0000;
    uint16_t wCPoly = 0x8005;
    uint8_t i;

    InvertUint16(&wCPoly);

    while(length--)
    {
        wCRCin ^= *(data++);
        for(i=0;i<8;i++)
        {

            if(wCRCin & 0x0001)
                wCRCin = (wCRCin >> 1) ^ wCPoly;
            else
                wCRCin >>= 1;
        }
    }
    return wCRCin;
}

uint16_t Get_Fw_Checksum(uint32_t flashAddr, uint32_t length )
{
		return Flash_Cal_Checksum((uint8_t *)flashAddr, length );
}

void App_Run(void )
{
    uint32_t appAddress;
    
    __disable_irq();
    
		SCB->VTOR = APP1_START_ADDR;
	
		if (((*(__IO uint32_t*)APP1_START_ADDR) & 0x2FFE0000 ) == 0x20000000)
		{
			appAddress = *(__IO uint32_t*) (APP1_START_ADDR + 4);
			
			application = (app_func_callback_t)appAddress;

			/* Initialize user application's stack pointer */
			__set_MSP(*(__IO uint32_t*) APP1_START_ADDR);
    
			__enable_irq();
			/* Jump to user application */
			application();
		
        //((void (*)())BootloaderAddress)();
		}
}

