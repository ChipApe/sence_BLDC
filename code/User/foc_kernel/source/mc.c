#include "foc_kernel/include/mc.h"
#include "foc_kernel/include/_math.h"
#include "SEGGER_RTT/SEGGER_RTT.h"

static s16	max_up_T;
static u8		n_to_sector[6] =  {2, 6, 1, 4, 3, 5};

void Sys_Init(pmcSys pmotor)
{
		variable_init(pmotor);
	
		// SMO初始化
		// MT6816初始化，使用软件SPI
}

void mcpwm_set_duty(s16 T1, s16 T2, s16 T3)
{
		if( T1 > max_up_T ) T1 = max_up_T;
		if( T2 > max_up_T ) T2 = max_up_T;
		if( T3 > max_up_T ) T3 = max_up_T;
		
		MCPWM_TH00 = -T1;
		MCPWM_TH01 = T1;
		
		MCPWM_TH10 = -T2;
		MCPWM_TH11 = T2;
		
		MCPWM_TH20 = -T3;
		MCPWM_TH21 = T3;
}

// 计算电压向量并设置pwm到逆变桥
void setVector(pmcSys pmotor)
{
		Svpwm_Core(&pmotor->mcSysCal.SVPWM, &pmotor->mcSysCal.Volt_2s);
		mcpwm_set_duty(pmotor->mcSysCal.SVPWM.Ta, pmotor->mcSysCal.SVPWM.Tb, pmotor->mcSysCal.SVPWM.Tc);
		MCPWM_Output(ENABLE);
}

void ADC_Sample(pmcSys pmotor)
{
		pmotor->mcSysCal.mcSample.s16ADC_DAT0 = ADC_DAT0;
		pmotor->mcSysCal.mcSample.s16ADC_DAT1 = ADC_DAT1;

		pmotor->mcSysCal.mcSample.s16ADC_DAT2 = ADC_DAT2;
		pmotor->mcSysCal.mcSample.s16ADC_DAT3 = ADC_DAT3;
}

void Get_Current_Offset(pmcSys pmotor)
{
		pmotor->mcSysCal.mcCurr.CurrOffsetB_Sum			+=	pmotor->mcSysCal.mcSample.s16ADC_DAT0;
		pmotor->mcSysCal.mcCurr.CurrOffsetB					=		pmotor->mcSysCal.mcCurr.CurrOffsetB_Sum >> 4;
		pmotor->mcSysCal.mcCurr.CurrOffsetB_Sum			-=	pmotor->mcSysCal.mcCurr.CurrOffsetB;
	
		pmotor->mcSysCal.mcCurr.CurrOffsetC_Sum			+=	pmotor->mcSysCal.mcSample.s16ADC_DAT1;
		pmotor->mcSysCal.mcCurr.CurrOffsetC					=		pmotor->mcSysCal.mcCurr.CurrOffsetC_Sum >> 4;
		pmotor->mcSysCal.mcCurr.CurrOffsetC_Sum			-=	pmotor->mcSysCal.mcCurr.CurrOffsetC;
	
		pmotor->mcSysCal.mcCurr.CurrOffsetA					= (pmotor->mcSysCal.mcCurr.CurrOffsetB + pmotor->mcSysCal.mcCurr.CurrOffsetC) / 2;
}

void Get_Current(pmcSys pmotor)
{
		pmotor->mcSysCal.mcCurr.CurrB = I_fValue(- pmotor->mcSysCal.mcSample.s16ADC_DAT0 + pmotor->mcSysCal.mcCurr.CurrOffsetB) * ADC_Range / R_Shunt / Amplify_Gain / 2048;
		pmotor->mcSysCal.mcCurr.CurrC = I_fValue(- pmotor->mcSysCal.mcSample.s16ADC_DAT1 + pmotor->mcSysCal.mcCurr.CurrOffsetC) * ADC_Range / R_Shunt / Amplify_Gain / 2048;
		pmotor->mcSysCal.mcCurr.CurrA = - pmotor->mcSysCal.mcCurr.CurrB - pmotor->mcSysCal.mcCurr.CurrC;
}

void Get_Vbus(pmcSys pmotor)
{
		// 滤波
}

void Get_Angle(pmcSys pmotor)
{
}

void Get_Speed(pmcSys pmotor)
{
		// 角度滤波
		// 速度滤波
		// 获取实际转速
}

void Ms_Task(pmcSys pmotor)
{
		// 启停开关判断
		// 电机转速控制
		// 电机转速控制
}

void MC_CarryWaveFollow_Task(pmcSys pmotor)
{
		Motor1.mcSysCtrl.CarryWaveCount++;
		if(Motor1.mcSysCtrl.CarryWaveCount >= ((PWM_FREQ + 500) / 1000)) {		// 1毫秒时间到
				Motor1.mcSysCtrl.CarryWaveCount = 0;
			
				// 毫秒任务
				Ms_Task(pmotor);
		}
}

void Svpwm_Core(pSVPWM v, pAxis_2s p)
{
}


