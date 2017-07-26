#include "timer.h"

float PNums_Of_PerS=1000.0/Scan_Cycle_ms;//counts/xmsת����counts/Sʱ��ϵ��

u8 volatile F1Count_State=0,F2Count_State=0;//Ƶ�ʲ���״̬��־
u32 volatile F1Count_Value=0,F2Count_Value=0;//Ƶ�ʲ���ֵ

//TIM3�����ڼ�����ģʽ
void TIM3_Init( void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  ///ʹ��TIM3ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//ʹ��GPIOFʱ��

	//����
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//����
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource6,GPIO_AF_TIM3); //PA0����λ��ʱ��5
	
	TIM3->CCMR1 |= 0x0001;			//IC1->TI1  IC2->TI2
	TIM3->CCMR1 &= 0xff0f;			//���˲���	
	TIM3->CCER&=0xfff5;//������
	TIM3->SMCR |=0x0007;			//��ģʽѡ���ⲿʱ��ģʽ1
	TIM3->SMCR &= ~0x0050;TIM3->SMCR |= 0x0050;//ѡ��TI1��Ϊ����Դ
	TIM3->CR1 |= 0x01;				//ʹ�ܶ�ʱ��
}
//TIM4�����ڼ�����ģʽ
void TIM4_Init( void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);  ///ʹ��TIM3ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);//ʹ��GPIOFʱ��

	//����
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//����ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//����
  GPIO_Init(GPIOD, &GPIO_InitStructure);//��ʼ��
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource12,GPIO_AF_TIM4); //PA0����λ��ʱ��5
	
	TIM4->CCMR1 |= 0x0001;			//IC1->TI1  IC2->TI2
	TIM4->CCMR1 &= 0xff0f;			//���˲���	
	TIM4->CCER&=0xfff5;//������
	TIM4->SMCR |=0x0007;			//��ģʽѡ���ⲿʱ��ģʽ1
	TIM4->SMCR &= ~0x0050;TIM4->SMCR |= 0x0050;//ѡ��TI1��Ϊ����Դ
	TIM4->CR1 |= 0x01;				//ʹ�ܶ�ʱ��
}

//���ڶ�ʱ��
void TIM2_Init(u32 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);  ///ʹ��TIM3ʱ��
	
  TIM_TimeBaseInitStructure.TIM_Period = arr; 	//�Զ���װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 	
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);//��ʼ��TIM3
	
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE); //����ʱ��3�����ж�
	TIM_Cmd(TIM2,ENABLE); //ʹ�ܶ�ʱ��3
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn; //��ʱ��3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x00; //��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x00; //�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}


//NULL
void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET) //����ж�
	{	
	}
	
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);  //����жϱ�־λ
}
////NULL
//void TIM4_IRQHandler(void)
//{
//	if(TIM_GetITStatus(TIM4,TIM_IT_Update)==SET) //����ж�
//	{	
//	}
//	
//	TIM_ClearITPendingBit(TIM4,TIM_IT_Update);  //����жϱ�־λ
//}












