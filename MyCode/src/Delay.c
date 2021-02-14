/*
 * @Author: your name
 * @Date: 2021-02-02 15:42:24
 * @LastEditTime: 2021-02-02 22:38:13
 * @LastEditors: Please set LastEditors
 * @Description: 
 * @FilePath: \FingerSim\MyCode\src\Delay.c
 * @Build by Zale, FzStudio
 */
#include "Delay.h"

//延时程序参考淘宝例程
static u8  fac_us=0;
static u16 fac_ms=0;
/**
 * @description: 延迟函数初始化
 * @param {*}
 * @return {*}
 */
void Delay_init()	 
{
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
	fac_us=SystemCoreClock/8000000;
    fac_ms=(u16)fac_us*1000;
}
/**
 * @description: 延迟n微秒
 * @param {u32} nus 微秒数
 * @return {*}
 */
void Delay_us(u32 nus)
{		
	u32 temp;	    	 
	SysTick->LOAD=nus*fac_us; 
	SysTick->VAL=0x00;
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;
	SysTick->VAL =0X00;
}
/**
 * @description: 延迟n毫秒
 * @param {u16} nms 毫秒数
 * @return {*}
 */
void Delay_ms(u16 nms)
{	 		  	  
	u32 temp;		   
	SysTick->LOAD=(u32)nms*fac_ms;
	SysTick->VAL =0x00;
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;
	SysTick->VAL =0X00;
}