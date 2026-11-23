#ifndef __MC_TYPE_H__
#define __MC_TYPE_H__

#include "lks32mc03x_lib.h"
#include "foc_kernel/include/config.h"

#define Define_Pointer(name)		typedef name##_t *p##name



/* 采样相关结构体定义 */
// ADC采样集合
typedef struct {
	s16			s16ADC_DAT0; 						// ADC采集的第一个值
  s16			s16ADC_DAT1; 						// ADC采集的第二个值
  s16			s16ADC_DAT2; 						// ADC采集的第三个值
  s16			s16ADC_DAT3; 						// ADC采集的第四个值
} mcSample_t;
Define_Pointer(mcSample);

// 三相电流采样
typedef struct {
	s16 		CurrOffsetA_Sum;
	s16 		CurrOffsetB_Sum;
	s16 		CurrOffsetC_Sum;
	
	s16 		CurrOffsetA;
	s16			CurrOffsetB;
	s16			CurrOffsetC;
	
	s16			CurrA;
	s16			CurrB;
	s16			CurrC;
	
	u16			AbsCurrA;
	u16			AbsCurrB;
	u16			AbsCurrC;
	
	u16			MaxCurrA;
	u16			MaxCurrB;
	u16			MaxCurrC;
} mcCurr_t;
Define_Pointer(mcCurr);

// 母线电压采样
typedef struct {
	s32			DcBusSum;						// 母线电压计算中间变量
	s16			DcBusFlt;						// 母线电压滤波值
	u32			DcBusPU;						// 母线电压标量值
	u8			DcBus;							// 母线电压实际值
} DcBus_t;
Define_Pointer(DcBus);


/* 坐标定义 */
// 三相静止坐标系
typedef struct {
	s16								A, B, C;
} Axis_3s_t;
Define_Pointer(Axis_3s);

// 两相静止坐标系
typedef struct {
	s16								Alpha, Beta;
} Axis_2s_t;
Define_Pointer(Axis_2s);

// 两相旋转坐标系
typedef struct {
	s16								Q, D;
} Axis_2r_t;
Define_Pointer(Axis_2r);


/* PID */
typedef enum {
	PID_POSITION		=	1,		// 位置式算法
	PID_INCREMENT		= 2,		// 增量式算法
}PID_Algorithm;

typedef struct
{
  s16 target_val;									// 目标值
	s16 actual_val;									// 实际值
	s16 pid_out;										// PID控制器输出值
	s16 pid_max_out, pid_min_out;		// PID控制器最大、小输出值
	
	s32 Kp, Ki, Kd;									// 定义比例、积分、微分系数
	s16 P_out, I_out, D_out;				// 比例、积分、微分输出
	
	s16 err;												// 当前偏差值
	s16 err_last;										// 上个偏差值
	
	PID_Algorithm algorithm;				// PID算法
	union {
		struct {		// 位置式
			s32 integral;								// 误差累积
			
			s32 max_integral;						// 累积最大值
			s32 min_integral;						// 累积最小值
		};
		
		struct {		// 增量式
			s16 err_before;							// 上上个偏差值
		};
	};
}PID_t;
Define_Pointer(PID);


/* svpwm */
typedef struct {
	s16			Ta, Tb, Tc;							// A、B、C 三相MOS管上管导通时间
	s32			tmp1, tmp2, tmp3;
	
	u8			DcBus;									// 母线电压
	u8			Sector;									// 当前所处扇区号
}SVPWM_t;
Define_Pointer(SVPWM);


/* 滑膜无感 */
typedef struct
{
    s32 Gsmopos;									// 滑膜常数1
    s32 Fsmopos;									// 滑膜常数2
    s32 E0;												// 滑膜的电流误差的限幅值 0.5
    s32 Kslf;											// 滤波器系数
    s32 Kslide;										// 滤波器系数
    s32 wZeroSpeedTime;						// 零速度定位时间
} SMOCoef_t;

typedef struct
{
    s16 Ealpha;										// 二相静止坐标系alpha-轴反电动势
    s16 Ebeta;										// 二相静止坐标系beta-轴反电动势
    s16 Zalpha;										// alfa轴滑膜观测器的z平面
    s16 Zbeta;										// beta轴滑膜观测器的z平面
    s16 EstIalpha;								// 滑膜估算alpha-轴电流
    s16 EstIbeta;									// 滑膜估算beta-轴电流
    s16 angle;										// 观测器电角度
    s16 angleopentoclose;					// 角度补偿
    s16 speed;										// 速度
    s16 SpeedCalcOldAngle;				// 闭环标志
    s32 wOpenAngle;								// 开环角度
    s32 bAngleClosedLoop;					// 闭环标志
    s32 wZeroSpeedCnt;						// 零速度定位计数器
    s32 wOpenSpeed;								// 开环速度
} SMOVariable_t;

typedef struct
{
    SMOCoef_t			coef;				// 观测器参数
    SMOVariable_t	variable;		// 观测器变量
} SMODef_t;


/* 软件系统结构体定义 */
// 系统状态机
typedef enum {
	FaultState = 0,		// 错误状态
	CalibState,				// 校准状态
	IdleState,				// 空闲状态
	PreChargeState,		// 预充电状态
	PosiCheckState,		// 自检测状态
	StartState,				// 强拖状态
	RunState,					// 运行状态
	StopState					// 停止状态
} SysStateDef;

// 系统错误源定义
typedef enum {
	Fault_NoSource = 0,								// 无错误
	Fault_OverHardCurrent,						// 硬件过流
	Fault_Offset											// 偏置错误
} SysFaultSourceDef;

// 电机启停控制
typedef enum {
	Motor_STOP = 0,
	Motor_START = 1
} MotorStartStopType;

// 系统切环状态
typedef enum {
	OpenLoop,
	CurrentLoop,
	SpeedLoop,
	PositionLoop
} RunLoopStateType;

// 系统控制
typedef struct {
	SysStateDef					SysState;								// 系统状态
	SysFaultSourceDef		SysFaultSource;					// 系统错误的来源
	MotorStartStopType	MotorStartStopFlag;			// 电机启停标志
	RunLoopStateType		LoopState;							// 当前系统环
	
	volatile	s32				SysCount;								// 系统计数器
	volatile	u32				CarryWaveCount;					// 载波计数器
	volatile	s16				MsCount;								// 毫秒计数器
} mcSysCtrl_t;
Define_Pointer(mcSysCtrl);

// 系统计算
typedef struct {
	u8								Motor_Dir;							// 电机转向
	u16								CarryWavePeriod;				// 载波周期(us)
	mcSample_t				mcSample;								// ADC采样原始值
	mcCurr_t					mcCurr;									// 电机采样电流
	DcBus_t						DcBus;									// 母线电压
	u16								ChargeDuty;							// 预充电占空比
	
	// 滑膜观测器
	SMODef_t					SMODef;
	
	// 编码器
	void *						Sensor_Handler;					// 编码器句柄
	s16								Sensor_Angle;						// 编码器获取的电机磁环角度值
	s16								Sensor_AngleE;					// 电机当前电角度
	s16								Sensor_AngleErad;				// 电角度标幺值
	s16								Sensor_AngleE_Offset;		// 电机电角度偏移补偿
	
	// 坐标变换
	Axis_3s_t					Curr_3s;
	Axis_2s_t					Curr_2s;
	Axis_2r_t					Curr_2r;
	
	Axis_2s_t					Volt_2s;
	Axis_2r_t					Volt_2r;
	
	// PID控制器
	PID_t							pid_Iq_controler;								// 输入Iq，输出Uq
	PID_t							pid_Id_controler;								// 输入Id，输出Ud
	PID_t							pid_speed_loop_controler;				// 输入转速，输出Iq
	PID_t							pid_position_loop_controler;		// 输入角度，输出转速
	
	float							Iq_Controller_Target;						// 电流环目标Iq值
	float							Id_Controller_Target;						// 电流环目标Id值
	float							Speed_Controller_Target;				// 速度环目标速度(RPM)
	float							Position_Controller_Target;			// 位置环目标位置(rad)
	
	// PID梯形策略设置目标值
	u16								Speed_Target_Final;							// 速度环最终目标值
	u16								Speed_Target_Inc_Dec;						// 速度环目标递增值
	
	// 强拖控速
	u16								ThetaIndex;											// 当前给定的强拖角度
	u16								StartSpeedStepTarget;						// 阶段强拖目标转速(RPM)
	u16								StartSpeedTarget;								// 最终强拖目标转速(RPM)
	u16								StartSpeedInc;									// 强拖转速增量(RPM)
	u16								StartRampTheta;									// 当前角度增量
	
	// 位置检测
	u8								SelfCheckState;									// 当前检测角度的索引
	u8								SelfCheck_PolePairs;						// 目前检测到的极对数
	u8								SelfCheckFlag;									// 检测标志，用于控制检测流程
	u16								SelfCheckTime;									// 一个角度的检测时间（载波周期）
	s16								SelfCheckCount;									// 当前角度已检测的载波周期数
	u16								SelfCheck_EncoderTheta_Offset;					// 最终检测偏差
	u16								SelfCheck_EncoderTheta_Offset_60E[6];
	u16								SelfCheck_EncoderTheta_Offset_360E[Pole_Pairs];
	u32								SelfCheck_EncoderTheta_Offset_360E_Sum;
	u32								SelfCheck_EncoderTheta_Offset_Sum;
	
	// 逆变桥 SVPWM 控制器
	SVPWM_t						SVPWM;
	
	// 速度滤波
	s32								SpeedSum;
	s16								SpeedFlt;
	float							SpeedActual;										// 当前转子转速(RPM)
	
	// 角度滤波
	s16								Angle_Difference_Buffer[10];
	u8								Angle_Flt_Period;								// 角度滤波周期，单位为载波周期
	s32								Angle_Difference_Sum;
	s16								Angle_Difference_Flt;						// 角度差滤波结果值
} mcSysCal_t;
Define_Pointer(mcSysCal);

// 电机系统封装结构体
typedef struct {
	mcSysCtrl_t				mcSysCtrl;
	mcSysCal_t				mcSysCal;
} mcSys_t;
Define_Pointer(mcSys);

#endif
