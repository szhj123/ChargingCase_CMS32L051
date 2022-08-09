#ifndef _HAL_CMS32L051_H
#define _HAL_CMS32L051_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CMS32L051.h"
#include "userdefine.h"
#include "clk.h"
#include "gpio.h"
#include "tim4.h"
#include "sci.h"
#include "adc.h"
#include "intp.h"
#include "adc.h"
#include "dma.h"

#define INTER_REF_VOL                1450u//mv


typedef void (*Hal_Isr_Callback_t)(void );

void Cms32l051_Systick_Init(void );
void Cms32l051_Gpio_Init(void );
void Cms32l051_Intp_Init(void );
void Cms32l051_Tim40_Channel0_Interval_Init(void );
void Cms32l051_Uart0_Init(void );
void Cms32l051_Spi20_Init(void );
void Cms32l051_Adc_Init(void );

#endif 

