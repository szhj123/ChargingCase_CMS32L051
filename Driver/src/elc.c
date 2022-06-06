/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    elc.c
* @brief   This file implements device driver for ELC module.
* @version 1.0.0  
* @date    2019/12/24
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "CMS32L051.h"
#include "elc.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "userdefine.h"

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
* Function Name: ELC_Start
* @brief  This function initializes the ELC module.
* @param  event_src - event resources number to be start (bit n for ELSELRn)
* @param  event_dst - event destination number to be start (value of ELSELRn)
* @return None
***********************************************************************************************************************/
void ELC_Start(uint32_t event_src, uint32_t event_dst)
{
    volatile uint8_t  * sfr_addr;
    
    sfr_addr = &ELC->ELSELR00;
    
    // ELSELRn(n=00~14) = Link Destination Number
    *(sfr_addr + event_src) = event_dst;
}

/***********************************************************************************************************************
* Function Name: ELC_Stop
* @brief  This function stops the ELC event resources.
* @param  event - event resources to be stoped (bit n for ELSELRn)
* @return None
***********************************************************************************************************************/
void ELC_Stop(uint32_t event)
{
    volatile uint32_t   w_count;
    volatile uint8_t  * sfr_addr;

    sfr_addr = &ELC->ELSELR00;
    
    for (w_count = 0U; w_count < ELC_DESTINATION_COUNT; w_count++) 
    {
        if (0x1U == ((event >> w_count) & 0x1U))
        {
            *sfr_addr = _00_ELC_EVENT_LINK_OFF;
        }
        
        sfr_addr++;
    }
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
