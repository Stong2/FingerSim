/*
 * @Author: Zale
 * @Date: 2021-02-02 15:28:10
 * @LastEditTime: 2021-02-13 22:43:54
 * @LastEditor: Zale
 * @Description: 硬件驱动程序头文件
 * @FilePath: \FingerSim\MyCode\inc\HardwareDriver.h
 * @Build by Zale, FzStudio
 */

#ifndef _HARDWAREDRIVER_H
#define _HARDWAREDRIVER_H
#include "include.h"

void PWMCfg();
void FingerCtrl(int Angle);
void Adc_Init(void);
u16 Get_Adc();
float GetAdcDeal();

#endif