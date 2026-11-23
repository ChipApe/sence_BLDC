/*******************************************************************************
 * 版权所有 (C)2015, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： lks32mc03x_DMA.h
 * 文件标识：
 * 内容摘要： DMA驱动头文件
 * 其它说明： 无
 * 当前版本： V 1.0
 * 作    者： Yangzj
 * 完成日期： 21/11/10
 *
 *******************************************************************************/

#ifndef __LKS32MC03x_DMA_H
#define __LKS32MC03x_DMA_H

#include "lks32mc03x_lib.h"

typedef struct
{
    u16 DMA_IRQ_EN; /* DMA 中断使能 */
    u8 DMA_RMODE;   /* 多轮传输使能 */
    u8 DMA_CIRC;    /* 循环模式使能 */
    u8 DMA_SINC;    /* 源地址递增使能 */
    u8 DMA_DINC;    /* 目的地址递增使能 */
    u8 DMA_SBTW;    /* 源地址访问位宽， 0:byte, 1:half-word, 2:word */
    u8 DMA_DBTW;    /* 目的地址访问位宽， 0:byte, 1:half-word, 2:word */
    u32 DMA_SADR;   /* DMA 通道 x 源地址 */
    u32 DMA_DADR;   /* DMA 通道 x 目的地址 */
    u16 DMA_REQ_EN; /* 通道 x 硬件 DMA 请求使能，高有效 */
    u16 null;       /* 地址对齐 */
} DMA_InitTypeDef;

typedef struct
{
    __IO u32 DMA_CCR;
    __IO u32 DMA_REN;
    __IO u32 DMA_CTMS;
    __IO u32 DMA_SADR;
    __IO u32 DMA_DADR;
} DMA_RegTypeDef;

#ifndef DMA_CH0
#define DMA_CH0 ((DMA_RegTypeDef *)DMA_BASE)
#endif
#ifndef DMA_CH1
#define DMA_CH1 ((DMA_RegTypeDef *)(DMA_BASE + 0x20))
#endif
#ifndef DMA_CH2
#define DMA_CH2 ((DMA_RegTypeDef *)(DMA_BASE + 0x40))
#endif
#ifndef DMA_CH3
#define DMA_CH3 ((DMA_RegTypeDef *)(DMA_BASE + 0x60))
#endif

#define DMA_TCIE BIT0 /* 传输完成中断使能，高有效 */

#define CH3_FIF BIT3 /* 通道 3 完成中断标志，高有效，写 1 清零 */
#define CH2_FIF BIT2 /* 通道 2 完成中断标志，高有效，写 1 清零 */
#define CH1_FIF BIT1 /* 通道 1 完成中断标志，高有效，写 1 清零 */
#define CH0_FIF BIT0 /* 通道 0 完成中断标志，高有效，写 1 清零 */

#define DMA_BYTE_TRANS 0     /* 访问位宽， 0:byte */
#define DMA_HALFWORD_TRANS 1 /* 访问位宽， 1:half-word */
#define DMA_WORD_TRANS 2     /* 访问位宽， 2:word */

#define DMA_SW_TRIG_REQ_EN BIT15 /* 软件触发 */
#define DMA_I2C_REQ_EN BIT14     /* I2C DMA请求使能 */
#define DMA_GPIO_REQ_EN BIT13    /* GPIO DMA请求使能 */
#define DMA_CMP_REQ_EN BIT12     /* CMP DMA请求使能 */
#define DMA_SPI_TX_REQ_EN BIT11  /* SPI TX DMA请求使能 */
#define DMA_SPI_RX_REQ_EN BIT10  /* SPI RX DMA请求使能 */
#define DMA_UART_TX_REQ_EN BIT7  /* UART TX DMA请求使能 */
#define DMA_UART_RX_REQ_EN BIT6  /* UART RX DMA请求使能 */
#define DMA_TIMER1_REQ_EN BIT5   /* TIMER1 DMA请求使能 */
#define DMA_TIMER0_REQ_EN BIT4   /* TIMER0 DMA请求使能 */
#define DMA_HALL_REQ_EN BIT2     /* HALL DMA请求使能 */
#define DMA_MCPWM_REQ_EN BIT1    /* MCPWM DMA请求使能 */
#define DMA_ADC_REQ_EN BIT0      /* ADC DMA请求使能 */

void DMA_Init(DMA_RegTypeDef *DMAx, DMA_InitTypeDef *DMAInitStruct);
void DMA_StructInit(DMA_InitTypeDef *DMAInitStruct);
u32 DMA_GetIRQFlag(u32 timer_if);
void DMA_ClearIRQFlag(u32 tempFlag);
void DMA_CHx_EN(DMA_RegTypeDef *DMAx, u32 Channel_EN, u32 set);

#endif
/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
