/********************************************************
* @file       drv_flash.c
* @author     szhj13
* @version    V1.0
* @date       2022-06-06
* @brief      the start address of program
**********************************************************
* @Modify

**********************************************************/

/* Includes ---------------------------------------------*/
#include "drv_flash.h"
#include "drv_timer.h"

/* Private typedef --------------------------------------*/
/* Private define ------------------ ------------------- -*/
/* Private macro ---------------------------------------*/
/* Private function ---------------------------------- --*/
/* Private variables ------------------------------------*/
static uint8_t flashWrEndFlag = 0;
static uint8_t flashRdEndFlag = 0;

static user_data_t userData;

void Drv_Flash_Init(void )
{   
    Hal_Flash_Init();

    //Drv_Flash_Chip_Erase();
}

void Drv_Flash_Read_Jedec_Id(void )
{
    uint8_t dummy[3] = {0x00};
    
    Hal_Flash_Start();

    Hal_Flash_Single_Write(READ_JEDEC_ID);

    Hal_Flash_Multiple_Read(dummy, sizeof(dummy));

    Hal_Flash_Stop();
}

void Drv_Flash_Wait_Bus_Idle(void )
{
    uint8_t status;
    
    Hal_Flash_Start();
    
    Hal_Flash_Single_Write(READ_STATUS_REGISTER);

    do{
        Hal_Flash_Multiple_Read((uint8_t *)&status, 1);
    }while(status & 0x01);

    Hal_Flash_Stop();
}

void Drv_Write_Enable(void )
{
    Hal_Flash_Start();

    Hal_Flash_Single_Write(WRITE_ENABLE);
    
    Hal_Flash_Stop();

    Drv_Flash_Wait_Bus_Idle();
}

void Drv_Flash_Sector_Erase(uint32_t addr )
{
    Drv_Write_Enable();

    Hal_Flash_Start();

    Hal_Flash_Single_Write(SECTOR_ERASE);

    Hal_Flash_Single_Write((uint8_t )(addr >> 16));
    Hal_Flash_Single_Write((uint8_t )(addr >> 8));
    Hal_Flash_Single_Write((uint8_t )(addr));

    Hal_Flash_Stop();

    Drv_Flash_Wait_Bus_Idle();
}

void Drv_Flash_Block_64k_Erase(uint32_t addr )
{
    Drv_Write_Enable();

    Hal_Flash_Start();

    Hal_Flash_Single_Write(BLOCK_ERASE_64K);

    Hal_Flash_Single_Write((uint8_t )(addr >> 16));
    Hal_Flash_Single_Write((uint8_t )(addr >> 8));
    Hal_Flash_Single_Write((uint8_t )(addr));

    Hal_Flash_Stop();

    Drv_Flash_Wait_Bus_Idle();
}

void Drv_Flash_Chip_Erase(void )
{
    Drv_Write_Enable();

    Hal_Flash_Start();

    Hal_Flash_Single_Write(CHIP_ERASE);

    Hal_Flash_Stop();

    Drv_Flash_Wait_Bus_Idle();
}

void Drv_Flash_Write_With_Loop(uint32_t addr, uint8_t *buf, uint16_t length )
{
    Drv_Write_Enable();

    Hal_Flash_Start();

    Hal_Flash_Single_Write(PAGE_PROGRAM);

    Hal_Flash_Single_Write((uint8_t )(addr >> 16));
    Hal_Flash_Single_Write((uint8_t )(addr >> 8));
    Hal_Flash_Single_Write((uint8_t )(addr));

    Hal_Flash_Multiple_Send(buf, length );

    Hal_Flash_Stop();

    Drv_Flash_Wait_Bus_Idle();
}

void Drv_Flash_Read_With_Loop(uint32_t addr, uint8_t *buf, uint16_t length )
{
    Hal_Flash_Start();

    Hal_Flash_Single_Write(READ_DATA);

    Hal_Flash_Single_Write((uint8_t )(addr >> 16));
    Hal_Flash_Single_Write((uint8_t )(addr >> 8));
    Hal_Flash_Single_Write((uint8_t )(addr));

    Hal_Flash_Multiple_Read(buf, length );

    Hal_Flash_Stop();
}

static void Drv_Flash_Write_End_Callback(void )
{
    flashWrEndFlag = 1;
}

void Drv_Flash_Write_With_DMA(uint32_t addr, uint8_t *buf, uint16_t length )
{
    if(length < 1)
    {
        return ;
    }
    
    Drv_Write_Enable();
    
    Hal_Flash_Start();
    
    Hal_Flash_Single_Write(PAGE_PROGRAM);

    Hal_Flash_Single_Write((uint8_t )(addr >> 16));
    Hal_Flash_Single_Write((uint8_t )(addr >> 8));
    Hal_Flash_Single_Write((uint8_t )(addr));
    
    Hal_Flash_Multiple_Write_With_DMA(buf, length, Drv_Flash_Write_End_Callback);

    while(!flashWrEndFlag);
    flashWrEndFlag = 0;

    Hal_Flash_Stop();

    Drv_Flash_Wait_Bus_Idle();
}

void Drv_Flash_Write(uint32_t addr, uint8_t *buf, uint32_t length )
{
    uint16_t firstPageByte;
    uint16_t lastPageByte;
    uint32_t pageNum;
    uint32_t i;
   
    if((addr % PAGE_SIZE) != 0)
    {
        firstPageByte = PAGE_SIZE - (addr % PAGE_SIZE);        
    }
    else
    {
        firstPageByte = 0;
    }

    if(length > firstPageByte)
    {
        pageNum = (length - firstPageByte) / PAGE_SIZE;

        lastPageByte = (length - firstPageByte) % PAGE_SIZE;

        if(firstPageByte)
        {
            Drv_Flash_Write_With_DMA(addr, buf, firstPageByte);
            
            addr += firstPageByte;
        
            buf += firstPageByte;
        }
        
        for(i=0;i<pageNum;i++)
        {
            Drv_Flash_Write_With_DMA(addr, buf, PAGE_SIZE);

            addr += PAGE_SIZE;
            
            buf += PAGE_SIZE;
        }

        if(lastPageByte)
        {
            Drv_Flash_Write_With_DMA(addr, buf, lastPageByte);
        }
    }
    else
    {
        if(length)
        {
            Drv_Flash_Write_With_DMA(addr, buf, length);
        }
    }
}

static void Drv_Flash_Read_End_Callback(void )
{
    flashRdEndFlag = 1;
}

void Drv_Flash_Read(uint32_t addr, uint8_t *buf, uint32_t length )
{
    Hal_Flash_Start();

    Hal_Flash_Single_Write(READ_DATA);

    Hal_Flash_Single_Write((uint8_t )(addr >> 16));
    Hal_Flash_Single_Write((uint8_t )(addr >> 8));
    Hal_Flash_Single_Write((uint8_t )(addr));

    Hal_Flash_Multiple_Read_With_DMA(buf, length, Drv_Flash_Read_End_Callback);

    while(!flashRdEndFlag);
    flashRdEndFlag = 0;
    
    Hal_Flash_Stop();
}

int Drv_Internal_Flash_Sector_Erase(uint32_t adr )
{
    FMC->FLERMD = 0x10;
    FMC->FLPROT = 0xF1;
    FMC->FLOPMD1 = 0x55;
    FMC->FLOPMD2 = 0xAA;  
    // Write data to start address of sector to trigger Erase Operation
    *(uint32_t *) adr = 0xFFFFFFFF;
    
    // polling Erase Over Flag
    while((FMC->FLSTS & FMC_FLSTS_OVF_Msk) == 0);
    FMC->FLSTS |= FMC_FLSTS_OVF_Msk;
    FMC->FLERMD = 0x00;
    FMC->FLPROT = 0x00;

    if(FMC->FLSTS & FMC_FLSTS_EVF_Msk)
    {
        return(1);  /* verify ng */
    }
    else
    {
        return(0);  /* verify ok */
    }
}

int Drv_Internal_Flash_ProgramPage (uint32_t adr, uint32_t sz, uint8_t *buf)
{
    uint32_t i;
    uint8_t *ptr;
    
    ptr = (uint8_t *) adr;
    
    FMC->FLPROT = 0xF1;
    
    for(i=0; i<sz; i++) 
    {
        FMC->FLOPMD1 = 0xAA;
        FMC->FLOPMD2 = 0x55;  
        *ptr++ = *buf++;    
        // polling OVER Flag
        while((FMC->FLSTS & FMC_FLSTS_OVF_Msk) == 0);
        FMC->FLSTS |= FMC_FLSTS_OVF_Msk;
    }

    FMC->FLPROT = 0x00;
    
    return (0);
}

void Drv_Flash_App2_Erase(uint32_t fwSize )
{
    uint16_t j;

    uint32_t addr = APP2_START_ADDR;

    do{
        for(j=0;j<3;j++)
        {
            if(!Drv_Internal_Flash_Sector_Erase(addr))
            {
                break;
            }
        }

        if(j >= 3)
        {
            //flash erased error

            return ;
        }

        
        addr += INTERNALE_FLASH_SECTOR_SIZE;

    }while(addr < (APP2_START_ADDR + fwSize));

}

void Drv_Flash_App2_Program(uint32_t dataOffsetAddr, uint8_t *buf, uint32_t length )
{
    Drv_Internal_Flash_ProgramPage(APP2_START_ADDR + dataOffsetAddr, length, buf);
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

uint16_t Drv_Flash_Cal_Checksum(uint8_t *data, uint32_t length)
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

uint16_t Drv_Flash_App2_Get_Checksum(uint32_t fwSize )
{
    uint16_t checksum = 0;
    
    uint8_t *fwDataPtr = (uint8_t *)APP2_START_ADDR;

    checksum = Drv_Flash_Cal_Checksum(fwDataPtr, fwSize);

    return checksum;
}

void Drv_Flash_Set_Upg_Flag(uint8_t flag )
{
    userData.fwUpgFlag = flag;
}

void Drv_Flash_Save_User_Data(void )
{
    Drv_Internal_Flash_Sector_Erase(USER_DATA_START_ADDR);

    Drv_Internal_Flash_ProgramPage(USER_DATA_START_ADDR, sizeof(user_data_t), (uint8_t *)&userData);
}

void Bootloader_Run(void )
{
    typedef void (*bld_func_callback_t)(void );

    bld_func_callback_t Bootloader = NULL;

    uint32_t BootloaderAddress;
    
    __disable_irq();
    
	SCB->VTOR = BLD_START_ADDR;
	
	if (((*(__IO uint32_t*)BLD_START_ADDR) & 0x2FFE0000 ) == 0x20000000)
	{
		BootloaderAddress = *(__IO uint32_t*) (BLD_START_ADDR + 4);
		Bootloader = (bld_func_callback_t) BootloaderAddress;

		/* Initialize user application's stack pointer */
		__set_MSP(*(__IO uint32_t*) BLD_START_ADDR);
    
		__enable_irq();
		/* Jump to user application */
		Bootloader();
		
        //((void (*)())BootloaderAddress)();
	}
}


