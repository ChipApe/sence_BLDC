/*******************************************************************************
 * 版权所有 (C)2021, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： lks32mc03x_adc.h
 * 文件标识：
 * 内容摘要： ADC外设驱动程序头文件
 * 其它说明： 无
 * 当前版本： V 1.0
 * 作    者：   HMG
 * 完成日期： 2021年10月14日
 *
 *******************************************************************************/

#ifndef _LKS32MC03x_ADC_H_
#define _LKS32MC03x_ADC_H_

/* Includes ------------------------------------------------------------------*/
#include "lks32mc03x_lib.h"

typedef struct
{
    __IO u32 DAT0; /* ADC数据寄存器0 */
    __IO u32 DAT1; /* ADC数据寄存器1 */
    __IO u32 DAT2; /* ADC数据寄存器2 */
    __IO u32 DAT3; /* ADC数据寄存器3 */
    __IO u32 DAT4; /* ADC数据寄存器4 */
    __IO u32 DAT5; /* ADC数据寄存器5 */
    __IO u32 DAT6; /* ADC数据寄存器6 */
    __IO u32 DAT7; /* ADC数据寄存器7 */
    __IO u32 DAT8; /* ADC数据寄存器8 */
    __IO u32 DAT9; /* ADC数据寄存器9 */

    __IO u32 null0; /* 空闲 */
    __IO u32 null1; /* 空闲 */

    __IO u32 LTH; /* ADC模拟看门狗低阈值 */
    __IO u32 HTH; /* ADC模拟看门狗高阈值 */
    __IO u32 GEN; /* ADC模拟看门狗监测使能 */

    __IO u32 null2; /* 空闲 */

    __IO u32 CHN0; /* ADC采样信号来源寄存器0 */
    __IO u32 CHN1; /* ADC采样信号来源寄存器1 */
    __IO u32 CHN2; /* ADC采样信号来源寄存器2 */

    __IO u32 null3; /* 空闲 */

    __IO u32 CHNT; /* ADC每各段采样通道数配置寄存器 */

    __IO u32 CFG; /* ADC模式配置寄存器 */
    __IO u32 SWT; /* ADC软件触发寄存器 */

    __IO u32 null4; /* 空闲 */

    __IO u32 DC;  /* ADC直流偏置寄存器 */
    __IO u32 AMC; /* ADC增益校正寄存器 */

    __IO u32 IE; /* ADC中断寄存器 */
    __IO u32 IF; /* ADC中断标志位寄存器 */

} ADC_TypeDef;

#ifndef ADC
#define ADC ((ADC_TypeDef *)ADC_BASE)
#endif

typedef struct
{
    u16 ADC_SAMP_CLK; /* ADC 采样时间选择从5->36个ADC时钟周期可选*/

    u16 IE; /* Configures ADC_IRQ */

    u16 SEL_En;       /* TADC触发来源选择。0:MCPWM，1:UTimer */
    u16 FSM_RESET;    /* ADC 状态机复位控制信号  */
    u16 Align;        /* Configures ADC Result Align */
    u16 Trigger_Mode; /* ADC trigger mode 单段，两端，四段触发*/
    u16 Trigger_Cnt;  /* 单段模式下触发下一次采样所需的触发事件数 */
    u16 Trigger_En;   /* TADC触发ADC采样使能信号 */

    u16 FirSeg_Ch; /* 第一段采样的总通道数 */
    u16 SecSeg_Ch; /* 第二段采样的总通道数 */
    u16 ThrSeg_Ch; /* 第三段采样的总通道数 */
    u16 FouSeg_Ch; /* 第四段采样的总通道数 */

    u16 ADC_GEN_En;  /* ADC模拟看门狗 */
    u16 ADC_GEN_HTH; /* ADC模拟看门狗上阈值 */
    u16 ADC_GEN_LTH; /* ADC模拟看门狗下阈值 */
    u16 REFOUT_EN;   /* ADC REF输出使能*/

    u16 ADC_RANGE; /* ADC量程0:3.6V，1:2.4V*/

} ADC_InitTypeDef;

#define ADC_MCPWM_TRG 0x0  /* 选择MCPWM为ADC触发来源 */
#define ADC_UTIMER_TRG 0x1 /* 选择UTIMER为ADC触发来源 */

#define ADC_RANGE_2V4 0x01 /*ADC量程2.4V*/
#define ADC_RANGE_3V6 0x00 /*ADC量程3.6V*/

#define ADC_1_TIMES_SAMPLE ((u8)1) /* ADC采样通道数1次采样 */
#define ADC_2_TIMES_SAMPLE ((u8)2) /* ADC采样通道数2次采样 */
#define ADC_3_TIMES_SAMPLE ((u8)3) /* ADC采样通道数3次采样 */
#define ADC_4_TIMES_SAMPLE ((u8)4) /* ADC采样通道数4次采样 */
#define ADC_5_TIMES_SAMPLE ((u8)5) /* ADC采样通道数5次采样 */
#define ADC_6_TIMES_SAMPLE ((u8)6) /* ADC采样通道数6次采样 */
#define ADC_7_TIMES_SAMPLE ((u8)7) /* ADC采样通道数7次采样 */
#define ADC_8_TIMES_SAMPLE ((u8)8) /* ADC采样通道数8次采样 */
#define ADC_9_TIMES_SAMPLE ((u8)9) /* ADC采样通道数9次采样 */

#define ADC_GEN_DAT0 ((u16)0x01)  /* DAT0看门狗监测使能 */
#define ADC_GEN_DAT1 ((u16)0x02)  /* DAT1看门狗监测使能 */
#define ADC_GEN_DAT2 ((u16)0x04)  /* DAT2看门狗监测使能 */
#define ADC_GEN_DAT3 ((u16)0x08)  /* DAT3看门狗监测使能 */
#define ADC_GEN_DAT4 ((u16)0x10)  /* DAT4看门狗监测使能 */
#define ADC_GEN_DAT5 ((u16)0x20)  /* DAT5看门狗监测使能 */
#define ADC_GEN_DAT6 ((u16)0x40)  /* DAT6看门狗监测使能 */
#define ADC_GEN_DAT7 ((u16)0x80)  /* DAT7看门狗监测使能 */
#define ADC_GEN_DAT8 ((u16)0x100) /* DAT8看门狗监测使能 */
#define ADC_GEN_DAT9 ((u16)0x200) /* DAT9看门狗监测使能 */

#define ADC_EOS0_IRQ_EN ((u16)0x01)     /* 第一段扫描结束中断 */
#define ADC_EOS1_IRQ_EN ((u16)0x02)     /* 第二段扫描结束中断 */
#define ADC_EOS2_IRQ_EN ((u16)0x04)     /* 第三段扫描结束中断 */
#define ADC_EOS3_IRQ_EN ((u16)0x08)     /* 第四段扫描结束中断 */
#define ADC_CONFLICT_IRQ_EN ((u16)0x10) /* 软件触发冲突 */
#define ADC_HERR_IRQ_EN ((u16)0x20)     /* 硬件触发冲突 */
#define ADC_DAT0_OV_IRQ_EN ((u16)0x40)  /* 超阈值中断 */

#define ADC_EOS0_DMA_EN ((u16)0x100)      /* 第一段扫描结束DMA请求使能 */
#define ADC_EOS1_DMA_EN ((u16)0x200)      /* 第二段扫描结束DMA请求使能 */
#define ADC_EOS2_DMA_EN ((u16)0x400)      /* 第三段扫描结束DMA请求使能 */
#define ADC_EOS3_DMA_EN ((u16)0x800)      /* 第四段扫描结束DMA请求使能 */
#define ADC_CONFLICT_DMA_EN ((u16)0x1000) /* 软件触发冲突DMA请求使能 */
#define ADC_HERR_DMA_EN ((u16)0x2000)     /* 硬件触发冲突DMA请求使能 */
#define ADC_DAT0_OV_DMA_EN ((u16)0x4000)  /* 超阈值DMA请求使能 */

#define ADC_ALL_IRQ_IF ((u16)0x7f)      /* ADC全部中断标志位——可用于初始化 */
#define ADC_DAT0_OV_IRQ_IF ((u16)0x40)  /* 超阈值中断 */
#define ADC_CONFLICT_IRQ_IF ((u16)0x20) /* 硬件触发冲突标志 */
#define ADC_HERR_IRQ_IF ((u16)0x10)     /* 软件触发冲突标志 */
#define ADC_EOS3_IRQ_IF ((u16)0x08)     /* 第四段扫描结束中断标志 */
#define ADC_EOS2_IRQ_IF ((u16)0x04)     /* 第三段扫描结束中断标志*/
#define ADC_EOS1_IRQ_IF ((u16)0x02)     /* 第二段扫描结束中断标志 */
#define ADC_EOS0_IRQ_IF ((u16)0x01)     /* 第一段扫描结束中断标志 */

#define ADC_LEFT_ALIGN ((u16)0x0000)  /* ADC数据输出左对齐 */
#define ADC_RIGHT_ALIGN ((u16)0x0001) /* ADC数据输出右对齐 */

#define ADC_DAT0_HTH ((u16)0x0001) /* ADC_DAT0_TH作为上阈值 */
#define ADC_DAT0_LTH ((u16)0x0000) /* ADC_DAT0_TH作为下阈值 */

#define ADC_MCPWM_SEL ((u16)0x0000)  /* MCPWM 触发ADC采样 */
#define ADC_UTIMER_SEL ((u16)0x0001) /* UTIMER触发ADC采样 */

#define ADC_1SEG_TRG ((u16)0x00) /* ADC采用单段模式 */
#define ADC_2SEG_TRG ((u16)0x01) /* ADC采用2段模式 */
#define ADC_4SEG_TRG ((u16)0x03) /* ADC采用4段模式 */

#define ADC_CHANNEL_0 ((u16)0x00)  /* ADC通道0  OPA0_OUT*/
#define ADC_CHANNEL_1 ((u16)0x01)  /* ADC通道1  ADC_CH1*/
#define ADC_CHANNEL_2 ((u16)0x02)  /* ADC通道2  ADC_CH2*/
#define ADC_CHANNEL_3 ((u16)0x03)  /* ADC通道3  ADC_CH3*/
#define ADC_CHANNEL_4 ((u16)0x04)  /* ADC通道4  ADC_CH4*/
#define ADC_CHANNEL_5 ((u16)0x05)  /* ADC通道5  ADC_CH5*/
#define ADC_CHANNEL_6 ((u16)0x06)  /* ADC通道6  ADC_CH6*/
#define ADC_CHANNEL_7 ((u16)0x07)  /* ADC通道7  ADC_CH7*/
#define ADC_CHANNEL_8 ((u16)0x08)  /* ADC通道8  ADC_CH8/OPA1_OUT*/
#define ADC_CHANNEL_9 ((u16)0x09)  /* ADC通道9  ADC_CH9*/
#define ADC_CHANNEL_10 ((u16)0x0a) /* ADC通道10 ADC_CH10*/
#define ADC_CHANNEL_11 ((u16)0x0b) /* ADC通道11 温度传感器*/
#define ADC_CHANNEL_12 ((u16)0x0c) /* ADC通道12 内部地*/
#define ADC_CHANNEL_13 ((u16)0x0d) /* ADC通道13 2.4V基准源*/

#define ADC_HARDWARE_T0_TRG ((u16)0x01) /* ADC采用硬件T0事件触发 */
#define ADC_HARDWARE_T1_TRG ((u16)0x02) /* ADC采用硬件T1事件触发 */
#define ADC_HARDWARE_T2_TRG ((u16)0x04) /* ADC采用硬件T2事件触发 */
#define ADC_HARDWARE_T3_TRG ((u16)0x08) /* ADC采用硬件T3事件触发 */

/* ADC采样信号来源寄存器序号 */
typedef enum
{
    CHN0 = 0,
    CHN1,
    CHN2,
} CHNx;

/* ADC数据寄存器序号 */
typedef enum
{
    DAT0 = 0,
    DAT1,
    DAT2,
    DAT3,
    DAT4,
    DAT5,
    DAT6,
    DAT7,
    DAT8,
    DAT9,
} DATx;

void ADC_Init(ADC_TypeDef *ADCx, ADC_InitTypeDef *ADC_InitStruct);
void ADC_StructInit(ADC_InitTypeDef *ADC_InitStruct);
void ADC_ClearIRQFlag(ADC_TypeDef *ADCx, u16 INT_flag);
u16 ADC_GetIRQFlag(ADC_TypeDef *ADCx, u16 INT_flag);
void ADC_ChannelConfig(ADC_TypeDef *ADCx, CHNx CHNum, u16 Ch_n0, u16 Ch_n1, u16 Ch_n2, u16 Ch_n3);
s16 ADC_GetConversionValue(DATx DATNum);
void ADC_SoftTrgEN(ADC_TypeDef *ADCx, FuncState state);
#endif /*_CONNIE_ADC_H_ */

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
