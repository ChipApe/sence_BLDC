/*******************************************************************************
 * 版权所有 (C)2021, LINKO SEMICONDUCTOR Co.ltd
 *
 * 文件名称： LKS32MC_03x_flash.h
 * 文件标识：
 * 内容摘要： flash外设驱动程序
 * 其它说明： 无
 * 当前版本： V 1.0
 * 作    者：   HMG
 * 完成日期： 2021年10月14日
 *
 *
 *******************************************************************************/
#ifndef __LKS32MC03x_FLASH__
#define __LKS32MC03x_FLASH__
#include "lks32mc03x_lib.h"

extern volatile u32 erase_flag;
extern volatile u32 progm_flag;
void EraseSector(u32 adr);
s32 ProgramPage(u32 adr, u32 sz, u8 *buf);
void Read_More_Flash(u32 adr, u32 sz, u32 *buf);
u32 Read_Flash(u32 adr);

#endif

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR *****END OF FILE****/
