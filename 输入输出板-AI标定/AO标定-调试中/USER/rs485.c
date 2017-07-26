#include "sys.h"		    
#include "rs485.h"	 
#include "delay.h"
#include "timer4_usart.h"

//���ջ����� 	
u8 MB_CH1_RX_BUF[RX_SIZE];  	//���ջ���
u8 MB_CH2_RX_BUF[RX_SIZE];  	
u8 MB_CH3_RX_BUF[RX_SIZE];  	
u8 MB_CH4_RX_BUF[RX_SIZE];  	
//���յ������ݳ���
u8 MB_CH1_RX_CNT=0;						//�������ݳ���
u8 MB_CH2_RX_CNT=0; 
u8 MB_CH3_RX_CNT=0; 
u8 MB_CH4_RX_CNT=0; 



/***********/
/***********/
#if MB_CH1_Enable
/***********/
#define MB_CH1_TX_EN		PAout(8)	//ch1 control pin
//��ʼ��IO ����1
//bound:������	  
void MB_CH1_Init(u32 bound)
{  	 
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(MB_CH1_PORT_RCC,ENABLE); //ʹ�ܴ��ڹܽ�ʱ��
	RCC_AHB1PeriphClockCmd(MB_CH1_CON_RCC,ENABLE); //ʹ�ܿ��ƹܽ�ʱ��
	RCC_APB2PeriphClockCmd(MB_CH1_USART_RCC,ENABLE);//ʹ�ܴ�������ʱ��
	
  //����2���Ÿ���ӳ��
	GPIO_PinAFConfig(GPIOA,MB_CH1_USART_TX_PS,MB_CH1_USART_AF); //����
	GPIO_PinAFConfig(GPIOA,MB_CH1_USART_RX_PS,MB_CH1_USART_AF); //����
	
	//USART2    
  GPIO_InitStructure.GPIO_Pin = MB_CH1_USART_RX | MB_CH1_USART_TX; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
	GPIO_Init(MB_CH1_USART_PORT,&GPIO_InitStructure); //��ʼ��
	
	//PG8���������485ģʽ����  
  GPIO_InitStructure.GPIO_Pin = MB_CH1_CON_PIN; //
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //�������
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
	GPIO_Init(MB_CH1_USART_PORT,&GPIO_InitStructure); //��ʼ��
	
	//USART2 ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
  USART_Init(MB_CH1_USART, &USART_InitStructure); //��ʼ������
	
  USART_Cmd(MB_CH1_USART, ENABLE);  //ʹ�ܴ���
	USART_ClearFlag(MB_CH1_USART, USART_FLAG_TC);
	
#if MB_CH1_RX_EN	
	USART_ITConfig(MB_CH1_USART, USART_IT_RXNE, ENABLE);//���������ж�

	//Usart2 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = MB_CH1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��NVIC�Ĵ���

#endif	

	MB_CH1_TX_EN=1;				//Ĭ��Ϊ����ģʽ	
}
//RS485����len���ֽ�.
//buf:�������׵�ַ
//len:���͵��ֽ���(Ϊ�˺ͱ�����Ľ���ƥ��,���ｨ�鲻Ҫ����64���ֽ�)
void MB_CH1_SendData(u8 *buf,u8 len)
{
	u8 t;
	MB_CH1_TX_EN=0;			//����Ϊ����ģʽ
  	for(t=0;t<len;t++)		//ѭ����������
	{
	  while(USART_GetFlagStatus(MB_CH1_USART,USART_FLAG_TC)==RESET); //�ȴ����ͽ���		
    USART_SendData(MB_CH1_USART,buf[t]); //��������
	}	 
	while(USART_GetFlagStatus(MB_CH1_USART,USART_FLAG_TC)==RESET); //�ȴ����ͽ���		
	MB_CH1_RX_CNT=0;	  
	MB_CH1_TX_EN=1;				//����Ϊ����ģʽ	
}
#endif







/***********/
/***********/
#if MB_CH2_Enable
/***********/
#define MB_CH2_TX_EN		PCout(9)	////ch2 control pin
//��ʼ��IO ����2
//bound:������	  
void MB_CH2_Init(u32 bound)
{  	 
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	//
	TIM4_Int_Init( 500 - 1, 8400 - 1); //��ʱ��ʱ��84M����Ƶϵ��8400������84M/8400=10Khz�ļ���Ƶ�ʣ�����100��Ϊ10ms

	//
	RCC_AHB1PeriphClockCmd(MB_CH2_PORT_RCC,ENABLE); //ʹ�ܴ��ڹܽ�ʱ��
	RCC_AHB1PeriphClockCmd(MB_CH2_CON_RCC,ENABLE); //ʹ�ܿ��ƹܽ�ʱ��
	RCC_APB2PeriphClockCmd(MB_CH2_USART_RCC,ENABLE);//ʹ�ܴ�������ʱ��
	
  //����2���Ÿ���ӳ��
	GPIO_PinAFConfig(MB_CH2_USART_PORT,MB_CH2_USART_RX_PS,MB_CH2_USART_AF); //����
	GPIO_PinAFConfig(MB_CH2_USART_PORT,MB_CH2_USART_TX_PS,MB_CH2_USART_AF); //����
	
	//USART2    
  GPIO_InitStructure.GPIO_Pin = MB_CH2_USART_RX | MB_CH2_USART_TX; //
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
	GPIO_Init(MB_CH2_USART_PORT,&GPIO_InitStructure); //��ʼ��
	
	//PG8���������485ģʽ����  
	GPIO_InitStructure.GPIO_Pin = MB_CH2_CON_PIN; //GPIOG8
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //�������
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
	GPIO_Init(MB_CH2_CON_PORT,&GPIO_InitStructure); //��ʼ��
	
	//USART2 ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
  USART_Init(MB_CH2_USART, &USART_InitStructure); //��ʼ������
	
  USART_Cmd(MB_CH2_USART, ENABLE);  //ʹ�ܴ���
	USART_ClearFlag(MB_CH2_USART, USART_FLAG_TC);
	
#if MB_CH2_RX_EN	
	USART_ITConfig(MB_CH2_USART, USART_IT_RXNE, ENABLE);//���������ж�

	//Usart2 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = MB_CH2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =2;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��NVIC�Ĵ���

#endif	
	
	MB_CH2_TX_EN=1;				//Ĭ��Ϊ����ģʽ	
}
//RS485����len���ֽ�.
//buf:�������׵�ַ
//len:���͵��ֽ���(Ϊ�˺ͱ�����Ľ���ƥ��,���ｨ�鲻Ҫ����64���ֽ�)
void MB_CH2_SendData(u8 *buf,u8 len)
{
	u8 t;
	MB_CH2_TX_EN=0;			//����Ϊ����ģʽ
  	for(t=0;t<len;t++)		//ѭ����������
	{
	  while(USART_GetFlagStatus(MB_CH2_USART,USART_FLAG_TC)==RESET); //�ȴ����ͽ���		
    USART_SendData(MB_CH2_USART,buf[t]); //��������
	}	 
	while(USART_GetFlagStatus(MB_CH2_USART,USART_FLAG_TC)==RESET); //�ȴ����ͽ���		
	MB_CH2_RX_CNT=0;	  
	MB_CH2_TX_EN=1;				//����Ϊ����ģʽ	
}
#endif






/***********/
/***********/
#if MB_CH3_Enable
/***********/
#define MB_CH3_TX_EN		PDout(11)//ch3 control pin
//��ʼ��IO ����6
//bound:������	  
void MB_CH3_Init(u32 bound)
{  	 
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(MB_CH3_PORT_RCC,ENABLE); //ʹ�ܴ��ڹܽ�ʱ��
	RCC_AHB1PeriphClockCmd(MB_CH3_CON_RCC,ENABLE); //ʹ�ܿ��ƹܽ�ʱ��
	RCC_APB1PeriphClockCmd(MB_CH3_USART_RCC,ENABLE);//ʹ�ܴ�������ʱ��
	
  //����2���Ÿ���ӳ��
	GPIO_PinAFConfig(MB_CH3_USART_PORT,MB_CH3_USART_RX_PS,MB_CH3_USART_AF); //����
	GPIO_PinAFConfig(MB_CH3_USART_PORT,MB_CH3_USART_TX_PS,MB_CH3_USART_AF); //����
	
	//USART2    
  GPIO_InitStructure.GPIO_Pin = MB_CH3_USART_RX | MB_CH3_USART_TX; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
	GPIO_Init(MB_CH3_USART_PORT,&GPIO_InitStructure); //��ʼ��
	
	//PG8���������485ģʽ����  
  GPIO_InitStructure.GPIO_Pin = MB_CH3_CON_PIN; //
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //�������
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
	GPIO_Init(MB_CH3_CON_PORT,&GPIO_InitStructure); //��ʼ��

	//USART2 ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
  USART_Init(MB_CH3_USART, &USART_InitStructure); //��ʼ������
	
  USART_Cmd(MB_CH3_USART, ENABLE);  //ʹ�ܴ���
	USART_ClearFlag(MB_CH3_USART, USART_FLAG_TC);
	
#if MB_CH3_RX_EN	
	USART_ITConfig(MB_CH3_USART, USART_IT_RXNE, ENABLE);//���������ж�

	//Usart2 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = MB_CH3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;		//�����ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��NVIC�Ĵ���

#endif	
	
	MB_CH3_TX_EN=1;				//Ĭ��Ϊ����ģʽ	
}
//RS485����len���ֽ�.
//buf:�������׵�ַ
//len:���͵��ֽ���(Ϊ�˺ͱ�����Ľ���ƥ��,���ｨ�鲻Ҫ����64���ֽ�)
void MB_CH3_SendData(u8 *buf,u8 len)
{
	u8 t;
	MB_CH3_TX_EN=0;			//����Ϊ����ģʽ
  	for(t=0;t<len;t++)		//ѭ����������
	{
	  while(USART_GetFlagStatus(MB_CH3_USART,USART_FLAG_TC)==RESET); //�ȴ����ͽ���		
    USART_SendData(MB_CH3_USART,buf[t]); //��������
	}	 
	while(USART_GetFlagStatus(MB_CH3_USART,USART_FLAG_TC)==RESET); //�ȴ����ͽ���		
	MB_CH3_RX_CNT=0;	  
	MB_CH3_TX_EN=1;				//����Ϊ����ģʽ	
}
#endif





/***********/
/***********/
#if MB_CH4_Enable
/***********/
#define MB_CH4_TX_EN		PDout(10)	//ch4 control pin
//��ʼ��IO ����1
//bound:������	  
void MB_CH4_Init(u32 bound)
{  	 
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(MB_CH4_PORT_RCC,ENABLE); //ʹ�ܴ��ڹܽ�ʱ��
	RCC_AHB1PeriphClockCmd(MB_CH4_CON_RCC,ENABLE); //ʹ�ܿ��ƹܽ�ʱ��
	RCC_APB1PeriphClockCmd(MB_CH4_USART_RCC,ENABLE);//ʹ�ܴ�������ʱ��
	
  //����2���Ÿ���ӳ��
	GPIO_PinAFConfig(MB_CH4_USART_PORT,MB_CH4_USART_RX_PS,MB_CH4_USART_AF); //����
	GPIO_PinAFConfig(MB_CH4_USART_PORT,MB_CH4_USART_TX_PS,MB_CH4_USART_AF); //����
	
	//USART2    
  GPIO_InitStructure.GPIO_Pin = MB_CH4_USART_RX | MB_CH4_USART_TX; //
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
	GPIO_Init(MB_CH4_USART_PORT,&GPIO_InitStructure); //��ʼ��
	
	//PG8���������485ģʽ����  
  GPIO_InitStructure.GPIO_Pin = MB_CH4_CON_PIN; //
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //�������
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
	GPIO_Init(MB_CH4_CON_PORT,&GPIO_InitStructure); //��ʼ��
	
	//USART2 ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
  USART_Init(MB_CH4_USART, &USART_InitStructure); //��ʼ������
	
  USART_Cmd(MB_CH4_USART, ENABLE);  //ʹ�ܴ��� 2
	USART_ClearFlag(MB_CH4_USART, USART_FLAG_TC);
	
#if MB_CH4_RX_EN	
	USART_ITConfig(MB_CH4_USART, USART_IT_RXNE, ENABLE);//���������ж�

	//Usart2 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = MB_CH4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =2;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��NVIC�Ĵ���

#endif	

	MB_CH4_TX_EN=1;				//Ĭ��Ϊ����ģʽ	
}
//RS485����len���ֽ�.
//buf:�������׵�ַ
//len:���͵��ֽ���(Ϊ�˺ͱ�����Ľ���ƥ��,���ｨ�鲻Ҫ����64���ֽ�)
void MB_CH4_SendData(u8 *buf,u8 len)
{
	u8 t;
	MB_CH4_TX_EN=0;			//����Ϊ����ģʽ
  	for(t=0;t<len;t++)		//ѭ����������
	{
	  while(USART_GetFlagStatus(MB_CH4_USART,USART_FLAG_TC)==RESET); //�ȴ����ͽ���		
    USART_SendData(MB_CH4_USART,buf[t]); //��������
	}	 
	while(USART_GetFlagStatus(MB_CH4_USART,USART_FLAG_TC)==RESET); //�ȴ����ͽ���		
	MB_CH4_RX_CNT=0;	  
	MB_CH4_TX_EN=1;				//����Ϊ����ģʽ	
}



#endif

volatile u8 ch2_rec_flag=0;
volatile u8 ch3_rec_flag=0;
volatile u8 ch4_rec_flag=0;


//USART2�жϳ���
void USART2_IRQHandler()
{
	if( USART_GetITStatus( USART2,USART_IT_RXNE)!=RESET)//���ܵ�����
	{			

//			USART1_RX_BUF[USART1_RX_STA++]=USART_ReceiveData( USART2);

		ch4_rec_flag = 1;//while(1);
		
	//��������жϱ�־		
			USART_ClearITPendingBit( USART2,USART_IT_RXNE) ;
	}
}



//USART2�жϳ���
void USART3_IRQHandler()
{
	if( USART_GetITStatus( USART3,USART_IT_RXNE)!=RESET)//���ܵ�����
	{			

//			USART1_RX_BUF[USART1_RX_STA++]=USART_ReceiveData( USART3);
				
				ch3_rec_flag = 1;

		
	//��������жϱ�־		
			USART_ClearITPendingBit( USART3,USART_IT_RXNE) ;
	}
}

//u16		USART_CH2_RX_STA=0;
//u8 USART_CH2_RX_BUF[200];
////USART2�жϳ���
//void USART6_IRQHandler()
//{
//	u8 temp_rec=0;
//	//
//	if( USART_GetITStatus( USART6,USART_IT_RXNE)!=RESET)//���ܵ�����
//	{			
//			temp_rec=USART_ReceiveData( USART6);

//			USART_CH2_RX_BUF[USART_CH2_RX_STA++]=USART_ReceiveData( USART6);
//			if( temp_rec)
//			{
//			ch2_rec_flag = 1;
//			}

//		
//	//��������жϱ�־		
//			USART_ClearITPendingBit( USART6,USART_IT_RXNE) ;
//	}
//}







