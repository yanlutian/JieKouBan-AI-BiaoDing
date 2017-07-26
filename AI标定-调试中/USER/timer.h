#ifndef _TIMER_H
#define _TIMER_H
#include "sys.h"




#define		CycleEvent_TIMX		TIM2	//�������¼���ʱ��
#define		F1Count_TIMX		TIM3	//Ƶ��1������ʱ��
#define		F2Count_TIMX		TIM4	//Ƶ��2������ʱ��

#define		Scan_Cycle_ms		500				//�������¼����ڣ���λ��ms<���ȡ��Ϊ:100*n,1=<n<=5>  ɨ������(����)������Ƶ�ʳɷ���(����)

extern float PNums_Of_PerS;//counts/xmsת����counts/Sʱ��ϵ��

extern u8 volatile F1Count_State,F2Count_State;//Ƶ�ʲ���״̬��־
extern u32 volatile F1Count_Value,F2Count_Value;//Ƶ�ʲ���ֵ


void TIM2_Int_Init( void);
void TIM5_Int_Init( void);
void TIM3_Int_Init(u32 arr,u16 psc);

void TIM3_Init( void);
void TIM4_Init( void);
void TIM2_Init(u32 arr,u16 psc);

#endif
