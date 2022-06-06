/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    dma.h
* @brief   This file implements device driver for DTC module.
* @version 1.0.0  
* @date    2019/12/24
***********************************************************************************************************************/
#ifndef DMA_H
#define DMA_H

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/
/*
    Bit Position of DMACR
*/
#define SZ_Pos       6
#define RPTINT_Pos   5
#define CHNE_Pos     4
#define DAMOD_Pos    3
#define SAMOD_Pos    2
#define RPTSEL_Pos   1
#define MODE_Pos     0

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
typedef enum {
   DMA_VECTOR_FLASH     =  0U,  /* Flash擦除/写入结束 */
   DMA_VECTOR_INTP0 	=  1U,  /* 外部中断INTP0 */
   DMA_VECTOR_INTP1 	=  2U,  /* 外部中断INTP1 */
   DMA_VECTOR_INTP2 	=  3U,  /* 外部中断INTP2 */
   DMA_VECTOR_INTP3 	=  4U,  /* 外部中断INTP3 */
   DMA_VECTOR_ADC   	=  5U,  /* A/D 转换结束 */
   //DMA_VECTOR_CMP0      =  6U,  /* 比较器0 */
   //DMA_VECTOR_CMP1      =  7U,  /* 比较器1 */
   DMA_VECTOR_SR0       =  8U,  /* UART0接收传送结束/SPI01传送结束或者缓冲器空/IIC01传送结束 */
   DMA_VECTOR_SPI01     =  8U,  /* UART0接收传送结束/SPI01传送结束或者缓冲器空/IIC01传送结束 */
   DMA_VECTOR_IIC01     =  8U,  /* UART0接收传送结束/SPI01传送结束或者缓冲器空/IIC01传送结束 */
   DMA_VECTOR_ST0       =  9U,  /* UART0发送传送结束/SPI00传送结束或者缓冲器空/IIC00传送结束 */
   DMA_VECTOR_SPI00     =  9U,  /* UART0发送传送结束/SPI00传送结束或者缓冲器空/IIC00传送结束 */
   DMA_VECTOR_IIC00     =  9U,  /* UART0发送传送结束/SPI00传送结束或者缓冲器空/IIC00传送结束 */
   DMA_VECTOR_SR1       = 10U,  /* UART1接收传送结束/SPI11传送结束或者缓冲器空/IIC11传送结束 */
   DMA_VECTOR_SPI11     = 10U,  /* UART1接收传送结束/SPI11传送结束或者缓冲器空/IIC11传送结束 */
   DMA_VECTOR_IIC11     = 10U,  /* UART1接收传送结束/SPI11传送结束或者缓冲器空/IIC11传送结束 */
   DMA_VECTOR_ST1       = 11U,  /* UART1发送传送结束/SPI10传送结束或者缓冲器空/IIC10传送结束 */
   DMA_VECTOR_SPI10     = 11U,  /* UART1发送传送结束/SPI10传送结束或者缓冲器空/IIC10传送结束 */
   DMA_VECTOR_IIC10     = 11U,  /* UART1发送传送结束/SPI10传送结束或者缓冲器空/IIC10传送结束 */
   DMA_VECTOR_SPI       = 11U,  /* SPI传送结束或者缓冲器空 */
   DMA_VECTOR_SR2       = 12U,  /* UART2接收传送结束/SPI21传送结束或者缓冲器空/IIC21传送结束 */
   DMA_VECTOR_SPI21     = 12U,  /* UART2接收传送结束/SPI21传送结束或者缓冲器空/IIC21传送结束 */
   DMA_VECTOR_IIC21     = 12U,  /* UART2接收传送结束/SPI21传送结束或者缓冲器空/IIC21传送结束 */
   DMA_VECTOR_ST2       = 13U,  /* UART2发送传送结束/SPI20传送结束或者缓冲器空/IIC20传送结束 */
   DMA_VECTOR_SPI20     = 13U,  /* UART2发送传送结束/SPI20传送结束或者缓冲器空/IIC20传送结束 */
   DMA_VECTOR_IIC20     = 13U,  /* UART2发送传送结束/SPI20传送结束或者缓冲器空/IIC20传送结束 */
   DMA_VECTOR_IICA      = 14U,  /* IICA通信结束 */
   DMA_VECTOR_IT        = 15U,  /* 间隔定时器中断 */
   DMA_VECTOR_TM40_CH0  = 16U,  /* 定时器阵列单元0的通道0的计数结束或者捕获结束 */
   DMA_VECTOR_TM40_CH1  = 17U,  /* 定时器阵列单元0的通道1的计数结束或者捕获结束 */ 
   DMA_VECTOR_TM40_CH2  = 18U,  /* 定时器阵列单元0的通道2的计数结束或者捕获结束 */
   DMA_VECTOR_TM40_CH3  = 19U,  /* 定时器阵列单元0的通道3的计数结束或者捕获结束 */
   DMA_VECTOR_TM41_CH0  = 20U,  /* 定时器阵列单元1的通道0的计数结束或者捕获结束 */
   DMA_VECTOR_TM41_CH1  = 21U,  /* 定时器阵列单元1的通道1的计数结束或者捕获结束 */ 
   DMA_VECTOR_TM41_CH2  = 22U,  /* 定时器阵列单元1的通道2的计数结束或者捕获结束 */
   DMA_VECTOR_TM41_CH3  = 23U   /* 定时器阵列单元1的通道3的计数结束或者捕获结束 */

} dma_vector_t;

typedef enum {
	DMA_SIZE_BYTE, 				/*  8bits transfer */ 
	DMA_SIZE_HALF,  			/* 16bits transfer */
	DMA_SIZE_WORD   			/* 32bits transfer */
} dma_size_t;

typedef enum {
	DMA_MODE_NORMAL, 			/* Normal mode */ 
	DMA_MODE_REPEAT   			/* Repeat mode */
} dma_mode_t;

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
#if 1
void DMA_Start(dma_vector_t vect_num, uint8_t ctrl_data_num, dma_mode_t mode, dma_size_t size, uint16_t count, void *src_adr, void *dst_adr);
#else
void DMA_Start(dma_vector_t vect_num, uint8_t ctrl_data_num, DMAVEC_CTRL_Type ctrl_data);
#endif
void DMA_Enable(dma_vector_t vect_num);
void DMA_Stop(dma_vector_t vect_num);
void DMA_Trigger(dma_vector_t vect_num);
/* Start user code for function. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#endif
