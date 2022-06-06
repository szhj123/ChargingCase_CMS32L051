/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    iica.c
* @brief   This file implements device driver for IICA module.
* @version 1.0.0  
* @date    2019/12/24
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "userdefine.h"
#include "CMS32L051.h"
#include "iica.h"
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
volatile uint8_t   g_iica0_master_status_flag; /* iica0 master flag */
volatile uint8_t   g_iica0_slave_status_flag;  /* iica0 slave flag */
volatile uint8_t * gp_iica0_rx_address;        /* iica0 receive buffer address */
volatile uint16_t  g_iica0_rx_len;             /* iica0 receive data length */
volatile uint16_t  g_iica0_rx_cnt;             /* iica0 receive data count */
volatile uint8_t * gp_iica0_tx_address;        /* iica0 send buffer address */
volatile uint16_t  g_iica0_tx_cnt;             /* iica0 send data count */
volatile uint8_t   g_iica0_tx_end;             /* iica0 send data end */
volatile uint8_t   g_iica0_rx_end;             /* iica0 receive data end */
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: IICA0_Init
* @brief  This function initializes the IICA0 module.
* @param  None
* @return None
***********************************************************************************************************************/
void IICA0_Init(void)
{
    CGC->PER0 |= CGC_PER0_IICA0EN_Msk;              /* enables input clock supply */
    IICA->IICCTL00 = _00_IICA_OPERATION_STOP;       /* stop operation */
    INTC_DisableIRQ(IICA_IRQn);                         /* disable INTIICA interrupt flag */           
    INTC_ClearPendingIRQ(IICA_IRQn);                    /* clear INTIICA interrupt flag */         

#ifdef IICA_STANDARD_MODE /* Max rate: 100Kbps */
    IICA->IICCTL01  = _00_IICA_OPERATE_STANDARD;  /* operates in standard mode */
    IICA->IICWL0    = _4B_IICA_LOW_WIDTH;
    IICA->IICWH0    = _53_IICA_HIGH_WIDTH;
#endif
#ifdef IICA_FAST_MODE /* Max rate: 400Kbps */
    IICA->IICCTL01  = _08_IICA_OPERATE_FAST;  /* operates in fast mode */
    IICA->IICCTL01 |= _04_IICA_FILTER_ON;     /* filter on */
    IICA->IICWL0    = _14_IICA_LOW_WIDTH;
    IICA->IICWH0    = _12_IICA_HIGH_WIDTH;
#endif
    IICA->IICCTL01 |= _01_IICA_FCLK_2_SELECTED;
    IICA->SVA0      = _98_IICA0_SLAVEADDRESS;
    IICA->IICF0    |= _02_IICA_WITHOUT_DETECTION; /* enable generation of a start condition without detecting a stop
condition */
    IICA->IICF0    |= _01_IICA_RESERVATION_DISABLE;       /* disable communication reservation */
    IICA->IICCTL00 |= _08_IICA_INTERRUPT_REQUEST_NINTH; /* interrupt request is generated at the ninth clock's falling edge */
    IICA->IICCTL00 |= _04_IICA_ACKOWNLEDGMENT_ENABLE;   /* enable acknowledgment */
    IICA->IICCTL00 |= _80_IICA_OPERATION_ENABLE;                /* enable operation */
    IICA->IICCTL00 |= _40_IICA_OPERATION_STANDBY;       /* this exits from the current communications and sets standby mode */
    INTC_EnableIRQ(IICA_IRQn);                          /* enable INTIICA interrupt flag */     
		
    /* Set SCLA0, SDAA0 pin */
    SCLA0_PORT_SETTING();
    SDAA0_PORT_SETTING();
}
/***********************************************************************************************************************
* Function Name: IICA0_Stop
* @brief  This function stops IICA0 module operation.
* @param  None
* @return None
***********************************************************************************************************************/
void IICA0_Stop(void)
{
    IICA->IICCTL00 &= ~IICA_IICCTL00_IICE_Msk;     /* stop operation */
}
/***********************************************************************************************************************
* Function Name: IICA0_StopCondition
* @brief  This function sets IICA0 stop condition flag.
* @param  None
* @return None
***********************************************************************************************************************/
void IICA0_StopCondition(void)
{
    IICA->IICCTL00 |= IICA_IICCTL00_SPT_Msk;      /* stop condition is generated */
}
/***********************************************************************************************************************
* Function Name: IICA0_MasterSend
* @brief  This function starts to send data as master mode.
* @param  adr - send address
* @param  tx_buf - transfer buffer pointer
* @param  tx_num - buffer size
* @param  wait
*             - wait for start condition
* @return status
*             - MD_OK or MD_ERROR1 or MD_ERROR2
***********************************************************************************************************************/
MD_STATUS IICA0_MasterSend(uint8_t adr, uint8_t * const tx_buf, uint16_t tx_num, uint8_t wait)
{
    MD_STATUS status = MD_OK;

    INTC_DisableIRQ(IICA_IRQn);   /* disable INTIICA0 interrupt */

    if (IICA->IICF0 & IICA_IICF0_IICBSY_Msk)
    {
        /* Check bus busy */
        INTC_EnableIRQ(IICA_IRQn);   /* enable INTIICA0 interrupt */
        status = MD_ERROR1;
    }
    else
    {
        IICA->IICCTL00 |= IICA_IICCTL00_STT_Msk;      /* generate a start condition */
        INTC_EnableIRQ(IICA_IRQn);   /* enable INTIICA0 interrupt */
        
        /* Wait */
        while (wait--)
        {
            ;
        }
        
        if (0U == (IICA->IICS0 & IICA_IICS0_STD_Msk))
        {
            status = MD_ERROR2;
        }
        
        /* Set parameter */
        g_iica0_tx_cnt = tx_num;
        gp_iica0_tx_address = tx_buf;
        g_iica0_tx_end = 0;	
        g_iica0_master_status_flag = _00_IICA_MASTER_FLAG_CLEAR;
        adr &= (uint8_t)~0x01U; /* set send mode */
        IICA->IICA0 = adr; /* send address */
    }

    return (status);
}
/***********************************************************************************************************************
* Function Name: IICA0_MasterReceive
* @brief  This function starts to receive IICA0 data as master mode.
* @param  adr - receive address
* @param  rx_buf - receive buffer pointer
* @param  rx_num - buffer size
* @param  wait
*             - wait for start condition
* @return status
*             - MD_OK or MD_ERROR1 or MD_ERROR2
***********************************************************************************************************************/
MD_STATUS IICA0_MasterReceive(uint8_t adr, uint8_t * const rx_buf, uint16_t rx_num, uint8_t wait)
{
    MD_STATUS status = MD_OK;

    INTC_DisableIRQ(IICA_IRQn);   /* disable INTIICA0 interrupt */

    if (IICA->IICF0 & IICA_IICF0_IICBSY_Msk)
    {
        /* Check bus busy */
        INTC_EnableIRQ(IICA_IRQn);   /* enable INTIICA0 interrupt */
        status = MD_ERROR1;
    }
    else
    {
        IICA->IICCTL00 |= IICA_IICCTL00_STT_Msk;      /* generate a start condition */
        INTC_EnableIRQ(IICA_IRQn);   /* enable INTIICA0 interrupt */
        
        /* Wait */
        while (wait--)
        {
            ;
        }
        
        if (0U == (IICA->IICS0 & IICA_IICS0_STD_Msk))
        {
            status = MD_ERROR2;
        }
        
        /* Set parameter */
        g_iica0_rx_len = rx_num;
        g_iica0_rx_cnt = 0U;
        gp_iica0_rx_address = rx_buf;
        g_iica0_rx_end = 0;	
        g_iica0_master_status_flag  = _00_IICA_MASTER_FLAG_CLEAR;
        adr |= 0x01U; /* set receive mode */
        IICA->IICA0 = adr; /* receive address */
    }

    return (status);
}

/***********************************************************************************************************************
* Function Name: IICA0_SlaveSend
* @brief  This function sends data as slave mode.
* @param  adr - send address
* @param  tx_buf - transfer buffer pointer
* @param  tx_num - buffer size
* @return None
***********************************************************************************************************************/
void IICA0_SlaveSend(uint8_t adr, uint8_t * const tx_buf, uint16_t tx_num)
{
    g_iica0_tx_cnt = tx_num;
    gp_iica0_tx_address = tx_buf;
    g_iica0_tx_end = 0;	
    g_iica0_slave_status_flag = 0U;
    IICA->SVA0 = adr; /* slave address */
}
/***********************************************************************************************************************
* Function Name: IICA0_SlaveReceive
* @brief  This function receives data as slave mode.
* @param  adr - send address
* @param  tx_buf - receive buffer pointer
* @param  rx_num - buffer size
* @return None
***********************************************************************************************************************/
void IICA0_SlaveReceive(uint8_t adr, uint8_t * const rx_buf, uint16_t rx_num)
{
    g_iica0_rx_len = rx_num;
    g_iica0_rx_cnt = 0U;
    gp_iica0_rx_address = rx_buf;
    g_iica0_rx_end = 0;	
    g_iica0_slave_status_flag  = 0U;
    IICA->SVA0 = adr; /* slave address */
}
/***********************************************************************************************************************
* Function Name: IICA0_Set_Wakeup
* @brief  This function sets the WUPn bit of IICCTL01 register.
* @param  None
* @return None
***********************************************************************************************************************/
void IICA0_Set_Wakeup(void)
{
    IICA->IICCTL01 |= 0x80; /* WUP = 1 */
  	__NOP();
  	__NOP();
  	__NOP();	
	
    __STOP();
}

/***********************************************************************************************************************
* Function Name: IICA0_Clear_Wakeup
* @brief  This function clears the WUPn bit of IICCTL01 register.
* @param  None
* @return None
***********************************************************************************************************************/
void IICA0_Clear_Wakeup(void)
{
    IICA->IICCTL01 &= ~0x80; /* WUP = 0 */
  	__NOP();
  	__NOP();
  	__NOP();	
  	__NOP();
  	__NOP();	
}
/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
