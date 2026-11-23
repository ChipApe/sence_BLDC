/*******************************************************************************
 * 版权所有 (C)2015, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： lks32mc03x_cmp.h
 * 文件标识：
 * 内容摘要： 比较器驱动头文件
 * 其它说明： 无
 * 当前版本： V 1.0
 * 作    者： YangZJ
 * 完成日期： 2021年11月09日
 *
 *******************************************************************************/
#ifndef __LKS32MC03x_CMP_H
#define __LKS32MC03x_CMP_H
/* Includes ------------------------------------------------------------------*/
#include "lks32mc03x_lib.h"

// 比较器回差选择
#define CMP_HYS_20mV 0
#define CMP_HYS_0mV 1

// 比较器信号正端选择
#define CMP_SELP_IP0 0
#define CMP_SELP_OPA0_IP 1
#define CMP_SELP_OPA0_OUT 2
#define CMP_SELP_IP1 3
#define CMP_SELP_IP2 4
#define CMP_SELP_IP3 5

// 比较器信号负端选择
#define CMP_SELN_IN 0
#define CMP_SELN_REF 1
#define CMP_SELN_DAC 2
#define CMP_SELN_HALL_MID 3

typedef struct
{
    __IO u32 IE;     // 比较器中断使能寄存器
    __IO u32 IF;     // 比较器中断标志寄存器
    __IO u32 TCLK;   // 比较器分频时钟控制寄存器
    __IO u32 CFG;    // 比较器控制寄存器
    __IO u32 BLCWIN; // 比较器开窗控制寄存器
    __IO u32 DATA;   // 比较器输出数值寄存器
} CMP_TypeDef;
#ifndef CMP
#define CMP ((CMP_TypeDef *)CMP_BASE)
#endif
#define CMP0 0
#define CMP1 1
typedef struct
{
    // 比较器IO配置
    u32 FIL_CLK10_DIV16; // 比较器 1/0 滤波
    u32 FIL_CLK10_DIV2;  // 比较器 1/0 滤波时钟分频
    u32 CMP_HYS;         // 比较器回差选择
    u32 CMP0_SELP;       // 比较器 0 信号正端选择
    u32 CMP0_SELN;       // 比较器 0 信号负端选择
    u32 CMP0_W_PWM_POL;  // 比较器 0 开窗 PWM 信号极性选择
    u32 CMP0_POL;        // 比较器 0 极性选择
    u32 CMP1_SELP;       // 比较器 1 信号正端选择
    u32 CMP1_SELN;       // 比较器 1 信号负端选择
    u32 CMP1_W_PWM_POL;  // 比较器 1 开窗 PWM 信号极性选择
    u32 CMP1_POL;        // 比较器 1 极性选择
    FuncState CLK10_EN;  // 比较器 1/0 滤波时钟使能
    FuncState CMP_FT;    // 比较器快速比较使能

    // 比较器0
    FuncState CMP0_EN;           // 比较器 0 使能
    FuncState CMP0_IE;           // 比较器 0 中断使能
    FuncState CMP0_RE;           // 比较器 0 DMA 请求使能
    FuncState CMP0_IRQ_TRIG;     // 比较器 0 边沿触发使能
    FuncState CMP0_IN_EN;        // 比较器 0 信号输入使能
    FuncState CMP0_CHN3P_WIN_EN; // MCPWM 模块 CHN3_P 通道使能比较器 0 开窗
    FuncState CMP0_CHN2P_WIN_EN; // MCPWM 模块 CHN2_P 通道使能比较器 0 开窗
    FuncState CMP0_CHN1P_WIN_EN; // MCPWM 模块 CHN1_P 通道使能比较器 0 开窗
    FuncState CMP0_CHN0P_WIN_EN; // MCPWM 模块 CHN0_P 通道使能比较器 0 开窗

    // 比较器1
    FuncState CMP1_EN;           // 比较器 1 使能
    FuncState CMP1_RE;           // 比较器 1 DMA 请求使能
    FuncState CMP1_IE;           // 比较器 1 中断使能
    FuncState CMP1_IRQ_TRIG;     // 比较器 1 边沿触发使能
    FuncState CMP1_IN_EN;        // 比较器 1 信号输入使能
    FuncState CMP1_CHN3P_WIN_EN; // MCPWM 模块 CHN3_P 通道使能比较器 1 开窗
    FuncState CMP1_CHN2P_WIN_EN; // MCPWM 模块 CHN2_P 通道使能比较器 1 开窗
    FuncState CMP1_CHN1P_WIN_EN; // MCPWM 模块 CHN1_P 通道使能比较器 1 开窗
    FuncState CMP1_CHN0P_WIN_EN; // MCPWM 模块 CHN0_P 通道使能比较器 1 开窗
} CMP_InitTypeDef;

void CMP_Init(CMP_InitTypeDef *);       // 比较器初始化
void CMP_StructInit(CMP_InitTypeDef *); // 比较器配置结构体初始化
void CMP_ClearIRQFlag(u8 CMPx);         // 清CMP中断
u8 CMP_GetIRQFlag(u8 CMPx);             // 读CMP中断
u8 GET_CMP_data(u8 CMPx, u8 GET_CMP_val);
#endif /*__lks32mc03x_cmp_H */
/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
