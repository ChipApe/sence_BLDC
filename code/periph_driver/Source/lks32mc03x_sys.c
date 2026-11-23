/*******************************************************************************
 * 版权所有 (C)2015, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： lks32mc03x_sys.c
 * 文件标识：
 * 内容摘要： SYS外设驱动程序
 * 其它说明： 无
 * 当前版本： V 1.0
 * 作    者： YangZJ
 * 完成日期： 2021年11月09日
 *
 *******************************************************************************/
#include "lks32mc03x_sys.h"

static WAKE_InitTypeDef WAKE_InitStruct;

/*******************************************************************************
 函数名称：    void SYS_Init(SYS_InitTypeDef* SYS_InitStruct)
 功能描述：    SYS模块初始化函数
 操作的表：    无
 输入参数：    SYS_InitTypeDef* SYS_InitStruct
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2021/11/10    V1.0           Yangzj              创建
 *******************************************************************************/
void SYS_Init(SYS_InitTypeDef *SYS_InitStruct)
{
    u32 tmp1;

    SYS_WR_PROTECT = 0x7A83; //解除系统寄存器写保护
    tmp1 = SYS_AFE_REG0;
    tmp1 &= 0x7FFF;
    tmp1 |= (SYS_InitStruct->PLL_SrcSel << 15);
    SYS_AFE_REG0 = tmp1;
    SYS_CLK_CFG = SYS_InitStruct->PLL_DivSel + (SYS_InitStruct->PLL_ReDiv << 8);

    SYS_CLK_DIV0 = SYS_InitStruct->Clk_DivI2C;
    SYS_CLK_DIV2 = SYS_InitStruct->Clk_DivUART;
    SYS_CLK_FEN = SYS_InitStruct->Clk_FEN;
    SYS_WR_PROTECT = 0;
}

/*******************************************************************************
 函数名称：    void SYS_StructInit(SYS_InitTypeDef* SYS_InitStruct)
 功能描述：    SYS结构体初始化
 操作的表：    无
 输入参数：    SYS_InitTypeDef* SYS_InitStruct
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2021/11/10    V1.0           YangZJ              创建
 *******************************************************************************/
void SYS_StructInit(SYS_InitTypeDef *SYS_InitStruct)
{
    SYS_InitStruct->PLL_SrcSel = SYS_PLLSRSEL_RCH;
    SYS_InitStruct->PLL_DivSel = 0xFF;
    SYS_InitStruct->PLL_ReDiv = SYS_PLLREDIV_1;

    SYS_InitStruct->Clk_DivI2C = SYS_Clk_SPIDiv1;
    SYS_InitStruct->Clk_DivUART = SYS_Clk_UARTDiv1;
    SYS_InitStruct->Clk_FEN = 0;
}

/*******************************************************************************
 函数名称：    void SYS_ClearRst(void)
 功能描述：    SYS清除复位标志
 操作的表：    无
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：    由于复位记录工作于低速时钟域，清除执行完成需要一定时间，不应清除后立即读记录状态
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2021/11/10    V1.0           YangZJ              创建
 *******************************************************************************/
void SYS_ClearRst(void)
{
    AON_EVT_RCD = 0xCA40;
}

/*******************************************************************************
 函数名称：    u32 SYS_GetRstSource(void)
 功能描述：    获得SYS复位源信号
 操作的表：    无
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2021/11/10    V1.0           YangZJ              创建
 *******************************************************************************/
u32 SYS_GetRstSource(void)
{
    return AON_EVT_RCD;
}

/*******************************************************************************
 函数名称：    void SYS_ModuleClockCmd(u32 nModule, FuncState state)
 功能描述：    模块时钟使能和停止
 操作的表：    无
 输入参数：    u32 nModule：对应的模块
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2021/11/10    V1.0           YangZJ              创建
 *******************************************************************************/
void SYS_ModuleClockCmd(u32 nModule, FuncState state)
{
    SYS_WR_PROTECT = 0x7A83; //解除系统寄存器写保护
    if (state != DISABLE)
    {
        SYS_CLK_FEN |= nModule;
    }
    else
    {
        SYS_CLK_FEN &= ~nModule;
    }
    SYS_WR_PROTECT = 0;
}

/*******************************************************************************
 函数名称：    void SYS_AnalogModuleClockCmd(u32 nModule, FuncState state)
 功能描述：    模拟模块使能和停止
 操作的表：    无
 输入参数：    u32 nModule：对应的模块
 输出参数：    无
 返 回 值：    无
 其它说明：    模拟部分时钟是使能：PGA、ADC、DAC
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2021/11/10    V1.0           YangZJ              创建
 *******************************************************************************/
void SYS_AnalogModuleClockCmd(u32 nModule, FuncState state)
{
    SYS_WR_PROTECT = 0x7A83; //解除系统寄存器写保护

    if (state == ENABLE)
    {
        if (nModule & SYS_AnalogModule_BGP)
        { // BGP与其他模块极性相反
            SYS_AFE_REG0 &= ~SYS_AnalogModule_BGP;
            nModule &= ~SYS_AnalogModule_BGP;
        }
        SYS_AFE_REG0 |= nModule;
    }
    else
    {
        if (nModule & SYS_AnalogModule_BGP)
        { // BGP与其他模块极性相反
            SYS_AFE_REG0 |= SYS_AnalogModule_BGP;
            nModule |= SYS_AnalogModule_BGP;
        }
        SYS_AFE_REG0 &= ~nModule;
    }
    SYS_WR_PROTECT = 0;
}

/*******************************************************************************
 函数名称：    void SYS_SoftResetModule(u32 nModule)
 功能描述：    模块软复位
 操作的表：    无
 输入参数：    u32 nModule：对应的模块
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2021/11/10    V1.0           Yangzj              创建
 *******************************************************************************/
void SYS_SoftResetModule(u32 nModule)
{
    SYS_WR_PROTECT = 0x7A83; //解除系统寄存器写保护
    SYS_SFT_RST = nModule;
    SYS_SFT_RST = 0;
    SYS_WR_PROTECT = 0;
}

/*******************************************************************************
 函数名称：    void SYS_VolSelModule(u32 Vol)
 功能描述：    时钟校正函数
 操作的表：    无
 输入参数：    Vol的值为0，代表当前的系统工作电压为3.3V，函数将加载3.3V下的时钟校准参数。
              Vol的值为1，代表当前的系统工作电压为5.0V，函数将加载5.0V下的时钟校准参数。
              系统上电后，默认加载的是5.0V的时钟校准参数。
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/3/24     V1.0           HuangMG              创建
*******************************************************************************/
void SYS_VolSelModule(u32 Vol)
{
    if ((Read_Trim(0x000001D4) >> 16) >= 0x03)
    {
        if (Vol == 0) // 3.3 Voltage
        {

            SYS_AFE_REG5 = (Read_Trim(0x00000198) >> 16) & 0xffff;

            SYS_AFE_REG6 = (Read_Trim(0x0000019C) >> 16) & 0xffff;
        }

        else // 5.0 Voltage
        {

            SYS_AFE_REG5 = Read_Trim(0x00000198) & 0xffff;

            SYS_AFE_REG6 = Read_Trim(0x0000019C) & 0xffff;
        }
    }
}

/*******************************************************************************
 函数名称：    void SoftDelay(void)
 功能描述：    延时函数
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/4/14     V1.0           HuangMG            创建
 *******************************************************************************/
static void SoftDelay(u32 cnt)
{
    volatile u32 t_cnt;
    for (t_cnt = 0; t_cnt < cnt; t_cnt++)
    {
        __NOP();
    }
}

/*******************************************************************************
 函数名称：    void Switch2PLL(void)
 功能描述：    休眠唤醒后，系统时钟切换到PLL时钟函数
 操作的表：    无
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：    无
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/4/26      V1.0          HuangMG            创建
 *******************************************************************************/
void Switch2PLL(void)
{
    SYS_WR_PROTECT = 0x7a83;                        /*开启寄存器写使能*/
    SYS_AFE_REG0 = WAKE_InitStruct.AFE_REG0_RECORD; /*开启 PLL,BGP*/
    SoftDelay(200);
    SYS_CLK_CFG = WAKE_InitStruct.CLK_CFG_RECORD; /*将主时钟切换到PLL时钟*/
    SYS_WR_PROTECT = 0x0;
}

/*******************************************************************************
 函数名称：    void Switch2HRC(void)
 功能描述：    休眠唤醒前一时刻，系统时钟切换到HRC时钟函数
 操作的表：    无
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：    无
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/4/26      V1.0          HuangMG            创建
 *******************************************************************************/
void Switch2HRC(void)
{
    SYS_WR_PROTECT = 0x7a83; /*开启寄存器写使能*/
    WAKE_InitStruct.AFE_REG0_RECORD = SYS_AFE_REG0;
    WAKE_InitStruct.CLK_CFG_RECORD = SYS_CLK_CFG;
    SYS_CLK_CFG = 0;       /* 切换到HRC时钟*/
    SYS_AFE_REG0 = 0x0400; /* 准备关闭 PLL,BGP*/
    SYS_WR_PROTECT = 0x0;
}

/*******************************************************************************
 函数名称：    void SetWakeIO(u32 wakeIO, enumWakeTrigLevel trigLevel, u32 flt , bool ena)
 功能描述：    设置休眠唤醒IO
 操作的表：    无
 输入参数：     wakeIO:
               wakeIO = BIT5: GPIO 1[5]  / P1[5]  外部唤醒使能。1：使能；0：禁用。
                     wakeIO = BIT4: GPIO 0[10] / P0[10] 外部唤醒使能。1：使能；0：禁用。
               wakeIO = BIT3: GPIO 0[9]  / P0[9]  外部唤醒使能。1：使能；0：禁用。
                     wakeIO = BIT2: GPIO 0[8]  / P0[8]  外部唤醒使能。1：使能；0：禁用。
                     wakeIO = BIT1: GPIO 0[2]  / P0[2]  外部唤醒使能。1：使能；0：禁用。
                     wakeIO = BIT0: GPIO 0[0]  / P0[0]  外部唤醒使能。1：使能；0：禁用。
                     trigLevel:唤醒电平选择：0、低电平唤醒，1:高电平唤醒
                     flt:ENABLE：开启IO滤波 DISABLE：关闭IO滤波
               ena:ENABLE： 开启IO唤醒  DISABLE：关闭IO唤醒

 输出参数：    无
 返 回 值：    无
 其它说明：    IO唤醒信号滤波默认使能
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/4/26     V1.0           HuangMG            创建
 *******************************************************************************/
void SetWakeIO(u32 wakeIO, enumWakeTrigLevel trigLevel, u32 flt, bool ena)
{
    if (ena == ENABLE)
    {
        AON_IO_WAKE_EN |= wakeIO;
    }
    else
    {
        AON_IO_WAKE_EN &= ~wakeIO;
    }

    if (trigLevel == WAKETRIG_HIGH)
    {
        AON_IO_WAKE_POL = 0x01;
    }
    else
    {
        AON_IO_WAKE_POL = 0x00;
    }

    if (flt == IOWK_FLT_EN)
    {
        AON_PWR_CFG = BIT1;
    }
    else
    {
        AON_PWR_CFG = 0;
    }
}

/*******************************************************************************
 函数名称：    void SYS_FallSleep(void)
 功能描述：    触发系统进入休眠状态
 操作的表：    无
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：    无
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/4/26     V1.0           HuangMG            创建
 *******************************************************************************/
void SYS_FallSleep(void)
{
    IWDG_PSW = 0xA6B4;
    IWDG_CLR = 0x798D;
    SCB->SCR |= (1UL << 2);
    __WFI(); /*PC指针停止运行，等待中断*/
}

/*******************************************************************************
 函数名称：    void SYS_EVTCLRSleep(void)
 功能描述：    清除休眠全部事件记录
 操作的表：    无
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：    无
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/4/26     V1.0           HuangMG            创建
 *******************************************************************************/
void SYS_EVTCLRSleep(void)
{
    AON_EVT_RCD = PSW_EVT_CLR; /* 清除全部事件记录*/
}

/*******************************************************************************
 函数名称：    void SYS_SetWakeInterval(u32 nInterval)
 功能描述：    设置休眠唤醒周期
 操作的表：    无
 输入参数：    rth：看门狗超时复位门限值，也是重新装载值(最大值0x1FF000)。
              wth：看门狗定时唤醒门限值(最大值小于rth)
              ena:ENABLE：开启定时唤醒  DISABLE：关闭定时唤醒
 输出参数：    无
 返 回 值：    无
 其它说明：    唤醒时间计算公式：
              WakeupIWDG = tLRC * (rth - Iwth)
              tLRC 为 LRC时钟周期，1/64kHz=15.625uS
              rth - wth    唤醒时间
                 16000        0.25S
                 32000        0.5S
                 64000        1S
                 128000       2S
                 256000       4S

 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/4/26     V1.0           HuangMG            创建
 *******************************************************************************/
void SYS_SetWakeInterval(u32 rth, u32 wth, bool ena)
{
    if (ena == ENABLE)
    {
        IWDG_CFG |= (u32)(0x01 << 4); /*深度休眠定时唤醒使能*/
    }
    else
    {
        IWDG_CFG &= (u32)(~(0x01 << 4)); /*关闭深度休眠定时唤醒*/
    }
    IWDG_PSW = 0xA6B4; /*使能看门狗部分寄存器写操作*/
    IWDG_RTH = rth;
    IWDG_WTH = wth;
}

/*******************************************************************************
 函数名称：    void DSP_Init(void)
 功能描述：    DSP时钟使能
 操作的表：    无
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2016/6/28      V1.0           cfwu          创建
 *******************************************************************************/
void DSP_Init(void)
{
    SYS_ModuleClockCmd(SYS_Module_DSP, ENABLE); /* DSP时钟使能*/
}
/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
