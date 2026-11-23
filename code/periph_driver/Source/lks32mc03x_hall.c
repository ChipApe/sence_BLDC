/*******************************************************************************
 * 版权所有 (C)2021, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： lks32mc03x_hall.c
 * 文件标识：
 * 内容摘要： HALL驱动程序
 * 其它说明： 无
 * 当前版本： V 1.0
 * 作    者：   HuangMG
 * 完成日期： 2021年10月14日
 *
 *******************************************************************************/
#include "lks32mc03x_hall.h"

/*******************************************************************************
 函数名称：    void HALL_Init(HALL_InitTypeDef* HALL_InitStruct)
 功能描述：    HALL初始化
 操作的表：    无
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
2021/10/14    V1.0            HuangMG               创建
 *******************************************************************************/
void HALL_Init(HALL_InitTypeDef *HALL_InitStruct)
{

    SYS_ModuleClockCmd(SYS_Module_HALL, ENABLE); // HALL时钟使能
    HALL_CFG = (u32)(HALL_InitStruct->FilterLen) |
               (u32)(HALL_InitStruct->ClockDivision << 16) |
               (u32)(HALL_InitStruct->Filter75_Ena << 20) |
               (u32)(HALL_InitStruct->HALL_Ena << 24) |
               (u32)(HALL_InitStruct->HALL_CHGDMA_Ena << 25) |
               (u32)(HALL_InitStruct->HALL_OVDMA_Ena << 26) |
               (u32)(HALL_InitStruct->Capture_IRQ_Ena << 28) |
               (u32)(HALL_InitStruct->OverFlow_IRQ_Ena << 29) |
               (u32)(HALL_InitStruct->softIE << 30);
    HALL_TH = HALL_InitStruct->CountTH;
    HALL_INFO = 0;
}

/*******************************************************************************
 函数名称：    void HALL_StructInit(HALL_InitTypeDef* HALL_InitStruct)
 功能描述：    HALL结构体初始化
 操作的表：    无
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
2021/10/14    V1.0            HuangMG               创建
 *******************************************************************************/
void HALL_StructInit(HALL_InitTypeDef *HALL_InitStruct)
{
    HALL_InitStruct->FilterLen = 1023;
    HALL_InitStruct->ClockDivision = HALL_CLK_DIV1;
    HALL_InitStruct->Filter75_Ena = ENABLE;
    HALL_InitStruct->HALL_Ena = ENABLE;
    HALL_InitStruct->Capture_IRQ_Ena = ENABLE;
    HALL_InitStruct->HALL_CHGDMA_Ena = DISABLE;
    HALL_InitStruct->HALL_OVDMA_Ena = DISABLE;
    HALL_InitStruct->OverFlow_IRQ_Ena = DISABLE;
    HALL_InitStruct->CountTH = 1000;
    HALL_InitStruct->softIE = DISABLE;
}

/*******************************************************************************
 函数名称：    u32 HALL_GetFilterValue(void)
 功能描述：    取得HALL值，滤波结果
 操作的表：    无
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
2021/10/14    V1.0            HuangMG               创建
 *******************************************************************************/
u32 HALL_GetFilterValue(void)
{
    return (HALL_INFO & 0x07);
}

/*******************************************************************************
 函数名称：    u32 HALL_GetCaptureValue(void)
 功能描述：    取得HALL值，发生HALL事件时的锁存结果
 操作的表：    无
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
2021/10/14    V1.0            HuangMG               创建
 *******************************************************************************/
u32 HALL_GetCaptureValue(void)
{
    return (HALL_INFO >> 8) & 0x07;
}

/*******************************************************************************
 函数名称：    u32 HALL_GetCount(void)
 功能描述：    取得发生捕获事件时HALL计数值
 操作的表：    无
 输入参数：    无
 输出参数：    无
 返 回 值：    当发生HALL 信号变化时，将此时刻的HALL_CNT值保存到HALL_WIDTH寄存器
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2016/04/19      V1.0           cfwu          创建
 *******************************************************************************/
u32 HALL_WIDCount(void)
{
    return HALL->WIDTH;
}

/*******************************************************************************
 函数名称：    u32 HALL_GetCount(void)
 功能描述：    取得HALL计数器值
 操作的表：    无
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
2021/10/14    V1.0            HuangMG               创建
 *******************************************************************************/
u32 HALL_GetCount(void)
{
    return HALL_CNT;
}

/*******************************************************************************
 函数名称：    u32 HALL_GetIRQFlag(u32 tempFlag)
 功能描述：    取得HALL中断标志
 操作的表：    无
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
2022/5/20      V1.0           HuangMG          创建
 *******************************************************************************/
u32 HALL_GetIRQFlag(u32 tempFlag)
{
    return (HALL_INFO & tempFlag);
}

/*******************************************************************************
 函数名称：    void HALL_ClearIRQFlag(u32 tempFlag)
 功能描述：    清除HALL中断标志位
 操作的表：    无
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
2022/5/20      V1.0           HuangMG            创建
 *******************************************************************************/
void HALL_ClearIRQFlag(u32 tempFlag)
{
    HALL_INFO = tempFlag;
}
/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
