/*******************************************************************************
 * 版权所有 (C)2015, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： lks32mc03x_spi.h
 * 文件标识：
 * 内容摘要： SPI驱动头文件
 * 其它说明： 无
 * 当前版本： V 1.0
 * 作    者： Yangzj
 * 完成日期： 21/11/10
 *
 *******************************************************************************/

#ifndef __LKS32MC03x_SPI_H
#define __LKS32MC03x_SPI_H

/* Includes ------------------------------------------------------------------*/
#include "lks32mc03x_lib.h"

typedef enum
{
    SPI_Master = 0x01,
    SPI_Slave = 0x00
} SPI_Mode;

typedef enum
{
    SPI_Full = 0x0,    //全双工
    SPI_Half_Tx = 0x2, //半双工，仅发送
    SPI_Half_Rx = 0x3  //半双工，仅接受
} SPI_Duplex;

typedef struct
{
    __IO u32 CFG;     /* SPI控制寄存器 */
    __IO u32 IE;      /* SPI中断寄存器 */
    __IO u32 BAUD;    /* SPI波特率控制寄存器 */
    __IO u32 TX_DATA; /* SPI发送数据寄存器 */
    __IO u32 RX_DATA; /* SPI接收数据寄存器 */
    __IO u32 SIZE;    /* SPI传输数据长度寄存器 */
} SPI_TypeDef;

#ifndef SPI
#define SPI ((SPI_TypeDef *)SPI_BASE)
#endif

typedef struct
{
    SPI_Duplex Duplex; //半双工模式设置
    u8 CS;        // SPI 从设备下，片选信号来源。0:Slave 模式下，片选信号恒为有效值 1:Slave 模式下，片选信号来自 Master 设备
    SPI_Mode Mode;     // SPI 主从模式选择。
    u8 CPHA;      // SPI 相位选择。
    u8 CPOL;      // SPI 极性选择。
    u8 ENDIAN;    // SPI 模块传输顺序。
    u8 EN;        // SPI Enable Signal, 0: disable;1: enable

    u8 IRQEna;     // SPI 中断使能。
    u8 TRANS_TRIG; //传输触发选择。

    u8 TRANS_MODE; // SPI 数据搬移方式。0 DMA 方式。
    u8 BAUD;       // SPI 传输波特率配置, SPI 传输速度 = 系统时钟 / (2*(BAUD + 1)),最小为3

    u8 BITSIZE; //字节长度寄存器。8-16
} SPI_InitTypeDef;

#define SPI_FIRSTSEND_LSB 1 /* 低位先传 */
#define SPI_FIRSTSEND_MSB 0 /* 高位先传 */

#define SPI_DMA_ENABLE 0  /* 使能DMA搬运 */
#define SPI_DMA_DISABLE 1 /* 禁止DMA搬运 */

/*中断使能定义*/
#define SPI_IRQEna_Enable BIT7   // SPI Interrupt Enable
#define SPI_IRQEna_TranDone BIT6 // Transmit Done IRQ
#define SPI_IRQEna_SSErr BIT5    // SS Signal Error IRQ
#define SPI_IRQEna_DataOver BIT4 // Transmit Data Over Flow IRQ

/*中断标志定义*/
#define SPI_IF_TranDone BIT2 // Transmit Done IF
#define SPI_IF_SSErr BIT1    // SS Signal Error IF
#define SPI_IF_DataOver BIT0 // Transmit Data Over Flow IF

void SPI_Init(SPI_TypeDef *SPIx, SPI_InitTypeDef *SPI_InitStruct);
void SPI_StructInit(SPI_InitTypeDef *SPI_InitStruct);

u8 SPI_GetIRQFlag(SPI_TypeDef *SPIx, u8 IRQ_Flag);
void SPI_ClearIRQFlag(SPI_TypeDef *SPIx, u8 IRQ_Flag);

void SPI_SendData(SPI_TypeDef *SPIx, u8 n);
u8 SPI_ReadData(SPI_TypeDef *SPIx);
#endif /*__lks32mc03x_SPI_H */

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
