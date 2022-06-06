/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    key.c
* @brief   This file implements device driver for KEY module.
* @version 1.0.0
* @date    2019/12/24
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "userdefine.h"
#include "CMS32L051.h"
#include "key.h"
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
* Function Name: KEY_Init
* @brief  This function initializes the key return module.
* @param  pinMsk - select the active key input pins
* @return None
***********************************************************************************************************************/
void KEY_Init(uint8_t pinMsk)
{
    volatile uint8_t w_count;
    /* Set KRn pin */
    PORT->PMC7 &= ~pinMsk;
    PORT->PU7 |= pinMsk;
    PORT->PM7 |= pinMsk;
    INTC_DisableIRQ(KEY_IRQn);      /* disable INTKR interrupt */
    INTC_ClearPendingIRQ(KEY_IRQn); /* clear INTKR interrupt flag */
    KEY->KRM = pinMsk;
    /* Change the waiting time according to the system  */
    for (w_count = 0U; w_count <= KEY_WAITTIME; w_count++)
    {   
        __NOP();
    }
}
/***********************************************************************************************************************
* Function Name: KEY_Start
* @brief  This function clears INTKR interrupt flag and enables interrupt.
* @param  None
* @return None
***********************************************************************************************************************/
void KEY_Start(void)
{
    INTC_ClearPendingIRQ(KEY_IRQn); /* clear INTKR interrupt flag */
    INTC_EnableIRQ(KEY_IRQn);/* enable INTKR interrupt */
}
/***********************************************************************************************************************
* Function Name: KEY_Stop
* @brief  This function disables INTKR interrupt and clears interrupt flag.
* @param  None
* @return None
***********************************************************************************************************************/
void KEY_Stop(void)
{
    INTC_DisableIRQ(KEY_IRQn);      /* disable INTKR interrupt */
    INTC_ClearPendingIRQ(KEY_IRQn); /* clear INTKR interrupt flag */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
