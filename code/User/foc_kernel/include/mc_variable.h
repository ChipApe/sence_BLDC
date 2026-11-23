#ifndef __MC_VARIABLE_H__
#define __MC_VARIABLE_H__

#include "foc_kernel/include/mc_type.h"
#include "foc_kernel/include/mt6816.h"

extern mcSys_t Motor1;
extern SPI_t mt6816_spi_handler;
extern MT6816_t mt6816;


// 适合用于（1）无符号整形转成无符号整型（2）有符号整形转成有符号整型
#define		_Q1(x)			(		(x) << 1		)
#define		_Q2(x)			(		(x) << 2		)
#define		_Q3(x)			(		(x) << 3		)
#define		_Q4(x)			(		(x) << 4		)
#define		_Q5(x)			(		(x) << 5		)
#define		_Q6(x)			(		(x) << 6		)
#define		_Q7(x)			(		(x) << 7		)
#define		_Q8(x)			(		(x) << 8		)
#define		_Q9(x)			(		(x) << 9		)
#define		_Q10(x)			(		(x) << 10		)
#define		_Q11(x)			(		(x) << 11		)
#define		_Q12(x)			(		(x) << 12		)
#define		_Q13(x)			(		(x) << 13		)
#define		_Q14(x)			(		(x) << 14		)
#define		_Q15(x)			(		(x) << 15		)
#define		_Q16(x)			(		(x) << 16		)
#define		_Q17(x)			(		(x) << 17		)
#define		_Q18(x)			(		(x) << 18		)
#define		_Q19(x)			(		(x) << 19		)
#define		_Q20(x)			(		(x) << 20		)
#define		_Q21(x)			(		(x) << 21		)
#define		_Q22(x)			(		(x) << 22		)
#define		_Q23(x)			(		(x) << 23		)
#define		_Q24(x)			(		(x) << 24		)
#define		_Q25(x)			(		(x) << 25		)
#define		_Q26(x)			(		(x) << 26		)
#define		_Q27(x)			(		(x) << 27		)
#define		_Q28(x)			(		(x) << 28		)
#define		_Q29(x)			(		(x) << 29		)
#define		_Q30(x)			(		(x) << 30		)
#define		_Q31(x)			(		(x) << 31		)

// 适合用于（1）无符号整形转回无符号整型（2）有符号整形转回有符号整型
#define		_Inv_Q1(x)		(		(x) >> 1		)
#define		_Inv_Q2(x)		(		(x) >> 2		)
#define		_Inv_Q3(x)		(		(x) >> 3		)
#define		_Inv_Q4(x)		(		(x) >> 4		)
#define		_Inv_Q5(x)		(		(x) >> 5		)
#define		_Inv_Q6(x)		(		(x) >> 6		)
#define		_Inv_Q7(x)		(		(x) >> 7		)
#define		_Inv_Q8(x)		(		(x) >> 8		)
#define		_Inv_Q9(x)		(		(x) >> 9		)
#define		_Inv_Q10(x)		(		(x) >> 10		)
#define		_Inv_Q11(x)		(		(x) >> 11		)
#define		_Inv_Q12(x)		(		(x) >> 12		)
#define		_Inv_Q13(x)		(		(x) >> 13		)
#define		_Inv_Q14(x)		(		(x) >> 14		)
#define		_Inv_Q15(x)		(		(x) >> 15		)
#define		_Inv_Q16(x)		(		(x) >> 16		)
#define		_Inv_Q17(x)		(		(x) >> 17		)
#define		_Inv_Q18(x)		(		(x) >> 18		)
#define		_Inv_Q19(x)		(		(x) >> 19		)
#define		_Inv_Q20(x)		(		(x) >> 20		)
#define		_Inv_Q21(x)		(		(x) >> 21		)
#define		_Inv_Q22(x)		(		(x) >> 22		)
#define		_Inv_Q23(x)		(		(x) >> 23		)
#define		_Inv_Q24(x)		(		(x) >> 24		)
#define		_Inv_Q25(x)		(		(x) >> 25		)
#define		_Inv_Q26(x)		(		(x) >> 26		)
#define		_Inv_Q27(x)		(		(x) >> 27		)
#define		_Inv_Q28(x)		(		(x) >> 28		)
#define		_Inv_Q29(x)		(		(x) >> 29		)
#define		_Inv_Q30(x)		(		(x) >> 30		)
#define		_Inv_Q31(x)		(		(x) >> 31		)

// 适合用于（1）浮点型转成整型
#define		_fQ1(x)			(		(x) * 2		)
#define		_fQ2(x)			(		(x) * 4		)
#define		_fQ3(x)			(		(x) * 8		)
#define		_fQ4(x)			(		(x) * 16		)
#define		_fQ5(x)			(		(x) * 32		)
#define		_fQ6(x)			(		(x) * 64		)
#define		_fQ7(x)			(		(x) * 128		)
#define		_fQ8(x)			(		(x) * 256		)
#define		_fQ9(x)			(		(x) * 512		)
#define		_fQ10(x)			(		(x) * 1024		)
#define		_fQ11(x)			(		(x) * 2048		)
#define		_fQ12(x)			(		(x) * 4096		)
#define		_fQ13(x)			(		(x) * 8192		)
#define		_fQ14(x)			(		(x) * 16384		)
#define		_fQ15(x)			(		(x) * 32768		)
#define		_fQ16(x)			(		(x) * 65536		)
#define		_fQ17(x)			(		(x) * 131072		)
#define		_fQ18(x)			(		(x) * 262144		)
#define		_fQ19(x)			(		(x) * 524288		)
#define		_fQ20(x)			(		(x) * 1048576		)
#define		_fQ21(x)			(		(x) * 2097152		)
#define		_fQ22(x)			(		(x) * 4194304		)
#define		_fQ23(x)			(		(x) * 8388608		)
#define		_fQ24(x)			(		(x) * 16777216		)
#define		_fQ25(x)			(		(x) * 33554432		)
#define		_fQ26(x)			(		(x) * 67108864		)
#define		_fQ27(x)			(		(x) * 134217728		)
#define		_fQ28(x)			(		(x) * 268435456		)
#define		_fQ29(x)			(		(x) * 536870912		)
#define		_fQ30(x)			(		(x) * 1073741824		)
#define		_fQ31(x)			(		(x) * 2147483648		)

// 适合用于（1）整型转回浮点型
#define		_Inv_fQ1(x)		(		(x) / 2.0f		)
#define		_Inv_fQ2(x)		(		(x) / 4.0f		)
#define		_Inv_fQ3(x)		(		(x) / 8.0f		)
#define		_Inv_fQ4(x)		(		(x) / 16.0f		)
#define		_Inv_fQ5(x)		(		(x) / 32.0f		)
#define		_Inv_fQ6(x)		(		(x) / 64.0f		)
#define		_Inv_fQ7(x)		(		(x) / 128.0f		)
#define		_Inv_fQ8(x)		(		(x) / 256.0f		)
#define		_Inv_fQ9(x)		(		(x) / 512.0f		)
#define		_Inv_fQ10(x)		(		(x) / 1024.0f		)
#define		_Inv_fQ11(x)		(		(x) / 2048.0f		)
#define		_Inv_fQ12(x)		(		(x) / 4096.0f		)
#define		_Inv_fQ13(x)		(		(x) / 8192.0f		)
#define		_Inv_fQ14(x)		(		(x) / 16384.0f		)
#define		_Inv_fQ15(x)		(		(x) / 32768.0f		)
#define		_Inv_fQ16(x)		(		(x) / 65536.0f		)
#define		_Inv_fQ17(x)		(		(x) / 131072.0f		)
#define		_Inv_fQ18(x)		(		(x) / 262144.0f		)
#define		_Inv_fQ19(x)		(		(x) / 524288.0f		)
#define		_Inv_fQ20(x)		(		(x) / 1048576.0f		)
#define		_Inv_fQ21(x)		(		(x) / 2097152.0f		)
#define		_Inv_fQ22(x)		(		(x) / 4194304.0f		)
#define		_Inv_fQ23(x)		(		(x) / 8388608.0f		)
#define		_Inv_fQ24(x)		(		(x) / 16777216.0f		)
#define		_Inv_fQ25(x)		(		(x) / 33554432.0f		)
#define		_Inv_fQ26(x)		(		(x) / 67108864.0f		)
#define		_Inv_fQ27(x)		(		(x) / 134217728.0f		)
#define		_Inv_fQ28(x)		(		(x) / 268435456.0f		)
#define		_Inv_fQ29(x)		(		(x) / 536870912.0f		)
#define		_Inv_fQ30(x)		(		(x) / 1073741824.0f		)
#define		_Inv_fQ31(x)		(		(x) / 2147483648.0f		)


// 电流
#define		I_BASE									(					256						)							// 电流基准值
#define		I_BITS									(					15						)							// 电流标量占用位数
#define		I_Value(x)							(		_Q15(x)/I_BASE			)							// 整型值转成标量值
#define		I_fValue(x)							(		_fQ15(x)/I_BASE			)							// 浮点值转成标量值
#define		I_Value_Inv(x)					(		_Inv_Q15(x*I_BASE)	)							// 标量值转回整型值
#define		I_fValue_Inv(x)					(		_Inv_fQ15(x*I_BASE)	)							// 标量值转回浮点值

// 电压
#define		V_BASE									(					64						)							// 电压基准值
#define		V_BITS									(					15						)							// 电压标量占用位数
#define		V_Value(x)							(		_Q15(x)/V_BASE			)							// 整型值转成标量值
#define		V_fValue(x)							(		_fQ15(x)/V_BASE			)							// 浮点值转成标量值
#define		V_Value_Inv(x)					(		_Inv_Q15(x*V_BASE)	)							// 标量值转回整型值
#define		V_fValue_Inv(x)					(		_Inv_fQ15(x*V_BASE)	)							// 标量值转回浮点值

// 速度
#define		Speed_BASE							(						2048					)							// 速度基准值
#define		Speed_BITS							(						15						)							// 速度标量占用位数
#define		Speed_Value(x)					(		_Q15(x)/Speed_BASE		)							// 整型值转成标量值
#define		Speed_fValue(x)					(		_fQ15(x)/Speed_BASE		)							// 浮点值转成标量值
#define		Speed_Value_Inv(x)			(	_Inv_Q15(x*Speed_BASE)	)							// 标量值转回整型值
#define		Speed_fValue_Inv(x)			(	_Inv_fQ15(x*Speed_BASE)	)							// 标量值转回浮点值

// PID参数：Kp、Ki、Kd
#define		PID_BASE								(						5							)							// 速度基准值
#define		PID_BITS								(						15						)							// PID参数标量占用位数
#define		PID_Value(x)						(			_Q15(x)/PID_BASE		)							// 整型值转成标量值
#define		PID_fValue(x)						(			_fQ15(x)/PID_BASE		)							// 浮点值转成标量值
#define		PID_Value_Inv(x)				(		_Inv_Q15(x*PID_BASE)	)							// 标量值转回整型值
#define		PID_fValue_Inv(x)				(		_Inv_fQ15(x*PID_BASE)	)							// 标量值转回浮点值

// 角度(弧度制)
/*	对于_Q10：
 *	可以精确到 360 / _Q10(1) = 0.35156°
 *	正余弦表占用 Flash 大小为 (2 * 3.1416 * _Q10(1)) * 2 * 2 = 6433 * 4 = 25732 = 0x6484 字节
*/
#define		Angle_BITS									(				10					)						// 角度标量占用位数
#define		Angle_Value(x)							(		_Q10(x)				)							// 整型值转成标量值
#define		Angle_fValue(x)							(		_fQ10(x)				)						// 浮点值转成标量值
#define		Angle_Value_Inv(x)					(		_Inv_Q10(x)		)							// 标量值转回整型值
#define		Angle_fValue_Inv(x)					(		_Inv_fQ10(x)		)						// 标量值转回浮点值
#define		Angle_90_Degree							(				1608				)							// 90°对应标量值：Angle_fValue( 3.1415926 / 2 )
#define		Angle_180_Degree						(				3217				)							// 180°对应标量值
#define		Angle_270_Degree						(				4825				)							// 270°对应标量值
#define		Angle_360_Degree						(				6434				)							// 360°对应标量值

#endif
