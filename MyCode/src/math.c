/*
 * @Author: Zale
 * @Date: 2021-02-01 17:12:38
 * @LastEditTime: 2021-02-02 21:21:14
 * @LastEditor: Zale
 * @Description: 
 * @FilePath: \prjtest\MyCode\src\math.c
 * @Build by Zale, FzStudio
 */

#include "math.h"

/**
 * @description: 归一化处理
 * @param {float} Uplimit 数值上限
 * @param {float} Lowlimit 数值下限
 * @param {float} Val 待处理数值
 * @return {float} 处理后的数值
 */
float Normalize(float Uplimit,float Lowlimit,float Val)
{
    return (Val-Lowlimit)/(Uplimit-Lowlimit);
}

/**
 * @description: 快速排序
 * @param {u16} arr 待排序数组
 * @param {u8} low 本次排序的起始位置
 * @param {u8} Val 本次排序的终止位置
 * @return {} 
 */
void QuickSort(u16 arr[],u8 low,u8 high)
{
    u8 i = low;
    u8 j = high;
    u16 k = arr[low];
    if (low < high)
    {
        while (i < j)
        {
            while(i < j && arr[j] >= k)     // 从右向左找第一个小于k的数
            {
                j--;
            }
 
            if(i < j)
            {
                arr[i++] = arr[j];
            }
 
            while(i < j && arr[i] < k)      // 从左向右找第一个大于等于k的数
            {
                i++;
            }

            if(i < j)
            {
                arr[j--] = arr[i];
            }
        }
 
        arr[i] = k;
 
        // 递归调用
        QuickSort(arr, low, i - 1);     // 排序k左边
        QuickSort(arr, i + 1, high);    // 排序k右边
    }
    
}
