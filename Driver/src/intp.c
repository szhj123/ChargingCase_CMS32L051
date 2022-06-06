/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    intp.c
* @brief   This file implements device driver for INTP module.
* @version 1.0.0
* @date    2019/12/24
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "userdefine.h"
#include "CMS32L051.h"
#include "intp.h"
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

/***********************************************************************************************************************
* Function Name: INTP_Init
* @brief  This function initializes the external interrupt module.
* @param  pinMsk - select the active external interrupt pins
* @param  edge - specify the active edge of external interrupt
* @return None
***********************************************************************************************************************/
void INTP_Init(uint16_t pinMsk, intp_edge_t edge)
{
    volatile uint8_t w_count;
    /* Set INTPn pin */
    if(pinMsk & (1 << 0))
    {
        INTP0_PORT_SETTING();
        /* disable INTP0 interrupt */
        INTC_DisableIRQ(INTP0_IRQn);        
        /* clear INTP0 interrupt flag */
        INTC_ClearPendingIRQ(INTP0_IRQn); 
        INTM->EGN0 &= ~(1 << 0);
        INTM->EGP0 &= ~(1 << 0);
        INTM->EGN0 |= ((edge & 0x01U) >> 0) << 0;
        INTM->EGP0 |= ((edge & 0x02U) >> 1) << 0;
    }
    if(pinMsk & (1 << 1))
    {
        INTP1_PORT_SETTING();
        /* disable INTP1 interrupt */
        INTC_DisableIRQ(INTP1_IRQn);        
        /* clear INTP1 interrupt flag */
        INTC_ClearPendingIRQ(INTP1_IRQn); 
        INTM->EGN0 &= ~(1 << 1);
        INTM->EGP0 &= ~(1 << 1);
        INTM->EGN0 |= ((edge & 0x01U) >> 0) << 1;
        INTM->EGP0 |= ((edge & 0x02U) >> 1) << 1;
    }
    if(pinMsk & (1 << 2))
    {
        INTP2_PORT_SETTING();
        /* disable INTP2 interrupt */
        INTC_DisableIRQ(INTP2_IRQn);        
        /* clear INTP2 interrupt flag */
        INTC_ClearPendingIRQ(INTP2_IRQn); 
        INTM->EGN0 &= ~(1 << 2);
        INTM->EGP0 &= ~(1 << 2);
        INTM->EGN0 |= ((edge & 0x01U) >> 0) << 2;
        INTM->EGP0 |= ((edge & 0x02U) >> 1) << 2;
    }
    if(pinMsk & (1 << 3))
    {
        INTP3_PORT_SETTING();
        /* disable INTP3 interrupt */
        INTC_DisableIRQ(INTP3_IRQn);        
        /* clear INTP3 interrupt flag */
        INTC_ClearPendingIRQ(INTP3_IRQn); 
        INTM->EGN0 &= ~(1 << 3);
        INTM->EGP0 &= ~(1 << 3);
        INTM->EGN0 |= ((edge & 0x01U) >> 0) << 3;
        INTM->EGP0 |= ((edge & 0x02U) >> 1) << 3;
    }
    
    /* Change the waiting time according to the system  */
    for (w_count = 0U; w_count <= INTP_WAITTIME; w_count++)
    {   
        __NOP();
    }
}
/***********************************************************************************************************************
* Function Name: INTP_Start
* @brief  This function clears INTP interrupt flag and enables interrupt.
* @param  pinMsk - select the active external interrupt pins
* @return None
***********************************************************************************************************************/
void INTP_Start(uint16_t pinMsk)
{
    if(pinMsk & (1 << 0))
    {
        INTC_ClearPendingIRQ(INTP0_IRQn); /* clear INTP interrupt flag */
        INTC_EnableIRQ(INTP0_IRQn);       /* enable INTP interrupt */
    }
    if(pinMsk & (1 << 1))
    {
        INTC_ClearPendingIRQ(INTP1_IRQn); /* clear INTP interrupt flag */
        INTC_EnableIRQ(INTP1_IRQn);       /* enable INTP interrupt */
    }
    if(pinMsk & (1 << 2))
    {
        INTC_ClearPendingIRQ(INTP2_IRQn); /* clear INTP interrupt flag */
        INTC_EnableIRQ(INTP2_IRQn);       /* enable INTP interrupt */
    }
    if(pinMsk & (1 << 3))
    {
        INTC_ClearPendingIRQ(INTP3_IRQn); /* clear INTP interrupt flag */
        INTC_EnableIRQ(INTP3_IRQn);       /* enable INTP interrupt */
    }
}
/***********************************************************************************************************************
* Function Name: INTP_Stop
* @brief  This function disables INTP interrupt and clears interrupt flag.
* @param  pinMsk - select the active external interrupt pins
* @return None
***********************************************************************************************************************/
void INTP_Stop(uint16_t pinMsk)
{
    if(pinMsk & (1 << 0))
    {
        INTC_DisableIRQ(INTP0_IRQn);       /* disable INTP interrupt */
        INTC_ClearPendingIRQ(INTP0_IRQn);  /* clear INTP interrupt flag */
    }
    if(pinMsk & (1 << 1))
    {
        INTC_DisableIRQ(INTP1_IRQn);       /* disable INTP interrupt */
        INTC_ClearPendingIRQ(INTP1_IRQn);  /* clear INTP interrupt flag */
    }
    if(pinMsk & (1 << 2))
    {
        INTC_DisableIRQ(INTP2_IRQn);       /* disable INTP interrupt */
        INTC_ClearPendingIRQ(INTP2_IRQn);  /* clear INTP interrupt flag */
    }
    if(pinMsk & (1 << 3))
    {
        INTC_DisableIRQ(INTP3_IRQn);       /* disable INTP interrupt */
        INTC_ClearPendingIRQ(INTP3_IRQn);  /* clear INTP interrupt flag */
    }
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
