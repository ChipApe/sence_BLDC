#include "foc_kernel/include/mt6816.h"
#include "foc_kernel/include/_math.h"
#include "foc_kernel/include/mc_variable.h"

void MT6816_Init(pMT6816 p, SPI_Way way)
{
		ca_spi_init(p->spi_handler, SPI_MODE_3, way);
		MT6816_GetDigAngle(p);
}

/**
  * 函    数：MT6816获取内部滤波后的角度(数字量)
  * 参    数：MT6816句柄
  * 返 回 值：12位角度值（0-4095）
  * 说    明：经过滤波和零位校准后的角度
  */
uint16_t MT6816_GetDigAngle(pMT6816 p)
{
}

/**
	*	函		数：获取MT6816连续角度值(弧度坐标系)
	*	参		数：MT6816句柄
	* 返 回 值：0表示获取成功，1表示失败
	* 注		意：这个函数计算的是调用期间编码器的绝对连续角度值
	*/
uint8_t MT6816_GetConAngle(pMT6816 p)
{
}
