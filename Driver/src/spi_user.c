/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    spi_user.c
* @brief   This file implements device driver for SPI module.
* @version 1.0.0
* @date    2019/12/24
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "CMS32L051.h"
#include "spi.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
void IRQ13_Handler(void) __attribute__((alias("spi_interrupt")));
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
extern volatile uint8_t * gp_spi_rx_address;         /* spi receive buffer address */
extern volatile uint16_t  g_spi_rx_length;           /* spi receive data length */
extern volatile uint16_t  g_spi_rx_count;            /* spi receive data count */
extern volatile uint8_t * gp_spi_tx_address;         /* spi send buffer address */
extern volatile uint16_t  g_spi_tx_length;           /* spi send data length */
extern volatile uint16_t  g_spi_tx_count;            /* spi send data count */
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: spi_interrupt
* @brief  SPI interrupt service routine
* @param  None
* @return None
***********************************************************************************************************************/
void spi_interrupt(void)
{
    volatile uint8_t sio_dummy;

    if (g_spi_tx_count > 0U || g_spi_rx_count > 1U)
    {
        /* reveive data */
        if (0U != gp_spi_rx_address)
        {
            *gp_spi_rx_address = SPI->SDRI;
            gp_spi_rx_address++;
            g_spi_rx_count--;
        }
        else
        {
            sio_dummy = SPI->SDRI;
        }

        /* send data */
        if (0U != gp_spi_tx_address)
        {
            SPI->SDRO = *gp_spi_tx_address;
            gp_spi_tx_address++;
            g_spi_tx_count--;
        }
        else
        {
            SPI->SDRO = 0xFFU;
        }

    }
    else 
    {
        /* CPU receive the last data */
        if (1U == g_spi_rx_count)
        {
            SPI->SPIM &= ~_0080_SPI_START_TRG_ON;
            if (0U != gp_spi_rx_address)
            {
                *gp_spi_rx_address = SPI->SDRI;
                 g_spi_rx_count--;
            }
            else
            {
                sio_dummy = SPI->SDRI;
            }
        }
        if (0U != gp_spi_rx_address)
        {
            spi_callback_receiveend();    /* complete receive */
        }
        /* wait the last data sent for DMA transfer */
        if (0U != gp_spi_tx_address)
        {
            while(SPI->SPIM & _0001_SPI_UNDER_EXECUTE) 
            {
                ;
            }
            spi_callback_sendend();    /* complete send */
        }
    }
    INTC_ClearPendingIRQ(SPI_IRQn);
}
/***********************************************************************************************************************
* Function Name: spi_callback_receiveend
* @brief  This function is a callback function when spi finishes reception.
* @param  None
* @return None
***********************************************************************************************************************/
static void spi_callback_receiveend(void)
{
    /* Start user code. Do not edit comment generated here */
		SPI_Stop();
    gp_spi_rx_address = 0;    /* reinitialize global variable */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: spi_callback_sendend
* @brief  This function is a callback function when spi finishes transmission.
* @param  None
* @return None
***********************************************************************************************************************/
static void spi_callback_sendend(void)
{
    /* Start user code. Do not edit comment generated here */
		SPI_Stop();
    gp_spi_tx_address = 0;    /* reinitialize global variable */
    /* End user code. Do not edit comment generated here */
}
/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
