#include "foc_kernel/include/mc.h"
#include "foc_kernel/include/_math.h"

void ADC_IRQHandler(void);
void PendSV_Handler(void);

/*******************************************************************************
 函数名称：    int ADC0_IRQHandler(void)
 功能描述：    ADC中断函数
 输入参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2026/01/30    V1.0           ChipApe            创建
 *******************************************************************************/
void ADC_IRQHandler(void)
{
    ADC_IF = BIT0;							// 清除中断标志位
	
		GPIO_SetBits(GPIO_TEST);		// 进入中断
	
		Motor1.mcSysCal.Sensor_AngleE		= ((MT6816_MAX_DIG + Motor1.mcSysCal.Sensor_Angle - Motor1.mcSysCal.Sensor_AngleE_Offset) * Pole_Pairs) & MT6816_MASK;
		
		ADC_Sample(&Motor1);
		Get_Current(&Motor1);
		Get_Vbus(&Motor1);
	
#if((SYS_MODE != MOTOR_START_MODE) || (MOTOR_START_SET_ANGLE_WAY == MOTOR_START_USE_SENSOR))
		Get_Angle(&Motor1);
		Get_Speed(&Motor1);
#endif
		
		SysState_Control(&Motor1);						// 系统状态机

		MC_CarryWaveFollow_Task(&Motor1);
		
		GPIO_ResetBits(GPIO_TEST);		// 退出中断
}
