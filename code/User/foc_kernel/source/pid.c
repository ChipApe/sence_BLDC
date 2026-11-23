#include "foc_kernel/include/pid.h"
#include "foc_kernel/include/_math.h"

/**
  * @brief  PID参数初始化
	*	@note 	无
  * @retval 无
  */
void PID_Init(PID_t *pid, float Kp, float Ki, float Kd, PID_Algorithm algo)
{
	/* 初始化参数 */
}

/**
  * @brief  PID算法实现
  * @param  val		目标值
	*	@note 	无
  * @retval 通过PID计算后的输出
  */
float PID_Core(PID_t *pid) 
{
	/* 计算目标值与实际值的误差 */
	
	/* PID算法实现 */
	if( pid->algorithm == PID_POSITION ) {		// 位置式
	} else if ( pid->algorithm == PID_INCREMENT ) {		// 增量式
	}
	
	return pid->pid_out;
}

void PID_SetParam(PID_t *pid, float p, float i, float d)
{
}

void PID_GetParam(PID_t *pid, float *buf)
{
}


