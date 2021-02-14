/*
 * @Author: Zale
 * @Date: 2021-02-01 17:09:20
 * @LastEditTime: 2021-02-14 00:18:51
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \FingerSim\MyCode\main.c
 * 程序运行前务必先确认<include.h>中的TESTMODE变量值
 * 是否置为指定值
 */
#include <include.h>
//此处根据<include.h>中定义的测试模式修改
#define TESTMODE ALLTEST

#if TESTMODE==ALLTEST
/**
 * @description: 全部test，也就是release了
 *              全部丢在一个大的while里跑
 * @param {*}
 * @return {*}
 */
int main()
{
    //AngleSensorValue角度传感器采集到的AD值
    //FingerAngle换算得到的角度值，目前假设二者之间是一个正比例关系
    float AngleSensorValue,FingerAngle;
    //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    //定时器中断配置初始化
    PWMCfg();
    Delay_init();
    while(1)
    {
        //读取均值滤波和归一化处理后的传感器角度数据
        AngleSensorValue=Normalize(SensorMax,SensorMin,GetAdcDeal());
        //将传感器角度数据转化为角度值
        FingerAngle=AngleSensorValue*kAngle;
        //控制舵机旋转至指定角度
        FingerCtrl(FingerAngle);
    }
}
#elif TESTMODE==PWMTEST
/**
 * @description: PWMtest，测试舵机模块
 * @param {*}
 * @return {*}
 */
int main()
{
    int t=0,f=1;
    PWMCfg();
    Delay_init();
    while(1)
    {
        if(f)
        {
            FingerCtrl(t);
            t+=10;
            if(t>=180)
                f=0;
        }
        else
        {
            FingerCtrl(t);
            t-=10;
            if(t<=10)
                f=1;
        }
        Delay_ms(500);
    }
}
#elif TESTMODE==ADCTEST
/**
 * @description: ADCtest，测试弯曲传感器模块
 *              由于没有串口等输出模块，建议直接在debug模式
 *              中读取指定变量的值
 * @param {*}
 * @return {*}
 */
int main()
{
    int ADCvalue=0;
    Adc_Init();
    delay_init();
    while(1)
    {
        ADCvalue=GetAdcDeal();
        Delay_ms(100);
    }
}
#endif