/*******************************************************************************
 * 版权所有 (C)2015, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： LKS32MC03x_DMA.c
 * 文件标识：
 * 其它说明： 无
 * 当前版本： V 1.0
 * 作    者： Yangzj
 * 完成日期： 2021年10月14日
 *
 *******************************************************************************/
#include "lks32mc03x_dma.h"
#include "string.h"

/*******************************************************************************
 函数名称：    void DMA_StructInit(DMA_InitTypeDef *DMAInitStruct)
 功能描述：    DMA结构体初始化
 操作的表：    无
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2021.10.14      V1.0           Yangzj              创建
 *******************************************************************************/
void DMA_StructInit(DMA_InitTypeDef *DMAInitStruct)
{
    memset(DMAInitStruct, 0, sizeof(DMA_InitTypeDef));
}

/*******************************************************************************
 函数名称：    void DMA_Init(DMA_RegTypeDef *DMAx, DMA_InitTypeDef *DMAInitStruct)
 功能描述：    DMA初始化
 操作的表：    无
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2021.10.14      V1.0           Yangzj              创建
 *******************************************************************************/
void DMA_Init(DMA_RegTypeDef *DMAx, DMA_InitTypeDef *DMAInitStruct)
{
    /* 通道配置寄存器 赋值*/
    DMAx->DMA_CCR = 0;
    DMAx->DMA_SADR = DMAInitStruct->DMA_SADR; /* 外设地址寄存器 */
    DMAx->DMA_DADR = DMAInitStruct->DMA_DADR; /* 内存地址寄存器 */
    DMAx->DMA_REN = DMAInitStruct->DMA_REQ_EN;
    DMAx->DMA_CCR = (u32)(DMAInitStruct->DMA_SBTW << 10) |
                    (u32)(DMAInitStruct->DMA_DBTW << 8) |
                    (u32)(DMAInitStruct->DMA_SINC << 6) |
                    (u32)(DMAInitStruct->DMA_DINC << 4) |
                    (u32)(DMAInitStruct->DMA_CIRC << 3) |
                    (u32)(DMAInitStruct->DMA_RMODE << 1);

    if (DMAInitStruct->DMA_IRQ_EN)
        switch ((u32)DMAx)
        {
        case (u32)DMA_BASE:
            DMA_IE |= BIT0;
            break;
        case (u32)DMA_BASE + 0x20:
            DMA_IE |= BIT1;
            break;
        case (u32)DMA_BASE + 0x40:
            DMA_IE |= BIT2;
            break;
        case (u32)DMA_BASE + 0x60:
            DMA_IE |= BIT3;
            break;
        }
    DMA_CTRL = 0x0001; /*DMA整体使能*/
}

/*******************************************************************************
 函数名称：    void CAN_CHx_EN(DMA_RegTypeDef *DMAx,u32 Channel_EN)
 功能描述：    使能DMA通道
 操作的表：    无
 输入参数：    DMAx：DMA通道选择
              Channel_EN：ENABLE：使能DMA通道，DISABLE：关闭DMA通道使能
              set： DMA通道 x 数据搬运轮数或次数1~255
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/4/13      V1.0           HuangMG            创建
 *******************************************************************************/
void DMA_CHx_EN(DMA_RegTypeDef *DMAx, u32 Channel_EN, u32 set)
{
    DMAx->DMA_CCR &= ~BIT0; /*关闭通道使能*/
    DMAx->DMA_CTMS = set;   /*配置DMA搬运轮数或次数*/
    if (Channel_EN)
    {
        DMAx->DMA_CCR |= BIT0; /*使能DMA搬运*/
    }
}

/*******************************************************************************
 函数名称：    u32 DMA_GetIRQFlag(u32 timer_if)
 功能描述：    DMA中断标志
 操作的表：    无
 输入参数：    无
 输出参数：    无
 返 回 值：    DMA中断标志
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/4/13      V1.0           HuangMG            创建
 *******************************************************************************/
u32 DMA_GetIRQFlag(u32 timer_if)
{
    if (DMA_IF & timer_if && DMA_IE)
    {
        return 1;
    }
    return 0;
}

/*******************************************************************************
 函数名称：    void DMA_ClearIRQFlag(u32 tempFlag)
 功能描述：    清除DMA中断标志
 操作的表：    无
 输入参数：    DMA中断标志
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/4/13      V1.0           HuangMG            创建
 *******************************************************************************/
void DMA_ClearIRQFlag(u32 tempFlag)
{
    DMA_IF = tempFlag;
}

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
