/********************************************************
* @file       hal_key.c
* @author     szhj13
* @version    V1.0
* @date       2022-06-06
* @brief      the start address of program
**********************************************************
* @Modify

**********************************************************/

/* Includes ---------------------------------------------*/
#include "hal_key.h"

/* Private typedef --------------------------------------*/
/* Private define ---------------------------------------*/
/* Private macro ----------------------------------------*/
/* Private function -------------------------------------*/
static void App_Com_Msg_Set(uint8_t cmd, uint8_t *buf, uint16_t length );
static void App_Com_Rx_Handler(void *arg );

/* Private variables ------------------------------------*/

