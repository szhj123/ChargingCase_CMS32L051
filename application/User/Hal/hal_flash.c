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
static uint8_t  *spi00TxPtr = NULL;
static uint8_t spi00TxReqFlag;
static uint16_t spi00TxLength;
static spi00_isr_callback_t spi00_tx_end_callback = NULL;

static uint8_t *spi00RxPtr = NULL;
static uint8_t  spi00RxReqFlag;
static uint16_t spi00RxLength;
static spi00_isr_callback_t spi00_rx_end_callback = NULL;

void Hal_Flash_Init(void )
{
    Cms32l051_Spi00_Init();
}

void Hal_Flash_Start(void )
{
    SPI00_Start();
}

void Hal_Flash_Stop(void )
{
    SPI00_Stop();
}

void Hal_Flash_Single_Write(uint8_t dat )
{
    SCI0->SIO00 = dat;
    
    while (SCI0->SSR00 & _0040_SCI_UNDER_EXECUTE)
    {
        ;
    }
}

void Hal_Flash_Multiple_Send(uint8_t *buf, uint16_t length )
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

void Hal_Flash_Multiple_Read(uint8_t *buf, uint16_t length )
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

void Hal_Flash_Multiple_Write_With_DMA(uint8_t *buf, uint16_t length , spi00_isr_callback_t callback )
{
    if (length < 1U)
    {
        return ;
    }
    else
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

        spi00TxReqFlag = 1;
        spi00TxLength = 1;         /* send data count */
        spi00TxPtr = buf;          /* send buffer pointer */
        spi00_tx_end_callback = callback;

        SPI00_Start();
        SCI0->SIO00 = *spi00TxPtr; /* started by writing data to SDR[7:0] */
        spi00TxPtr++;
        spi00TxLength--;
    }
}

void Hal_Flash_Multiple_Read_With_DMA(uint8_t *buf, uint16_t length , spi00_isr_callback_t callback )
{
    static uint8_t dummy_sio00 = 0xFFU;

    if (length < 1U)
    {
        return ;
    }
    else
    {
        /* read receive data with DMA */
        DMAVEC->VEC[DMA_VECTOR_SPI00] = CTRL_DATA_SPI00;
        DMAVEC->CTRL[CTRL_DATA_SPI00].DMACR = (0 << CTRL_DMACR_SZ_Pos) | (1 << CTRL_DMACR_CHNE_Pos) |
                                              (1 << CTRL_DMACR_DAMOD_Pos) | (0 << CTRL_DMACR_SAMOD_Pos) |
                                              (0 << CTRL_DMACR_MODE_Pos);
        DMAVEC->CTRL[CTRL_DATA_SPI00].DMBLS = 1;
        DMAVEC->CTRL[CTRL_DATA_SPI00].DMACT = length - 1;
        DMAVEC->CTRL[CTRL_DATA_SPI00].DMRLD = length - 1;
        DMAVEC->CTRL[CTRL_DATA_SPI00].DMSAR = (uint32_t)&SCI0->SIO00;
        DMAVEC->CTRL[CTRL_DATA_SPI00].DMDAR = (uint32_t)buf;

        /* write dummy transfer data with DMA */
        DMAVEC->CTRL[CTRL_DATA_SPI00 + 1].DMACR = (0 << CTRL_DMACR_SZ_Pos) | (0 << CTRL_DMACR_CHNE_Pos) |
                                                  (0 << CTRL_DMACR_DAMOD_Pos) | (0 << CTRL_DMACR_SAMOD_Pos) |
                                                  (0 << CTRL_DMACR_MODE_Pos);
        DMAVEC->CTRL[CTRL_DATA_SPI00 + 1].DMBLS = 1;
        DMAVEC->CTRL[CTRL_DATA_SPI00 + 1].DMACT = length - 1;
        DMAVEC->CTRL[CTRL_DATA_SPI00 + 1].DMRLD = length - 1;
        DMAVEC->CTRL[CTRL_DATA_SPI00 + 1].DMSAR = (uint32_t)&dummy_sio00;
        DMAVEC->CTRL[CTRL_DATA_SPI00 + 1].DMDAR = (uint32_t)&SCI0->SIO00;

        /* init DMA registers */
        CGC->PER1 |= CGC_PER1_DMAEN_Msk;
        DMA->DMABAR = DMAVEC_BASE;
        DMA->DMAEN1 |= (1 << DMA_VECTOR_SPI00 % 8);

        spi00RxReqFlag = 1;
        spi00RxLength = 1;                      /* receive data count */
        spi00RxPtr = buf + length - 1; /* receive buffer pointer */
        spi00_rx_end_callback = callback;

        SPI00_Start();
        SCI0->SIO00 = dummy_sio00;
    }
}

void Hal_Flash_Spi00_Tx_Isr_Handler(void )
{
    if(spi00TxReqFlag)
    {
        if(spi00TxLength)
        {
            SCI0->SIO00 = *spi00TxPtr;
            spi00TxPtr++;
            spi00TxLength--;
        }
        else
        {
            while (SCI0->SSR00 & _0040_SCI_UNDER_EXECUTE)
            {
                ;
            }

            spi00TxReqFlag = 0;
            spi00TxPtr = NULL;
            
            if(spi00_tx_end_callback != NULL)
            {
                spi00_tx_end_callback();

                spi00_tx_end_callback = NULL;
            }
        }
    }
}

void Hal_Flash_Spi00_Rx_Isr_Handler(void )
{
    volatile uint8_t sio_dummy;
    
    if(spi00RxReqFlag)
    {
        if(spi00RxLength > 1)
        {
            if (0U != spi00RxPtr)
            {
                *spi00RxPtr = SCI0->SIO00;
                spi00RxPtr++;
                spi00RxLength--;
            }
            else
            {
                sio_dummy = SCI0->SIO00;
            }
        }
        else
        {
            if (1U == spi00RxLength)
            {
                /* receive the last data */
                while ((SCI0->SSR00 & _0020_SCI_VALID_STORED) == 0)
                {
                    ;
                }
                if (0U != spi00RxPtr)
                {
                    *spi00RxPtr = SCI0->SIO00;
                     spi00RxLength--;
                }
                else
                {
                    sio_dummy = SCI0->SIO00;
                }
                
                spi00RxReqFlag = 0;

                 /* complete receive */
                if(spi00_rx_end_callback != NULL)
                {
                    spi00_rx_end_callback();

                    spi00_rx_end_callback = NULL;
                }
            }
        }
    }            
}

