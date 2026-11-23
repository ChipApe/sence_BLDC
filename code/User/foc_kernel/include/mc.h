#ifndef __MC_H__
#define __MC_H__

#include "lks32mc03x_lib.h"
#include "foc_kernel/include/mc_variable.h"
#include "foc_kernel/include/mc_type.h"

/* *************************PWM 频率及死区定义***************************** */
#define PWM_FREQ				((u16)10000)														// PWM载波频率

#define DEADTIME_NS			((u16)20)															// 死区时间
#define DEADTIME (u16)	(((unsigned long long)MCU_MCLK * (unsigned long long)DEADTIME_NS) / 1000000000uL)

/* *****************************ADC通道定义************************************ */
#define ADC0_CURRETN_B_CHANNEL		(ADC_CHANNEL_0)								// A相电流采样通道
#define ADC0_CURRETN_C_CHANNEL		(ADC_CHANNEL_8)								// B相电流采样通道
#define ADC0_BUS_VOL_MSK					(ADC_CHANNEL_5)								// 母线电压采样通道
#define ADC0_SPEED_MSK					(ADC_SPEED_CHANNEL)							// 温度采样通道

/* ADC量程范围（3.6V、2.4V） */
#if (ADC_Range_Choose == ADC_Range_3V6)
#define		ADC_Range								(3.6f)
#elif (ADC_Range_Choose == ADC_Range_2V4)
#define		ADC_Range								(2.4f)
#endif

/* MCPWM 输出控制 */
#define	MCPWM_Output(state)				PWMOutputs(MCPWM0, state)

/* PWM总计数周期 */
#define PWM_PERIOD								((s16)(MCPWM0->PWM_TH0<<1))

/* 运放放大倍数 */
#if(RES_OPA_Config == RES_OPA_200_10)
    #define		Amplify_Gain		( 200/(10+OPA_EXT_RES) )
#elif(RES_OPA_Config == RES_OPA_190_20)
		#define		Amplify_Gain		( 190/(20+OPA_EXT_RES) )
#elif(RES_OPA_Config == RES_OPA_180_30)
		#define		Amplify_Gain		( 180/(30+OPA_EXT_RES) )
#elif(RES_OPA_Config == RES_OPA_170_40)
		#define		Amplify_Gain		( 170/(40+OPA_EXT_RES) )
#endif

/* 坐标变换 */
// 克拉克变换：void Axis_3s_2s_trfm(Axis_3s_t in, Axis_2s_t out);
#define Axis_3s_2s_trfm(in, out)  do{	\
			(out).Alpha	= (in).A; \
			(out).Beta		=	(s16)(( DIY_1_SQRT3 * (((in).B << 1) + (in).A) ) >> DIY_MATH_BITS); \
		} while(0)

// 帕克变换：void Axis_2s_2r_trfm(Axis_2s_t in, Axis_2r_t out, s16 angleElecRad)
#define Axis_2s_2r_trfm(in, out, angleE) do{ \
			(out).D	= (s16)((  diy_cos( angleE ) * (in).Alpha + diy_sin( angleE ) * (in).Beta ) >> DIY_MATH_BITS); \
			(out).Q	= (s16)(( -diy_sin( angleE ) * (in).Alpha + diy_cos( angleE ) * (in).Beta ) >> DIY_MATH_BITS); \
		} while(0)

// 帕克反变换：void Axis_2r_2s_trfm(Axis_2r_t in, Axis_2s_t out, angleElecRad)
#define Axis_2r_2s_trfm(in, out, angleE) do { \
			(out).Alpha	= (s16)(( diy_cos( angleE ) * (in).D - diy_sin( angleE ) * (in).Q ) >> DIY_MATH_BITS); \
			(out).Beta		= (s16)(( diy_sin( angleE ) * (in).D + diy_cos( angleE ) * (in).Q ) >> DIY_MATH_BITS); \
		} while(0)

		
// 梯形设置PID目标值
#define	Trapezoid_Set_Target(target_handler, final_target, inc_dec) do {	\
		if((target_handler) > (final_target)) {																\
				(target_handler) -= (inc_dec);																		\
				if((target_handler) < (final_target)) {														\
						(target_handler) = (final_target);														\
				}																																	\
		}	else if((target_handler) < (final_target)) {												\
				(target_handler) += (inc_dec);																		\
				if((target_handler) > (final_target)) {														\
						(target_handler) = (final_target);														\
				}																																	\
		}																																			\
	} while(0)
		
void Hardware_Init(void);
		
void Sys_Init(pmcSys pmotor);
void mcpwm_set_duty(s16 T1, s16 T2, s16 T3);
void setVector(pmcSys pmotor);
void ADC_Sample(pmcSys p);
void Get_Current_Offset(pmcSys pmotor);
void Get_Current(pmcSys pmotor);
void Get_Vbus(pmcSys p);
void Get_Angle(pmcSys pmotor);
void Get_Speed(pmcSys pmotor);
void Ms_Task(pmcSys pmotor);
void MC_CarryWaveFollow_Task(pmcSys pmotor);
void Svpwm_Core(pSVPWM v, pAxis_2s p);
		
void variable_init(pmcSys pmotor);
		
void SysState_Control(pmcSys pmotor);
		
void SMO_init(pmcSys pmotor);
void SMO_clear(pmcSys pmotor);
s16 SMO_CalcElAngle(pmcSys pmotor);
		
#endif
