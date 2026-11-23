/*******************************************************************************
 * 版权所有 (C)2015, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： lks32mc03x_spi.c
 * 文件标识：
 * 内容摘要： SPI外设驱动程序
 * 其它说明： 无
 * 当前版本： V 1.0
 * 作    者： Yangzj
 * 完成日期： 21/11/10
 *
 *******************************************************************************/
#include "lks32mc03x_spi.h"

/*******************************************************************************
 函数名称：    void SPI_Init(SPI_TypeDef* SPIx, ESPI_InitTypeDef* SPI_InitStruct)
 功能描述：    SPI初始化
 操作的表：    无
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2021/11/10    V1.0           YangZJ            创建
 *******************************************************************************/
void SPI_Init(SPI_TypeDef *SPIx, SPI_InitTypeDef *SPI_InitStruct)
{
    SYS_ModuleClockCmd(SYS_Module_SPI, ENABLE);
    SPIx->CFG = 0;
    SPIx->IE = (u32)(SPI_InitStruct->TRANS_TRIG << 3) |
               (u32)(SPI_InitStruct->IRQEna);
    SPIx->BAUD = (u32)(SPI_InitStruct->BAUD) |
                 (u32)(SPI_InitStruct->TRANS_MODE << 7);
    SPIx->SIZE = (u32)SPI_InitStruct->BITSIZE;
    SPIx->CFG = (u32)(SPI_InitStruct->EN) |
                (u32)(SPI_InitStruct->ENDIAN << 1) |
                (u32)(SPI_InitStruct->CPOL << 2) |
                (u32)(SPI_InitStruct->CPHA << 3) |
                (u32)(SPI_InitStruct->Mode << 4) |
                (u32)(SPI_InitStruct->CS << 5) |
                (u32)(SPI_InitStruct->Duplex << 6);
}

/*******************************************************************************
 函数名称：    void SPI_StructInit(SPI_InitTypeDef* SPI_InitStruct)
 功能描述：    SPI结构体初始化
 操作的表：    无
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2021/11/10    V1.0           YangZJ            创建
 *******************************************************************************/
void SPI_StructInit(SPI_InitTypeDef *SPI_InitStruct)
{

    SPI_InitStruct->Duplex = SPI_Full;
    SPI_InitStruct->CS = 0;
    SPI_InitStruct->Mode = SPI_Slave;
    SPI_InitStruct->CPOL = 0;
    SPI_InitStruct->CPHA = 0;
    SPI_InitStruct->ENDIAN = 0;
    SPI_InitStruct->EN = 0;

    SPI_InitStruct->IRQEna = DISABLE;
    SPI_InitStruct->TRANS_TRIG = 0;

    SPI_InitStruct->TRANS_MODE = 0;
    SPI_InitStruct->BAUD = 3;

    SPI_InitStruct->BITSIZE = 0;
}

/*******************************************************************************
 函数名称：    void SPI_SENDDATA(SPI_TypeDef *SPIx, uinu32
 功能描述：    SPI发送数据
 操作的表：    无
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2021/11/10    V1.0           YangZJ            创建
 *******************************************************************************/
void SPI_SendData(SPI_TypeDef *SPIx, u8 n)
{
    SPIx->TX_DATA = n;
}

/*******************************************************************************
 函数名称：    uinu32I_ReadData(SPI_TypeDef *SPIx)
 功能描述：    SPI读缓冲区数据
 操作的表：    无
 输入参数：    SPI_TypeDef *SPIx
 输出参数：    无
 返 回 值：    缓冲区数据
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2021/11/10    V1.0           YangZJ            创建
 *******************************************************************************/
u8 SPI_ReadData(SPI_TypeDef *SPIx)
{
    return (u8)SPIx->RX_DATA;
}

/*******************************************************************************
 函数名称：    uinu8I_GetIRQFlag(SPI_TypeDef *SPIx,u8 IRQ_Flag)
 功能描述：    取得SPI中断标志
 操作的表：    无
 输入参数：    SPI_InitTypeDef *SPIx:要操作的SPI对象
 输出参数：    无
 返 回 值：    SPI中断标志
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/04/20    V1.0            Zhu Jie          创建
 *******************************************************************************/
u8 SPI_GetIRQFlag(SPI_TypeDef *SPIx, u8 IRQ_Flag)
{
    u8 SPI_IRQFlag = 0;
    if (SPIx->IE & IRQ_Flag)
    {
        SPI_IRQFlag = 1;
    }
    else
    {
        SPI_IRQFlag = 0;
    }
    return SPI_IRQFlag;
}

/*******************************************************************************
 函数名称：    void SPI_ClearIRQFlag(SPI_TypeDef *SPIx,u8 IRQ_Flag)
 功能描述：    SPI中断标志位清零
 操作的表：    无
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：    写1清零
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/04/20    V1.0            Zhu Jie          创建
 *******************************************************************************/
void SPI_ClearIRQFlag(SPI_TypeDef *SPIx, u8 IRQ_Flag)
{
    SPIx->IE |= IRQ_Flag;
}
/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
