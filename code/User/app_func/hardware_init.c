#include "foc_kernel/include/mc.h"

void Hardware_init(void);
void OPA_init(void);
void ADC_init(void);
void ADC_NormalModeCFG(void);
void GPIO_init(void);
void MCPWM_init(void);
void SoftDelay(u32 cnt);

/*******************************************************************************
 函数名称：    void Hardware_init(void)
 功能描述：    初始化外设
 输入参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2026/01/30    V1.0           ChipApe            创建
 *******************************************************************************/
void Hardware_Init(void)
{
    DSP_Init();     // DSP模块初始化
    ADC_init();     // ADC初始化
    MCPWM_init();   // PWM初始化
    GPIO_init();    // GPIO初始化
    OPA_init();     // OPA 初始化
    IWDG_DISABLE(); // 关闭看门狗

    NVIC_SetPriority(ADC_IRQn, 1);
    NVIC_EnableIRQ(ADC_IRQn);
}

/*******************************************************************************
 函数名称：    void PGA_init(void)
 功能描述：    初始化运放
 输入参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2026/01/30    V1.0           ChipApe            创建
 *******************************************************************************/
void OPA_init(void)
{
    OPA_InitTypeDef OPA_InitStruct;
    OPA_InitStruct.OPA_B_EN = 0;
    OPA_InitStruct.OPA_CLEna = 0;
	
#if(RES_OPA_Config == RES_OPA_200_10)
    OPA_InitStruct.OPA_Gain = PGA_GAIN_20;
#elif(RES_OPA_Config == RES_OPA_190_20)
		OPA_InitStruct.OPA_Gain = PGA_GAIN_9P5;
#elif(RES_OPA_Config == RES_OPA_180_30)
		OPA_InitStruct.OPA_Gain = PGA_GAIN_6;
#elif(RES_OPA_Config == RES_OPA_170_40)
		OPA_InitStruct.OPA_Gain = PGA_GAIN_4P25;
#endif
	
    OPA_Init(OPA, &OPA_InitStruct);
    SYS_AnalogModuleClockCmd(SYS_AnalogModule_OPA, ENABLE);
}

/*******************************************************************************
 函数名称：    void ADC_init(void)
 功能描述：    初始化ADC
 输入参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2026/01/30    V1.0           ChipApe            创建
 *******************************************************************************/
void ADC_init(void)
{
    ADC_InitTypeDef ADC_InitStructure;

    ADC_StructInit(&ADC_InitStructure);

    ADC_InitStructure.ADC_SAMP_CLK = 20;								// ADC 采样时间选择从5->36个ADC时钟周期可选
    ADC_InitStructure.IE = ADC_EOS0_IRQ_EN;							// ADC第一段采样结束中断使能
    ADC_InitStructure.SEL_En = ADC_MCPWM_TRG;												// 打开 MCPWM 硬件触发事件
    ADC_InitStructure.Align = ADC_RIGHT_ALIGN;					// Configures ADC Result Align
    ADC_InitStructure.Trigger_Mode = ADC_1SEG_TRG;			// 设置ADC转换模式为单段式采样
    ADC_InitStructure.Trigger_Cnt = 0;									// 单段模式下触发下一次采样所需的触发事件数
    ADC_InitStructure.Trigger_En = ADC_HARDWARE_T0_TRG;	// 使能 T0 硬件触发ADC采样
    ADC_InitStructure.FirSeg_Ch = 4;										// 第一段采样的总通道数
    ADC_InitStructure.SecSeg_Ch = 0;										// 第二段采样的总通道数
    ADC_InitStructure.ThrSeg_Ch = 0;										// 第三段采样的总通道数
    ADC_InitStructure.FouSeg_Ch = 0;										// 第四段采样的总通道数
    ADC_InitStructure.ADC_GEN_En = DISABLE;							// ADC模拟看门狗
    ADC_InitStructure.ADC_GEN_HTH = 0;									// ADC模拟看门狗上阈值
    ADC_InitStructure.ADC_GEN_LTH = 0;									// ADC模拟看门狗下阈值
    ADC_InitStructure.REFOUT_EN = DISABLE;							// ADC REF输出使能
	
#if (ADC_Range_Choose == ADC_Range_3V6)									// ADC量程（0:3.6V，1:2.4V）
		ADC_InitStructure.ADC_RANGE = 0;
#elif (ADC_Range_Choose == ADC_Range_2V4)
		ADC_InitStructure.ADC_RANGE = 1;
#endif

    ADC_Init(ADC, &ADC_InitStructure);

    ADC_IF = 0xff;

    ADC_NormalModeCFG();
}

/*******************************************************************************
 函数名称：    void ADC_NormalModeCFG(void)
 功能描述：    初始化ADC采样通道
 输入参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2026/01/30    V1.0           ChipApe            创建
 *******************************************************************************/
void ADC_NormalModeCFG(void)
{
    ADC_CHN0 = ADC0_CURRETN_B_CHANNEL |
               (ADC0_CURRETN_C_CHANNEL << 4) |
               (ADC0_BUS_VOL_MSK << 8) |
               (ADC0_SPEED_MSK << 0xc);
}

/*******************************************************************************
 函数名称：    void GPIO_init(void)
 功能描述：    初始化GPIO
 输入参数：    无
 返 回 值：    无
 其它说明：
 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2026/01/30    V1.0           ChipApe            创建
 *******************************************************************************/
void GPIO_init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_StructInit(&GPIO_InitStruct);

    /* MCPWM P0.10~P0.15 */
    GPIO_PinAFConfig(GPIO0, GPIO_PinSource_10, AF3_MCPWM);
    GPIO_PinAFConfig(GPIO0, GPIO_PinSource_11, AF3_MCPWM);
    GPIO_PinAFConfig(GPIO0, GPIO_PinSource_12, AF3_MCPWM);
    GPIO_PinAFConfig(GPIO0, GPIO_PinSource_13, AF3_MCPWM);
    GPIO_PinAFConfig(GPIO0, GPIO_PinSource_14, AF3_MCPWM);
    GPIO_PinAFConfig(GPIO0, GPIO_PinSource_15, AF3_MCPWM);
    GPIO_SetMode(GPIO0, GPIO_Pin_10, GPIO_Mode_OUT);
    GPIO_SetMode(GPIO0, GPIO_Pin_11, GPIO_Mode_OUT);
    GPIO_SetMode(GPIO0, GPIO_Pin_12, GPIO_Mode_OUT);
    GPIO_SetMode(GPIO0, GPIO_Pin_13, GPIO_Mode_OUT);
    GPIO_SetMode(GPIO0, GPIO_Pin_14, GPIO_Mode_OUT);
    GPIO_SetMode(GPIO0, GPIO_Pin_15, GPIO_Mode_OUT);
	
		/* SPI */
//		GPIO_SetMode( ((pMT6816)Motor1.mcSysCal.Sensor_Handler)->spi_handler->cs_port, ((pMT6816)Motor1.mcSysCal.Sensor_Handler)->spi_handler->cs_pin, GPIO_Mode_OUT );				// CSN
//		GPIO_SetMode( ((pMT6816)Motor1.mcSysCal.Sensor_Handler)->spi_handler->clk_port, ((pMT6816)Motor1.mcSysCal.Sensor_Handler)->spi_handler->clk_pin, GPIO_Mode_OUT );			// CLK
//		GPIO_SetMode( ((pMT6816)Motor1.mcSysCal.Sensor_Handler)->spi_handler->mosi_port, ((pMT6816)Motor1.mcSysCal.Sensor_Handler)->spi_handler->mosi_pin, GPIO_Mode_OUT );		// MOSI
//		GPIO_SetMode( ((pMT6816)Motor1.mcSysCal.Sensor_Handler)->spi_handler->miso_port, ((pMT6816)Motor1.mcSysCal.Sensor_Handler)->spi_handler->miso_pin, GPIO_Mode_IN );		// MISO


		GPIO_SetMode( GPIO0, GPIO_Pin_9, GPIO_Mode_OUT );		// CSN
		GPIO_SetMode( GPIO0, GPIO_Pin_8, GPIO_Mode_OUT );		// CLK
		GPIO_SetMode( GPIO0, GPIO_Pin_5, GPIO_Mode_OUT );		// MOSI
		GPIO_SetMode( GPIO0, GPIO_Pin_6, GPIO_Mode_IN );		// MISO

    /* 启停开关 */
    GPIO_SetMode(GPIO_START_STOP, GPIO_Mode_IN);
		
		/* LED */
		GPIO_SetMode(GPIO_LED, GPIO_Mode_OUT);
		
		/* 测试GPIO */
		GPIO_SetMode(GPIO_TEST, GPIO_Mode_OUT);
}

/*******************************************************************************
 函数名称：    void MCPWM_init(void)
 功能描述：    初始化MCPWM
 输入参数：    无
 返 回 值：    无
 其它说明：		 MCPWM 模块有两个递增计数器(时基)，从 -TH(t0) 递增到 0(t1) 再到 TH(t2)，
							 由于MCPWM的通道0、1、2都由时基0控制，因此这里不使能时基1

 修改日期      版本号          修改人            修改内容
 -----------------------------------------------------------------------------
 2026/01/30    V1.0           ChipApe            创建
 *******************************************************************************/
void MCPWM_init(void)
{
    MCPWM_InitTypeDef MCPWM_InitStructure;

    MCPWM_StructInit(&MCPWM_InitStructure);

    MCPWM_InitStructure.CLK_DIV = 0;								// MCPWM时钟分频设置
    MCPWM_InitStructure.MCLK_EN = ENABLE;						// 模块时钟开启
    MCPWM_InitStructure.MCPWM_Cnt0_EN = ENABLE;			// 时基0主计数器开始计数使能开关
    MCPWM_InitStructure.MCPWM_Cnt1_EN = DISABLE;			// 时基1主计数器开始计数使能开关
    MCPWM_InitStructure.MCPWM_WorkModeCH0 = CENTRAL_PWM_MODE;	// 通道0工作模式设置，中心对齐或边沿对齐
    MCPWM_InitStructure.MCPWM_WorkModeCH1 = CENTRAL_PWM_MODE;	// 通道1工作模式设置，中心对齐或边沿对齐
    MCPWM_InitStructure.MCPWM_WorkModeCH2 = CENTRAL_PWM_MODE;	// 通道2工作模式设置，中心对齐或边沿对齐

    /* 自动更新使能寄存器 MCPWM_TH00 自动加载使能 MCPWM_TMR0 自动加载使能 MCPWM_0TH 自动加载使能 MCPWM_0CNT 自动加载使能 */
    MCPWM_InitStructure.AUEN = TH00_AUEN | TH01_AUEN | TH10_AUEN | TH11_AUEN |
                               TH20_AUEN | TH21_AUEN | TMR0_AUEN | TMR1_AUEN |
                               TMR2_AUEN | TMR3_AUEN | TH0_AUEN | TH30_AUEN | TH31_AUEN;

    MCPWM_InitStructure.GPIO_BKIN_Filter = 12;	// 急停事件(来自IO口信号)数字滤波器时间设置
    MCPWM_InitStructure.CMP_BKIN_Filter = 12;		// 急停事件(来自比较器信号)数字滤波器时间设置

    MCPWM_InitStructure.TimeBase0_PERIOD = ((u16)(MCU_MCLK / (u32)(2 * PWM_FREQ)));           // 时基0周期设置
    MCPWM_InitStructure.TimeBase1_PERIOD = ((u16)(MCU_MCLK / (u32)(2 * PWM_FREQ)));           // 时基1周期设置
    MCPWM_InitStructure.TriggerPoint0 = (u16)(10 - ((u16)(MCU_MCLK / (u32)(2 * PWM_FREQ))));  // MCPWM_TMR0 ADC触发事件T0 设置
//    MCPWM_InitStructure.TriggerPoint1 = (u16)(800 - ((u16)(MCU_MCLK / (u32)(2 * PWM_FREQ)))); // MCPWM_TMR1 ADC触发事件T1 设置

    MCPWM_InitStructure.DeadTimeCH0123N = DEADTIME;		// CH0123N死区时间设置
    MCPWM_InitStructure.DeadTimeCH0123P = DEADTIME;		// CH0123P死区时间设置

    MCPWM_InitStructure.CH0N_Polarity_INV = ENABLE;		// CH0N通道输出极性设置 | 正常输出或取反输出
    MCPWM_InitStructure.CH0P_Polarity_INV = DISABLE;	// CH0P通道输出极性设置 | 正常输出或取反输出
    MCPWM_InitStructure.CH1N_Polarity_INV = ENABLE;
    MCPWM_InitStructure.CH1P_Polarity_INV = DISABLE;
    MCPWM_InitStructure.CH2N_Polarity_INV = ENABLE;
    MCPWM_InitStructure.CH2P_Polarity_INV = DISABLE;

    MCPWM_InitStructure.Switch_CH0N_CH0P = ENABLE;		// 通道交换选择设置 | CH0P和CH0N是否选择信号交换
    MCPWM_InitStructure.Switch_CH1N_CH1P = ENABLE;		// 通道交换选择设置
    MCPWM_InitStructure.Switch_CH2N_CH2P = ENABLE;		// 通道交换选择设置

//		MCPWM_InitStructure.Switch_CH0N_CH0P = DISABLE;		// 通道交换选择设置 | CH0P和CH0N是否选择信号交换
//    MCPWM_InitStructure.Switch_CH1N_CH1P = DISABLE;		// 通道交换选择设置
//    MCPWM_InitStructure.Switch_CH2N_CH2P = DISABLE;		// 通道交换选择设置

		MCPWM_InitStructure.CH0P_default_output = LOW_LEVEL;
    MCPWM_InitStructure.CH0N_default_output = LOW_LEVEL;
    MCPWM_InitStructure.CH1P_default_output = LOW_LEVEL;
    MCPWM_InitStructure.CH1N_default_output = LOW_LEVEL;
    MCPWM_InitStructure.CH2P_default_output = LOW_LEVEL;
    MCPWM_InitStructure.CH2N_default_output = LOW_LEVEL;
		
    MCPWM_InitStructure.DebugMode_PWM_out = DISABLE;			// 暂停MCU运行时默认电平输出使能
    MCPWM_InitStructure.MCPWM_Base0T0_UpdateEN = ENABLE;	// MCPWM 时基0 T0事件更新使能
    MCPWM_InitStructure.MCPWM_Base0T1_UpdateEN = DISABLE;	// MCPWM 时基0 T1事件更新 禁止
    MCPWM_InitStructure.MCPWM_Base1T0_UpdateEN = ENABLE;	// MCPWM 时基1 T0事件更新使能
    MCPWM_InitStructure.MCPWM_Base1T1_UpdateEN = DISABLE;	// MCPWM 时基1 T1事件更新 禁止
    MCPWM_InitStructure.CNT0_T0_Update_INT_EN = DISABLE;	// T0更新事件 中断使能或关闭
    MCPWM_InitStructure.FAIL0_INT_EN = DISABLE;						// FAIL0事件 中断使能或关闭
    MCPWM_InitStructure.FAIL1_INT_EN = DISABLE;						// FAIL1事件 中断使能或关闭
    MCPWM_InitStructure.FAIL1_INPUT_EN = DISABLE;					// FAIL1通道急停功能打开或关闭
    MCPWM_InitStructure.FAIL1_Signal_Sel = FAIL_SEL_CMP;	// FAIL1事件信号选择，比较器或IO口
    MCPWM_InitStructure.FAIL1_Polarity = LOW_LEVEL;				// FAIL1事件极性选择，高有效或低有效

    MCPWM_Init(MCPWM0, &MCPWM_InitStructure);			// MCPWM0 模块初始化
//    MCPWM_SwapFunction();
}

