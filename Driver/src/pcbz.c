/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    pcbz.c
* @brief   This file implements device driver for PCLBUZ module.
* @version 1.0.0
* @date    2019/12/24
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "CMS32L051.h"
#include "userdefine.h"
#include "pcbz.h"
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
* Function Name: PCBZ_Init
* @brief  This function initializes the pclbuz.
* @param  ch - specify the channel of pcbz
* @param  cks - specify the clock divider of pcbz
* @return None
***********************************************************************************************************************/
void PCBZ_Init(pcbz_channel_t ch, pcbz_clock_t cks)
{
    if(ch == PCBZ_CHANNEL_0)
    {
   	    CLKBUZ0_PORT_SETTING(); 
        PCBZ->CKS0  = 0x80U | cks;    	
    }
    if(ch == PCBZ_CHANNEL_1)
    {
   	    CLKBUZ1_PORT_SETTING(); 
        PCBZ->CKS1  = 0x80U | cks;    	
    }
}

/***********************************************************************************************************************
* Function Name: PCBZ_Start
* @brief  This function start the pclbuz.
* @param  ch - specify the channel of pcbz
* @return None
***********************************************************************************************************************/
void PCBZ_Start(pcbz_channel_t ch)
{
    if(ch == PCBZ_CHANNEL_0)
    {
        PCBZ->CKS0  |= 0x80U;    	
    }
    if(ch == PCBZ_CHANNEL_1)
    {
        PCBZ->CKS1  |= 0x80U;    	
    }
}

/***********************************************************************************************************************
* Function Name: PCBZ_Stop
* @brief  This function stop the pclbuz.
* @param  ch - specify the channel of pcbz
* @return None
***********************************************************************************************************************/
void PCBZ_Stop(pcbz_channel_t ch)
{
    if(ch == PCBZ_CHANNEL_0)
    {
        PCBZ->CKS0  &= ~0x80U;    	
    }
    if(ch == PCBZ_CHANNEL_1)
    {
        PCBZ->CKS1  &= ~0x80U;    	
    }
}
/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
