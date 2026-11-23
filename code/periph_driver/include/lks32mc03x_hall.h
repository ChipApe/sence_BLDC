/*******************************************************************************
 * 版权所有 (C)2021, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： lks32mc03x_hall.h
 * 文件标识：
 * 内容摘要： HALL驱动头文件
 * 其它说明： 无
 * 当前版本： V 1.0
 * 作    者：   HMG
 * 完成日期： 2021年10月14日
 *
 *******************************************************************************/
#ifndef __LKS32MC03x_HALL_H
#define __LKS32MC03x_HALL_H

/* Includes ------------------------------------------------------------------*/
#include "lks32mc03x_lib.h"

typedef struct
{
    __IO u32 CFG;
    __IO u32 INFO;
    __IO u32 WIDTH;
    __IO u32 TH;
    __IO u32 CNT;

} HALL_TypeDef;

#ifndef HALL
#define HALL ((HALL_TypeDef *)HALL_BASE)
#endif

typedef struct
{
    u16 FilterLen;       /*滤波长度,0对应长度1,1023对应长度1024滤波长度*/
    u8 ClockDivision;    /*分频 0~3:/1 /2 /4 /8*/
    u8 Filter75_Ena;     /*使能第一级7/5滤波,高电平有效*/
    u8 HALL_Ena;         /*使能HALL,高电平有效*/
    u8 HALL_CHGDMA_Ena;  /*HALL信号变化DMA请求使能,高电平有效*/
    u8 HALL_OVDMA_Ena;   /*HALL计数器溢出DMA请求使能,高电平有效*/
    u8 Capture_IRQ_Ena;  /*HALL信号变化中断使能,高电平有效*/
    u32 CountTH;         /*HALL计数器门限值*/
    u8 softIE;           /*软件中断使能 */
    u8 OverFlow_IRQ_Ena; /*HALL计数器溢出中断使能,高电平有效*/
    u16 null;                 // 地址对齐
} HALL_InitTypeDef;

#define HALL_CLK_DIV1 ((u32)0x00) /*HALL时钟为主时钟1分频*/
#define HALL_CLK_DIV2 ((u32)0x01) /*HALL时钟为主时钟2分频*/
#define HALL_CLK_DIV4 ((u32)0x02) /*HALL时钟为主时钟4分频*/
#define HALL_CLK_DIV8 ((u32)0x03) /*HALL时钟为主时钟8分频*/
/*HALL中断使能和标志定义*/
#define HALL_CAPTURE_EVENT ((u32)0x00010000)  /*HALL信号变化中断*/
#define HALL_OVERFLOW_EVENT ((u32)0x00020000) /*HALL信号溢出中断*/

void HALL_Init(HALL_InitTypeDef *HALL_InitStruct);
void HALL_StructInit(HALL_InitTypeDef *HALL_InitStruct);

u32 HALL_GetFilterValue(void);
u32 HALL_GetCaptureValue(void);
u32 HALL_WIDCount(void);
u32 HALL_GetCount(void);

u32 HALL_GetIRQFlag(u32 tempFlag);
void HALL_ClearIRQFlag(u32 tempFlag);

#endif /*__lks32mc03x_HALL_H */

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
