/*******************************************************************************
 * 版权所有 (C)2015, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： lks32mc03x_gpio.c
 * 文件标识：
 * 内容摘要： GPIO外设驱动程序
 * 其它说明： 无
 * 当前版本： V 1.0
 * 作    者： Yangzj
 * 完成日期： 2021/11/10
 *
 *******************************************************************************/
#include "lks32mc03x_gpio.h"

/*******************************************************************************
 函数名称：    void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct)
 功能描述：    GPIO初始化
 操作的表：    无
 输入参数：    GPIOx:GPIO对象, GPIO_InitStruct:GPIO初始化结构体
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2021/11/10    V1.0           YangZJ            创建
 *******************************************************************************/
void GPIO_Init(GPIO_TypeDef *GPIOx, GPIO_InitTypeDef *GPIO_InitStruct)
{
    u32 pinpos = 0x00, pos = 0x00, currentpin = 0x00, tempreg = 0x00;

    /*-------------------------- Configure the port pins -----------------------*/
    for (pinpos = 0x00; pinpos < 0x10; pinpos++)
    {
        pos = ((u32)0x01) << pinpos;

        /* Get the port pins position */
        currentpin = (GPIO_InitStruct->GPIO_Pin) & pos;
        if (currentpin == pos)
        {
            if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IN)
            {
                tempreg = GPIOx->PIE; /*使能输入*/
                tempreg |= (BIT0 << pinpos);
                GPIOx->PIE = tempreg;

                tempreg = GPIOx->POE; /*禁止输出*/
                tempreg &= ~(BIT0 << pinpos);
                GPIOx->POE = tempreg;
            }
            else if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_OUT)
            {
                tempreg = GPIOx->PIE; /*禁止输入*/
                tempreg &= ~(BIT0 << pinpos);
                GPIOx->PIE = tempreg;

                tempreg = GPIOx->POE; /*使能输出*/
                tempreg |= (BIT0 << pinpos);
                GPIOx->POE = tempreg;
            }
            else if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_ANA)
            {
                tempreg = GPIOx->PIE; /*禁止输入*/
                tempreg &= ~(BIT0 << pinpos);
                GPIOx->PIE = tempreg;

                tempreg = GPIOx->POE; /*禁止输出*/
                tempreg &= ~(BIT0 << pinpos);
                GPIOx->POE = tempreg;
            }

            if (GPIO_InitStruct->GPIO_PuPd == GPIO_PuPd_UP)
            {
                tempreg = GPIOx->PUE;
                tempreg |= (BIT0 << pinpos);
                GPIOx->PUE = tempreg;
            }

            else if (GPIO_InitStruct->GPIO_PuPd == GPIO_PuPd_NOPULL)
            {
                tempreg = GPIOx->PUE;
                tempreg &= ~(BIT0 << pinpos);
                GPIOx->PUE = tempreg;
            }

            tempreg = GPIOx->PODE;
            if (GPIO_InitStruct->GPIO_PODEna == (u32)ENABLE)
            {
                tempreg |= (BIT0 << pinpos);
            }
            else
            {
                tempreg &= ~(BIT0 << pinpos);
            }
            GPIOx->PODE = tempreg;
        }
    }
}

/*******************************************************************************
 函数名称：    void GPIO_StructInit(GPIO_InitTypeDef* GPIO_InitStruct)
 功能描述：    GPIO结构体初始化
 操作的表：    无
 输入参数：    GPIO_InitStruct:GPIO初始化结构体
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2021/11/10    V1.0           YangZJ            创建
 *******************************************************************************/
void GPIO_StructInit(GPIO_InitTypeDef *GPIO_InitStruct)
{
    GPIO_InitStruct->GPIO_Pin = GPIO_Pin_NONE;
    GPIO_InitStruct->GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct->GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct->GPIO_PODEna = DISABLE;
}

/*******************************************************************************
 函数名称：    u8 GPIO_ReadInputDataBit(GPIO_TypeDef* GPIOx, u16 GPIO_Pin)
 功能描述：    读取GPIO的指定Pin的输入值
 操作的表：    无
 输入参数：    GPIOx:GPIO对象, GPIO_Pin:指定的Pin
 输出参数：    无
 返 回 值：    指定Pin的输入值
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2021/11/10    V1.0           YangZJ            创建
 *******************************************************************************/
u8 GPIO_ReadInputDataBit(GPIO_TypeDef *GPIOx, u16 GPIO_Pin)
{
    u8 bitstatus = 0x00;
    if ((GPIOx->PDI & GPIO_Pin) != 0)
    {
        bitstatus = (u8)Bit_SET;
    }
    else
    {
        bitstatus = (u8)Bit_RESET;
    }
    return bitstatus;
}

/*******************************************************************************
 函数名称：    u32 GPIO_ReadInputData(GPIO_TypeDef* GPIOx)
 功能描述：    读取GPIO的输入数据
 操作的表：    无
 输入参数：    GPIOx:GPIO对象
 输出参数：    无
 返 回 值：    输入数据
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2021/11/10    V1.0           YangZJ            创建
 *******************************************************************************/
u32 GPIO_ReadInputData(GPIO_TypeDef *GPIOx)
{
    return GPIOx->PDI;
}

/*******************************************************************************
 函数名称：    u8 GPIO_ReadOutputDataBit(GPIO_TypeDef* GPIOx, u16 GPIO_Pin)
 功能描述：    读取GPIO的指定Pin的输出值
 操作的表：    无
 输入参数：    GPIOx:GPIO对象, GPIO_Pin:指定的Pin
 输出参数：    无
 返 回 值：    指定Pin的输出值
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2021/11/10    V1.0           YangZJ            创建
 *******************************************************************************/
u8 GPIO_ReadOutputDataBit(GPIO_TypeDef *GPIOx, u16 GPIO_Pin)
{
    u8 bitstatus = 0x00;
    if ((GPIOx->PDO & GPIO_Pin) != 0)
    {
        bitstatus = (u8)Bit_SET;
    }
    else
    {
        bitstatus = (u8)Bit_RESET;
    }
    return bitstatus;
}

/*******************************************************************************
 函数名称：    u32 GPIO_ReadOutputData(GPIO_TypeDef* GPIOx)
 功能描述：    读取GPIO的当前输出数据
 操作的表：    无
 输入参数：    GPIOx:GPIO对象
 输出参数：    无
 返 回 值：    输出数据
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2021/11/10    V1.0           YangZJ            创建
 *******************************************************************************/
u32 GPIO_ReadOutputData(GPIO_TypeDef *GPIOx)
{
    return GPIOx->PDO;
}

/*******************************************************************************
 函数名称：    void GPIO_SetBits(GPIO_TypeDef* GPIOx, u16 GPIO_Pin)
 功能描述：    GPIO指定Pin置1
 操作的表：    无
 输入参数：    GPIOx:GPIO对象, GPIO_Pin:指定的Pin
 输出参数：    无
 返 回 值：
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2021/11/10    V1.0           YangZJ            创建
 *******************************************************************************/
void GPIO_SetBits(GPIO_TypeDef *GPIOx, u16 GPIO_Pin)
{
    GPIOx->BSRR = GPIO_Pin;
}

/*******************************************************************************
 函数名称：    void GPIO_ResetBits(GPIO_TypeDef* GPIOx, u16 GPIO_Pin)
 功能描述：    GPIO指定Pin置0
 操作的表：    无
 输入参数：    GPIOx:GPIO对象, GPIO_Pin:指定的Pin
 输出参数：    无
 返 回 值：
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2021/11/10    V1.0           YangZJ            创建
 *******************************************************************************/
void GPIO_ResetBits(GPIO_TypeDef *GPIOx, u16 GPIO_Pin)
{
    GPIOx->BRR = GPIO_Pin;
}

/*******************************************************************************
 函数名称：    void GPIO_WriteBit(GPIO_TypeDef* GPIOx, u16 GPIO_Pin, u8 BitVal)
 功能描述：    向GPIO指定的Pin写入数据
 操作的表：    无
 输入参数：    GPIOx:GPIO对象, GPIO_Pin:指定的Pin, BitVal:写入的Bit值
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2021/11/10    V1.0           YangZJ            创建
 *******************************************************************************/
void GPIO_WriteBit(GPIO_TypeDef *GPIOx, u16 GPIO_Pin, BitAction BitVal)
{
    if (BitVal != Bit_RESET)
    {
        GPIOx->BSRR = GPIO_Pin;
    }
    else
    {
        GPIOx->BRR = GPIO_Pin;
    }
}

/*******************************************************************************
 函数名称：    void GPIO_Write(GPIO_TypeDef* GPIOx, u32 Val)
 功能描述：    向GPIO写入数据
 操作的表：    无
 输入参数：    GPIOx:GPIO对象, Val:写入的值
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2021/11/10    V1.0           YangZJ            创建
 *******************************************************************************/
void GPIO_Write(GPIO_TypeDef *GPIOx, u32 Val)
{
    GPIOx->PDO = Val;
}

/*******************************************************************************
 函数名称：    void GPIO_PadAFConfig(GPIO_TypeDef* GPIOx, u32 GPIO_PadSource, u32 GPIO_AF)
 功能描述：    GPIO功能选择
 操作的表：    无
 输入参数：    GPIOx:GPIO对象, GPIO_PadSource:指定的PadSource, GPIO_AF:指定的功能
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2021/11/10    V1.0           YangZJ            创建
 *******************************************************************************/
void GPIO_PinAFConfig(GPIO_TypeDef *GPIOx, u32 GPIO_PinSource, u32 GPIO_AF)
{
    u32 temp;
    switch (GPIO_PinSource)
    {
    /*F3210*/
    case 0:
    {
        temp = GPIOx->F3210 & 0xFFF0;  /*get F321*/
        GPIOx->F3210 = temp + GPIO_AF; /*F321 + F0*/
        break;
    }
    case 1:
    {
        temp = GPIOx->F3210 & 0xFF0F;
        GPIOx->F3210 = temp + (GPIO_AF << 4);
        break;
    }
    case 2:
    { /* 2020.8.13 Repair bug HL */
        temp = GPIOx->F3210 & 0xF0FF;
        GPIOx->F3210 = temp + (GPIO_AF << 8);
        break;
    }
    case 3:
    {
        temp = GPIOx->F3210 & 0x0FFF;
        GPIOx->F3210 = temp + (GPIO_AF << 12);
        break;
    }
    /*F7654*/
    case 4:
    {
        temp = GPIOx->F7654 & 0xFFF0;
        GPIOx->F7654 = temp + GPIO_AF;
        break;
    }
    case 5:
    {
        temp = GPIOx->F7654 & 0xFF0F;
        GPIOx->F7654 = temp + (GPIO_AF << 4);
        break;
    }
    case 6:
    {
        temp = GPIOx->F7654 & 0xF0FF;
        GPIOx->F7654 = temp + (GPIO_AF << 8);
        break;
    }
    case 7:
    {
        temp = GPIOx->F7654 & 0x0FFF;
        GPIOx->F7654 = temp + (GPIO_AF << 12);
        break;
    }
    /*FBA98*/
    case 8:
    {
        temp = GPIOx->FBA98 & 0xFFF0;
        GPIOx->FBA98 = temp + GPIO_AF;
        break;
    }
    case 9:
    {
        temp = GPIOx->FBA98 & 0xFF0F;
        GPIOx->FBA98 = temp + (GPIO_AF << 4);
        break;
    }
    case 10:
    {
        temp = GPIOx->FBA98 & 0xF0FF;
        GPIOx->FBA98 = temp + (GPIO_AF << 8);
        break;
    }
    case 11:
    {
        temp = GPIOx->FBA98 & 0x0FFF;
        GPIOx->FBA98 = temp + (GPIO_AF << 12);
        break;
    }
    /*FFEDC*/
    case 12:
    {
        temp = GPIOx->FFEDC & 0xFFF0;
        GPIOx->FFEDC = temp + GPIO_AF;
        break;
    }
    case 13:
    {
        temp = GPIOx->FFEDC & 0xFF0F;
        GPIOx->FFEDC = temp + (GPIO_AF << 4);
        break;
    }
    case 14:
    {
        temp = GPIOx->FFEDC & 0xF0FF;
        GPIOx->FFEDC = temp + (GPIO_AF << 8);
        break;
    }
    case 15:
    {
        temp = GPIOx->FFEDC & 0x0FFF;
        GPIOx->FFEDC = temp + (GPIO_AF << 12);
        break;
    }
    default:
        break;
    }
}
/*******************************************************************************
 函数名称：    void EXTI_Trigger_Config(GPIO_TypeDef* GPIOx, u32 GPIO_PadSource, u16 EXTI_Trigger)
 功能描述：    GPIO外部触发极性选择
 操作的表：    无
 输入参数：    GPIOx:GPIO对象, GPIO_PadSource:指定的PadSource, EXTI_Trigger:指定的触发极性
 输出参数：    无
 返 回 值：    无
 其它说明：    需要打开EXTI_IE才有效
              参考  用户手册   表 15-19 GPIO 中断资源分布表
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2021/11/10    V1.0           YangZJ            创建
 *******************************************************************************/
void EXTI_Trigger_Config(GPIO_TypeDef *GPIOx, u32 GPIO_PinSource, u16 EXTI_Trigger)
{
    if (GPIOx == GPIO0)
    {
        switch (GPIO_PinSource)
        {
        case 0:
            EXTI->CR0 = (u32)(EXTI->CR0 & 0xfffc) |
                        (u32)(EXTI_Trigger);
            break;
        case 2:
            EXTI->CR0 = (u32)(EXTI->CR0 & 0xfff3) |
                        (u32)(EXTI_Trigger << 2);
            break;
        case 4:
            EXTI->CR0 = (u32)(EXTI->CR0 & 0xffcf) |
                        (u32)(EXTI_Trigger << 4);
            break;
        case 5:
            EXTI->CR0 = (u32)(EXTI->CR0 & 0xff3f) |
                        (u32)(EXTI_Trigger << 6);
            break;
        case 6:
            EXTI->CR0 = (u32)(EXTI->CR0 & 0xfcff) |
                        (u32)(EXTI_Trigger << 8);
            break;
        case 7:
            EXTI->CR0 = (u32)(EXTI->CR0 & 0xf3ff) |
                        (u32)(EXTI_Trigger << 10);
            break;
        case 8:
            EXTI->CR0 = (u32)(EXTI->CR0 & 0xcfff) |
                        (u32)(EXTI_Trigger << 12);
            break;
        case 9:
            EXTI->CR0 = (u32)(EXTI->CR0 & 0x3fff) |
                        (u32)(EXTI_Trigger << 14);
            break;
        case 14:
            EXTI->CR1 = (u32)(EXTI->CR0 & 0xfffc) |
                        (u32)(EXTI_Trigger);
            break;
        case 15:
            EXTI->CR1 = (u32)(EXTI->CR0 & 0xfff3) |
                        (u32)(EXTI_Trigger << 2);
            break;
        default:
            break;
        }
    }
    if (GPIOx == GPIO1)
    {
        switch (GPIO_PinSource)
        {
        case 4:
            EXTI->CR1 = (u32)(EXTI->CR0 & 0xffcf) |
                        (u32)(EXTI_Trigger << 4);
            break;
        case 5:
            EXTI->CR1 = (u32)(EXTI->CR0 & 0xff3f) |
                        (u32)(EXTI_Trigger << 6);
            break;
        case 6:
            EXTI->CR1 = (u32)(EXTI->CR0 & 0xfcff) |
                        (u32)(EXTI_Trigger << 8);
            break;
        case 7:
            EXTI->CR1 = (u32)(EXTI->CR0 & 0xf3ff) |
                        (u32)(EXTI_Trigger << 10);
            break;
        case 8:
            EXTI->CR1 = (u32)(EXTI->CR0 & 0xcfff) |
                        (u32)(EXTI_Trigger << 12);
            break;
        case 9:
            EXTI->CR1 = (u32)(EXTI->CR0 & 0x3fff) |
                        (u32)(EXTI_Trigger << 14);
            break;
        default:
            break;
        }
    }
    if (EXTI->CR1 || EXTI->CR0)
    {
        EXTI->IE = 3;
    }
}

/*******************************************************************************
 函数名称：    u8 EXTI_GetIRQFlag(GPIO_TypeDef *GPIOx, u32 GPIO_PinSource)
 功能描述：    读取比较器中断
 操作的表：    无
 输入参数：    无
 输出参数：    无
 返 回 值：    外部中断标志
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/04/21    V1.0           Yangzj            创建
 *******************************************************************************/
u8 EXTI_GetIRQFlag(GPIO_TypeDef *GPIOx, u32 GPIO_PinSource)
{
    u16 gpio0_if_def[16] = {BIT0, 0, BIT1, 0, BIT2, BIT3, BIT4, BIT5, BIT6, BIT7, 0, 0, 0, 0, BIT8, BIT9};
    u16 gpio1_if_def[16] = {0, 0, 0, 0, BIT10, BIT11, BIT12, BIT13, BIT14, BIT15, 0, 0, 0, 0, 0, 0};
    if (GPIO_PinSource >= 16)
    {
        return 0;
    }
    if (GPIOx == GPIO0)
    {
        if (EXTI_IF & gpio0_if_def[GPIO_PinSource])
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    if (GPIOx == GPIO1)
    {
        if (EXTI_IF & gpio1_if_def[GPIO_PinSource])
        {
            return 1;
        }
        else
        {
            return 0;
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
void EXTI_ClearIRQFlag(GPIO_TypeDef *GPIOx, u32 GPIO_PinSource)
{
    u16 gpio0_if_def[16] = {BIT0, 0, BIT1, 0, BIT2, BIT3, BIT4, BIT5, BIT6, BIT7, 0, 0, 0, 0, BIT8, BIT9};
    u16 gpio1_if_def[16] = {0, 0, 0, 0, BIT10, BIT11, BIT12, BIT13, BIT14, BIT15, 0, 0, 0, 0, 0, 0};
    if (GPIOx == GPIO0)
    {
        EXTI_IF = gpio0_if_def[GPIO_PinSource];
    }
    if (GPIOx == GPIO1)
    {
        EXTI_IF = gpio1_if_def[GPIO_PinSource];
    }
}
/*******************************************************************************
 函数名称：    void GPIO_SetMode(GPIO_TypeDef* GPIOx, u16 GPIO_Pin, GPIOMode_TypeDef GPIO_Mode)
 功能描述：    设置某一个GPIO的工作模式
 操作的表：    无
 输入参数：    GPIOx:GPIO对象, GPIO_Pin:指定的Pin, GPIO_Mode:GPIO工作模式
 输出参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2022/07/06    V1.0           YangZJ            创建
 *******************************************************************************/
void GPIO_SetMode(GPIO_TypeDef* GPIOx, u16 GPIO_Pin, GPIOMode_TypeDef GPIO_Mode)
{
    u32 reg;
    u32 PRIMASK;
    PRIMASK = __get_PRIMASK();
    __disable_irq();
    switch(GPIO_Mode)
    {
        case GPIO_Mode_IN:
            reg = GPIOx->PIE;
            reg |= GPIO_Pin;
            GPIOx->PIE = reg;
        
            reg = GPIOx->POE;
            reg &= ~GPIO_Pin;
            GPIOx->POE = reg;
            break;
        case GPIO_Mode_OUT:
            reg = GPIOx->PIE;
            reg &= ~GPIO_Pin;
            GPIOx->PIE = reg;
        
            reg = GPIOx->POE;
            reg |= GPIO_Pin;
            GPIOx->POE = reg;
            break;
        case GPIO_Mode_ANA:
            reg = GPIOx->PIE;
            reg &= ~GPIO_Pin;
            GPIOx->PIE = reg;
        
            reg = GPIOx->POE;
            reg |= GPIO_Pin;
            GPIOx->POE = reg;
            break;
    }
    __set_PRIMASK(PRIMASK);
}
/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
