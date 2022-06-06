/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    flash.c
* @brief   This file implements flash sector erase and program.
* @version 1.0.0
* @date    2019/12/24
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "CMS32L051.h"
#include "flash.h"

#if defined (__CC_ARM)
#pragma arm section code = "ram_fetch_code"   // Arm Compiler 5
#elif defined (__ARMCC_VERSION) && (__ARMCC_VERSION > 6010050)
#pragma clang section text = "ram_fetch_code" // Arm Compiler 6
#endif
/***********************************************************************************************************************
* Function Name: EraseChip
* @brief  Chip Erase Flash
* @param  adr - Any address of user code flash 
* @return None
***********************************************************************************************************************/
int EraseChip (uint32_t adr)
{
    FMC->FLERMD = 0x08;
    FMC->FLPROT = 0xF1;
    FMC->FLOPMD1 = 0x55;
    FMC->FLOPMD2 = 0xAA;  
    // Write data to start address of sector to trigger Erase Operation
    *(uint32_t *) adr = 0xFFFFFFFF;
    
    // polling OVER Flag
    while((FMC->FLSTS & FMC_FLSTS_OVF_Msk) == 0);
    FMC->FLSTS |= FMC_FLSTS_OVF_Msk;
    FMC->FLERMD = 0x00;

    return(0);
}

/***********************************************************************************************************************
* Function Name: EraseSector
* @brief  Sector Erase Flash
* @param  adr - sector address of user code flash
* @return status: 0 - OK, 1 - Failed
***********************************************************************************************************************/
int EraseSector (uint32_t adr)
{
    FMC->FLERMD = 0x10;
    FMC->FLPROT = 0xF1;
    FMC->FLOPMD1 = 0x55;
    FMC->FLOPMD2 = 0xAA;  
    // Write data to start address of sector to trigger Erase Operation
    *(uint32_t *) adr = 0xFFFFFFFF;
    
    // polling Erase Over Flag
    while((FMC->FLSTS & FMC_FLSTS_OVF_Msk) == 0);
    FMC->FLSTS |= FMC_FLSTS_OVF_Msk;
    FMC->FLERMD = 0x00;
    FMC->FLPROT = 0x00;

    if(FMC->FLSTS & FMC_FLSTS_EVF_Msk)
    {
        return(1);  /* verify ng */
    }
    else
    {
        return(0);  /* verify ok */
    }
}

/***********************************************************************************************************************
* Function Name: ProgramPage
* @brief  Write data to Flash
* @param  adr - Page Start Address 
* @param  sz - Page Size 
* @param  buf - Page Data 
* @return None
***********************************************************************************************************************/
int ProgramPage (uint32_t adr, uint32_t sz, uint8_t *buf)
{
    uint32_t i;
    uint8_t *ptr;
    
    ptr = (uint8_t *) adr;
    
    FMC->FLPROT = 0xF1;
    
    for(i=0; i<sz; i++) 
    {
        FMC->FLOPMD1 = 0xAA;
        FMC->FLOPMD2 = 0x55;  
        *ptr++ = *buf++;    
        // polling OVER Flag
        while((FMC->FLSTS & FMC_FLSTS_OVF_Msk) == 0);
        FMC->FLSTS |= FMC_FLSTS_OVF_Msk;
    }

    FMC->FLPROT = 0x00;
    
    return (0);
}

#if defined (__CC_ARM)
#pragma arm section code        // Arm Compiler 5
#elif defined (__ARMCC_VERSION) && (__ARMCC_VERSION > 6010050)
#pragma clang section text = "" // Arm Compiler 6
#endif
