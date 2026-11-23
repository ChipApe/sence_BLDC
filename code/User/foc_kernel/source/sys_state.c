#include "foc_kernel/include/mc.h"
#include "foc_kernel/include/mc_type.h"
#include "foc_kernel/include/_math.h"
#include "foc_kernel/include/pid.h"

void Fault_Handler(pmcSys pmotor)
{
		variable_init(pmotor);
		MCPWM_Output(DISABLE);
	
		SMO_clear(pmotor);
}

void Calib_Handler(pmcSys pmotor)
{
}

void IdleState_Handler(pmcSys pmotor)
{
}


void PreCharge_Handler(pmcSys pmotor)
{
}

u16 PosiCheck_ThetaIndex[6] = {(u16)MT6816_Degree_To_Digital(0), (u16)MT6816_Degree_To_Digital(60), (u16)MT6816_Degree_To_Digital(120), (u16)MT6816_Degree_To_Digital(180), (u16)MT6816_Degree_To_Digital(240), (u16)MT6816_Degree_To_Digital(300)};
void PosiCheck_Handler(pmcSys pmotor)
{
#if((PosiCheckEnable == 1) || (SYS_MODE == POSI_CHECK_MODE))
		if( (pmotor->mcSysCal.SelfCheckFlag == 0) || (pmotor->mcSysCtrl.MotorStartStopFlag != Motor_START) )
		{
				pmotor->mcSysCal.Sensor_AngleE_Offset								= MT6816_MAX_DIG - pmotor->mcSysCal.SelfCheck_EncoderTheta_Offset;
			
#if(SYS_MODE == POSI_CHECK_MODE)
				pmotor->mcSysCtrl.MotorStartStopFlag								= Motor_STOP;
				pmotor->mcSysCtrl.SysState		 											= IdleState;
				pmotor->mcSysCal.SelfCheck_EncoderTheta_Offset_Sum	= 0;
#elif(SYS_MODE == MOTOR_START_MODE)
				pmotor->mcSysCtrl.SysCount													=	0;
				pmotor->mcSysCal.Iq_Controller_Target								=	0.9;
				pmotor->mcSysCtrl.SysState		 											= StartState;
#elif(SYS_MODE == MOTOR_RUN_MODE)

#if(Motor_Run_Start_Choose == Motor_Run_With_Start)
		pmotor->mcSysCtrl.SysCount													=	0;
		pmotor->mcSysCal.Iq_Controller_Target								=	Motor_Run_Start_Uq;
		pmotor->mcSysCtrl.SysState		 											= StartState;
#else
		pmotor->mcSysCtrl.SysState		 											= RunState;
#endif
			
#endif
				MCPWM_Output(DISABLE);
		}
		else if(pmotor->mcSysCal.SelfCheckFlag == 1)
		{
				pmotor->mcSysCal.SelfCheckCount++;
				if( pmotor->mcSysCal.SelfCheckCount > pmotor->mcSysCal.SelfCheckTime )
				{				// 电机已经就位，可以进行角度检测，同时给定下一个角度
						pmotor->mcSysCal.SelfCheckCount = 0;
						
						// 计算电角度，并将电角度限制在0-360°
						pmotor->mcSysCal.Sensor_AngleE		=	pmotor->mcSysCal.Sensor_Angle * Pole_Pairs;		// 计算电角度
						pmotor->mcSysCal.SelfCheck_EncoderTheta_Offset_60E[pmotor->mcSysCal.SelfCheckState]	= ( MT6816_MAX_DIG + pmotor->mcSysCal.Sensor_AngleE - pmotor->mcSysCal.ThetaIndex ) & MT6816_MASK;

						// 对电角度偏差进行累加
						pmotor->mcSysCal.SelfCheck_EncoderTheta_Offset_360E_Sum	+= pmotor->mcSysCal.SelfCheck_EncoderTheta_Offset_60E[pmotor->mcSysCal.SelfCheckState];
						
						pmotor->mcSysCal.SelfCheckState++;
						if( pmotor->mcSysCal.SelfCheckState >= 6 )
						{						// 转过 360°电角度
							pmotor->mcSysCal.SelfCheckState = 0;
							
							pmotor->mcSysCal.SelfCheck_EncoderTheta_Offset_360E[pmotor->mcSysCal.SelfCheck_PolePairs] = pmotor->mcSysCal.SelfCheck_EncoderTheta_Offset_360E_Sum / 6;
							pmotor->mcSysCal.SelfCheck_EncoderTheta_Offset_Sum += pmotor->mcSysCal.SelfCheck_EncoderTheta_Offset_360E_Sum;
							pmotor->mcSysCal.SelfCheck_EncoderTheta_Offset_360E_Sum = 0;
							
							pmotor->mcSysCal.SelfCheck_PolePairs++;
						}
						
						if(pmotor->mcSysCal.SelfCheck_PolePairs >= Pole_Pairs) {
							pmotor->mcSysCal.SelfCheckFlag = 0;
							pmotor->mcSysCal.SelfCheck_EncoderTheta_Offset = pmotor->mcSysCal.SelfCheck_EncoderTheta_Offset_Sum / (Pole_Pairs * 6);
						} else {
							pmotor->mcSysCal.SelfCheckFlag = 2;
						}
						
						pmotor->mcSysCal.ThetaIndex		= PosiCheck_ThetaIndex[pmotor->mcSysCal.SelfCheckState];
				}
		}
		else if (pmotor->mcSysCal.SelfCheckFlag == 2)
		{
				pmotor->mcSysCal.Volt_2r.D 	= pmotor->mcSysCal.Motor_Dir * V_fValue(2.5);
				pmotor->mcSysCal.Volt_2r.Q		=	pmotor->mcSysCal.Motor_Dir * V_Value(0);
				Axis_2r_2s_trfm(pmotor->mcSysCal.Volt_2r, pmotor->mcSysCal.Volt_2s, MT6816_Digital_To_scaRadian(pmotor->mcSysCal.ThetaIndex));
				setVector( pmotor );
			
				pmotor->mcSysCal.SelfCheckFlag		= 1;
		}
#else
		
		pmotor->mcSysCal.Sensor_AngleE_Offset = MT6816_MAX_DIG - 14280;
//		pmotor->mcSysCal.Sensor_AngleE_Offset = 14280;
		pmotor->mcSysCtrl.SysFaultSource			=	Fault_NoSource;
		
#if(SYS_MODE == MOTOR_START_MODE)

		pmotor->mcSysCtrl.SysCount													=	0;
		pmotor->mcSysCtrl.SysState		 											= StartState;
		
#if(START_MODE == START_USER_MODE)
		pmotor->mcSysCal.Iq_Controller_Target								=	Motor_Open_Start_Uq;
#elif(START_MODE == START_IF_MODE)
		pmotor->mcSysCal.Iq_Controller_Target								=	Motor_Open_Start_Iq;
#endif
		
#elif(SYS_MODE == MOTOR_RUN_MODE)

#if(Motor_Run_Start_Choose == Motor_Run_With_Start)
		pmotor->mcSysCtrl.SysCount													=	0;
		pmotor->mcSysCtrl.SysState		 											= StartState;
		
#if(START_MODE == START_USER_MODE)
		pmotor->mcSysCal.Iq_Controller_Target								=	Motor_Run_Start_Uq;
#elif(START_MODE == START_IF_MODE)
		pmotor->mcSysCal.Iq_Controller_Target								=	Motor_Run_Start_Iq;
#endif
		
#else
		pmotor->mcSysCtrl.SysState		 											= RunState;
#endif

#endif
#endif
}

void Start_Handler(pmcSys pmotor)
{
		if(pmotor->mcSysCtrl.MotorStartStopFlag == Motor_START)
		{
				// 获取电角度
				
				// 克拉克变换
				Axis_3s_2s_trfm(pmotor->mcSysCal.Curr_3s, pmotor->mcSysCal.Curr_2s);				
				// 帕克变换
				Axis_2s_2r_trfm(pmotor->mcSysCal.Curr_2s, pmotor->mcSysCal.Curr_2r, ( pmotor->mcSysCal.ThetaIndex * DIY_2PI ) >> (16 + DIY_MATH_BITS - Angle_BITS));

				// 恒流I/F
				// 变流I/F
				// PID计算Ud、Uq
}


void Run_Handler(pmcSys pmotor)
{
}

void Stop_Handler(pmcSys pmotor)
{
}

void SysState_Control(pmcSys pmotor)
{
		if(pmotor->mcSysCtrl.SysFaultSource != Fault_NoSource) {
				pmotor->mcSysCtrl.SysState = FaultState;
		}
	
		switch(pmotor->mcSysCtrl.SysState) {
			case FaultState:
				Fault_Handler(pmotor);
				break;
			case CalibState:
				Calib_Handler(pmotor);
				break;
			case IdleState:
				IdleState_Handler(pmotor);
				break;
			case PreChargeState:
				PreCharge_Handler(pmotor);
				break;
			case PosiCheckState:
				PosiCheck_Handler(pmotor);
				break;
			case StartState:
				Start_Handler(pmotor);
				break;
			case RunState:
				Run_Handler(pmotor);
				break;
			case StopState:
				Stop_Handler(pmotor);
				break;
		}
}
