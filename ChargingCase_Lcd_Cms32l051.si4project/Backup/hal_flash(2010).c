/********************************************************
* @file       hal_flash.c
* @author     szhj13
* @version    V1.0
* @date       2022-06-06
* @brief      the start address of program
**********************************************************
* @Modify

**********************************************************/

/* Includes ---------------------------------------------*/
#include "hal_flash.h"
/* Private typedef --------------------------------------*/
/* Private define ------------------ ------------------- -*/
/* Private macro ---------------------------------------*/
/* Private function ---------------------------------- --*/
/* Private variables ------------------------------------*/
static uint8_t flashWrRequest = 0;
static uint8_t *flashWrPtr = NULL;
static uint32_t flashWrLength;

static uint8_t flashRdRequet = 0;
static uint8_t *flashRdPtr = NULL;
static uint8_t flashRdLength;

static flash_isr_callback_t flash_write_end_callback = NULL;
static flash_isr_callback_t flash_Read_end_callback = NULL;

void Hal_Flash_Init(void )
{
    Cms32l051_Spi00_Init();
}

void Hal_Flash_Start(void )
{
    /* SSn Active */
    SS00_PORT_CLR();
    SCI0->SOE0 |= _0001_SCI_CH0_OUTPUT_ENABLE;
    SCI0->SS0 |= _0001_SCI_CH0_START_TRG_ON;
}

void Hal_Flash_Stop(void )
{
    /* disable INTSPI00 interrupt */
    INTC_DisableIRQ(SPI00_IRQn);
    SCI0->ST0 |= _0001_SCI_CH0_STOP_TRG_ON;
    SCI0->SOE0 &= (uint16_t)~_0001_SCI_CH0_OUTPUT_ENABLE;
    /* clear INTSPI00 interrupt flag */
    INTC_ClearPendingIRQ(SPI00_IRQn);
    /* SSn Inactive */
    SS00_PORT_SET();
}

void Hal_Flash_Single_Write(uint8_t dat )
{
    SCI0->SIO00 = dat;
    SCI0->SOE0 |= _0001_SCI_CH0_OUTPUT_ENABLE;
    SCI0->SS0 |= _0001_SCI_CH0_START_TRG_ON;
    
    while (SCI0->SSR00 & _0040_SCI_UNDER_EXECUTE)
    {
        ;
    }
}

void Hal_Flash_Multiple_Write_With_Loop(uint8_t *buf, uint16_t length )
{
    uint16_t i;

    for(i=0;i<length;i++)
    {
        SCI0->SIO00 = buf[i];        
        SCI0->SOE0 |= _0001_SCI_CH0_OUTPUT_ENABLE;
        SCI0->SS0 |= _0001_SCI_CH0_START_TRG_ON;
    
        while (SCI0->SSR00 & _0040_SCI_UNDER_EXECUTE)
        {
            ;
        }
    }
}

void Hal_Flash_Multiple_Read_With_Loop(uint8_t *buf, uint16_t length )
{
    uint16_t i;
    uint8_t dummy = 0xff;

    for(i=0;i<length;i++)
    {
        SCI0->SIO00 = dummy; 
        SCI0->SOE0 |= _0001_SCI_CH0_OUTPUT_ENABLE;
        SCI0->SS0 |= _0001_SCI_CH0_START_TRG_ON;
        
        while (SCI0->SSR00 & _0040_SCI_UNDER_EXECUTE)
        {
            ;
        }

        buf[i] = SCI0->SIO00;
    }
}

void Hal_Flash_Write_With_Interrupt(uint8_t *buf, uint32_t length , flash_isr_callback_t callback )
{
    if (length < 1U)
    {
        return ;
    }
    else
    {
        SCI0->SCR00 &= ~_C000_SCI_RECEPTION_TRANSMISSION;
        SCI0->SCR00 |= _8000_SCI_TRANSMISSION;
        
        flashWrRequest = 1;
        flashWrLength = length;    /* send data count */
        flashWrPtr = buf; /* send buffer pointer */
        flash_write_end_callback = callback;

        SPI00_Start();
        SCI0->SIO00 = *flashWrPtr; /* started by writing data to SDR[7:0] */
        flashWrPtr++;
        flashWrLength--;
    }
}

void Hal_Flash_Write_With_DMA(uint8_t *buf, uint32_t length , flash_isr_callback_t callback )
{
    /* write transfer data with DMA */
    DMAVEC->VEC[DMA_VECTOR_SPI00] = CTRL_DATA_SPI00;
    DMAVEC->CTRL[CTRL_DATA_SPI00].DMACR = (0 << CTRL_DMACR_SZ_Pos) | (0 << CTRL_DMACR_CHNE_Pos) |
                                          (0 << CTRL_DMACR_DAMOD_Pos) | (1 << CTRL_DMACR_SAMOD_Pos) |
                                          (0 << CTRL_DMACR_MODE_Pos);
    DMAVEC->CTRL[CTRL_DATA_SPI00].DMBLS = 1;
    DMAVEC->CTRL[CTRL_DATA_SPI00].DMACT = length - 1;
    DMAVEC->CTRL[CTRL_DATA_SPI00].DMRLD = length - 1;
    DMAVEC->CTRL[CTRL_DATA_SPI00].DMSAR = (uint32_t)(buf + 1);
    DMAVEC->CTRL[CTRL_DATA_SPI00].DMDAR = (uint32_t)&SCI0->SIO00;

    /* init DMA registers */
    CGC->PER1 |= CGC_PER1_DMAEN_Msk;
    DMA->DMABAR = DMAVEC_BASE;
    DMA->DMAEN1 |= (1 << DMA_VECTOR_SPI00 % 8);

    flashWrRequest = 1;
    flashWrLength = 1;         /* send data count */
    flashWrPtr = buf; /* send buffer pointer */
    flash_write_end_callback = callback;

    SPI00_Start();
    SCI0->SIO00 = *flashWrPtr; /* started by writing data to SDR[7:0] */
    flashWrPtr++;
    flashWrLength--;
}

void Hal_Flash_Read_With_DMA(uint8_t *buf, uint32_t length, flash_isr_callback_t callback )
{
    static uint8_t dummy_sio01 = 0xFFU;

    if (length < 1U)
    {
        return ;
    }
    else
    {
        /* read receive data with DMA */
        DMAVEC->VEC[DMA_VECTOR_SPI01] = CTRL_DATA_SPI01;
        DMAVEC->CTRL[CTRL_DATA_SPI01].DMACR = (0 << CTRL_DMACR_SZ_Pos) | (1 << CTRL_DMACR_CHNE_Pos) |
                                              (1 << CTRL_DMACR_DAMOD_Pos) | (0 << CTRL_DMACR_SAMOD_Pos) |
                                              (0 << CTRL_DMACR_MODE_Pos);
        DMAVEC->CTRL[CTRL_DATA_SPI01].DMBLS = 1;
        DMAVEC->CTRL[CTRL_DATA_SPI01].DMACT = length - 1;
        DMAVEC->CTRL[CTRL_DATA_SPI01].DMRLD = length - 1;
        DMAVEC->CTRL[CTRL_DATA_SPI01].DMSAR = (uint32_t)&SCI0->SIO01;
        DMAVEC->CTRL[CTRL_DATA_SPI01].DMDAR = (uint32_t)buf;

        /* write dummy transfer data with DMA */
        DMAVEC->CTRL[CTRL_DATA_SPI01 + 1].DMACR = (0 << CTRL_DMACR_SZ_Pos) | (0 << CTRL_DMACR_CHNE_Pos) |
                                                  (0 << CTRL_DMACR_DAMOD_Pos) | (0 << CTRL_DMACR_SAMOD_Pos) |
                                                  (0 << CTRL_DMACR_MODE_Pos);
        DMAVEC->CTRL[CTRL_DATA_SPI01 + 1].DMBLS = 1;
        DMAVEC->CTRL[CTRL_DATA_SPI01 + 1].DMACT = length - 1;
        DMAVEC->CTRL[CTRL_DATA_SPI01 + 1].DMRLD = length - 1;
        DMAVEC->CTRL[CTRL_DATA_SPI01 + 1].DMSAR = (uint32_t)&dummy_sio01;
        DMAVEC->CTRL[CTRL_DATA_SPI01 + 1].DMDAR = (uint32_t)&SCI0->SIO01;

        /* init DMA registers */
        CGC->PER1 |= CGC_PER1_DMAEN_Msk;
        DMA->DMABAR = DMAVEC_BASE;
        DMA->DMAEN1 |= (1 << DMA_VECTOR_SPI01 % 8);

        flashRdRequet = 1;
        flashRdLength  = 1;                  /* receive data count */
        flashRdPtr = buf + length - 1; /* receive buffer pointer */
        flash_Read_end_callback = callback ;
        
        SPI01_Start();
        
        SCI0->SIO01 = dummy_sio01;
    }
}

void Hal_Flash_Write_Isr_Handler(void )
{
    if(flashWrRequest)
    {
        if(flashWrLength)
        {
            SCI0->SIO00 = *flashWrPtr;

            flashWrPtr++;

            flashWrLength--;
        }
        else
        {
            while (SCI0->SSR00 & _0040_SCI_UNDER_EXECUTE)
            {
                ;
            }

            if(flash_write_end_callback != NULL)
            {
                flash_write_end_callback();
                
                flashWrRequest = 0;

                flash_write_end_callback = NULL;
            }
        }
    }
}

void Hal_Flash_Read_Isr_Handler(void )
{
    volatile uint8_t sio_dummy;
    
    if(flashRdRequet)
    {
        if(1U == flashRdLength)
        {
            while ((SCI0->SSR00 & _0020_SCI_VALID_STORED) == 0)
            {
                ;
            }
            if (0U != flashRdPtr)
            {
                *flashRdPtr = SCI0->SIO00;
                 flashRdLength--;
            }
            else
            {
                sio_dummy = SCI0->SIO00;
            }
            
            if(flash_Read_end_callback != NULL)
            {
                flash_Read_end_callback();
                
                flashRdRequet = 0;

                flash_Read_end_callback = NULL;
            }
        }
    }
}

