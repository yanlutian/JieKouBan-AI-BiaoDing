#include "sys.h"		    
#include "rs485.h"	 
#include "delay.h"
#include "timer4_usart.h"

//接收缓存区 	
u8 MB_CH1_RX_BUF[RX_SIZE];  	//接收缓冲
u8 MB_CH2_RX_BUF[RX_SIZE];  	
u8 MB_CH3_RX_BUF[RX_SIZE];  	
u8 MB_CH4_RX_BUF[RX_SIZE];  	
//接收到的数据长度
u8 MB_CH1_RX_CNT=0;						//接收数据长度
u8 MB_CH2_RX_CNT=0; 
u8 MB_CH3_RX_CNT=0; 
u8 MB_CH4_RX_CNT=0; 



/***********/
/***********/
#if MB_CH1_Enable
/***********/
#define MB_CH1_TX_EN		PAout(8)	//ch1 control pin
//初始化IO 串口1
//bound:波特率	  
void MB_CH1_Init(u32 bound)
{  	 
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(MB_CH1_PORT_RCC,ENABLE); //使能串口管脚时钟
	RCC_AHB1PeriphClockCmd(MB_CH1_CON_RCC,ENABLE); //使能控制管脚时钟
	RCC_APB2PeriphClockCmd(MB_CH1_USART_RCC,ENABLE);//使能串口外设时钟
	
  //串口2引脚复用映射
	GPIO_PinAFConfig(GPIOA,MB_CH1_USART_TX_PS,MB_CH1_USART_AF); //复用
	GPIO_PinAFConfig(GPIOA,MB_CH1_USART_RX_PS,MB_CH1_USART_AF); //复用
	
	//USART2    
  GPIO_InitStructure.GPIO_Pin = MB_CH1_USART_RX | MB_CH1_USART_TX; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	GPIO_Init(MB_CH1_USART_PORT,&GPIO_InitStructure); //初始化
	
	//PG8推挽输出，485模式控制  
  GPIO_InitStructure.GPIO_Pin = MB_CH1_CON_PIN; //
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	GPIO_Init(MB_CH1_USART_PORT,&GPIO_InitStructure); //初始化
	
	//USART2 初始化设置
	USART_InitStructure.USART_BaudRate = bound;//波特率设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
  USART_Init(MB_CH1_USART, &USART_InitStructure); //初始化串口
	
  USART_Cmd(MB_CH1_USART, ENABLE);  //使能串口
	USART_ClearFlag(MB_CH1_USART, USART_FLAG_TC);
	
#if MB_CH1_RX_EN	
	USART_ITConfig(MB_CH1_USART, USART_IT_RXNE, ENABLE);//开启接受中断

	//Usart2 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = MB_CH1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化NVIC寄存器

#endif	

	MB_CH1_TX_EN=1;				//默认为接收模式	
}
//RS485发送len个字节.
//buf:发送区首地址
//len:发送的字节数(为了和本代码的接收匹配,这里建议不要超过64个字节)
void MB_CH1_SendData(u8 *buf,u8 len)
{
	u8 t;
	MB_CH1_TX_EN=0;			//设置为发送模式
  	for(t=0;t<len;t++)		//循环发送数据
	{
	  while(USART_GetFlagStatus(MB_CH1_USART,USART_FLAG_TC)==RESET); //等待发送结束		
    USART_SendData(MB_CH1_USART,buf[t]); //发送数据
	}	 
	while(USART_GetFlagStatus(MB_CH1_USART,USART_FLAG_TC)==RESET); //等待发送结束		
	MB_CH1_RX_CNT=0;	  
	MB_CH1_TX_EN=1;				//设置为接收模式	
}
#endif







/***********/
/***********/
#if MB_CH2_Enable
/***********/
#define MB_CH2_TX_EN		PCout(9)	////ch2 control pin
//初始化IO 串口2
//bound:波特率	  
void MB_CH2_Init(u32 bound)
{  	 
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	//
	TIM4_Int_Init( 500 - 1, 8400 - 1); //定时器时钟84M，分频系数8400，所以84M/8400=10Khz的计数频率，计数100次为10ms

	//
	RCC_AHB1PeriphClockCmd(MB_CH2_PORT_RCC,ENABLE); //使能串口管脚时钟
	RCC_AHB1PeriphClockCmd(MB_CH2_CON_RCC,ENABLE); //使能控制管脚时钟
	RCC_APB2PeriphClockCmd(MB_CH2_USART_RCC,ENABLE);//使能串口外设时钟
	
  //串口2引脚复用映射
	GPIO_PinAFConfig(MB_CH2_USART_PORT,MB_CH2_USART_RX_PS,MB_CH2_USART_AF); //复用
	GPIO_PinAFConfig(MB_CH2_USART_PORT,MB_CH2_USART_TX_PS,MB_CH2_USART_AF); //复用
	
	//USART2    
  GPIO_InitStructure.GPIO_Pin = MB_CH2_USART_RX | MB_CH2_USART_TX; //
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	GPIO_Init(MB_CH2_USART_PORT,&GPIO_InitStructure); //初始化
	
	//PG8推挽输出，485模式控制  
	GPIO_InitStructure.GPIO_Pin = MB_CH2_CON_PIN; //GPIOG8
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	GPIO_Init(MB_CH2_CON_PORT,&GPIO_InitStructure); //初始化
	
	//USART2 初始化设置
	USART_InitStructure.USART_BaudRate = bound;//波特率设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
  USART_Init(MB_CH2_USART, &USART_InitStructure); //初始化串口
	
  USART_Cmd(MB_CH2_USART, ENABLE);  //使能串口
	USART_ClearFlag(MB_CH2_USART, USART_FLAG_TC);
	
#if MB_CH2_RX_EN	
	USART_ITConfig(MB_CH2_USART, USART_IT_RXNE, ENABLE);//开启接受中断

	//Usart2 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = MB_CH2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =2;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化NVIC寄存器

#endif	
	
	MB_CH2_TX_EN=1;				//默认为接收模式	
}
//RS485发送len个字节.
//buf:发送区首地址
//len:发送的字节数(为了和本代码的接收匹配,这里建议不要超过64个字节)
void MB_CH2_SendData(u8 *buf,u8 len)
{
	u8 t;
	MB_CH2_TX_EN=0;			//设置为发送模式
  	for(t=0;t<len;t++)		//循环发送数据
	{
	  while(USART_GetFlagStatus(MB_CH2_USART,USART_FLAG_TC)==RESET); //等待发送结束		
    USART_SendData(MB_CH2_USART,buf[t]); //发送数据
	}	 
	while(USART_GetFlagStatus(MB_CH2_USART,USART_FLAG_TC)==RESET); //等待发送结束		
	MB_CH2_RX_CNT=0;	  
	MB_CH2_TX_EN=1;				//设置为接收模式	
}
#endif






/***********/
/***********/
#if MB_CH3_Enable
/***********/
#define MB_CH3_TX_EN		PDout(11)//ch3 control pin
//初始化IO 串口6
//bound:波特率	  
void MB_CH3_Init(u32 bound)
{  	 
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(MB_CH3_PORT_RCC,ENABLE); //使能串口管脚时钟
	RCC_AHB1PeriphClockCmd(MB_CH3_CON_RCC,ENABLE); //使能控制管脚时钟
	RCC_APB1PeriphClockCmd(MB_CH3_USART_RCC,ENABLE);//使能串口外设时钟
	
  //串口2引脚复用映射
	GPIO_PinAFConfig(MB_CH3_USART_PORT,MB_CH3_USART_RX_PS,MB_CH3_USART_AF); //复用
	GPIO_PinAFConfig(MB_CH3_USART_PORT,MB_CH3_USART_TX_PS,MB_CH3_USART_AF); //复用
	
	//USART2    
  GPIO_InitStructure.GPIO_Pin = MB_CH3_USART_RX | MB_CH3_USART_TX; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	GPIO_Init(MB_CH3_USART_PORT,&GPIO_InitStructure); //初始化
	
	//PG8推挽输出，485模式控制  
  GPIO_InitStructure.GPIO_Pin = MB_CH3_CON_PIN; //
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	GPIO_Init(MB_CH3_CON_PORT,&GPIO_InitStructure); //初始化

	//USART2 初始化设置
	USART_InitStructure.USART_BaudRate = bound;//波特率设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
  USART_Init(MB_CH3_USART, &USART_InitStructure); //初始化串口
	
  USART_Cmd(MB_CH3_USART, ENABLE);  //使能串口
	USART_ClearFlag(MB_CH3_USART, USART_FLAG_TC);
	
#if MB_CH3_RX_EN	
	USART_ITConfig(MB_CH3_USART, USART_IT_RXNE, ENABLE);//开启接受中断

	//Usart2 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = MB_CH3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;		//子优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化NVIC寄存器

#endif	
	
	MB_CH3_TX_EN=1;				//默认为接收模式	
}
//RS485发送len个字节.
//buf:发送区首地址
//len:发送的字节数(为了和本代码的接收匹配,这里建议不要超过64个字节)
void MB_CH3_SendData(u8 *buf,u8 len)
{
	u8 t;
	MB_CH3_TX_EN=0;			//设置为发送模式
  	for(t=0;t<len;t++)		//循环发送数据
	{
	  while(USART_GetFlagStatus(MB_CH3_USART,USART_FLAG_TC)==RESET); //等待发送结束		
    USART_SendData(MB_CH3_USART,buf[t]); //发送数据
	}	 
	while(USART_GetFlagStatus(MB_CH3_USART,USART_FLAG_TC)==RESET); //等待发送结束		
	MB_CH3_RX_CNT=0;	  
	MB_CH3_TX_EN=1;				//设置为接收模式	
}
#endif





/***********/
/***********/
#if MB_CH4_Enable
/***********/
#define MB_CH4_TX_EN		PDout(10)	//ch4 control pin
//初始化IO 串口1
//bound:波特率	  
void MB_CH4_Init(u32 bound)
{  	 
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(MB_CH4_PORT_RCC,ENABLE); //使能串口管脚时钟
	RCC_AHB1PeriphClockCmd(MB_CH4_CON_RCC,ENABLE); //使能控制管脚时钟
	RCC_APB1PeriphClockCmd(MB_CH4_USART_RCC,ENABLE);//使能串口外设时钟
	
  //串口2引脚复用映射
	GPIO_PinAFConfig(MB_CH4_USART_PORT,MB_CH4_USART_RX_PS,MB_CH4_USART_AF); //复用
	GPIO_PinAFConfig(MB_CH4_USART_PORT,MB_CH4_USART_TX_PS,MB_CH4_USART_AF); //复用
	
	//USART2    
  GPIO_InitStructure.GPIO_Pin = MB_CH4_USART_RX | MB_CH4_USART_TX; //
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	GPIO_Init(MB_CH4_USART_PORT,&GPIO_InitStructure); //初始化
	
	//PG8推挽输出，485模式控制  
  GPIO_InitStructure.GPIO_Pin = MB_CH4_CON_PIN; //
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	GPIO_Init(MB_CH4_CON_PORT,&GPIO_InitStructure); //初始化
	
	//USART2 初始化设置
	USART_InitStructure.USART_BaudRate = bound;//波特率设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
  USART_Init(MB_CH4_USART, &USART_InitStructure); //初始化串口
	
  USART_Cmd(MB_CH4_USART, ENABLE);  //使能串口 2
	USART_ClearFlag(MB_CH4_USART, USART_FLAG_TC);
	
#if MB_CH4_RX_EN	
	USART_ITConfig(MB_CH4_USART, USART_IT_RXNE, ENABLE);//开启接受中断

	//Usart2 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = MB_CH4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =2;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化NVIC寄存器

#endif	

	MB_CH4_TX_EN=1;				//默认为接收模式	
}
//RS485发送len个字节.
//buf:发送区首地址
//len:发送的字节数(为了和本代码的接收匹配,这里建议不要超过64个字节)
void MB_CH4_SendData(u8 *buf,u8 len)
{
	u8 t;
	MB_CH4_TX_EN=0;			//设置为发送模式
  	for(t=0;t<len;t++)		//循环发送数据
	{
	  while(USART_GetFlagStatus(MB_CH4_USART,USART_FLAG_TC)==RESET); //等待发送结束		
    USART_SendData(MB_CH4_USART,buf[t]); //发送数据
	}	 
	while(USART_GetFlagStatus(MB_CH4_USART,USART_FLAG_TC)==RESET); //等待发送结束		
	MB_CH4_RX_CNT=0;	  
	MB_CH4_TX_EN=1;				//设置为接收模式	
}



#endif

volatile u8 ch2_rec_flag=0;
volatile u8 ch3_rec_flag=0;
volatile u8 ch4_rec_flag=0;


//USART2中断程序
void USART2_IRQHandler()
{
	if( USART_GetITStatus( USART2,USART_IT_RXNE)!=RESET)//接受到数据
	{			

//			USART1_RX_BUF[USART1_RX_STA++]=USART_ReceiveData( USART2);

		ch4_rec_flag = 1;//while(1);
		
	//清零接收中断标志		
			USART_ClearITPendingBit( USART2,USART_IT_RXNE) ;
	}
}



//USART2中断程序
void USART3_IRQHandler()
{
	if( USART_GetITStatus( USART3,USART_IT_RXNE)!=RESET)//接受到数据
	{			

//			USART1_RX_BUF[USART1_RX_STA++]=USART_ReceiveData( USART3);
				
				ch3_rec_flag = 1;

		
	//清零接收中断标志		
			USART_ClearITPendingBit( USART3,USART_IT_RXNE) ;
	}
}

//u16		USART_CH2_RX_STA=0;
//u8 USART_CH2_RX_BUF[200];
////USART2中断程序
//void USART6_IRQHandler()
//{
//	u8 temp_rec=0;
//	//
//	if( USART_GetITStatus( USART6,USART_IT_RXNE)!=RESET)//接受到数据
//	{			
//			temp_rec=USART_ReceiveData( USART6);

//			USART_CH2_RX_BUF[USART_CH2_RX_STA++]=USART_ReceiveData( USART6);
//			if( temp_rec)
//			{
//			ch2_rec_flag = 1;
//			}

//		
//	//清零接收中断标志		
//			USART_ClearITPendingBit( USART6,USART_IT_RXNE) ;
//	}
//}







