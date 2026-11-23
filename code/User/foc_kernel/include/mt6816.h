#ifndef __MT6816_H__
#define __MT6816_H__

#include "foc_kernel/include/_spi.h"

#define	MT6816_BITS							( 14 )
#define	MT6816_MASK							( 0x3FFF )

#define MT6816_MAX_DIG					( 16384 )
#define MT6816_MAX_MUTATION			( 8192 )

typedef enum {
	MT6816_UNKNOWN	= 0,		// 不确定
	MT6816_CW				= 1,		// 正转(顺时针)
	MT6816_CCW			= 2,		// 反转(逆时针)
}MT6816_DIR;

typedef struct {
		pSPI	spi_handler;
	
		uint16_t dig_angle;
		MT6816_DIR cur_dir;		// 当前旋转方向
		
		// 用于计算连续角度
		int16_t	dig_angle_difference;		// 角度差
		int32_t dig_continus_angle;
} MT6816_t;
typedef MT6816_t * pMT6816;

/**
 *	前缀说明
 *	无：正常单位
 *	sca：标量
 */
#define MT6816_Digital_To_scaRadian(dAngle)			( ( (dAngle) * DIY_2PI ) >> (DIY_MATH_BITS + MT6816_BITS - Angle_BITS) )
#define MT6816_Digital_To_Radian(dAngle)				( (float)(dAngle) * DIY_f2PI / MT6816_MAX_DIG )
#define MT6816_Digital_To_scaDegree(dAngle)			( ( Angle_Value(dAngle) * 360 ) >> MT6816_BITS )
#define MT6816_Digital_To_Degree(dAngle)				( (float)(dAngle) * 360.0f / MT6816_MAX_DIG )

#define	MT6816_scaRadian_To_scaDigital(rAngle)	( (( (rAngle) << (MT6816_BITS + 5) ) / DIY_2PI) >> (DIY_MATH_BITS - 5) )
#define	MT6816_scaRadian_To_Digital(rAngle)			( ( (rAngle) << (MT6816_BITS - Angle_BITS) ) / DIY_2PI )
#define	MT6816_Radian_To_Digital(rAngle)				( (rAngle) * MT6816_MAX_DIG / DIY_f2PI )
#define	MT6816_Radian_To_scaDigital(rAngle)			( (s16)Angle_fValue(MT6816_Radian_To_Digital(rAngle)) )

#define	MT6816_scaDegree_To_scaDigital(dAngle)	( ((dAngle) << MT6816_BITS) / 360 )
#define	MT6816_scaDegree_To_Digital(dAngle)			( ( (rAngle) << (MT6816_BITS - Angle_BITS) ) / 360 )
#define	MT6816_Degree_To_Digital(dAngle)				( (dAngle) * MT6816_MAX_DIG / 360.0f )
#define	MT6816_Degree_To_scaDigital(dAngle)			( (s16)Angle_fValue(MT6816_Degree_To_Digital(dAngle)) )

void MT6816_Init(pMT6816 p, SPI_Way way);
uint16_t MT6816_GetDigAngle(pMT6816 p);
uint8_t MT6816_GetConAngle(pMT6816 p);

#endif
