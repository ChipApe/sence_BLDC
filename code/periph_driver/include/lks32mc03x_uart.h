/*******************************************************************************
 * 版权所有 (C)2021, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： lks32mc03x_uart.h
 * 文件标识：
 * 内容摘要： UART驱动头文件
 * 其它说明： 无
 * 当前版本： V 1.0
 * 作    者：   HMG
 * 完成日期： 2021年10月14日
 *
 *******************************************************************************/

#ifndef __LKS32MC03x_UART_H
#define __LKS32MC03x_UART_H

/* Includes ------------------------------------------------------------------*/
#include "lks32mc03x_lib.h"

typedef enum
{
    UART_Parity_NO = 0x00,
    UART_Parity_EVEN = 0x01,
    UART_Parity_ODD = 0x02
} UART_ParityMode;

typedef struct
{
    __IO u32 CTRL;
    __IO u32 DIVH;
    __IO u32 DIVL;
    __IO u32 BUFF;
    __IO u32 ADR;
    __IO u32 STT;
    __IO u32 RE;
    __IO u32 IE;
    __IO u32 IF;
    __IO u32 INV;
} UART_TypeDef;

#ifndef UART0
#define UART0 ((UART_TypeDef *)UART_BASE)
#endif

typedef struct
{
    u32 BaudRate;          /*波特率*/
    u8 WordLength;         /*数据长度*/
    u8 StopBits;           /*停止位长度*/
    u8 FirstSend;          /*First bit to be sent,0:LSB 1:MSB*/
    UART_ParityMode ParityMode; /*奇偶校验,None,EVEN,ODD*/

    u16 Match485Addr; /*用作485通信时的匹配地址*/
    u8 IRQEna;        /*中断使能寄存器，具体含义*/
    u8 DMARE;         /*DMA 请求使能，具体含义*/
    u8 RXD_INV;       /*接收电平取反 */
    u8 TXD_INV;       /*发送电平取反 */
    u8 MultiDropEna;  /*使能Multi-drop,0:Disable 1:Enable*/
    u8 null;               // 地址对齐
} UART_InitTypeDef;

/*UART计算波特率时使用系统的时钟*/
#ifndef MCU_MCLK
#define MCU_MCLK (48000000LL) /* 系统时钟 */
#endif

#define UART_WORDLENGTH_8b 0 /*8bit数据位*/
#define UART_WORDLENGTH_9b 1 /*9bit数据位*/

#define UART_STOPBITS_1b 0 /*无停止位*/
#define UART_STOPBITS_2b 1 /*1bit停止位*/

#define UART_FIRSTSEND_LSB 0 /*低端先发送*/
#define UART_FIRSTSEND_MSB 1 /*高端先发送*/

/*中断使能定义*/
#define UART_IRQEna_SendOver BIT0      /*使能发送完成中断*/
#define UART_IRQEna_RcvOver BIT1       /*使能接收完成中断*/
#define UART_IRQEna_SendBuffEmpty BIT2 /*使能发送缓冲区空中断*/
#define UART_IRQEna_StopError BIT3     /*使能停止位错误*/
#define UART_IRQEna_CheckError BIT4    /*使能校验错误*/

/*中断标志定义*/
#define UART_IF_SendOver BIT0     /*发送完成中断*/
#define UART_IF_RcvOver BIT1      /*接收完成中断*/
#define UART_IF_SendBufEmpty BIT2 /*发送缓冲区空中断*/
#define UART_IF_StopError BIT3    /*停止位错误*/
#define UART_IF_CheckError BIT4   /*校验错误 */

/*DMA请求模式定义*/
#define UART_TX_DONE_RE BIT0      /*发送缓冲区空DMA请求开关*/
#define UART_RX_DONE_RE BIT1      /*接收完成DMA请求开关*/
#define UART_TX_BUF_EMPTY_RE BIT2 /*发送完成DMA请求开关*/

void UART_Init(UART_TypeDef *UARTx, UART_InitTypeDef *UART_InitStruct);
void UART_StructInit(UART_InitTypeDef *UART_InitStruct);

void UART_SendData(UART_TypeDef *UARTx, u32 n);
u32 UART_ReadData(UART_TypeDef *UARTx);

void UART_SendnData(UART_TypeDef *UARTx, s8 *sendData, u32 len);
void UART_RecvnData(UART_TypeDef *UARTx, s8 *recvData, u32 maxlen);

u32 UART_GetIRQFlag(UART_TypeDef *UARTx, u32 tempFlag);
void UART_ClearIRQFlag(UART_TypeDef *UARTx, u32 tempFlag);

u8 UART_SendAddr_485(UART_TypeDef *UARTx, u8 n);
u8 UART_SendData_485(UART_TypeDef *UARTx, u8 n);

#endif /*__lks32mc03x_UART_H */

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
