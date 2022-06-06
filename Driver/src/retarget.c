/*
 *-----------------------------------------------------------------------------
 * The confidential and proprietary information contained in this file may
 * only be used by a person authorised under and to the extent permitted
 * by a subsisting licensing agreement from ARM Limited.
 *
 *            (C) COPYRIGHT 2011-2012 ARM Limited.
 *                ALL RIGHTS RESERVED
 *
 * This entire notice must be reproduced on all copies of this file
 * and copies of this file may only be made by a person if such person is
 * permitted to do so under the terms of a subsisting license agreement
 * from ARM Limited.
 *
 *      SVN Information
 *
 *      Checked In          : $Date: 2012-01-11 17:13:57 +0000 (Wed, 11 Jan 2012) $
 *
 *      Revision            : $Revision: 197600 $
 *
 *      Release Information : Cortex-M0+ AT590-r0p1-00rel0
 *-----------------------------------------------------------------------------
 */

//
// printf retargetting functions
//

#include <stdio.h>
#include <rt_misc.h>
#include <stdint.h>
#include "CMS32L051.h"
#include "userdefine.h"
#include "sci.h"

#if defined ( __CC_ARM   )
#if (__ARMCC_VERSION < 400000)
#else
// Insist on keeping widthprec, to avoid X propagation by benign code in C-lib
#pragma import _printf_widthprec
#endif
#endif

//
// C library retargetting
//

#if defined ( __CC_ARM )
struct __FILE { int handle; /* Add whatever you need here */ };
#endif
FILE __stdout;
FILE __stdin;


void _ttywrch(int ch)
{
  UART0_Send(ch);
  return;
}

int fputc(int ch, FILE *f)
{
  UART0_Send(ch);
  if(ch == '\n')
  {
    UART0_Send('\r');
  }
  return ch;
}

int fgetc( FILE *f)
{
  uint8_t ch;
  ch = UART0_Receive();
#if 1
  if(ch == 0x0D) // 回车键
  {
    UART0_Send('\r'); // echo
    UART0_Send('\n'); // echo
  }
  else {
    UART0_Send(ch); // echo
  }
#endif
  return ch;
}

int ferror(FILE *f) {
  return EOF;
}

void _sys_exit(int return_code) {
	if(return_code) 
	{
		*((volatile uint32_t*)0x40028020) = 0x00000BAD;  /* simulation NG */
	}
	else
	{
		*((volatile uint32_t*)0x40028020) = 0x00000001;  /* simulation OK */
	}
  while (1);    /* endless loop */
}
