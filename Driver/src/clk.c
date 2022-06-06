/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    clk.c
* @brief   This file implements device driver for CGC module.
* @version 1.0.0  
* @date    2019/12/24
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "CMS32L051.h"
#include "clk.h"

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: CLK_Osc_Setting
* @brief  This function initializes the Main OSC and Sub OSC.
* @param  main
*             - OSC_PORT:        X1, X2 as PORT
*             - OSC_OSCILLATOR:  X1, X2 as oscillator and connect crystal/ceramic resonator
*             - OSC_EXCLK:       X1, as PORT, X2 as external clock input
* @param  sub 
*             - OSC_PORT:        XT1, XT2 as PORT
*             - OSC_OSCILLATOR:  XT1, XT2 as oscillator and connect crystal resonator
*             - OSC_EXCLK:       XT1 as PORT, XT2 as external clock input
* @return None
***********************************************************************************************************************/
void CLK_Osc_Setting(osc_pin_mode_t main, osc_pin_mode_t sub)
{
    volatile uint32_t w_count;
    uint8_t           temp_stab_set;
    uint8_t           temp_stab_wait;
    uint8_t           tmp;

    tmp = 0x00;
    if(main == OSC_PORT )
    {
        tmp |= (0 << CGC_CMC_EXCLK_Pos) | (0 << CGC_CMC_OSCSEL_Pos);
    }

    if(sub == OSC_PORT )
    {
        tmp |= (0 << CGC_CMC_EXCLKS_Pos) | (0 << CGC_CMC_OSCSELS_Pos);
    }

    if(main == OSC_OSCILLATOR)
    {
        tmp |= (0 << CGC_CMC_EXCLK_Pos) | (1 << CGC_CMC_OSCSEL_Pos) | (1 << CGC_CMC_AMPH_Pos);
    }

    if(sub == OSC_OSCILLATOR)
    {
        tmp |= (0 << CGC_CMC_EXCLKS_Pos) | (1 << CGC_CMC_OSCSELS_Pos) | (1 << CGC_CMC_AMPHS_Pos);
    }

    if(main == OSC_EXCLK)
    {
        tmp |= (1 << CGC_CMC_EXCLK_Pos) | (1 << CGC_CMC_OSCSEL_Pos);
    }

    if(sub == OSC_EXCLK)
    {
        tmp |= (1 << CGC_CMC_EXCLKS_Pos) | (1 << CGC_CMC_OSCSELS_Pos);
    }

    CGC->CMC = tmp;

    /* Set fMX */
    CGC->CSC &= ~(1<<7) ;   //MSTOP = 0

    if(main == OSC_OSCILLATOR)
    {
        temp_stab_set = _FF_CGC_OSCSTAB_STA18;
        
        do
        {
            temp_stab_wait = CGC->OSTC;
            temp_stab_wait &= temp_stab_set;
        }
        while (temp_stab_wait != temp_stab_set);
    }

    /* Set fSUB */
    CGC->CSC &= ~(1<<6) ;   //XTSTOP = 0

    if(sub == OSC_OSCILLATOR)
    {
        /* Change the waiting time according to the system */
        for (w_count = 0U; w_count <= CGC_SUBWAITTIME; w_count++)
        {
            __NOP();
        }
    }
}

/***********************************************************************************************************************
* Function Name: CLK_MainOsc_Setting
* @brief  This function initializes the Main OSC.
* @param  main
*             - OSC_OSCILLATOR:  X1, X2 as oscillator and connect crystal/ceramic resonator
*             - OSC_EXCLK:       X1, as PORT, X2 as external clock input
* @param  amph 
*             - OSC_UNDER_10M:   X1 frequency: 1MHz < fx < 10MHz
*             - OSC_OVER_10M:    X1 frequency: 10MHz < fx < 20MHz
* @return None
***********************************************************************************************************************/
void CLK_MainOsc_Setting(osc_pin_mode_t main, osc_speed_mode_t amph)
{
    volatile uint32_t w_count;
    uint8_t           temp_stab_set;
    uint8_t           temp_stab_wait;
    uint8_t           tmp;

    tmp = 0x00;
    if(main == OSC_PORT )
    {
        tmp |= (0 << CGC_CMC_EXCLK_Pos) | (0 << CGC_CMC_OSCSEL_Pos);
    }

    if(main == OSC_OSCILLATOR)
    {
        tmp |= (0 << CGC_CMC_EXCLK_Pos) | (1 << CGC_CMC_OSCSEL_Pos) | (amph << CGC_CMC_AMPH_Pos);
    }

    if(main == OSC_EXCLK)
    {
        tmp |= (1 << CGC_CMC_EXCLK_Pos) | (1 << CGC_CMC_OSCSEL_Pos);
    }

    CGC->CMC = tmp;

    /* Set fMX */
    CGC->CSC &= ~(1<<7) ;   //MSTOP = 0

    if(main == OSC_OSCILLATOR)
    {
        temp_stab_set = _FF_CGC_OSCSTAB_STA18;
        
        do
        {
            temp_stab_wait = CGC->OSTC;
            temp_stab_wait &= temp_stab_set;
        }
        while (temp_stab_wait != temp_stab_set);
    }
}

/***********************************************************************************************************************
* Function Name: CLK_SubOsc_Setting
* @brief  This function initializes the Sub OSC.
* @param  sub 
*             - OSC_PORT:        XT1, XT2 as PORT
*             - OSC_OSCILLATOR:  XT1, XT2 as oscillator and connect crystal resonator
*             - OSC_EXCLK:       XT1 as PORT, XT2 as external clock input
* @param  amphs
*             - OSC_LOW_POWER:       low power consumption oscillation
*             - OSC_NORMAL_POWER:    normal oscillation
*             - OSC_ULTRA_LOW_POWER: ultra-low power consumption oscillation
* @return None
***********************************************************************************************************************/
void CLK_SubOsc_Setting(osc_pin_mode_t sub, osc_power_mode_t amphs)
{
    volatile uint32_t w_count;
    uint8_t           tmp;

    tmp = 0x00;
    if(sub == OSC_PORT )
    {
        tmp |= (0 << CGC_CMC_EXCLKS_Pos) | (0 << CGC_CMC_OSCSELS_Pos);
    }

    if(sub == OSC_OSCILLATOR)
    {
        tmp |= (0 << CGC_CMC_EXCLKS_Pos) | (1 << CGC_CMC_OSCSELS_Pos) | (amphs << CGC_CMC_AMPHS_Pos);
    }

    if(sub == OSC_EXCLK)
    {
        tmp |= (1 << CGC_CMC_EXCLKS_Pos) | (1 << CGC_CMC_OSCSELS_Pos);
    }

    CGC->CMC = tmp;

    /* Set fSUB */
    CGC->CSC &= ~(1<<6) ;   //XTSTOP = 0

    if(sub == OSC_OSCILLATOR)
    {
        /* Change the waiting time according to the system */
        for (w_count = 0U; w_count <= CGC_SUBWAITTIME; w_count++)
        {
            __NOP();
        }
    }
}
/***********************************************************************************************************************
* Function Name: CLK_Fclk_Select
* @brief  This function selects the system clock(fCLK). 
* @param  cks
*             - MAINCLK_FIH:     fIH as system clock(fCLK)
*             - MAINCLK_FMX:     fMX as system clock(fCLK)
*             - MAINCLK_FSUB:    fSUB as system clock(fCLK)
*             - MAINCLK_FIL:     fIL as system clock(fCLK)
* @return CKC register value
***********************************************************************************************************************/
uint8_t CLK_Fclk_Select(clock_select_t cks)
{
    volatile uint32_t w_count;
    uint8_t           tmp;

    if(cks == MAINCLK_FIH) 
    {
        CGC->CKC = (0 << CGC_CKC_CSS_Pos) | (0 << CGC_CKC_MCM0_Pos );
        //CGC->CSC|= CGC_CSC_MSTOP_Msk;
    }

    if(cks == MAINCLK_FMX) 
    {
        CGC->CKC = (0 << CGC_CKC_CSS_Pos) | (1 << CGC_CKC_MCM0_Pos );
        //CGC->CSC|= CGC_CSC_HIOSTOP_Msk;

    }

    if(cks == MAINCLK_FSUB) 
    {
        CGC->SUBCKSEL = 0x00;
        CGC->CKC = (1 << CGC_CKC_CSS_Pos) | (0 << CGC_CKC_MCM0_Pos );
    }
    
    if(cks == MAINCLK_FIL) 
    {
        CGC->SUBCKSEL = CGC_SUBCKSEL_SELLOSC_Msk;
        CGC->CKC = (1 << CGC_CKC_CSS_Pos) | (0 << CGC_CKC_MCM0_Pos );
    }
    
    tmp = CGC->CKC;
    
    return tmp;
}

/***********************************************************************************************************************
* Function Name: CLK_MainOsc_Stop
* @brief  This function stops the main system clock oscilator (MOSC). 
* @param  None
* @return None
************************************************************************************************************************/
void CLK_MainOsc_Stop(void)
{
	CGC->CSC |= 1<<7; 	/* MSTOP = 1 */
}

/***********************************************************************************************************************
* Function Name: CLK_MainOsc_Start
* @brief  This function starts the main system clock oscilator (MOSC). 
* @param  None
* @return None
***********************************************************************************************************************/
void CLK_MainOsc_Start(void)
{
	CGC->CSC &= ~(1<<7); 	/* MSTOP = 0 */
}
/***********************************************************************************************************************
* Function Name: CLK_SubOsc_Stop
* @brief  This function stops the sub system clock oscilator (SOSC). 
* @param  None
* @return None
***********************************************************************************************************************/
void CLK_SubOsc_Stop(void)
{
	CGC->CSC |= 1<<6; 	/* XTSTOP = 1 */
}
/***********************************************************************************************************************
* Function Name: CLK_SubOsc_Start
* @brief  This function starts the sub system clock oscilator (SOSC). 
* @param  None
* @return None
***********************************************************************************************************************/
void CLK_SubOsc_Start(void)
{
	CGC->CSC &= ~(1<<6); 	/* XTSTOP = 0 */
}
/***********************************************************************************************************************
* Function Name: CLK_Hoco_Stop
* @brief  This function stops the high speed on chip oscilator (HOCO).
* @param  None
* @return None
***********************************************************************************************************************/
void CLK_Hoco_Stop(void)
{
	CGC->CSC |= 1<<0; 	/* HIOSTOP = 1 */
}
/***********************************************************************************************************************
* Function Name: CLK_Hoco_Start
* @brief  This function starts the high speed on chip oscilator (HOCO). 
* @param  None
* @return None
***********************************************************************************************************************/
void CLK_Hoco_Start(void)
{
	CGC->CSC &= ~(1<<0); 	/* HIOSTOP = 0 */
}
