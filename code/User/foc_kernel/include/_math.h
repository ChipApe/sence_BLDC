#ifndef ___MATH_H__
#define ___MATH_H__

#include "lks32mc03x_lib.h"
#include "foc_kernel/include/mc_variable.h"

/*放大倍数*/
#define		DIY_MATH_BITS						(7)
#define		DIY_Manification				(127)

/*宏*/
#define		DIY_PI				(402)
#define		DIY_2PI				(804)

#define		DIY_1					(128)
#define		DIY_1_2				(64)
#define		DIY_SQRT3			(222)
#define		DIY_SQRT3_2		(111)
#define		DIY_1_SQRT3		(74)

#define		DIY_3V3						(422)
#define		DIY_5V0						(640)

#define		DIY_fPI			(3.141593f)
#define		DIY_f2PI			(6.283185f)

#define		DIY_f1_2			(0.500000f)
#define		DIY_fSQRT3		(1.732051f)
#define		DIY_fSQRT3_2		(0.866025f)
#define		DIY_f1_SQRT3		(0.577350f)

#define		DIY_f3V3			(3.300000f)
#define		DIY_f5V0			(5.000000f)

#if (ADC_Range_Choose == ADC_Range_3V6)							// ADC_Range * DIY_Manification
#define		DIY_ADC_Range			(461)		
#elif (ADC_Range_Choose == ADC_Range_2V4)
#define		DIY_ADC_Range			(307)
#endif

/*宏函数*/
#define		scaRadian_To_scaDegree(rad)			((rad)*(23040)/(DIY_PI))
#define		scaRadian_To_Degree(rad)			((rad)*360*DIY_1/DIY_2PI/(1>>Angle_BITS))
#define		scaDegree_To_scaRadian(deg)			((deg)*(DIY_PI)/(23040))
#define		scaDegree_To_Degree(deg)			((deg)*DIY_2PI/360/DIY_1/(1>>Angle_BITS))

#define		Radian_To_scaDegree(rad)			Angle_fValue((rad)*(180.000000f)/(DIY_fPI))
#define		Radian_To_scaRadian(rad)			Angle_fValue(rad)
#define		Degree_To_scaRadian(deg)			Angle_fValue((deg)*(DIY_fPI)/(180.000000f))
#define		Degree_To_scaDegree(deg)			Angle_fValue(deg)

// 正余弦表
extern const s8 diy_sin_table[6438];

// 正余弦函数
#define	diy_sin(angle)			( diy_sin_table[angle] )
#define	diy_cos(angle)			( ((angle) >= Angle_90_Degree) ? -diy_sin_table[(angle)-Angle_90_Degree] : diy_sin_table[(angle)+Angle_90_Degree] )

// 对（x >> bits）进行四舍五入
#define		DIY_ROUND(x, bits)		( ( (x) + (((x)<<1) & (1<<(bits))) ) >> (bits) )

// 计算绝对值
#define 	ABS(x)								( (x)>0 ? (x) : -(x) )

// 约束函数, 返回约束后的值
#define			_constrain(input, low, high) ((input)<(low)?(low):((input)>(high)?high:(input)))

// 求最大值
//#define 		DIY_MAX_INT(a, b)		( (a) > (b) ? (a) : (b) )
#define 		DIY_MAX_INT(a, b)		( (a) ^ ( ((a)^(b)) & (((a) - (b)) >> 31) ) )

s16 _atan2(s16 x, s16 y);

#endif
