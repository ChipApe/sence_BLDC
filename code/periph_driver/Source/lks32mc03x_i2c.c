/*******************************************************************************
 * 版权所有 (C)2015, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： lks32mc03x_I2C.c
 * 文件标识：
 * 其它说明： 无
 * 当前版本： V 1.0
 * 作    者： YangZJ
 * 完成日期： 2021年11月09日
 *
 *******************************************************************************/
#include "lks32mc03x_i2c.h"

static volatile u8 i2c_dma_state = 0; // I2C发送状态
/*******************************************************************************
 函数名称：    void I2C_Init(I2C_InitTypeDef *this)
 功能描述：    I2C初始化
 输入参数：    this I2C配置结构体
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2021/11/10    V1.0           Yangzj              创建
 *******************************************************************************/
void I2C_Init(I2C_InitTypeDef *this)
{
    SYS_ModuleClockCmd(SYS_Module_I2C, ENABLE);
    SYS_SoftResetModule(SYS_Module_I2C);

    {
        u32 BaudRate;
        BaudRate = ((u32)48000000 + ((this->BaudRate * 17) >> 1)) / (this->BaudRate * 17) - 1;
        SYS_WR_PROTECT = 0x7A83; //解除系统寄存器写保护
        SYS_CLK_DIV0 = BaudRate;
        SYS_WR_PROTECT = 0; //解除系统寄存器写保护
    }

    I2C->ADDR = (this->ADRCMP << 7);
    I2C->CFG = (this->IE << 7) | (this->TC_IE << 6) |
               (this->BUS_ERR_IE << 5) | (this->STOP_IE << 4) |
               (this->MST_MODE << 1) | (this->SLV_MODE);
    I2C->SCR = 0;
    I2C->DATA = 0;
    I2C->MSCR = 0;
    I2C->BCR = (this->BURST_NACK << 7) | (this->BURST_ADDR_CMP << 6) |
               (this->DMA << 5);
    I2C->BSIZE = 0;
    if (this->DMA)
    {
        i2c_dma_init();
    }
}
/*******************************************************************************
 函数名称：    void I2C_StructInit(I2C_InitTypeDef *this)
 功能描述：    I2C结构体初始化
 输入参数：    this I2C配置结构体
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2021/11/10    V1.0           Yangzj              创建
 *******************************************************************************/
void I2C_StructInit(I2C_InitTypeDef *this)
{
    this->ADRCMP = DISABLE;         //  I2C 硬件地址比较使能开关，只有在 DMA 模式下开启才有效。
    this->MST_MODE = DISABLE;       //  I2C 主模式使能
    this->SLV_MODE = DISABLE;       //  I2C 从模式使能
    this->DMA = DISABLE;            //  I2C DMA传输使能
    this->BaudRate = 100000;        //  I2C 波特率
    this->IE = DISABLE;             //  I2C 中断使能
    this->TC_IE = DISABLE;          //  I2C 数据传输完成中断使能
    this->BUS_ERR_IE = DISABLE;     //  I2C 总线错误事件中断使能
    this->STOP_IE = DISABLE;        //  I2C STOP 事件中断使能
    this->BURST_NACK = DISABLE;     //  I2C 传输，NACK 事件中断使能
    this->BURST_ADDR_CMP = DISABLE; //  I2C 传输，硬件地址匹配中断使能
}
/*******************************************************************************
 函数名称：    void I2C_StrutInit(I2C_InitTypeDef *this)
 功能描述：    读I2C总线状态
 输入参数：    this I2C配置结构体
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2021/11/10    V1.0           Yangzj              创建
 *******************************************************************************/
u8 Read_I2c_Bus_State(u16 n)
{
    if (I2C->SCR & n)
    {
        return ENABLE;
    }
    else
    {
        return DISABLE;
    }
}
/*******************************************************************************
 函数名称：    void I2C_StrutInit(I2C_InitTypeDef *this)
 功能描述：    I2C总线状态复位
 输入参数：    this I2C配置结构体
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2021/11/10    V1.0           Yangzj              创建
 *******************************************************************************/
void Clear_I2c_Bus_State(u16 n)
{
    I2C_SCR &= ~n;
}
/*******************************************************************************
 函数名称：    void I2C_SENDDATA(I2C_TypeDef *I2Cx, u32 n)
 功能描述：    I2C发送数据
 操作的表：    无
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2016/05/21     V1.0           cfwu              创建
 *******************************************************************************/
void I2C_SendData(I2C_TypeDef *I2Cx, u8 n)
{
    I2Cx->DATA = n;
}

/*******************************************************************************
 函数名称：    u32 I2C_ReadData(I2C_TypeDef *I2Cx)
 功能描述：    I2C读缓冲区数据
 操作的表：    无
 输入参数：    I2C_TypeDef *I2Cx
 输出参数：    无
 返 回 值：    缓冲区数据
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2016/05/21     V1.0           cfwu              创建
 *******************************************************************************/
u8 I2C_ReadData(I2C_TypeDef *I2Cx)
{
    return (u8)I2Cx->DATA;
}
static void i2c_dma_delay_over()
{
    u32 t = 10000000;
    while (i2c_dma_state) // 等待I2C发送完成
    {
        t--;
        if (t == 0)
        { // 避免程序卡死
            return;
        }
    }
    i2c_dma_state = 0;
    while (I2C->MSCR & BIT3) // 等待I2C总线空闲
    {
        t--;
        if (t == 0)
        { // 避免程序卡死
            return;
        }
    }
}

void i2c_dma_state_over() // I2C发送完成
{
    i2c_dma_state = 0;
}
static void i2c_dma_state_start() // I2C开始发送
{
    i2c_dma_state = 1;
}
void i2c_dma_tx(u8 addr, u8 *data, u8 len)
{
    len = (len) ? len : 1;
    len = (len > 16) ? 16 : len; // 输入限制，1-16
    i2c_dma_delay_over();        // 等待I2C完成
    I2C->ADDR = addr & 0x7f;     // 从设备地址
    I2C->SCR |= BIT2;            // I2C传输方向
    I2C->BSIZE = len - 1;        // I2C传输数据长度
    DMA_CH3->DMA_CCR = 0;
    DMA_CH3->DMA_CTMS = 16;                  // DMA搬运的数据长度，实际传输数据长度为I2C->BSIZE+1,大于I2C数据传输长度即可
    DMA_CH3->DMA_SADR = (u32)data;           // DMA源地址
    DMA_CH3->DMA_DADR = (u32) & (I2C->DATA); // DMA目的地址
    DMA_CH3->DMA_CCR = BIT6 | BIT1 | BIT0;   // 配置DMA传输方向并使能DMA
    i2c_dma_state_start();
    I2C->MSCR = 1; // 触发I2C发送数据
}
void i2c_dma_rx(u8 addr, u8 *data, u8 len)
{
    len = (len) ? len : 1;
    len = (len > 16) ? 16 : len; // 输入限制，1-16
    i2c_dma_delay_over();        // 等待I2C完成
    I2C->ADDR = addr & 0x7f;     // 从设备地址
    I2C->SCR &= ~BIT2;           // I2C传输方向
    I2C->BSIZE = len - 1;        // I2C传输数据长度
    DMA_CH3->DMA_CCR = 0;
    DMA_CH3->DMA_CTMS = 16;                  // DMA搬运的数据长度，实际传输数据长度为I2C->BSIZE+1,大于I2C数据传输长度即可
    DMA_CH3->DMA_SADR = (u32) & (I2C->DATA); // DMA源地址
    DMA_CH3->DMA_DADR = (u32)data;           // DMA目的地址
    DMA_CH3->DMA_CCR = BIT4 | BIT1 | BIT0;   // 配置DMA传输方向并使能DMA
    i2c_dma_state_start();
    I2C->MSCR = 1; // 触发I2C发送数据
}
/*******************************************************************************
 函数名称：    void DMA_init(void)
 功能描述：    DMA硬件初始化
 输入参数：    无
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2015/11/5      V1.0           Howlet Li          创建
 *******************************************************************************/
void i2c_dma_init(void)
{
    DMA_InitTypeDef DMA_InitStruct;

    DMA_InitStruct.DMA_IRQ_EN = DISABLE;        /* DMA 中断使能 */
    DMA_InitStruct.DMA_RMODE = DISABLE;         /* 多轮传输使能 */
    DMA_InitStruct.DMA_CIRC = DISABLE;          /* 循环模式使能 */
    DMA_InitStruct.DMA_SINC = DISABLE;          /* 源地址递增使能 */
    DMA_InitStruct.DMA_DINC = DISABLE;          /* 目的地址递增使能 */
    DMA_InitStruct.DMA_SBTW = 0;                /* 源地址访问位宽， 0:byte, 1:half-word, 2:word */
    DMA_InitStruct.DMA_DBTW = 0;                /* 目的地址访问位宽， 0:byte, 1:half-word, 2:word */
    DMA_InitStruct.DMA_REQ_EN = DMA_I2C_REQ_EN; /* 通道 x 硬件 DMA 请求使能，高有效 */
    DMA_InitStruct.DMA_SADR = 0;                /* DMA 通道 x 源地址 */
    DMA_InitStruct.DMA_DADR = 0;                /* DMA 通道 x 目的地址 */

    DMA_Init(DMA_CH3, &DMA_InitStruct);
    DMA_CHx_EN(DMA_CH3, DISABLE, 1); /* 关闭DMA使能，DMA 通道 1 数据搬运次数 */
    DMA_IF = 0xff;
}
/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
