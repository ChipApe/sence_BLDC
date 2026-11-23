/*******************************************************************************
 * 版权所有 (C)2021, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： lks32mc03x_dac.h
 * 文件标识：
 * 内容摘要： DAC外设驱动程序头文件
 * 其它说明： 无
 * 当前版本： V 1.0
 * 作    者： Zhujie
 * 完成日期： 2022年4月18日
 *
 *******************************************************************************/

#ifndef _LKS32MC03x_DAC_H_
#define _LKS32MC03x_DAC_H_

/* Includes ------------------------------------------------------------------*/
#include "lks32mc03x_lib.h"
typedef struct
{
    u8 DACOUT_EN; /* DAC输出到IO使能：0，不使能；1，使能。 */
} DAC_InitTypeDef;

void DAC_StructInit(DAC_InitTypeDef *DAC_InitStruct); /* DAC结构体初始化 */
void DAC_Init(DAC_InitTypeDef *DAC_InitStruct);       /* DAC初始化 */
void DAC_OutputValue(u32 DACValue);              /* DAC输出数值设置--数字量 */
void DAC_OutputVoltage(u16 DACVoltage);          /* DAC输出模拟量数值设置--模拟量 */

#endif
