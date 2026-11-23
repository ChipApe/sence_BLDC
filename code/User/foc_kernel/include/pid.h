#ifndef __PID_H__
#define __PID_H__

#include "foc_kernel/include/mc_type.h"
#include "foc_kernel/include/mc_variable.h"

extern void		PID_Init(PID_t *pid, float Kp, float Ki, float Kd, PID_Algorithm algo);
extern float	PID_Core(PID_t *pid);
extern void		PID_SetParam(PID_t *pid, float p, float i, float d);
extern void		PID_GetParam(PID_t *pid, float *buf);

#endif

