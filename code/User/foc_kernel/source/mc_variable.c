#include "foc_kernel/include/mc.h"
#include "foc_kernel/include/mc_type.h"
#include "foc_kernel/include/pid.h"
#include "foc_kernel/include/_math.h"

SPI_t mt6816_spi_handler = {
		.miso_port	= GPIO0,	.miso_pin = GPIO_Pin_6,
		.mosi_port	= GPIO0,	.mosi_pin = GPIO_Pin_5,
		.clk_port		= GPIO0,	.clk_pin	= GPIO_Pin_8,
		.cs_port		= GPIO0,	.cs_pin		= GPIO_Pin_9,
};
MT6816_t mt6816 = { .spi_handler = &mt6816_spi_handler };

void variable_init(pmcSys pmotor)
{
		/* 初始状态设置 */
		pmotor->mcSysCtrl.SysCount						= 0;
		pmotor->mcSysCtrl.SysState						=	CalibState;
		pmotor->mcSysCtrl.SysFaultSource			= Fault_NoSource;
		pmotor->mcSysCtrl.MotorStartStopFlag	=	Motor_STOP;

// 用于PID单位转换
#define		Unit_Convert(x)			( 	Out_Unit(x) / In_Unit(1.0f)	)
		/* PID控制器初始化 */
			/* 电流环控制器初始化 */
			#define		In_Unit(x)					(		I_fValue(x)		)
			#define		Out_Unit(x)					(		V_fValue(x)		)
			// ID环
			PID_Init(&pmotor->mcSysCal.pid_Id_controler, Unit_Convert(MOTOR_ID_PID_KP), Unit_Convert(MOTOR_ID_PID_KI), Unit_Convert(MOTOR_ID_PID_KD), PID_POSITION);
			
			if( MOTOR_ID_PID_KI != 0.0f ) {
			pmotor->mcSysCal.pid_Id_controler.max_integral	= In_Unit(  ID_PID_MAX_IOUT ) / (float)( MOTOR_ID_PID_KI );
			pmotor->mcSysCal.pid_Id_controler.min_integral	= In_Unit( -ID_PID_MAX_IOUT ) / (float)( MOTOR_ID_PID_KI );
			}
			
			pmotor->mcSysCal.pid_Id_controler.pid_max_out		=	Out_Unit(  ID_PID_MAX_OUT );
			pmotor->mcSysCal.pid_Id_controler.pid_min_out		=	Out_Unit( -ID_PID_MAX_OUT );
			
			pmotor->mcSysCal.Id_Controller_Target					=	PID_ID_TARGET_INIT;
			
			// IQ环
			PID_Init(&pmotor->mcSysCal.pid_Iq_controler, Unit_Convert(MOTOR_IQ_PID_KP), Unit_Convert(MOTOR_IQ_PID_KI), Unit_Convert(MOTOR_IQ_PID_KD), PID_POSITION);
			
			if( MOTOR_IQ_PID_KI != 0.0f ) {
			pmotor->mcSysCal.pid_Iq_controler.max_integral	= In_Unit(  IQ_PID_MAX_IOUT ) / (float)( MOTOR_IQ_PID_KI );
			pmotor->mcSysCal.pid_Iq_controler.min_integral	= In_Unit( -IQ_PID_MAX_IOUT ) / (float)( MOTOR_IQ_PID_KI );
			}
			
			pmotor->mcSysCal.pid_Iq_controler.pid_max_out		=	Out_Unit(  IQ_PID_MAX_OUT );
			pmotor->mcSysCal.pid_Iq_controler.pid_min_out		=	Out_Unit( -IQ_PID_MAX_OUT );
			
			pmotor->mcSysCal.Iq_Controller_Target					=	PID_IQ_TARGET_INIT;
			#undef		In_Unit
			#undef		Out_Unit
			
		#if( DEBUGMODE == Mode_RUN )				// 运行模式
			/* 速度环控制器初始化 */
			#define		In_Unit(x)					(		Speed_fValue(x)		)
			#define		Out_Unit(x)					(			I_fValue(x)			)
			PID_Init(&pmotor->mcSysCal.pid_speed_loop_controler, Unit_Convert(MOTOR_VEL_PID_KP), Unit_Convert(MOTOR_VEL_PID_KI), Unit_Convert(MOTOR_VEL_PID_KD), PID_POSITION);
			
			if( MOTOR_VEL_PID_KI != 0.0f ) {
				pmotor->mcSysCal.pid_speed_loop_controler.max_integral	= In_Unit(  VEL_PID_MAX_IOUT ) / (float)(MOTOR_VEL_PID_KI);
				pmotor->mcSysCal.pid_speed_loop_controler.min_integral	= In_Unit( -VEL_PID_MAX_IOUT ) / (float)(MOTOR_VEL_PID_KI);
			}
			
			pmotor->mcSysCal.pid_speed_loop_controler.pid_max_out		=	Out_Unit(  VEL_PID_MAX_OUT );
			pmotor->mcSysCal.pid_speed_loop_controler.pid_min_out		=	Out_Unit( -VEL_PID_MAX_OUT );
			
			pmotor->mcSysCal.Speed_Controller_Target								= PID_VEL_TARGET_INIT;
			#undef		In_Unit
			#undef		Out_Unit
			
			/* 位置环控制器初始化 */
			#define		In_Unit(x)					(						(x)						)
			#define		Out_Unit(x)					(			Speed_fValue(x)			)
			PID_Init(&pmotor->mcSysCal.pid_position_loop_controler, Unit_Convert(MOTOR_POS_PID_KP), Unit_Convert(MOTOR_POS_PID_KI), Unit_Convert(MOTOR_POS_PID_KD), PID_POSITION);
			
			if( MOTOR_VEL_PID_KI != 0.0f ) {
				pmotor->mcSysCal.pid_position_loop_controler.max_integral	= In_Unit(  POS_PID_MAX_IOUT ) / (float)(MOTOR_VEL_PID_KI);
				pmotor->mcSysCal.pid_position_loop_controler.min_integral	= In_Unit( -POS_PID_MAX_IOUT ) / (float)(MOTOR_VEL_PID_KI);
			}
			
			pmotor->mcSysCal.pid_position_loop_controler.pid_max_out	= (s16)Out_Unit(  POS_PID_MAX_OUT );
			pmotor->mcSysCal.pid_position_loop_controler.pid_min_out	=	(s16)Out_Unit( -POS_PID_MAX_OUT );
			
			pmotor->mcSysCal.Position_Controller_Target								= PID_POS_TARGET_INIT;
			#undef		In_Unit
			#undef		Out_Unit
			
		#endif
#undef		Unit_Convert
		
#if	(Motor_Run_Trapezoid_Vel_Enable == 1)
		pmotor->mcSysCal.Speed_Target_Inc_Dec = Speed_fValue(Trapezoid_Vel_Inc_Dec);
#endif
			
		/* 强拖部分变量初始化 */
#if(SYS_MODE == MOTOR_START_MODE)
		pmotor->mcSysCal.Speed_Controller_Target	=	Motor_Open_Start_Target_Speed;
		pmotor->mcSysCal.StartSpeedInc						=	Speed_fValue(Motor_Open_Start_SpeedInc);
#elif((SYS_MODE == MOTOR_RUN_MODE) && (Motor_Run_Start_Choose == Motor_Run_With_Start))
		pmotor->mcSysCal.Speed_Controller_Target	=	Motor_Run_Start_Target_Speed;
		pmotor->mcSysCal.StartSpeedInc						= Speed_fValue(Motor_Run_Start_SpeedInc);
#endif
		
		/* 其他 */
		pmotor->mcSysCal.Angle_Flt_Period				=	_constrain(Angle_Filter_Period, 1, sizeof(pmotor->mcSysCal.Angle_Difference_Buffer) / sizeof(s16) - 1);
		pmotor->mcSysCal.Motor_Dir							=	MOTOR_DIR == MOTOR_CCW ? 1 : MOTOR_DIR == MOTOR_CW ? -1 : 0;
		pmotor->mcSysCal.CarryWavePeriod				=	1000000/PWM_FREQ ;
}
