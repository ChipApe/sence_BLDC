#include "foc_kernel/include/_math.h"
#include "foc_kernel/include/mc_type.h"
#include "foc_kernel/include/mc.h"

/* 未成功 */

#define EXP_NEG_RS_LD_PWMFREQ				(0.6902927f)

/*******************************************************************************
 函数名称：    void SMO_init(SMODef_t *this)
 功能描述：    滑膜观测器初始化
 输入参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2026/01/30    V1.0           ChipApe            创建
 *******************************************************************************/
void SMO_init(pmcSys pmotor)
{
		pmotor->mcSysCal.SMODef.coef.Fsmopos = EXP_NEG_RS_LD_PWMFREQ * 32768;
		pmotor->mcSysCal.SMODef.coef.Gsmopos = (s32)(pmotor->mcSysCal.DcBus.DcBus / 2 / ADC_Range / R_Shunt / Amplify_Gain / Rs * (1 - EXP_NEG_RS_LD_PWMFREQ) * 32768);
//    pmotor->mcSysCal.SMODef.coef.Fsmopos = (s32)(exp((-Rs / Ld) / PWM_FREQ) * 32768);
//    pmotor->mcSysCal.SMODef.coef.Gsmopos = (s32)(pmotor->mcSysCal.DcBus.DcBus / 2 / ADC_Range / R_Shunt / Amplify_Gain / Rs * (1 - exp((-Rs / Ld) / PWM_FREQ)) * 32768);
    pmotor->mcSysCal.SMODef.coef.Kslide = 20000;
    pmotor->mcSysCal.SMODef.coef.Kslf = 20000;
    pmotor->mcSysCal.SMODef.coef.E0 = 32670;
    pmotor->mcSysCal.SMODef.coef.wZeroSpeedTime = 1000;
}

/*******************************************************************************
 函数名称：    void SMO_clear(SMODef_t *this)
 功能描述：    滑膜观测器复位
 输入参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2026/01/30    V1.0           ChipApe            创建
 *******************************************************************************/
void SMO_clear(pmcSys pmotor)
{
		u16 i;
		u8 *p = (u8 *)( &(pmotor->mcSysCal.SMODef) );
		
		for(i=0; i<sizeof(SMOVariable_t); i++, p++) {
				*p = 0;
		}
}

/*******************************************************************************
 函数名称：    s16 SMO_CalcElAngle(SMODef_t * this,stru_CurrAlphBeta Ialfa_beta, stru_VoltAlphBeta Valfa_beta)
 功能描述：    触发滑膜观测器计算并得到角度
 输入参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2026/01/30    V1.0           ChipApe            创建
 *******************************************************************************/
s16 SMO_CalcElAngle(pmcSys pmotor)
{
    s16 EstIalpha, EstIbeta, Ealpha, Ebeta, Zalpha, Zbeta;
		s16 angle;

    // 滑膜观测器
    Zalpha = (s16)((_constrain(pmotor->mcSysCal.SMODef.variable.EstIalpha - pmotor->mcSysCal.Curr_2s.Alpha, -pmotor->mcSysCal.SMODef.coef.E0, pmotor->mcSysCal.SMODef.coef.E0) * pmotor->mcSysCal.SMODef.coef.Kslide) >> 15);
    Zbeta = (s16)((_constrain(pmotor->mcSysCal.SMODef.variable.EstIbeta - pmotor->mcSysCal.Curr_2s.Beta, -pmotor->mcSysCal.SMODef.coef.E0, pmotor->mcSysCal.SMODef.coef.E0) * pmotor->mcSysCal.SMODef.coef.Kslide) >> 15);
    Ealpha = pmotor->mcSysCal.SMODef.variable.Ealpha + (s16)((pmotor->mcSysCal.SMODef.coef.Kslf * (pmotor->mcSysCal.SMODef.variable.Zalpha - pmotor->mcSysCal.SMODef.variable.Ealpha)) >> 15);
    Ebeta = pmotor->mcSysCal.SMODef.variable.Ebeta + (s16)((pmotor->mcSysCal.SMODef.coef.Kslf * (pmotor->mcSysCal.SMODef.variable.Zbeta - pmotor->mcSysCal.SMODef.variable.Ebeta)) >> 15);
    EstIalpha = (s16)((pmotor->mcSysCal.SMODef.coef.Fsmopos * pmotor->mcSysCal.SMODef.variable.EstIalpha + pmotor->mcSysCal.SMODef.coef.Gsmopos * (pmotor->mcSysCal.Volt_2s.Alpha - pmotor->mcSysCal.SMODef.variable.Ealpha - pmotor->mcSysCal.SMODef.variable.Zalpha)) >> 15);
    EstIbeta = (s16)((pmotor->mcSysCal.SMODef.coef.Fsmopos * pmotor->mcSysCal.SMODef.variable.EstIbeta + pmotor->mcSysCal.SMODef.coef.Gsmopos * (pmotor->mcSysCal.Volt_2s.Beta - pmotor->mcSysCal.SMODef.variable.Ebeta - pmotor->mcSysCal.SMODef.variable.Zbeta)) >> 15);

    pmotor->mcSysCal.SMODef.variable.EstIalpha = EstIalpha;
    pmotor->mcSysCal.SMODef.variable.EstIbeta = EstIbeta;
    pmotor->mcSysCal.SMODef.variable.Ealpha = Ealpha;
    pmotor->mcSysCal.SMODef.variable.Ebeta = Ebeta;
    pmotor->mcSysCal.SMODef.variable.Zalpha = Zalpha;
    pmotor->mcSysCal.SMODef.variable.Zbeta = Zbeta;

    // 反正切得到角度
    pmotor->mcSysCal.SMODef.variable.angle = -_atan2(pmotor->mcSysCal.SMODef.variable.Ebeta, pmotor->mcSysCal.SMODef.variable.Ealpha);

    // 开环角度处理
    if (pmotor->mcSysCal.SMODef.variable.bAngleClosedLoop == 0)
    {
        pmotor->mcSysCal.SMODef.variable.wOpenAngle += pmotor->mcSysCal.SMODef.variable.wOpenSpeed;
        angle = pmotor->mcSysCal.SMODef.variable.wOpenAngle >> 16;
        pmotor->mcSysCal.SMODef.variable.angleopentoclose = angle - pmotor->mcSysCal.SMODef.variable.angle;
        return angle;
    }
    else
    {
        angle = pmotor->mcSysCal.SMODef.variable.angle + pmotor->mcSysCal.SMODef.variable.angleopentoclose;
        return angle;
    }
}
