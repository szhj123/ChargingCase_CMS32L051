/********************************************************
* @file       hal_lcd.c
* @author     szhj13
* @version    V1.0
* @date       2022-06-06
* @brief      the start address of program
**********************************************************
* @Modify

**********************************************************/

/* Includes ---------------------------------------------*/
#include "hal_lcd.h"

/* Private typedef --------------------------------------*/
/* Private define ------------------ ------------------- -*/
/* Private macro ---------------------------------------*/
/* Private function ---------------------------------- --*/
/* Private variables ------------------------------------*/
static Hal_Isr_Callback_t lcd_isr_callback = NULL;
static uint8_t lcdClrReqFlag;

void Hal_Lcd_Init(void )
{
    Cms32l051_Gpio_Init();

    Cms32l051_Spi20_Init();
}

void Hal_Lcd_Spi_Send_With_DMA(const uint8_t *buf, uint16_t length, Hal_Isr_Callback_t callback )
{
    LCD_CS_LOW();

	LCD_RS_HIGH();

    SCI1->SOE1 |= _0001_SCI_CH0_OUTPUT_ENABLE;
    SCI1->SS1 |= _0001_SCI_CH0_START_TRG_ON;

    SCI1->SCR10 &= ~_C000_SCI_RECEPTION_TRANSMISSION;
    SCI1->SCR10 |= _8000_SCI_TRANSMISSION;

    /* write transfer data with DMA */
    DMAVEC->VEC[DMA_VECTOR_SPI20] = CTRL_DATA_SPI20;
    DMAVEC->CTRL[CTRL_DATA_SPI20].DMACR = (0 << CTRL_DMACR_SZ_Pos) | (1 << CTRL_DMACR_RPTINT_Pos) | 
                                          (0 << CTRL_DMACR_DAMOD_Pos) | (1 << CTRL_DMACR_SAMOD_Pos) |
                                          (0 << CTRL_DMACR_MODE_Pos);
    DMAVEC->CTRL[CTRL_DATA_SPI20].DMBLS = 1;
    DMAVEC->CTRL[CTRL_DATA_SPI20].DMACT = length-1;
    DMAVEC->CTRL[CTRL_DATA_SPI20].DMRLD = length-1;
    DMAVEC->CTRL[CTRL_DATA_SPI20].DMSAR = (uint32_t)&buf[1];
    DMAVEC->CTRL[CTRL_DATA_SPI20].DMDAR = (uint32_t)&SCI1->SIO20;

    /* init DMA registers */
    CGC->PER1 |= CGC_PER1_DMAEN_Msk;
    DMA->DMABAR = DMAVEC_BASE;
    DMA_Enable(DMA_VECTOR_SPI20);
    
    /* clear INTSPI10 interrupt flag */
    INTC_ClearPendingIRQ(SPI20_IRQn);
    NVIC_ClearPendingIRQ(SPI20_IRQn);
    /* enable INTSPI10 interrupt */
    INTC_EnableIRQ(SPI20_IRQn);

    lcd_isr_callback = callback;

    lcdClrReqFlag = 1;

    SCI1->SIO20 = buf[0]; /* started by writing data to SDR[7:0] */
}

void Hal_Lcd_Spi_Send_One_Byte(uint8_t dat )
{
    SCI1->SOE1 |= _0001_SCI_CH0_OUTPUT_ENABLE;
    SCI1->SS1 |= _0001_SCI_CH0_START_TRG_ON;

    SCI1->SIO20 = dat; /* started by writing data to SDR[7:0] */
    while (SCI1->SSR10 & _0040_SCI_UNDER_EXECUTE)
    {
        ;
    }
}

void Hal_Lcd_Send_With_Loop(uint8_t *buf, uint16_t length )
{
    uint16_t i;

    SCI1->SOE1 |= _0001_SCI_CH0_OUTPUT_ENABLE;
    SCI1->SS1 |= _0001_SCI_CH0_START_TRG_ON;
    
    for(i=0;i<length;i++)
    {
        SCI1->SIO20 = buf[i]; /* started by writing data to SDR[7:0] */
        while (SCI1->SSR10 & _0040_SCI_UNDER_EXECUTE)
        {
            ;
        }
    }
}

void Hal_Lcd_Isr_Handler(void )
{
    if(lcdClrReqFlag)
    {
        lcdClrReqFlag = 0;
        
		LCD_CS_HIGH();
        
        if(lcd_isr_callback != NULL)
        {
            lcd_isr_callback();
        }
    }
}

