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

static flash_write_end_callback_t flash_write_end_callback = NULL;

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
        
        while (SCI0->SSR00 & _0040_SCI_UNDER_EXECUTE)
        {
            ;
        }

        buf[i] = SCI0->SIO00;
    }
}

void Hal_Flash_Write_With_Interrupt(uint8_t *buf, uint32_t length , flash_write_end_callback_t callback )
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

        SPI00_Start();
        SCI0->SIO00 = *flashWrPtr; /* started by writing data to SDR[7:0] */
        flashWrPtr++;
        flashWrLength--;
		}
}

void Hal_Flash_Write_With_DMA(uint8_t *buf, uint32_t length , flash_write_end_callback_t callback )
{
    SCI0->SCR00 &= ~_C000_SCI_RECEPTION_TRANSMISSION;
    SCI0->SCR00 |= _8000_SCI_TRANSMISSION;

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

void Hal_Flash_Isr_Handler(void )
{
    if(flashWrRequest)
    {
        flashWrRequest = 0;

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

                flash_write_end_callback = NULL;
            }
        }
    }
}

