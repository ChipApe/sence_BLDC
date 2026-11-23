

/*******************************************************************************
 * 版权所有 (C)2021, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： lks32mc03x_adc.c
 * 文件标识：
 * 内容摘要： ADC外设驱动程序
 * 其它说明： 无
 * 当前版本： V 1.0
 * 作    者：   HMG
 * 完成日期： 2021年10月14日
 *
 *******************************************************************************/
#include "lks32mc03x_adc.h"

/*******************************************************************************
 函数名称：    void ADC_Init(ADC_TypeDef* ADCx, ADC_InitTypeDef* ADC_InitStruct)
 功能描述：    ADC初始化
 操作的表：    无
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
2021/10/14    V1.0         HungMG           创建
 *******************************************************************************/
void ADC_Init(ADC_TypeDef *ADCx, ADC_InitTypeDef *ADC_InitStruct)
{

    u16 t_reg;

    SYS_AnalogModuleClockCmd(SYS_AnalogModule_ADC, ENABLE); // ADC模块使能

    ADCx->IE = ADC_InitStruct->IE;

    t_reg = (u16)(ADC_InitStruct->Align << 10) |
            (u16)(ADC_InitStruct->Trigger_En) |
            (u16)(ADC_InitStruct->SEL_En << 12) |
            (u16)(ADC_InitStruct->FSM_RESET << 11) |
            (u16)(ADC_InitStruct->Trigger_Cnt << 4) |
            (u16)(ADC_InitStruct->Trigger_Mode << 8);
    ADCx->CFG = t_reg;

    ADCx->CHNT = (u16)ADC_InitStruct->FirSeg_Ch |
                 (u16)(ADC_InitStruct->SecSeg_Ch << 4) |
                 (u16)(ADC_InitStruct->ThrSeg_Ch << 8) |
                 (u16)(ADC_InitStruct->FouSeg_Ch << 12);

    ADC_LTH = ADC_InitStruct->ADC_GEN_LTH;

    ADC_HTH = ADC_InitStruct->ADC_GEN_HTH;

    ADC_GEN = ADC_InitStruct->ADC_GEN_En;

    SYS_WR_PROTECT = 0x7a83; /* 解除系统寄存器写保护 */

    if (ADC_InitStruct->ADC_SAMP_CLK > 4)
    {
        t_reg = ADC_InitStruct->ADC_SAMP_CLK - 4;
    }
    else
    {
        t_reg = 0;
    }

    if (ADC_InitStruct->ADC_RANGE & 0x01) /*2.4V量程*/
    {
        SYS_AFE_REG0 |= 0x01 << 6;       /*ADC量程选择*/
        ADC_AMC = Read_Trim(0x000001AC); /*ADC_AMC1校正值，1倍增益*/
        ADC_DC = Read_Trim(0x000001A8);  /*ADC_DC1校正值 ，1倍增益*/
    }
    else
    {                                       /*3.6V量程*/
        SYS_AFE_REG0 &= (u16) ~(0x01 << 6); /*ADC量程选择*/
        ADC_AMC = Read_Trim(0x000001A4);    /*ADC_AMC0校正值，2/3倍增益*/
        ADC_DC = Read_Trim(0x000001A0);     /*ADC_DC0校正值 ，2/3倍增益*/
    }
    SYS_AFE_REG2 = (u16)(t_reg << 8); //设置ADC采样时间
    SYS_AFE_REG1 |= (u16)(ADC_InitStruct->REFOUT_EN << 6);

    SYS_WR_PROTECT = 0; /* 开启系统寄存器写保护 */
}
/*******************************************************************************
 函数名称：    void ADC_StructInit(ADC_InitTypeDef* ADC_InitStruct)
 功能描述：    ADC结构体初始化
 操作的表：    无
 输入参数：    无
 输出参数：    无
 返 回 值：     无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
2021/10/14    V1.0             HMG               创建
 *******************************************************************************/
void ADC_StructInit(ADC_InitTypeDef *ADC_InitStruct)
{
    ADC_InitStruct->ADC_SAMP_CLK = 0;
    ADC_InitStruct->IE = 0;
    ADC_InitStruct->SEL_En = 0;
    ADC_InitStruct->FSM_RESET = 0;
    ADC_InitStruct->Align = 0;
    ADC_InitStruct->Trigger_Mode = 0;
    ADC_InitStruct->Trigger_Cnt = 0;
    ADC_InitStruct->Trigger_En = 0;

    ADC_InitStruct->FirSeg_Ch = 0;
    ADC_InitStruct->SecSeg_Ch = 0;
    ADC_InitStruct->ThrSeg_Ch = 0;
    ADC_InitStruct->FouSeg_Ch = 0;

    ADC_InitStruct->ADC_GEN_En = 0;
    ADC_InitStruct->ADC_GEN_HTH = 0;
    ADC_InitStruct->ADC_GEN_LTH = 0;
    ADC_InitStruct->REFOUT_EN = 0;

    ADC_InitStruct->ADC_RANGE = 0;
}
/*******************************************************************************
 函数名称：    void ADC_ClearIRQFlag(ADC_TypeDef* ADCx, u16 INT_flag)
 功能描述：    ADC中断标志位清零
 操作的表：    无
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：    写1清零
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/04/20    V1.0            Zhu Jie          创建
 *******************************************************************************/
void ADC_ClearIRQFlag(ADC_TypeDef *ADCx, u16 INT_flag)
{
    ADCx->IF = INT_flag;
}
/*******************************************************************************
 函数名称：    u16 ADC_GetIRQFlag(ADC_TypeDef* ADCx, u16 INT_flag)
 功能描述：    获取ADC中断标志位
 操作的表：    无
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：    读标志位是否为1
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/04/20    V1.0            Zhu Jie           创建
 *******************************************************************************/
u16 ADC_GetIRQFlag(ADC_TypeDef *ADCx, u16 INT_flag)
{
    u8 ADCIRQFlag = 0;
    if (ADCx->IF & INT_flag)
    {
        ADCIRQFlag = 1;
    }
    else
    {
        ADCIRQFlag = 0;
    }
    return ADCIRQFlag;
}
/*******************************************************************************
 函数名称：    void ADC_ChannelConfig(ADC_TypeDef* ADCx,CHNx CHNum, u16 Channel_0 ,u16 Channel_1)
 功能描述：    ADC采样通道设置
 操作的表：    无
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：    一次只能配置一个通道寄存器，对应两个采样通道
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/04/20    V1.0            Zhu Jie          创建
 *******************************************************************************/
void ADC_ChannelConfig(ADC_TypeDef *ADCx, CHNx CHNum, u16 Ch_n0, u16 Ch_n1, u16 Ch_n2, u16 Ch_n3)
{
    if (CHNum == CHN0)
    {
        ADCx->CHN0 = (u32)(Ch_n0) |
                     (u32)(Ch_n1 << 4) |
                     (u32)(Ch_n2 << 8) |
                     (u32)(Ch_n3 << 12);
    }
    else if (CHNum == CHN1)
    {
        ADCx->CHN1 = (u32)(Ch_n0) |
                     (u32)(Ch_n1 << 4) |
                     (u32)(Ch_n2 << 8) |
                     (u32)(Ch_n3 << 12);
    }
    else if (CHNum == CHN2)
    {
        ADCx->CHN2 = (u32)(Ch_n0) |
                     (u32)(Ch_n1 << 4);
    }
}
/*******************************************************************************
 函数名称：    s16 ADC_GetConversionValue(DATNx DATNum)
 功能描述：    ADC采样通道设置
 操作的表：    无
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：    一次只能配置一个通道寄存器，对应两个采样通道
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/04/20    V1.0            Zhu Jie          创建
 *******************************************************************************/
s16 ADC_GetConversionValue(DATx DATNum)
{
    if (DATNum == DAT0)
    {
        return ADC_DAT0;
    }
    else if (DATNum == DAT1)
    {
        return ADC_DAT1;
    }
    else if (DATNum == DAT2)
    {
        return ADC_DAT2;
    }
    else if (DATNum == DAT3)
    {
        return ADC_DAT3;
    }
    else if (DATNum == DAT4)
    {
        return ADC_DAT4;
    }
    else if (DATNum == DAT5)
    {
        return ADC_DAT5;
    }
    else if (DATNum == DAT6)
    {
        return ADC_DAT6;
    }
    else if (DATNum == DAT7)
    {
        return ADC_DAT7;
    }
    else if (DATNum == DAT8)
    {
        return ADC_DAT8;
    }
    else if (DATNum == DAT9)
    {
        return ADC_DAT9;
    }
    return 0;
}
/*******************************************************************************
 函数名称：    void ADC_SoftTrgEN(ADC_TypeDef* ADCx, FuncState state)
 功能描述：    ADC采样软件触发使能
 操作的表：    无
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：    ADC0_SWT写0x5AA5仅触发一次，完成后自动清零，等待下次软件触发
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/04/24    V1.0            Zhu Jie          创建
 *******************************************************************************/
void ADC_SoftTrgEN(ADC_TypeDef *ADCx, FuncState state)
{
    if (state == ENABLE)
    {
        ADCx->SWT = 0x5AA5;
    }
}

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
