#ifndef __CONFIG_H__
#define __CONFIG_H__

/* 模式选择 */
#define		CONTROL_BY_HAND									(1)
#define		CONTROL_BY_KEY									(2)
#define		CONTROL_WAY									(CONTROL_BY_KEY)

#define		MOSTEST_MODE										(1)
#define		POSI_CHECK_MODE									(2)
#define		MOTOR_START_MODE								(3)
#define		MOTOR_RUN_MODE									(4)
#define		SYS_MODE										(MOTOR_RUN_MODE)

#define		PreChargeEnable									(1)				// 预充电使能
#define		PreChargeDuty									(0.8f)			// 预充电占空比

#define		PrePosiEnable										(1)				// 预定位使能，打开后自检测更准

#define		PosiCheckEnable									(0)				// 自检测使能

#if(SYS_MODE == MOTOR_START_MODE)

/* MOTOR_START_MODE */
#define		MOTOR_START_USE_SENSOR					(0)				// 使用编码器
#define		MOTOR_START_NO_SENSOR						(1)				// 不使用编码器
#define		MOTOR_START_SET_ANGLE_WAY		(MOTOR_START_NO_SENSOR)

#define		START_USER_MODE										(1)			// 用户给定Uq
#define		START_UF_MODE											(2)			// UF控制给定Uq
#define 	START_IF_MODE											(3)			// IF控制给定Uq
#define 	START_MODE										(START_IF_MODE)

#if(START_MODE == START_USER_MODE)
#define		Motor_Open_Start_Uq						(1.0f)			// 强拖给定Uq大小
#elif(START_MODE == START_UF_MODE)
#define		Motor_Open_START_U_F					(0.06f)			// 额定电压/额定转速
#elif(START_MODE == START_IF_MODE)
#define		Motor_Open_Start_Iq						(0.25f)			// 强拖给定Iq大小
//#define		Motor_Open_START_I_F					(0.0004)			// 额定电流/额定转速
#endif

#define   Motor_Open_Start_Target_Speed		(60) 			// 强拖模式下最高速度
#define   Motor_Open_Start_SpeedInc			(0.15f)			// 强拖模式下启动速度增量

#elif(SYS_MODE == MOTOR_RUN_MODE)

/* MOTOR_RUN_MODE */
#define		Motor_Run_With_Start						(1)				// 启动前进行强拖
#define		Motor_Run_Without_Start					(2)				// 启动前不进行强拖
#define		Motor_Run_Start_Choose			(Motor_Run_Without_Start)

#if(Motor_Run_Start_Choose == Motor_Run_With_Start)
#define		START_USER_MODE										(1)			// 用户给定Uq
#define		START_UF_MODE											(2)			// UF控制给定Uq
#define 	START_IF_MODE											(3)			// IF控制给定Uq
#define 	START_MODE										(START_IF_MODE)

#if(START_MODE == START_USER_MODE)
#define		Motor_Run_Start_Uq							(1.0f)		// 强拖给定Uq大小
#elif(START_MODE == START_UF_MODE)
#define		Motor_Run_START_U_F							(0.06f)		// 额定电压/额定转速
#elif(START_MODE == START_IF_MODE)
#define		Motor_Run_Start_Iq							(0.25f)		// 强拖给定Iq大小
#endif

#define		Motor_Run_Start_Target_Speed		(60)			// 强拖阶段最高转速(RPM)
#define		Motor_Run_Start_SpeedInc				(1.0f)		// 强拖阶段目标速度增量（达到这个速度后会切电流环）

#endif

#define		CURRENT_LOOP										(1)				// 电流环
#define		SPEED_LOOP											(2)				// 速度环
#define		POSITION_LOOP										(3)				// 位置环
#define		RUN_MODE_LOOP								(SPEED_LOOP)

#define		Motor_Run_Trapezoid_Vel_Enable	(1)				// 速度环启用梯形设置目标值

#endif


/* 用户个性配置 */
// 电机参数
#define 	Pole_Pairs											(7)				// 电机极对数
#define		Rs														(2.55)			// 电机相电阻，单位：Ω
#define		Ld														(0.86)			// 电机相电感，单位：mH
#define		Lq														(0.86)			// 电机相电感，单位：mH

// 母线采样电阻
#define		RV1														(100)			// 上拉电阻，单位kohm
#define		RV2														(20)			// 下拉电阻，单位kohm

// 电流采样电阻
#define 	R_Shunt												(0.3)			// 单位：Ω

// 运放外置电阻
#define		OPA_EXT_RES										(10)			// 单位：kΩ


/* 功能参数配置 */
// 电机运行方向
#define		MOTOR_CW												(1)				// 顺时针
#define		MOTOR_CCW												(2)				// 逆时针
#define		MOTOR_DIR										(MOTOR_CCW)

#define		Angle_Filter_Period							(4)				// 角度滤波间隔，单位为载波周期

// ADC量程选择
#define		ADC_Range_3V6										(0)				// 3.6V
#define		ADC_Range_2V4										(1)				// 2.4V
#define		ADC_Range_Choose							(ADC_Range_3V6)

// 运放反馈电阻选择
#define 	RES_OPA_200_10									(1)
#define 	RES_OPA_190_20									(2)
#define 	RES_OPA_180_30									(3)
#define 	RES_OPA_170_40									(4)
#define		RES_OPA_Config							( RES_OPA_200_10 )

// Q轴电流环PID参数
#define		MOTOR_IQ_PID_KP								(0.6f)
#define		MOTOR_IQ_PID_KI								(0.01f)
#define		MOTOR_IQ_PID_KD								(0.0f)
#define		IQ_PID_MAX_OUT 								(8.0f)			// Q轴电流环输出限值
#define		IQ_PID_MAX_IOUT								(7.0f)			// Q轴电流环积分限值
#define		PID_IQ_TARGET_INIT						(0.06f)			// Q轴电流环初始值

// D轴电流环PID参数
#define		MOTOR_ID_PID_KP								(0.6f)
#define		MOTOR_ID_PID_KI								(0.01f)
#define		MOTOR_ID_PID_KD								(0.0f)
#define		ID_PID_MAX_OUT 								(8.0f)
#define		ID_PID_MAX_IOUT								(7.0f)
#define		PID_ID_TARGET_INIT						(0.0f)

// 速度环PID参数
#if(Motor_Run_Trapezoid_Vel_Enable == 1)

#define 	MOTOR_VEL_PID_KP							(0.006f)
#define 	MOTOR_VEL_PID_KI							(0.0004f)
#define 	MOTOR_VEL_PID_KD							(0.0f)
#define 	VEL_PID_MAX_OUT 							(0.60f)
#define 	VEL_PID_MAX_IOUT							(0.40f)
#define		PID_VEL_TARGET_INIT						(400)
#define		Trapezoid_Vel_Inc_Dec					(0.2f)					// 速度环梯形曲线斜率(单位为rpm)

#else

#define 	MOTOR_VEL_PID_KP							(0.008f)
#define 	MOTOR_VEL_PID_KI							(0.0004f)
#define 	MOTOR_VEL_PID_KD							(0.0f)
#define 	VEL_PID_MAX_OUT 							(0.60f)
#define 	VEL_PID_MAX_IOUT							(0.50f)
#define		PID_VEL_TARGET_INIT						(400)

#endif

// 位置环PID参数
#define 	MOTOR_POS_PID_KP							(0.15f)
#define 	MOTOR_POS_PID_KI							(0)
#define 	MOTOR_POS_PID_KD							(0)
#define 	POS_PID_MAX_OUT 							(150)
#define 	POS_PID_MAX_IOUT							(150)
#define		PID_POS_TARGET_INIT						(0)

// 外设GPIO定义
#define		GPIO_LED											GPIO1, GPIO_Pin_4		// LED
#define		GPIO_START_STOP								GPIO1, GPIO_Pin_6		// 电机启停按键
#define		GPIO_SPEED										GPIO0, GPIO_Pin_4		// 控制电机转速
#define		GPIO_TEST											GPIO1, GPIO_Pin_7		// 测试用GPIO
#define		ADC_SPEED_CHANNEL							(ADC_CHANNEL_1)

#endif
