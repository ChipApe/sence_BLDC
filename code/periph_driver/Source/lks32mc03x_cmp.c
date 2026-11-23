/*******************************************************************************
 * 版权所有 (C)2015, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： lks32mc03x_cmp.c
 * 文件标识：
 * 其它说明： 无
 * 当前版本： V 1.0
 * 作    者： YangZJ
 * 完成日期： 2021年11月09日
 *
 *******************************************************************************/
#include "lks32mc03x_cmp.h"
void CMP_INIT_REF(void);
u8 GET_CMP_data(u8 CMPx, u8 GET_CMP_val);

/*******************************************************************************
 函数名称：    void CMP_INIT_REF(void)
 功能描述：    比较器配置参考
 输入参数：    无
 返 回 值：    无
 其它说明：    该程序仅供参考，不建议修改和调用
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/04/13    V1.0           Yangzj            创建
*******************************************************************************/
void CMP_INIT_REF(void)
{
    CMP_InitTypeDef CMP_InitStruct;
    CMP_StructInit(&CMP_InitStruct);
    CMP_InitStruct.CLK10_EN = DISABLE;  // 比较器 1/0 滤波时钟使能
    CMP_InitStruct.FIL_CLK10_DIV16 = 0; // 比较器 1/0 滤波系数       0-0xF
    CMP_InitStruct.FIL_CLK10_DIV2 = 0;  // 比较器 1/0 滤波移位系数   0-0x7   最终分频系数为 (DIV16+1)<<DIV2
    CMP_InitStruct.CMP_FT = DISABLE;    // 比较器快速比较使能
    CMP_InitStruct.CMP_HYS = 0;         // 比较器回差选择            0：回差20mV 1：回差0mV

    CMP_InitStruct.CMP1_SELP = CMP_SELP_IP0;    // 比较器 1 信号正端选择 见 CMP1_SELP_CMP1_IP0 比较器定义
    CMP_InitStruct.CMP1_SELN = CMP_SELN_IN;     // 比较器 1 信号负端选择
    CMP_InitStruct.CMP1_POL = 0;                // 比较器 1 极性选择     0：高电平有效 1：低电平有效 只影响比较器中断
    CMP_InitStruct.CMP1_IE = DISABLE;           // 比较器 1 中断使能
    CMP_InitStruct.CMP1_RE = DISABLE;           // 比较器 1 DMA 请求使能
    CMP_InitStruct.CMP1_IRQ_TRIG = DISABLE;     // 比较器 1 边沿触发使能
    CMP_InitStruct.CMP1_IN_EN = DISABLE;        // 比较器 1 信号输入使能 影响比较器数字模块信号，模拟部分不受影响
    CMP_InitStruct.CMP1_CHN3P_WIN_EN = DISABLE; // MCPWM 模块 CHN3_P 通道使能比较器 1 开窗
    CMP_InitStruct.CMP1_CHN2P_WIN_EN = DISABLE; // MCPWM 模块 CHN2_P 通道使能比较器 1 开窗
    CMP_InitStruct.CMP1_CHN1P_WIN_EN = DISABLE; // MCPWM 模块 CHN1_P 通道使能比较器 1 开窗
    CMP_InitStruct.CMP1_CHN0P_WIN_EN = DISABLE; // MCPWM 模块 CHN0_P 通道使能比较器 1 开窗
    CMP_InitStruct.CMP1_W_PWM_POL = DISABLE;    // 比较器 1 开窗 PWM 信号极性选择  0:高电平有效；1:低电平有效

    CMP_InitStruct.CMP0_SELP = CMP_SELP_IP0;    // 比较器 0 信号正端选择
    CMP_InitStruct.CMP0_SELN = CMP_SELN_IN;     // 比较器 0 信号负端选择
    CMP_InitStruct.CMP0_POL = 0;                // 比较器 0 极性选择     0：高电平有效 1：低电平有效 只影响比较器中断
    CMP_InitStruct.CMP0_IE = DISABLE;           // 比较器 0 中断使能
    CMP_InitStruct.CMP0_RE = DISABLE;           // 比较器 0 DMA 请求使能
    CMP_InitStruct.CMP0_W_PWM_POL = DISABLE;    // 比较器 0 开窗 PWM 信号极性选择
    CMP_InitStruct.CMP0_IRQ_TRIG = DISABLE;     // 比较器 0 边沿触发使能
    CMP_InitStruct.CMP0_IN_EN = DISABLE;        // 比较器 0 信号输入使能
    CMP_InitStruct.CMP0_CHN3P_WIN_EN = DISABLE; // MCPWM 模块 CHN3_P 通道使能比较器 0 开窗
    CMP_InitStruct.CMP0_CHN2P_WIN_EN = DISABLE; // MCPWM 模块 CHN2_P 通道使能比较器 0 开窗
    CMP_InitStruct.CMP0_CHN1P_WIN_EN = DISABLE; // MCPWM 模块 CHN1_P 通道使能比较器 0 开窗
    CMP_InitStruct.CMP0_CHN0P_WIN_EN = DISABLE; // MCPWM 模块 CHN0_P 通道使能比较器 0 开窗
    CMP_Init(&CMP_InitStruct);
}
/*******************************************************************************
 函数名称：    void cmp_Init(CMP_InitTypeDef *this)
 功能描述：    比较器初始化
 输入参数：    this：I2C配置结构体
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2021/11/10    V1.0           Yangzj            创建
 2021/11/17    V1.1           Yangzj            增加CMP信号来源选择
 2022/04/25    V1.2           Yangzj            修改模块使能
 2022/04/26    V1.3           Yangzj            修复滤波配置
*******************************************************************************/
void CMP_Init(CMP_InitTypeDef *this)
{
    // Comparator初始化
    SYS_WR_PROTECT = 0x7A83;
    SYS_AFE_REG1 = (u32)(SYS_AFE_REG1 & (BIT15 | BIT6 | BIT1 | BIT0)) |
                   (u32)(this->CMP1_SELP << 12) |
                   (u32)(this->CMP_FT << 11) |
                   (u32)(this->CMP0_SELP << 8) |
                   (u32)(this->CMP_HYS << 7) |
                   (u32)(this->CMP1_SELN << 4) |
                   (u32)(this->CMP0_SELN << 2);
    SYS_WR_PROTECT = 0;
    SYS_AnalogModuleClockCmd(SYS_AnalogModule_CMP1, this->CMP1_EN);
    SYS_AnalogModuleClockCmd(SYS_AnalogModule_CMP0, this->CMP0_EN);

    // CMP初始化
    if (this->CMP1_IN_EN || this->CMP0_IN_EN)
    {
        SYS_ModuleClockCmd(SYS_Module_CMP, ENABLE);
    }
    else
    {
        SYS_ModuleClockCmd(SYS_Module_CMP, DISABLE);
    }
    CMP->IE = (u32)(this->CMP1_RE << 9) |
              (u32)(this->CMP0_RE << 8) |
              (u32)(this->CMP1_IE << 1) |
              (u32)(this->CMP0_IE);
    if (this->CLK10_EN == DISABLE)
    {
        if (this->CMP1_IN_EN || this->CMP0_IN_EN)
        {
            CMP->TCLK = BIT3;
        }
        else
        {
            CMP->TCLK = 0;
        }
    }
    else
    {
        CMP->TCLK = (u32)(this->FIL_CLK10_DIV16 << 4) |
                    (u32)(this->CLK10_EN << 3) |
                    (u32)(this->FIL_CLK10_DIV2);
    }
    CMP->CFG = (u32)(this->CMP1_W_PWM_POL << 7) |
               (u32)(this->CMP1_IRQ_TRIG << 6) |
               (u32)(this->CMP1_IN_EN << 5) |
               (u32)(this->CMP1_POL << 4) |
               (u32)(this->CMP0_W_PWM_POL << 3) |
               (u32)(this->CMP0_IRQ_TRIG << 2) |
               (u32)(this->CMP0_IN_EN << 1) |
               (u32)(this->CMP0_POL);
    CMP->BLCWIN = (u32)(this->CMP1_CHN3P_WIN_EN << 7) |
                  (u32)(this->CMP1_CHN2P_WIN_EN << 6) |
                  (u32)(this->CMP1_CHN1P_WIN_EN << 5) |
                  (u32)(this->CMP1_CHN0P_WIN_EN << 4) |
                  (u32)(this->CMP0_CHN3P_WIN_EN << 3) |
                  (u32)(this->CMP0_CHN2P_WIN_EN << 2) |
                  (u32)(this->CMP0_CHN1P_WIN_EN << 1) |
                  (u32)(this->CMP0_CHN0P_WIN_EN);
    CMP->IF = 3;
}
/*******************************************************************************
 函数名称：    void CMP_StructInit(CMP_InitTypeDef *this)
 功能描述：    CMP配置结构体初始化
 输入参数：    this CMP配置结构体
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2021/11/10    V1.0           Yangzj            创建
 2021/11/17    V1.1           Yangzj            增加CMP信号来源初始化
*******************************************************************************/
void CMP_StructInit(CMP_InitTypeDef *this)
{
    // 比较器IO滤波
    this->FIL_CLK10_DIV16 = 0;    // 比较器 1/0 滤波
    this->CLK10_EN = ENABLE;      // 比较器 1/0 滤波时钟使能
    this->FIL_CLK10_DIV2 = 0;     // 比较器 1/0 滤波时钟分频
    this->CMP_FT = ENABLE;        // 比较器快速比较使能
    this->CMP_HYS = CMP_HYS_20mV; // 比较器回差选择

    //比较器1
    this->CMP1_EN = DISABLE;           // 比较器 0 使能
    this->CMP1_IE = DISABLE;           // 比较器 1 中断使能
    this->CMP1_RE = DISABLE;           // 比较器 1 DMA 请求使能
    this->CMP1_W_PWM_POL = 0;          // 比较器 1 开窗 PWM 信号极性选择
    this->CMP1_IRQ_TRIG = DISABLE;     // 比较器 1 边沿触发使能
    this->CMP1_IN_EN = DISABLE;        // 比较器 1 信号输入使能
    this->CMP1_POL = 0;                // 比较器 1 极性选择
    this->CMP1_SELP = CMP_SELP_IP0;    // 比较器 1 信号正端选择
    this->CMP1_SELN = CMP_SELN_IN;     // 比较器 1 信号负端选择
    this->CMP1_CHN3P_WIN_EN = DISABLE; // MCPWM 模块 CHN3_P 通道使能比较器 1 开窗
    this->CMP1_CHN2P_WIN_EN = DISABLE; // MCPWM 模块 CHN2_P 通道使能比较器 1 开窗
    this->CMP1_CHN1P_WIN_EN = DISABLE; // MCPWM 模块 CHN1_P 通道使能比较器 1 开窗
    this->CMP1_CHN0P_WIN_EN = DISABLE; // MCPWM 模块 CHN0_P 通道使能比较器 1 开窗

    //比较器0
    this->CMP0_EN = DISABLE;           // 比较器 0 使能
    this->CMP0_IE = DISABLE;           // 比较器 0 中断使能
    this->CMP0_RE = DISABLE;           // 比较器 0 DMA 请求使能
    this->CMP0_W_PWM_POL = 0;          // 比较器 1 开窗 PWM 信号极性选择
    this->CMP0_IRQ_TRIG = DISABLE;     // 比较器 1 边沿触发使能
    this->CMP0_IN_EN = DISABLE;        // 比较器 1 信号输入使能
    this->CMP0_POL = 0;                // 比较器 1 极性选择
    this->CMP0_SELP = CMP_SELP_IP0;    // 比较器 0 信号正端选择
    this->CMP0_SELN = CMP_SELN_IN;     // 比较器 0 信号负端选择
    this->CMP0_CHN3P_WIN_EN = DISABLE; // MCPWM 模块 CHN3_P 通道使能比较器 0 开窗
    this->CMP0_CHN2P_WIN_EN = DISABLE; // MCPWM 模块 CHN2_P 通道使能比较器 0 开窗
    this->CMP0_CHN1P_WIN_EN = DISABLE; // MCPWM 模块 CHN1_P 通道使能比较器 0 开窗
    this->CMP0_CHN0P_WIN_EN = DISABLE; // MCPWM 模块 CHN0_P 通道使能比较器 0 开窗
}
u8 GET_CMP_data(u8 CMPx, u8 GET_CMP_val)
{
    if (CMPx == 0)
    {
        if (GET_CMP_val)
        {
            if (CMP->DATA & BIT9)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
        else
        {
            if (CMP->DATA & BIT1)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
    }
    else
    {
        if (GET_CMP_val)
        {
            if (CMP->DATA & BIT8)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
        else
        {
            if (CMP->DATA & BIT0)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
    }
}
/*******************************************************************************
 函数名称：    u8 CMP_GetIRQFlag(u8 CMPx)
 功能描述：    读取比较器中断
 操作的表：    无
 输入参数：    无
 输出参数：    无
 返 回 值：    TIM中断标志
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/04/21    V1.0           Yangzj            创建
 *******************************************************************************/
u8 CMP_GetIRQFlag(u8 CMPx)
{
    if (CMPx == CMP0)
    {
        if (CMP_IF & BIT0)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    else if (CMPx == CMP1)
    {
        if (CMP_IF & BIT1)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    return 0;
}

/*******************************************************************************
 函数名称：    void CMP_ClearIRQFlag(u8 CMPx)
 功能描述：    清除TIM中断标志
 操作的表：    无
 输入参数：    TIM中断标志
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/04/11      V1.0         HuangMG             创建
 *******************************************************************************/
void CMP_ClearIRQFlag(u8 CMPx)
{
    if (CMPx == CMP0)
    {
        CMP_IF = BIT0;
    }
    else if (CMPx == CMP1)
    {
        CMP_IF = BIT1;
    }
}

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
