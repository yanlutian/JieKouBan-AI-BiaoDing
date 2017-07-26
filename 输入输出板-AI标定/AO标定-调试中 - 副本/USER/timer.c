#include "timer.h"

float PNums_Of_PerS=1000.0/Scan_Cycle_ms;//counts/xms转换成counts/S时的系数

u8 volatile F1Count_State=0,F2Count_State=0;//频率测量状态标志
u32 volatile F1Count_Value=0,F2Count_Value=0;//频率测量值

//TIM3工作于计数器模式
void TIM3_Init( void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  ///使能TIM3时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//使能GPIOF时钟

	//计数
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//上拉
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource6,GPIO_AF_TIM3); //PA0复用位定时器5
	
	TIM3->CCMR1 |= 0x0001;			//IC1->TI1  IC2->TI2
	TIM3->CCMR1 &= 0xff0f;			//无滤波器	
	TIM3->CCER&=0xfff5;//上升沿
	TIM3->SMCR |=0x0007;			//从模式选择外部时钟模式1
	TIM3->SMCR &= ~0x0050;TIM3->SMCR |= 0x0050;//选择TI1作为触发源
	TIM3->CR1 |= 0x01;				//使能定时器
}
//TIM4工作于计数器模式
void TIM4_Init( void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);  ///使能TIM3时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);//使能GPIOF时钟

	//计数
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//下拉
  GPIO_Init(GPIOD, &GPIO_InitStructure);//初始化
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource12,GPIO_AF_TIM4); //PA0复用位定时器5
	
	TIM4->CCMR1 |= 0x0001;			//IC1->TI1  IC2->TI2
	TIM4->CCMR1 &= 0xff0f;			//无滤波器	
	TIM4->CCER&=0xfff5;//上升沿
	TIM4->SMCR |=0x0007;			//从模式选择外部时钟模式1
	TIM4->SMCR &= ~0x0050;TIM4->SMCR |= 0x0050;//选择TI1作为触发源
	TIM4->CR1 |= 0x01;				//使能定时器
}

//周期定时器
void TIM2_Init(u32 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);  ///使能TIM3时钟
	
  TIM_TimeBaseInitStructure.TIM_Period = arr; 	//自动重装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //定时器分频
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 	
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);//初始化TIM3
	
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE); //允许定时器3更新中断
	TIM_Cmd(TIM2,ENABLE); //使能定时器3
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn; //定时器3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x00; //抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x00; //子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}


//NULL
void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET) //溢出中断
	{	
	}
	
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);  //清除中断标志位
}
////NULL
//void TIM4_IRQHandler(void)
//{
//	if(TIM_GetITStatus(TIM4,TIM_IT_Update)==SET) //溢出中断
//	{	
//	}
//	
//	TIM_ClearITPendingBit(TIM4,TIM_IT_Update);  //清除中断标志位
//}












