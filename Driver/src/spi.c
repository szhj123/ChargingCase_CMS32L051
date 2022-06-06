/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    spi.c
* @brief   This file implements device driver for SPI module.
* @version 1.0.0
* @date    2019/12/24
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "CMS32L051.h"
#include "userdefine.h"
#include "spi.h"
#include "dma.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
volatile uint8_t *gp_spi_rx_address;       /* spi receive buffer address */
volatile uint16_t g_spi_rx_length;         /* spi receive data length */
volatile uint16_t g_spi_rx_count;          /* spi receive data count */
volatile uint8_t *gp_spi_tx_address;       /* spi send buffer address */
volatile uint16_t g_spi_tx_length;         /* spi send data length */
volatile uint16_t g_spi_tx_count;          /* spi send data count */

/***********************************************************************************************************************
* Function Name: SPI_MasterInit
* @brief  This function restarts the SPI module.
* @param  mode
*             - SPI_MODE_0: CPOL = 0, CPHA = 0; i.e. CKP = 1, DAP = 1
*             - SPI_MODE_1: CPOL = 0, CPHA = 1; i.e. CKP = 1, DAP = 0
*             - SPI_MODE_2: CPOL = 1, CPHA = 0; i.e. CKP = 0, DAP = 1
*             - SPI_MODE_3: CPOL = 1, CPHA = 1; i.e. CKP = 0, DAP = 0
* @return None
***********************************************************************************************************************/
void SPI_MasterInit(spi_mode_t mode)
{
    CGC->PER1 |= 0x80;
#ifdef SPI_WITH_DMA
    SPI->SPIC = _0003_SPI_SCK_fCLK_3 | (~mode & 0x03) << 3;    
#else
    SPI->SPIC = _0006_SPI_SCK_fCLK_6 | (~mode & 0x03) << 3;    
#endif
    SPI->SPIM = _0040_SPI_RECEPTION_TRANSMISSION | _0000_SPI_MSB | _0000_SPI_TRANSFER_END | _0000_SPI_LENGTH_8;
    NSS_PORT_SETTING();
    SCK_PORT_SETTING();
    MOSI_PORT_SETTING();
    MISO_PORT_SETTING();
}

/***********************************************************************************************************************
* Function Name: SPI_Start
* @brief  This function starts the SPI module operation.
* @param  None
* @return None
***********************************************************************************************************************/
void SPI_Start(void)
{
    /* clear INTSPI interrupt flag */
    INTC_ClearPendingIRQ(SPI_IRQn);
    NVIC_ClearPendingIRQ(SPI_IRQn);
    /* enable INTSPI interrupt */
    INTC_EnableIRQ(SPI_IRQn);
    NVIC_EnableIRQ(SPI_IRQn);
    SPI->SPIM |= _0080_SPI_START_TRG_ON; 
    /* SSn Active */
    NSS_PORT_CLR();
}
/***********************************************************************************************************************
* Function Name: SPI_Stop
* @brief  This function stops the SPI module operation.
* @param  None
* @return None
***********************************************************************************************************************/
void SPI_Stop(void)
{
    /* SSn Inactive */
    NSS_PORT_SET();
    SPI->SPIM &= ~_0080_SPI_START_TRG_ON; 
    /* disable INTSPI interrupt */
    INTC_DisableIRQ(SPI_IRQn);
    NVIC_DisableIRQ(SPI_IRQn);
    /* clear INTSPI interrupt flag */
    INTC_ClearPendingIRQ(SPI_IRQn);
    NVIC_ClearPendingIRQ(SPI_IRQn);
}
/***********************************************************************************************************************
* Function Name: SPI_MasterSend
* @brief  This function sends SPI data.
* @param  tx_buf - transfer buffer pointer
* @param  tx_num - buffer size
* @return status - MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS SPI_MasterSend(uint8_t *const tx_buf, uint16_t tx_num)
{
    MD_STATUS status = MD_OK;

    if (tx_num < 1U)
    {
        status = MD_ERROR;
    }
    else
    {
        SPI->SPIM |= _0040_SPI_RECEPTION_TRANSMISSION | _0008_SPI_BUFFER_EMPTY; /* transmission mode */
#ifdef SPI_WITH_DMA
        /* write transfer data with DMA */
        DMAVEC->VEC[DMA_VECTOR_SPI] = CTRL_DATA_SPI;
        DMAVEC->CTRL[CTRL_DATA_SPI].DMACR = (0 << CTRL_DMACR_SZ_Pos) | (0 << CTRL_DMACR_CHNE_Pos) |
                                              (0 << CTRL_DMACR_DAMOD_Pos) | (1 << CTRL_DMACR_SAMOD_Pos) |
                                              (0 << CTRL_DMACR_MODE_Pos);
        DMAVEC->CTRL[CTRL_DATA_SPI].DMBLS = 1;
        DMAVEC->CTRL[CTRL_DATA_SPI].DMACT = tx_num - 1;
        DMAVEC->CTRL[CTRL_DATA_SPI].DMRLD = tx_num - 1;
        DMAVEC->CTRL[CTRL_DATA_SPI].DMSAR = (uint32_t)(tx_buf + 1);
        DMAVEC->CTRL[CTRL_DATA_SPI].DMDAR = (uint32_t)&SPI->SDRO;

        /* init DMA registers */
        CGC->PER1 |= CGC_PER1_DMAEN_Msk;
        DMA->DMABAR = DMAVEC_BASE;
        DMA->DMAEN1 |= (1 << DMA_VECTOR_SPI % 8);
#endif
#ifdef SPI_WITH_DMA
        g_spi_tx_count = 1;         /* send data count */
        gp_spi_tx_address = tx_buf; /* send buffer pointer */
#else
        g_spi_tx_count = tx_num;    /* send data count */
        gp_spi_tx_address = tx_buf; /* send buffer pointer */
#endif
        SPI_Start();
        SPI->SDRO = *gp_spi_tx_address; /* started by writing data to SDRO */
        gp_spi_tx_address++;
        g_spi_tx_count--;
    }

    return (status);
}

/***********************************************************************************************************************
* Function Name: SPI_MasterReceive
* @brief  This function receives SPI data.
* @param  rx_buf - receive buffer pointer
* @param  rx_num - buffer size
* @return status - MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS SPI_MasterReceive(uint8_t *const rx_buf, uint16_t rx_num)
{
    MD_STATUS status = MD_OK;
    uint32_t dummy_sdr;

    if (rx_num < 1U)
    {
        status = MD_ERROR;
    }
    else
    {
        SPI->SPIM &= ~(_0040_SPI_RECEPTION_TRANSMISSION | _0008_SPI_BUFFER_EMPTY); /* reception mode */
#ifdef SPI_WITH_DMA
        /* read receive data with DMA */
        DMAVEC->VEC[DMA_VECTOR_SPI] = CTRL_DATA_SPI;
        DMAVEC->CTRL[CTRL_DATA_SPI].DMACR = (0 << CTRL_DMACR_SZ_Pos) | (0 << CTRL_DMACR_CHNE_Pos) |
                                            (1 << CTRL_DMACR_DAMOD_Pos) | (0 << CTRL_DMACR_SAMOD_Pos) |
                                            (0 << CTRL_DMACR_MODE_Pos);
        DMAVEC->CTRL[CTRL_DATA_SPI].DMBLS = 1;
        DMAVEC->CTRL[CTRL_DATA_SPI].DMACT = rx_num;
        DMAVEC->CTRL[CTRL_DATA_SPI].DMRLD = rx_num;
        DMAVEC->CTRL[CTRL_DATA_SPI].DMSAR = (uint32_t)&SPI->SDRI;
        DMAVEC->CTRL[CTRL_DATA_SPI].DMDAR = (uint32_t)rx_buf;

        /* init DMA registers */
        CGC->PER1 |= CGC_PER1_DMAEN_Msk;
        DMA->DMABAR = DMAVEC_BASE;
        DMA->DMAEN1 |= (1 << DMA_VECTOR_SPI % 8);
#endif
#ifdef SPI_WITH_DMA
        g_spi_rx_count = 0;                      /* receive data count */
        gp_spi_rx_address = rx_buf + rx_num ;    /* receive buffer pointer */
#else
        g_spi_rx_count = rx_num;    /* receive data count */
        gp_spi_rx_address = rx_buf; /* receive buffer pointer */
#endif

        SPI_Start();
        dummy_sdr = SPI->SDRI;
    }

    return (status);
}
/***********************************************************************************************************************
* Function Name: SPI_SlaveInit
* @brief  This function restarts the SPI module.
* @param  mode
*             - SPI_MODE_0: CPOL = 0, CPHA = 0; i.e. CKP = 1, DAP = 1
*             - SPI_MODE_1: CPOL = 0, CPHA = 1; i.e. CKP = 1, DAP = 0
*             - SPI_MODE_2: CPOL = 1, CPHA = 0; i.e. CKP = 0, DAP = 1
*             - SPI_MODE_3: CPOL = 1, CPHA = 1; i.e. CKP = 0, DAP = 0
* @return None
***********************************************************************************************************************/
void SPI_SlaveInit(spi_mode_t mode)
{
    CGC->PER1 |= 0x80;
    SPI->SPIC = _0007_SPI_SLAVE_MODE | (~mode & 0x03) << 3;    
    SPI->SPIM = _0040_SPI_RECEPTION_TRANSMISSION | _0000_SPI_MSB | _0000_SPI_TRANSFER_END | _0000_SPI_LENGTH_8;
    NSS_PORT_SETTING();
    SCK_PORT_SETTING();
    MOSI_PORT_SETTING();
    MISO_PORT_SETTING();
}
/***********************************************************************************************************************
* Function Name: SPI_SlaveSend
* @brief  This function sends SPI data.
* @param  tx_buf - transfer buffer pointer
* @param  tx_num - buffer size
* @return status - MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS SPI_SlaveSend(uint8_t *const tx_buf, uint16_t tx_num)
{
    MD_STATUS status = MD_OK;

    if (tx_num < 1U)
    {
        status = MD_ERROR;
    }
    else
    {
        SPI->SPIM |= _0040_SPI_RECEPTION_TRANSMISSION | _0008_SPI_BUFFER_EMPTY; /* transmission mode */
#ifdef SPI_WITH_DMA
        /* write transfer data with DMA */
        DMAVEC->VEC[DMA_VECTOR_SPI] = CTRL_DATA_SPI;
        DMAVEC->CTRL[CTRL_DATA_SPI].DMACR = (0 << CTRL_DMACR_SZ_Pos) | (0 << CTRL_DMACR_CHNE_Pos) |
                                              (0 << CTRL_DMACR_DAMOD_Pos) | (1 << CTRL_DMACR_SAMOD_Pos) |
                                              (0 << CTRL_DMACR_MODE_Pos);
        DMAVEC->CTRL[CTRL_DATA_SPI].DMBLS = 1;
        DMAVEC->CTRL[CTRL_DATA_SPI].DMACT = tx_num - 1;
        DMAVEC->CTRL[CTRL_DATA_SPI].DMRLD = tx_num - 1;
        DMAVEC->CTRL[CTRL_DATA_SPI].DMSAR = (uint32_t)(tx_buf + 1);
        DMAVEC->CTRL[CTRL_DATA_SPI].DMDAR = (uint32_t)&SPI->SDRO;

        /* init DMA registers */
        CGC->PER1 |= CGC_PER1_DMAEN_Msk;
        DMA->DMABAR = DMAVEC_BASE;
        DMA->DMAEN1 |= (1 << DMA_VECTOR_SPI % 8);
#endif
#ifdef SPI_WITH_DMA
        g_spi_tx_count = 1;         /* send data count */
        gp_spi_tx_address = tx_buf; /* send buffer pointer */
#else
        g_spi_tx_count = tx_num;    /* send data count */
        gp_spi_tx_address = tx_buf; /* send buffer pointer */
#endif
        SPI_Start();
        SPI->SDRO = *gp_spi_tx_address; /* started by writing data to SDRO */
        gp_spi_tx_address++;
        g_spi_tx_count--;
    }

    return (status);
}

/***********************************************************************************************************************
* Function Name: SPI_SlaveReceive
* @brief  This function receives SPI data.
* @param  rx_buf - receive buffer pointer
* @param  rx_num - buffer size
* @return status - MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS SPI_SlaveReceive(uint8_t *const rx_buf, uint16_t rx_num)
{
    MD_STATUS status = MD_OK;
    uint32_t dummy_sdr;

    if (rx_num < 1U)
    {
        status = MD_ERROR;
    }
    else
    {
        SPI->SPIM &= ~(_0040_SPI_RECEPTION_TRANSMISSION | _0008_SPI_BUFFER_EMPTY); /* reception mode */
#ifdef SPI_WITH_DMA
        /* read receive data with DMA */
        DMAVEC->VEC[DMA_VECTOR_SPI] = CTRL_DATA_SPI;
        DMAVEC->CTRL[CTRL_DATA_SPI].DMACR = (0 << CTRL_DMACR_SZ_Pos) | (0 << CTRL_DMACR_CHNE_Pos) |
                                            (1 << CTRL_DMACR_DAMOD_Pos) | (0 << CTRL_DMACR_SAMOD_Pos) |
                                            (0 << CTRL_DMACR_MODE_Pos);
        DMAVEC->CTRL[CTRL_DATA_SPI].DMBLS = 1;
        DMAVEC->CTRL[CTRL_DATA_SPI].DMACT = rx_num;
        DMAVEC->CTRL[CTRL_DATA_SPI].DMRLD = rx_num;
        DMAVEC->CTRL[CTRL_DATA_SPI].DMSAR = (uint32_t)&SPI->SDRI;
        DMAVEC->CTRL[CTRL_DATA_SPI].DMDAR = (uint32_t)rx_buf;

        /* init DMA registers */
        CGC->PER1 |= CGC_PER1_DMAEN_Msk;
        DMA->DMABAR = DMAVEC_BASE;
        DMA->DMAEN1 |= (1 << DMA_VECTOR_SPI % 8);
#endif
#ifdef SPI_WITH_DMA
        g_spi_rx_count = 0;                      /* receive data count */
        gp_spi_rx_address = rx_buf + rx_num; /* receive buffer pointer */
#else
        g_spi_rx_count = rx_num;    /* receive data count */
        gp_spi_rx_address = rx_buf; /* receive buffer pointer */
#endif

        SPI_Start();
        dummy_sdr = SPI->SDRI;
    }

    return (status);
}
/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
