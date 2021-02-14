/*
 * @Author: Zale
 * @Date: 2021-02-02 15:28:37
 * @LastEditTime: 2021-02-02 22:25:37
 * @LastEditor: Zale
 * @Description: 硬件驱动相关函数
 * @FilePath: \prjtest\MyCode\src\HardwareDriver.c
 * @Build by Zale, FzStudio
 */

#include "HardwareDriver.h"
//ADC读取部分参考淘宝例程
/**
 * @description: ADC模块初始化程序
 *               使用A1引脚读取输入，ADC1通道
 * @param {*}
 * @return {*}
 */
void  Adc_Init(void)
{ 	
	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_ADC1,ENABLE);	  
 

	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   

	//配置引脚A1，其作为ADC输入引脚
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	ADC_DeInit(ADC1);

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfChannel = 1;
	ADC_Init(ADC1, &ADC_InitStructure); 


	ADC_Cmd(ADC1, ENABLE);
	
	ADC_ResetCalibration(ADC1);	

	while(ADC_GetResetCalibrationStatus(ADC1));	
	
	ADC_StartCalibration(ADC1);
 
	while(ADC_GetCalibrationStatus(ADC1));
 
//	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		

}
/**
 * @description: 读取一次ADC的值
 * @param {*}
 * @return {*}
 */
u16 Get_Adc()   
{

	ADC_RegularChannelConfig(ADC1,1,1,ADC_SampleTime_239Cycles5);
  
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);

	while(!ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC));

	return ADC_GetConversionValue(ADC1);
}

/**
 * @description: 获取处理过后的ADC值，
 * 				读取十二次数据，去掉最大值最小值对剩下的十个值取均值
 * @param {*} 无
 * @return {float} 处理后的值
 */
float GetAdcDeal()
{
    u8 i;
    u16 tmp[12],lt=0,ht=0;
	int sum=0;
	//读取12次ADC的值
    for(i=0;i<12;++i)
    {
        tmp[i]=Get_Adc();
    }
	//遍历查找最大值和最小值所处于的位置
    for(i=0;i<12;++i)
    {
        if(tmp[i]<tmp[lt])
		{
			lt=i;
		}
		if(tmp[i]>tmp[i])
		{
			ht=i;
		}
    }
	//去掉最大值最小值求和
	for(i=0;i<12;++i)
	{
		if((i!=lt)||(i!=ht))
		{
			sum+=tmp[i];
		}
	}
	//返回均值
	return sum/10;
}

//PWM部分程序参考 https://blog.csdn.net/qq_38410730/article/details/79996222
//定时器程序参考 https://blog.csdn.net/qq_38410730/article/details/79976785
/**
 * @description: 设定一个定时器中断用于PWM波生成
 * @param {*}
 * @return {*}
 */
void PWMCfg()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//使能定时器3时钟
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  | RCC_APB2Periph_AFIO, ENABLE);  //使能GPIO外设和AFIO复用功能模块时钟
	
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE); //Timer3部分重映射  TIM3_CH2->PB5    
 
   //设置该引脚为复用输出功能,输出TIM3 CH2的PWM脉冲波形	GPIOB.5
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; //TIM_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIO
 
   //初始化TIM3
   //Tout=（ARR+1)(PSC+1)/TIMxCLK
	TIM_TimeBaseStructure.TIM_Period = arv; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler = psc; //设置用来作为TIMx时钟频率除数的预分频值 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	
	//初始化TIM3 Channel2 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM3 OC2
 
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM3在CCR2上的预装载寄存器
 
	TIM_Cmd(TIM3, ENABLE);  //使能TIM3

}


/**
 * @description: 按照指定占空比输出PWM信号
 * @param {int} Duty 占空比
 * @return {*}
 */
void PWMCtrl(int Duty)
{
	
	TIM_SetCompare2(TIM3,Duty);
}


/**
 * @description: 控制舵机旋转设定角度
 * @param {int} Angle 角度值
 * @return {*}
 */
void FingerCtrl(int Angle)
{
	TIM_SetCompare2(TIM3,(Angle/180)*20+175);
}