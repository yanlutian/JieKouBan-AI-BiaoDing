#ifndef _TIMER_H
#define _TIMER_H
#include "sys.h"




#define		CycleEvent_TIMX		TIM2	//周期性事件定时器
#define		F1Count_TIMX		TIM3	//频率1测量定时器
#define		F2Count_TIMX		TIM4	//频率2测量定时器

#define		Scan_Cycle_ms		500				//周期性事件周期，单位：ms<最好取整为:100*n,1=<n<=5>  扫描周期(速率)和输入频率成反比(正比)

extern float PNums_Of_PerS;//counts/xms转换成counts/S时的系数

extern u8 volatile F1Count_State,F2Count_State;//频率测量状态标志
extern u32 volatile F1Count_Value,F2Count_Value;//频率测量值


void TIM2_Int_Init( void);
void TIM5_Int_Init( void);
void TIM3_Int_Init(u32 arr,u16 psc);

void TIM3_Init( void);
void TIM4_Init( void);
void TIM2_Init(u32 arr,u16 psc);

#endif
