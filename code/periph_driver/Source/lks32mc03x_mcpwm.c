/*******************************************************************************
 * 版权所有 (C)2021, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： LKS32MC03x_MCPWM.c
 * 文件标识：
 * 内容摘要： MCPWM外设驱动程序
 * 其它说明： 无
 * 当前版本： V 1.0
 * 作    者：   HMG
 * 完成日期： 2021年10月14日
 *
 *******************************************************************************/
#include "lks32mc03x_mcpwm.h"
#include "string.h"

/*******************************************************************************
 函数名称：    void PWMOutputs(MCPWM_REG_TypeDef *MCPWM, FuncState t_state)
 功能描述：    MCPWM CH0/CH1/CH2 信号输出使能
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2021/10/14   V1.0             HMG              创建
 *******************************************************************************/
void PWMOutputs(MCPWM_REG_TypeDef *MCPWMx, FuncState t_state)
{
    MCPWMx->PWM_PRT = 0x0000DEAD;
    if (t_state == ENABLE)
    {
        MCPWMx->PWM_FAIL012 |= MCPWM_MOE_ENABLE_MASK;
    }
    else
    {
        MCPWMx->PWM_FAIL012 &= MCPWM_MOE_DISABLE_MASK;
    }
    MCPWMx->PWM_PRT = 0x0000CAFE;
}

/*******************************************************************************
 函数名称：    void PWMOutputs_CH3(MCPWM_REG_TypeDef *MCPWM, FuncState t_state)
 功能描述：    MCPWM CH3 信号输出使能
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2021/10/14   V1.0             HMG              创建
 *******************************************************************************/
void PWMOutputs_CH3(MCPWM_REG_TypeDef *MCPWMx, FuncState t_state)
{
    MCPWMx->PWM_PRT = 0x0000DEAD;
    if (t_state == ENABLE)
    {
        MCPWMx->PWM_FAIL3 |= MCPWM_MOE_ENABLE_MASK;
    }
    else
    {
        MCPWMx->PWM_FAIL3 &= MCPWM_MOE_DISABLE_MASK;
    }
    MCPWMx->PWM_PRT = 0x0000CAFE;
}

/*******************************************************************************
 函数名称：    void MCPWM_StructInit(MCPWM_InitTypeDef* MCPWM_InitStruct)
 功能描述：    MCPWM结构体初始化
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2021/10/14   V1.0             HMG              创建
 *******************************************************************************/
void MCPWM_StructInit(MCPWM_InitTypeDef *MCPWM_InitStruct)
{

    memset(MCPWM_InitStruct, 0, sizeof(MCPWM_InitTypeDef));
}

/*******************************************************************************
 函数名称：    void MCPWM_Init(MCPWM_REG_TypeDef *MCPWM, MCPWM_InitTypeDef* MCPWM_InitStruct)
 功能描述：    MCPWM初始化
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2021/10/14   V1.0             HMG              创建
 *******************************************************************************/
void MCPWM_Init(MCPWM_REG_TypeDef *MCPWMx, MCPWM_InitTypeDef *MCPWM_InitStruct)
{
    SYS_ModuleClockCmd(SYS_Module_MCPWM, ENABLE);

    MCPWMx->PWM_PRT = 0x0000DEAD; /*enter password to unlock write protection */
    MCPWMx->PWM_TCLK = (u32)MCPWM_InitStruct->CLK_DIV |
                       (u32)(MCPWM_InitStruct->MCLK_EN << 2) |
                       (u32)(MCPWM_InitStruct->TMR2_TimeBase_Sel << 4) |
                       (u32)(MCPWM_InitStruct->TMR3_TimeBase_Sel << 5) |
                       (u32)(MCPWM_InitStruct->MCPWM_Cnt0_EN << 6) |
                       (u32)(MCPWM_InitStruct->MCPWM_Cnt1_EN << 7) |
                       (u32)(MCPWM_InitStruct->TimeBase0_Trig_Enable << 8) |
                       (u32)(MCPWM_InitStruct->TimeBase1_Trig_Enable << 9);
    MCPWMx->PWM_TH0 = MCPWM_InitStruct->TimeBase0_PERIOD;
    MCPWMx->PWM_TH1 = MCPWM_InitStruct->TimeBase1_PERIOD;

    MCPWMx->PWM_TMR0 = MCPWM_InitStruct->TriggerPoint0;
    MCPWMx->PWM_TMR1 = MCPWM_InitStruct->TriggerPoint1;
    MCPWMx->PWM_TMR2 = MCPWM_InitStruct->TriggerPoint2;
    MCPWMx->PWM_TMR3 = MCPWM_InitStruct->TriggerPoint3;

    MCPWMx->PWM_FLT = (u32)(MCPWM_InitStruct->CMP_BKIN_Filter << 8) |
                      (u32)MCPWM_InitStruct->GPIO_BKIN_Filter;

    MCPWMx->PWM_IO01 = (u32)MCPWM_InitStruct->CH0N_Polarity_INV |
                       (u32)(MCPWM_InitStruct->CH0P_Polarity_INV << 1) |
                       (u32)(MCPWM_InitStruct->Switch_CH0N_CH0P << 6) |
                       (u32)(MCPWM_InitStruct->MCPWM_WorkModeCH0 << 7) |
                       (u32)(MCPWM_InitStruct->CH1N_Polarity_INV << 8) |
                       (u32)(MCPWM_InitStruct->CH1P_Polarity_INV << 9) |
                       (u32)(MCPWM_InitStruct->Switch_CH1N_CH1P << 14) |
                       (u32)(MCPWM_InitStruct->MCPWM_WorkModeCH1 << 15) |
                       (u32)(MCPWM_InitStruct->CH0P_SCTRLP << 5) |
                       (u32)(MCPWM_InitStruct->CH0N_SCTRLN << 4) |
                       (u32)(MCPWM_InitStruct->CH1P_SCTRLP << 13) |
                       (u32)(MCPWM_InitStruct->CH1N_SCTRLN << 12) |
                       (u32)(MCPWM_InitStruct->CH0_PS << 3) |
                       (u32)(MCPWM_InitStruct->CH0_NS << 2) |
                       (u32)(MCPWM_InitStruct->CH1_PS << 11) |
                       (u32)(MCPWM_InitStruct->CH1_NS << 10);

    MCPWMx->PWM_IO23 = (u32)MCPWM_InitStruct->CH2N_Polarity_INV |
                       (u32)(MCPWM_InitStruct->CH2P_Polarity_INV << 1) |
                       (u32)(MCPWM_InitStruct->Switch_CH2N_CH2P << 6) |
                       (u32)(MCPWM_InitStruct->MCPWM_WorkModeCH2 << 7) |
                       (u32)(MCPWM_InitStruct->CH3N_Polarity_INV << 8) |
                       (u32)(MCPWM_InitStruct->CH3P_Polarity_INV << 9) |
                       (u32)(MCPWM_InitStruct->Switch_CH3N_CH3P << 14) |
                       (u32)(MCPWM_InitStruct->MCPWM_WorkModeCH3 << 15) |
                       (u32)(MCPWM_InitStruct->CH2P_SCTRLP << 5) |
                       (u32)(MCPWM_InitStruct->CH2N_SCTRLN << 4) |
                       (u32)(MCPWM_InitStruct->CH2_PS << 3) |
                       (u32)(MCPWM_InitStruct->CH2_NS << 2) |
                       (u32)(MCPWM_InitStruct->CH3_PS << 11) |
                       (u32)(MCPWM_InitStruct->CH3_NS << 10);

    MCPWMx->PWM_FAIL012 = (u32)MCPWM_InitStruct->FAIL0_Signal_Sel |
                          (u32)(MCPWM_InitStruct->FAIL0_Polarity << 2) |
                          (u32)(MCPWM_InitStruct->FAIL0_INPUT_EN << 4) |
                          (u32)(MCPWM_InitStruct->FAIL1_INPUT_EN << 5) |
                          (u32)(MCPWM_InitStruct->FAIL1_Signal_Sel << 1) |
                          (u32)(MCPWM_InitStruct->FAIL1_Polarity << 3) |
                          (u32)(MCPWM_InitStruct->DebugMode_PWM_out << 7) |
                          (u32)(MCPWM_InitStruct->CH0N_default_output << 8) |
                          (u32)(MCPWM_InitStruct->CH0P_default_output << 9) |
                          (u32)(MCPWM_InitStruct->CH1N_default_output << 10) |
                          (u32)(MCPWM_InitStruct->CH1P_default_output << 11) |
                          (u32)(MCPWM_InitStruct->CH2N_default_output << 12) |
                          (u32)(MCPWM_InitStruct->CH2P_default_output << 13);

    MCPWMx->PWM_FAIL3 = (u32)MCPWM_InitStruct->FAIL2_Signal_Sel |
                        (u32)(MCPWM_InitStruct->FAIL2_Polarity << 2) |
                        (u32)(MCPWM_InitStruct->FAIL2_INPUT_EN << 4) |
                        (u32)(MCPWM_InitStruct->FAIL3_INPUT_EN << 5) |
                        (u32)(MCPWM_InitStruct->FAIL3_Signal_Sel << 1) |
                        (u32)(MCPWM_InitStruct->FAIL3_Polarity << 3) |
                        (u32)(MCPWM_InitStruct->DebugMode_PWM_out << 7) |
                        (u32)(MCPWM_InitStruct->CH3P_default_output << 8) |
                        (u32)(MCPWM_InitStruct->CH3N_default_output << 9);

    MCPWMx->PWM_SDCFG = (u32)MCPWM_InitStruct->MCPWM_UpdateT0Interval |
                        (u32)(MCPWM_InitStruct->MCPWM_Base0T0_UpdateEN << 4) |
                        (u32)(MCPWM_InitStruct->MCPWM_Base0T1_UpdateEN << 5) |
                        (u32)(MCPWM_InitStruct->MCPWM_Auto0_ERR_EN << 6) |
                        (u32)(MCPWM_InitStruct->MCPWM_UpdateT1Interval) << 8 |
                        (u32)(MCPWM_InitStruct->MCPWM_Base1T0_UpdateEN << 12) |
                        (u32)(MCPWM_InitStruct->MCPWM_Base1T1_UpdateEN << 13) |
                        (u32)(MCPWM_InitStruct->MCPWM_Auto1_ERR_EN << 14);

    MCPWMx->PWM_DTH0 = MCPWM_InitStruct->DeadTimeCH0123N;
    MCPWMx->PWM_DTH1 = MCPWM_InitStruct->DeadTimeCH0123P;

    MCPWMx->PWM_AUEN = MCPWM_InitStruct->AUEN;

    MCPWMx->PWM_EVT0 = MCPWM_InitStruct->TimeBase_TrigEvt0;
    MCPWMx->PWM_EVT1 = MCPWM_InitStruct->TimeBase_TrigEvt1;

    MCPWMx->PWM_CNT0 = (u32)MCPWM_InitStruct->TimeBase0Init_CNT;
    MCPWMx->PWM_CNT1 = (u32)MCPWM_InitStruct->TimeBase1Init_CNT;

    MCPWMx->PWM_IE0 = (u32)MCPWM_InitStruct->CNT0_T0_Update_INT_EN |
                      (u32)(MCPWM_InitStruct->CNT0_T1_Update_INT_EN << 1) |
                      (u32)(MCPWM_InitStruct->CNT0_Update_TH00_EN << 2) |
                      (u32)(MCPWM_InitStruct->CNT0_Update_TH01_EN << 3) |
                      (u32)(MCPWM_InitStruct->CNT0_Update_TH10_EN << 4) |
                      (u32)(MCPWM_InitStruct->CNT0_Update_TH11_EN << 5) |
                      (u32)(MCPWM_InitStruct->CNT0_Update_TH20_EN << 6) |
                      (u32)(MCPWM_InitStruct->CNT0_Update_TH21_EN << 7) |
                      (u32)(MCPWM_InitStruct->CNT0_Update_TH30_EN << 8) |
                      (u32)(MCPWM_InitStruct->CNT0_Update_TH31_EN << 9) |
                      (u32)(MCPWM_InitStruct->CNT0_TMR0_Match_INT_EN << 10) |
                      (u32)(MCPWM_InitStruct->CNT0_TMR1_Match_INT_EN << 11) |
                      (u32)(MCPWM_InitStruct->CNT0_TMR2_Match_INT_EN << 12) |
                      (u32)(MCPWM_InitStruct->CNT0_TMR3_Match_INT_EN << 13) |
                      (u32)(MCPWM_InitStruct->CNT0_Update_EN << 14);
    MCPWMx->PWM_IE1 = (u32)MCPWM_InitStruct->CNT1_T0_Update_INT_EN |
                      (u32)(MCPWM_InitStruct->CNT1_T1_Update_INT_EN << 1) |
                      (u32)(MCPWM_InitStruct->CNT1_Update_TH30_EN << 8) |
                      (u32)(MCPWM_InitStruct->CNT1_Update_TH31_EN << 9) |
                      (u32)(MCPWM_InitStruct->CNT1_TMR2_Match_INT_EN << 12) |
                      (u32)(MCPWM_InitStruct->CNT1_TMR3_Match_INT_EN << 13) |
                      (u32)(MCPWM_InitStruct->CNT1_Update_EN << 14);

    MCPWMx->PWM_EIE = (u32)(MCPWM_InitStruct->FAIL0_INT_EN << 4) |
                      (u32)(MCPWM_InitStruct->FAIL1_INT_EN << 5) |
                      (u32)(MCPWM_InitStruct->FAIL2_INT_EN << 6) |
                      (u32)(MCPWM_InitStruct->FAIL3_INT_EN << 7);

    MCPWMx->PWM_RE = (u32)(MCPWM_InitStruct->TMR0_DMA_RE) |
                     (u32)(MCPWM_InitStruct->TMR1_DMA_RE << 1) |
                     (u32)(MCPWM_InitStruct->TMR2_DMA_RE << 2) |
                     (u32)(MCPWM_InitStruct->TMR3_DMA_RE << 3) |
                     (u32)(MCPWM_InitStruct->TR0_T0_DMA_RE << 4) |
                     (u32)(MCPWM_InitStruct->TR0_T1_DMA_RE << 5) |
                     (u32)(MCPWM_InitStruct->TR1_T0_DMA_RE << 6) |
                     (u32)(MCPWM_InitStruct->TR1_T1_DMA_RE << 7);

    MCPWMx->PWM_PP = MCPWM_InitStruct->IO_PPE;

    MCPWMx->PWM_UPDATE = 0xffff; /* write whatever value to trigger update */

    MCPWMx->PWM_IF0 = 0xffff;
    MCPWMx->PWM_IF1 = 0xffff;
    MCPWMx->PWM_EIF = 0xffff;

    MCPWMx->PWM_PRT = 0x0000CAFE; /* write any value other than 0xDEAD to enable write protection */
}

/*******************************************************************************
 函数名称：    void Predrive_Circuit(void)
 功能描述：    MCPWM通道连接预驱时交换
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：    芯片内部带预驱时使用
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2021/10/14   V1.0             HMG              创建
 *******************************************************************************/
void MCPWM_SwapFunction(void)
{
    MCPWM_PRT = 0x0000DEAD; /* 解除MCPWM 寄存器写保护*/
    MCPWM_SWAP = 0x67;      /* 开启芯片内部MCPWM通道转换顺序*/
    MCPWM_PRT = 0x0000CAFE; /* 开启MCPWM 寄存器写保护*/
}
/*******************************************************************************
 函数名称：    void MCPWM_Update(strPWM_DutyCycleDef *Duty)
 功能描述：    MCPWM更新比较门限值
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：    芯片内部带预驱时使用
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2021/10/14   V1.0             HMG              创建
 *******************************************************************************/
void MCPWM_Update(strPWM_DutyCycleDef *Duty)
{
    MCPWM_TH00 = Duty->th00;
    MCPWM_TH01 = Duty->th01;

    MCPWM_TH10 = Duty->th10;
    MCPWM_TH11 = Duty->th11;

    MCPWM_TH20 = Duty->th20;
    MCPWM_TH21 = Duty->th21;

    MCPWM_TH30 = Duty->th30;
    MCPWM_TH31 = Duty->th31;
}
/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
/*******************************************************************************
 函数名称：    u16 MCPWM_ReadIRQFlag(MCPWM_REG_TypeDef *MCPWMx, CNT_Num CNTx, u32 INT_flag)
 功能描述：    读MCPWM中断标志位
 操作的表：    无
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：    读标志位是否为1
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/04/20    V1.0            Zhu Jie           创建
 *******************************************************************************/
u16 MCPWM_ReadIRQFlag(MCPWM_REG_TypeDef *MCPWMx, CNT_Num CNTx, u32 INT_flag)
{
    u8 MCPWMIRQFlag = 0;
    if (INT_flag <= BIT14)
    {
        if (CNTx)
        {
            if (MCPWMx->PWM_IF1 & INT_flag)
            {
                MCPWMIRQFlag = 1;
            }
            else
            {
                MCPWMIRQFlag = 0;
            }
        }
        else
        {
            if (MCPWMx->PWM_IF0 & INT_flag)
            {
                MCPWMIRQFlag = 1;
            }
            else
            {
                MCPWMIRQFlag = 0;
            }
        }
    }
    else
    {

        if (MCPWMx->PWM_EIF & (INT_flag >> 15))
        {
            MCPWMIRQFlag = 1;
        }
        else
        {
            MCPWMIRQFlag = 0;
        }
    }
    return MCPWMIRQFlag;
}

/*******************************************************************************
 函数名称：    void MCPWM_ClearIRQFlag(MCPWM_REG_TypeDef *MCPWMx, CNT_Num CNTx, u16 INT_flag)
 功能描述：    清MCPWM中断标志位
 操作的表：    无
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：    读标志位是否为1
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/04/20    V1.0            Zhu Jie           创建
 *******************************************************************************/
void MCPWM_ClearIRQFlag(MCPWM_REG_TypeDef *MCPWMx, CNT_Num CNTx, u32 INT_flag)
{
    if (INT_flag <= BIT14)
    {
        if (CNTx)
        {
            MCPWMx->PWM_IF1 |= INT_flag;
        }
        else
        {
            MCPWMx->PWM_IF0 |= INT_flag;
        }
    }
    else
    {
        MCPWMx->PWM_EIF |= (INT_flag >> 15);
    }
}
