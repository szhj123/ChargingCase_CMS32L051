/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    flash_user.c
* @brief   This file implements device driver for FMC module.
* @version 1.0.0  
* @date    2019/12/24
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "CMS32L051.h"
#include "flash.h"
#include "userdefine.h"
#include "math.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
void IRQ31_Handler(void) __attribute__((alias("flash_interrupt")));

/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

#if defined (__CC_ARM)
#pragma arm section code = "ram_fetch_code"   // Arm Compiler 5
#elif defined (__ARMCC_VERSION) && (__ARMCC_VERSION > 6010050)
#pragma clang section text = "ram_fetch_code" // Arm Compiler 6
#endif
/***********************************************************************************************************************
* Function Name: flash_interrupt
* @brief  Flash Sequencer interrupt service routine
* @param  None
* @return None
***********************************************************************************************************************/
void flash_interrupt(void)
{
    INTC_ClearPendingIRQ(FMC_IRQn);     /* clear FMC interrupt flag */
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: flash_write
* @brief  Write data to Flash area. Automatically determines if erasure is needed.
*         If the destination area is blank, omits Erase and Pragram directly.
*         Otherwise, save data of flash to ram, erase flash, and then write flash.
* @param  adr - Page Start Address 
* @param  sz - Page Size 
* @param  buf - Page Data 
* @return status - MD_OK or MD_ERROR
* @note   sz must be less then or equal to SECTOR_SIZE, if not, return MD_ERROR and don't change flash contents.
***********************************************************************************************************************/
#define SECTOR_SIZE 512
#define WORD_SIZE 4
MD_STATUS flash_write(uint32_t adr, uint32_t sz, uint8_t *buf)
{
    MD_STATUS status = MD_OK;
    uint8_t dat, tmp[SECTOR_SIZE];
    uint8_t  blank = 1;
    uint8_t  cross;
    uint8_t *ptr;
    uint8_t *ptr_base;      /* sector base address */
    uint16_t offset;
    uint16_t i;
    uint32_t sector_num;

    if(sz > SECTOR_SIZE) {
       status = MD_ERROR; 
       return(status);
    }

    ptr = (uint8_t *)adr;

    /* Determine if the target area is blank */
    for(i=0; i<sz; i++) {
        dat = *ptr++;
        if(dat != 0xFFU)
        {
            blank = 0;  /* Not blank */
        }
    }

    /* if it is blank, omits erase and program directlly. */
    if(blank) {
        /* write data to flash data */
        ProgramPage(adr, sz, buf);
    /* if it isn't blank, erase and then program */
    } else {
        sector_num = (adr & ~(SECTOR_SIZE-1)) >> 9;
        if((adr+sz) > ((sector_num+1) << 9)) {
            cross = 1;  /* write area cross sectors */
        } else {
            cross = 0;
        }
        ptr_base = (uint8_t *)(adr & ~(SECTOR_SIZE-1));    /* get sector base address: Each sector is 512 bytes (i.e. 128 words) */
        offset   = adr & (SECTOR_SIZE-1);                  /* get offset */
        
        /* Save the Flash data temporarily */
        if(cross) {
            /* read two sectors */
            for(i = 0; i < SECTOR_SIZE * 2; i++)
            {
                tmp[i] = *ptr_base++;
            }
        } else {
            /* read one sector */
            for(i = 0; i < SECTOR_SIZE; i++)
            {
                tmp[i] = *ptr_base++;
            }
        }

        /* replace flash data with write data */
        for(i = 0; i < sz; i++) {
            tmp[offset+i] = *buf++;
        }

        /* write data to flash data */
        if(cross) {
            EraseSector((sector_num + 0 ) << 9);
            EraseSector((sector_num + 1 ) << 9);
            ProgramPage(sector_num << 9, SECTOR_SIZE * 2, tmp);
        } else {
            EraseSector((sector_num + 0 ) << 9);
            ProgramPage(sector_num << 9, SECTOR_SIZE * 1, tmp);
        }
    }
    
    return (status);
}

#if defined (__CC_ARM)
#pragma arm section code        // Arm Compiler 5
#elif defined (__ARMCC_VERSION) && (__ARMCC_VERSION > 6010050)
#pragma clang section text = "" // Arm Compiler 6
#endif
/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
