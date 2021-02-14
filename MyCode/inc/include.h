/*
 * @Author: your name
 * @Date: 2021-02-01 17:13:08
 * @LastEditTime: 2021-02-13 22:52:58
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \FingerSim\MyCode\inc\include.h
 */
#ifndef _INCLUDE_H_
#define _INCLUDE_H_

#include <stm32f10x_conf.h>
#include <math.h>
#include <Delay.h>
#include <HardwareDriver.h>

#define ALLTEST 0   //完整测试
#define PWMTEST 1   //PWM测试
#define ADCTEST 2   //弯曲传感器测试


//以下几个define都是瞎写的，需要根据硬件调试确定
#define SensorMax 999 //传感器所能读取到到的ADC最大值
#define SensorMin 0 //传感器所能独到的ADC最小值
#define kAngle 1 //由ADC值转化至角度值的转换系数，假设其是正比关系

//以下几个define是推算出的值
#define MotorMax 195 //舵机180度时的占空比
#define MotorMin 175 //舵机0度时的占空比
#define arv 199 //定时器中断自动重装载寄存器周期的值
#define psc 7199 //定时器中断的预分频系数

//



#endif
