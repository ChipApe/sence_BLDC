/*******************************************************************************
 * 版权所有 (C)2015, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： lks32mc03x_gpio.h
 * 文件标识：
 * 内容摘要： GPIO外设驱动程序头文件
 * 其它说明： 无
 * 当前版本： V 1.0
 * 作    者： Yangzj
 * 完成日期： 21/11/10
 *
 *******************************************************************************/

#ifndef __lks32mc03x_GPIO_H
#define __lks32mc03x_GPIO_H

/* Includes ------------------------------------------------------------------*/
#include "lks32mc03x.h"
#include "basic.h"

typedef struct
{
    __IO u32 PIE; /*!< 输入使能 */
    __IO u32 POE; /*!< 输出使能 */
    __IO u32 PDI; /*!< 输入数据 */
    __IO u32 PDO; /*!< 输出数据 */
    __IO u32 PUE; /*!< 上拉使能 */
    __IO u32 null1;
    __IO u32 PODE; /*!< 开漏使能 */
    __IO u32 null2;
    __IO u32 F3210; /*!< 功能选择 GPIO_Pin_0-3 */
    __IO u32 F7654; /*!< 功能选择 GPIO_Pin_4-7 */
    __IO u32 FBA98; /*!< 功能选择 GPIO_Pin_8-11 */
    __IO u32 FFEDC; /*!< 功能选择 GPIO_Pin_12-15 */
    __IO u32 BSRR;  /*!< 位置一操作 */
    __IO u32 BRR;   /*!< 位清零操作 */
} GPIO_TypeDef;

typedef struct
{
    __IO u32 CR0;
    __IO u32 CR1;
    __IO u32 IE;
    __IO u32 IF;
    __IO u32 SEL;
} EXTI_TypeDef;

#ifndef GPIO0
#define GPIO0 ((GPIO_TypeDef *)GPIO0_BASE)
#endif
#ifndef GPIO1
#define GPIO1 ((GPIO_TypeDef *)GPIO1_BASE)
#endif
#ifndef EXTI
#define EXTI ((EXTI_TypeDef *)EXTI_BASE)
#endif
typedef enum
{
    EXTI_Trigger_None = 0x00,    // 不触发
    EXTI_Trigger_Negedge = 0x01, // 下降沿触发
    EXTI_Trigger_Posedge = 0x02, // 上升沿触发
    EXTI_Trigger_Edge = 0x03     // 上升沿、下降沿均触发
} EXTIMode_TypeDef;
typedef enum
{
    GPIO_Mode_IN = 0x00,  // GPIO输入模式
    GPIO_Mode_OUT = 0x01, // GPIO输出模式
    GPIO_Mode_ANA = 0x02  // GPIO禁止输入输出
} GPIOMode_TypeDef;

typedef enum
{
    GPIO_PuPd_NOPULL = 0x00, // 不配置上下拉电阻
    GPIO_PuPd_UP = 0x01,     // 上拉
} GPIOPuPd_TypeDef;

typedef enum
{
    Bit_RESET = 0,
    Bit_SET
} BitAction;

typedef struct
{
    u32 GPIO_Pin;          // 要配置的Pad
    u32 GPIO_PODEna;       // 开漏
    GPIOMode_TypeDef GPIO_Mode; // GPIO模式:输入、输出、模拟
    GPIOPuPd_TypeDef GPIO_PuPd; // 上拉OR不上拉（高阻态）
    u16 null;                   // 地址对齐
} GPIO_InitTypeDef;

// GPIO 复用功能
#define AF0_GPIO 0        /* 模拟功能 */
#define AF1_CMP 1         /* 比较器结果输出或时钟输出功能 */
#define AF2_HALL 2        /* HALL功能 */
#define AF3_MCPWM 3       /* MCPWM功能：通道信号输出或停机信号输入 */
#define AF4_UART 4        /* UART功能 */
#define AF5_SPI 5         /* SPI功能，SPI时钟、片选、数据输出、数据输入 */
#define AF6_I2C 6         /* I2C功能，I2C时钟、I2C数据 */
#define AF7_TIMER0 7      /* Timer0功能：比较模式输出、捕获模式或外部时钟源输入，对应通道0/1 */
#define AF8_TIMER1 8      /* Timer1功能：比较模式输出、捕获模式或外部时钟源输入，对应通道0/1 */
#define AF9_ADC_TRIGGER 9 /* ADC采样触发信号输出，每发生一次ADC采样，ADC_TRIGGER信号反转一次 */

// GPIO 引脚定义
#define GPIO_Pin_NONE 0
#define GPIO_Pin_0 BIT0
#define GPIO_Pin_1 BIT1
#define GPIO_Pin_2 BIT2
#define GPIO_Pin_3 BIT3
#define GPIO_Pin_4 BIT4
#define GPIO_Pin_5 BIT5
#define GPIO_Pin_6 BIT6
#define GPIO_Pin_7 BIT7
#define GPIO_Pin_8 BIT8
#define GPIO_Pin_9 BIT9
#define GPIO_Pin_10 BIT10
#define GPIO_Pin_11 BIT11
#define GPIO_Pin_12 BIT12
#define GPIO_Pin_13 BIT13
#define GPIO_Pin_14 BIT14
#define GPIO_Pin_15 BIT15
#define GPIO_Pin_ALL (u32)0xFFFF

// GPIO 编号定义
#define GPIO_PinSource_0 0
#define GPIO_PinSource_1 1
#define GPIO_PinSource_2 2
#define GPIO_PinSource_3 3
#define GPIO_PinSource_4 4
#define GPIO_PinSource_5 5
#define GPIO_PinSource_6 6
#define GPIO_PinSource_7 7
#define GPIO_PinSource_8 8
#define GPIO_PinSource_9 9
#define GPIO_PinSource_10 10
#define GPIO_PinSource_11 11
#define GPIO_PinSource_12 12
#define GPIO_PinSource_13 13
#define GPIO_PinSource_14 14
#define GPIO_PinSource_15 15

// EXTI_IF 中断标志位定义
#define GPIO_P00_EXTI_IF BIT0
#define GPIO_P02_EXTI_IF BIT1
#define GPIO_P04_EXTI_IF BIT2
#define GPIO_P05_EXTI_IF BIT3
#define GPIO_P06_EXTI_IF BIT4
#define GPIO_P07_EXTI_IF BIT5
#define GPIO_P08_EXTI_IF BIT6
#define GPIO_P09_EXTI_IF BIT7
#define GPIO_P014_EXTI_IF BIT8
#define GPIO_P015_EXTI_IF BIT9
#define GPIO_P14_EXTI_IF BIT10
#define GPIO_P15_EXTI_IF BIT11
#define GPIO_P16_EXTI_IF BIT12
#define GPIO_P17_EXTI_IF BIT13
#define GPIO_P18_EXTI_IF BIT14
#define GPIO_P19_EXTI_IF BIT15

// CLKO_SEL 时钟信号调试输出选择
#define CLKO_SEL_ADC BIT3 // 24MHz
#define CLKO_SEL_PLL BIT2 // 48MHz 无法驱动负载
#define CLKO_SEL_HSI BIT1 // 4MHz
#define CLKO_SEL_LSI BIT0 // 64kHz

// GPIO初始化
void GPIO_Init(GPIO_TypeDef *GPIOx, GPIO_InitTypeDef *GPIO_InitStruct);
void GPIO_StructInit(GPIO_InitTypeDef *GPIO_InitStruct);
void GPIO_SetMode(GPIO_TypeDef* GPIOx, u16 GPIO_Pin, GPIOMode_TypeDef GPIO_Mode);

// GPIO 读
u32 GPIO_ReadInputData(GPIO_TypeDef *GPIOx);
u32 GPIO_ReadOutputData(GPIO_TypeDef *GPIOx);
u8 GPIO_ReadInputDataBit(GPIO_TypeDef *GPIOx, u16 GPIO_Pin);
u8 GPIO_ReadOutputDataBit(GPIO_TypeDef *GPIOx, u16 GPIO_Pin);
// GPIO 写
void GPIO_Write(GPIO_TypeDef *GPIOx, u32 Val);
void GPIO_SetBits(GPIO_TypeDef *GPIOx, u16 GPIO_Pin);
void GPIO_ResetBits(GPIO_TypeDef *GPIOx, u16 GPIO_Pin);
void GPIO_WriteBit(GPIO_TypeDef *GPIOx, u16 GPIO_Pin, BitAction BitVal);

// GPIO功能选择
void GPIO_PinAFConfig(GPIO_TypeDef *GPIOx, u32 GPIO_PinSource, u32 GPIO_AF);

// EXTI相关
void EXTI_Trigger_Config(GPIO_TypeDef *GPIOx, u32 GPIO_PinSource, u16 EXTI_Trigger);
void EXTI_ClearIRQFlag(GPIO_TypeDef *GPIOx, u32 GPIO_PinSource);
u8 EXTI_GetIRQFlag(GPIO_TypeDef *GPIOx, u32 GPIO_PinSource);

#endif /*__lks32mc03x_GPIO_H */

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
