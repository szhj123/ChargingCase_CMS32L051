/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    dma.c
* @brief   This file implements device driver for DMA module.
* @version 1.0.0  
* @date    2019/5/23
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "CMS32L051.h"
#include "dma.h"
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

#if 1
/***********************************************************************************************************************
* Function Name: DMA_Start
* @brief  This function initializes the DMA module.
* @param  vect_num - the entry number of dma vector
* @param  ctrl_data_num - specify the control data set number 
* @param  mode - specify operation mode: DMA_MODE_NORMAL or DMA_MODE_REPEAT
* @param  size - specify transfer data size : DMA_SIZE_BYTE, DMA_SIZE_HALF or DMA_SIZE_WORD
* @param  count - specify the number of transfer
* @param  src_adr - specify source address ( pointer type ) 
* @param  dst_adr - specify destination address ( pointer type ) 
* @return None
***********************************************************************************************************************/
void DMA_Start(dma_vector_t vect_num, uint8_t ctrl_data_num, dma_mode_t mode, 
               dma_size_t size, uint16_t count, void *src_adr, void *dst_adr)
{
    volatile uint8_t  * sfr_addr;
    uint8_t rptsel, damod, samod;

    if(((uint32_t)src_adr & 0xF0000000) == 0x40000000)
    {
        samod = 0;  /* source address is mapped to peripherial area*/
    }
    else
    {
        samod = 1;  /* source address is not mapped to peripherial area*/
    }

    if(((uint32_t)dst_adr & 0xF0000000) == 0x40000000)
    {
        damod = 0;  /* destination address is mapped to peripherial area*/
    }
    else
    {
        damod = 1;  /* destination address is not mapped to peripherial area*/
    }

    if(!samod & damod)
    {
        rptsel = 0; /* destination is the repeat area */
    }
    else if(samod & !damod)
    {
        rptsel = 1; /* source is the repeat area */
    }
    else
    {
        rptsel = 0; /* ToDo: change the value according to your needs for repeate mode */
    }

    DMAVEC->VEC[vect_num] = ctrl_data_num;
    DMAVEC->CTRL[ctrl_data_num].DMACR = (size << CTRL_DMACR_SZ_Pos)      | (1 << CTRL_DMACR_RPTINT_Pos)    |
                                        (damod << CTRL_DMACR_DAMOD_Pos)  | (samod << CTRL_DMACR_SAMOD_Pos) |
                                        (rptsel << CTRL_DMACR_RPTSEL_Pos)| (mode << CTRL_DMACR_MODE_Pos);
    DMAVEC->CTRL[ctrl_data_num].DMBLS = 1;
    DMAVEC->CTRL[ctrl_data_num].DMACT = count;
    DMAVEC->CTRL[ctrl_data_num].DMRLD = count;
    DMAVEC->CTRL[ctrl_data_num].DMSAR = (uint32_t)src_adr;
    DMAVEC->CTRL[ctrl_data_num].DMDAR = (uint32_t)dst_adr;

    /* init DMA registers */
    CGC->PER1   |= CGC_PER1_DMAEN_Msk;
    DMA->DMABAR  = DMAVEC_BASE;
    sfr_addr = &DMA->DMAEN0;
    *(sfr_addr + vect_num / 8) |= 1 << (vect_num % 8);      /* DMAENn = 1 */
}

#else
/***********************************************************************************************************************
* Function Name: DMA_Start
* @brief  This function initializes the DMA module.
* @param  vect_num - the entry number of dma vector
* @param  ctrl_data_num - specify the control data set number 
* @param  ctrl_data - control data set
* @return : None
***********************************************************************************************************************/
void DMA_Start(dma_vector_t vect_num, uint8_t ctrl_data_num, DMAVEC_CTRL_Type ctrl_data)
{
    volatile uint8_t  * sfr_addr;

    DMAVEC->VEC[vect_num] = ctrl_data_num;
    DMAVEC->CTRL[ctrl_data_num].DMACR = ctrl_data.DMACR;
    DMAVEC->CTRL[ctrl_data_num].DMBLS = ctrl_data.DMBLS;;
    DMAVEC->CTRL[ctrl_data_num].DMACT = ctrl_data.DMACT;
    DMAVEC->CTRL[ctrl_data_num].DMRLD = ctrl_data.DMRLD;
    DMAVEC->CTRL[ctrl_data_num].DMSAR = ctrl_data.DMSAR;;
    DMAVEC->CTRL[ctrl_data_num].DMDAR = ctrl_data.DMDAR;;

    /* init DMA registers */
    CGC->PER1   |= CGC_PER1_DMAEN_Msk;
    DMA->DMABAR  = DMAVEC_BASE;
    sfr_addr = &DMA->DMAEN0;
    *(sfr_addr + vect_num / 8) |= 1 << (vect_num % 8);      /* DMAENn = 1 */
}
#endif
/***********************************************************************************************************************
* Function Name: DMA_Enable
* @brief  This function enable the DMA Operation.
* @param  vect_num - the entry number of dma vector
* @return None
***********************************************************************************************************************/
void DMA_Enable(dma_vector_t vect_num)
{
    volatile uint8_t  * sfr_addr;

    sfr_addr = &DMA->DMAEN0;
    *(sfr_addr + vect_num / 8) |= (1 << (vect_num % 8));    /* DMAENn = 1 */
    
}
/***********************************************************************************************************************
* Function Name: DMA_Stop
* @brief  This function stops the DMA Operation.
* @param  vect_num - the entry number of dma vector
* @return None
***********************************************************************************************************************/
void DMA_Stop(dma_vector_t vect_num)
{
    volatile uint8_t  * sfr_addr;

    sfr_addr = &DMA->DMAEN0;
    *(sfr_addr + vect_num / 8) &= ~(1 << (vect_num % 8));    /* DMAENn = 0 */
    
}
/***********************************************************************************************************************
* Function Name: DMA_Trigger
* @brief  This function trigger the DMA Operation.
* @param  vect_num - the entry number of dma vector
* @return None
***********************************************************************************************************************/
void DMA_Trigger(dma_vector_t vect_num)
{
    volatile uint8_t  * sfr_addr;
    DMA->IFPRCR = 0xF1;
    sfr_addr = &DMA->DMAIF0;
    *(sfr_addr + vect_num / 8) = (1 << (vect_num % 8));    /* DMAIFn = 1 */
    DMA->IFPRCR = 0x00;
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
