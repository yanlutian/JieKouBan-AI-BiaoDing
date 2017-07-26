#ifndef __RS485_H
#define __RS485_H			 
#include "sys.h"	 								  



	  	
extern u8 RS485_RX_BUF[64]; 		//接收缓冲,最大64个字节
extern u8 RS485_RX_CNT;   			//接收到的数据长度


//
#define MB_CH1_RX_EN 	1			//0,不接收;1,接收.
#define MB_CH2_RX_EN 	1			//0,不接收;1,接收.
#define MB_CH3_RX_EN 	1			//0,不接收;1,接收.
#define MB_CH4_RX_EN 	1			//0,不接收;1,接收.


//modbus通道使能
#define		MB_CH1_Enable		1
#define		MB_CH2_Enable		1
#define		MB_CH3_Enable		1
#define		MB_CH4_Enable		1

#define		RX_SIZE		64
//接收缓存区 	
extern u8 MB_CH1_RX_BUF[RX_SIZE];  	//接收缓冲
extern u8 MB_CH2_RX_BUF[RX_SIZE];  	
extern u8 MB_CH3_RX_BUF[RX_SIZE];  	
extern u8 MB_CH4_RX_BUF[RX_SIZE];  	
//接收到的数据长度
extern u8 MB_CH1_RX_CNT;						//接收数据长度
extern u8 MB_CH2_RX_CNT; 
extern u8 MB_CH3_RX_CNT; 
extern u8 MB_CH4_RX_CNT; 

/**********MB_CH1**********/
#define		MB_CH1_USART				USART1
#define		MB_CH1_USART_RX			GPIO_Pin_10
#define		MB_CH1_USART_TX			GPIO_Pin_9
#define		MB_CH1_USART_RCC		RCC_APB2Periph_USART1
#define		MB_CH1_PORT_RCC			RCC_AHB1Periph_GPIOA
#define		MB_CH1_USART_PORT		GPIOA
#define		MB_CH1_USART_AF			GPIO_AF_USART1
#define		MB_CH1_CON_RCC			RCC_AHB1Periph_GPIOA
#define		MB_CH1_CON_PORT			GPIOA
#define		MB_CH1_CON_PIN			GPIO_Pin_8
#define		MB_CH1_USART_RX_PS	GPIO_PinSource10
#define		MB_CH1_USART_TX_PS	GPIO_PinSource9
#define		MB_CH1_IRQn					USART1_IRQn
/**********************/

/**********MB_CH2**********/
#define		MB_CH2_USART				USART6
#define		MB_CH2_USART_RX			GPIO_Pin_7
#define		MB_CH2_USART_TX			GPIO_Pin_6
#define		MB_CH2_USART_RCC		RCC_APB2Periph_USART6
#define		MB_CH2_PORT_RCC			RCC_AHB1Periph_GPIOC
#define		MB_CH2_USART_PORT		GPIOC
#define		MB_CH2_USART_AF			GPIO_AF_USART6
#define		MB_CH2_CON_RCC			RCC_AHB1Periph_GPIOC
#define		MB_CH2_CON_PORT			GPIOC
#define		MB_CH2_CON_PIN			GPIO_Pin_9
#define		MB_CH2_USART_RX_PS	GPIO_PinSource7
#define		MB_CH2_USART_TX_PS	GPIO_PinSource6
#define		MB_CH2_IRQn					USART6_IRQn
/**********************/

/**********MB_CH3**********/
#define		MB_CH3_USART				USART3
#define		MB_CH3_USART_RX			GPIO_Pin_9
#define		MB_CH3_USART_TX			GPIO_Pin_8
#define		MB_CH3_USART_RCC		RCC_APB1Periph_USART3
#define		MB_CH3_PORT_RCC			RCC_AHB1Periph_GPIOD
#define		MB_CH3_USART_PORT		GPIOD
#define		MB_CH3_USART_AF			GPIO_AF_USART3
#define		MB_CH3_CON_RCC			RCC_AHB1Periph_GPIOD
#define		MB_CH3_CON_PORT			GPIOD
#define		MB_CH3_CON_PIN			GPIO_Pin_11
#define		MB_CH3_USART_RX_PS	GPIO_PinSource9
#define		MB_CH3_USART_TX_PS	GPIO_PinSource8
#define		MB_CH3_IRQn					USART3_IRQn
/**********************/

/**********MB_CH4**********/
#define		MB_CH4_USART				USART2
#define		MB_CH4_USART_RX			GPIO_Pin_3
#define		MB_CH4_USART_TX			GPIO_Pin_2
#define		MB_CH4_USART_RCC		RCC_APB1Periph_USART2
#define		MB_CH4_PORT_RCC			RCC_AHB1Periph_GPIOA
#define		MB_CH4_USART_PORT		GPIOA
#define		MB_CH4_USART_AF			GPIO_AF_USART2
#define		MB_CH4_CON_RCC			RCC_AHB1Periph_GPIOD
#define		MB_CH4_CON_PORT			GPIOD
#define		MB_CH4_CON_PIN			GPIO_Pin_10
#define		MB_CH4_USART_RX_PS	GPIO_PinSource3
#define		MB_CH4_USART_TX_PS	GPIO_PinSource2
#define		MB_CH4_IRQn					USART2_IRQn
/**********************/

///**********MB_CH4**********/
//#define		MB_CH4_USART				UART4
//#define		MB_CH4_USART_RX			GPIO_Pin_1
//#define		MB_CH4_USART_TX			GPIO_Pin_0
//#define		MB_CH4_USART_RCC		RCC_APB1Periph_UART4
//#define		MB_CH4_PORT_RCC			RCC_AHB1Periph_GPIOA
//#define		MB_CH4_USART_PORT		GPIOA
//#define		MB_CH4_USART_AF			GPIO_AF_UART4
//#define		MB_CH4_CON_RCC			RCC_AHB1Periph_GPIOD
//#define		MB_CH4_CON_PORT			GPIOD
//#define		MB_CH4_CON_PIN			GPIO_Pin_10
//#define		MB_CH4_USART_RX_PS	GPIO_PinSource1
//#define		MB_CH4_USART_TX_PS	GPIO_PinSource0
//#define		MB_CH4_IRQn					UART4_IRQn
///**********************/
									
//INIT
void MB_CH1_Init(u32 bound);
void MB_CH2_Init(u32 bound);
void MB_CH3_Init(u32 bound);
void MB_CH4_Init(u32 bound);
//SEND DATA
void MB_CH1_SendData(u8 *buf,u8 len);
void MB_CH2_SendData(u8 *buf,u8 len);
void MB_CH3_SendData(u8 *buf,u8 len);
void MB_CH4_SendData(u8 *buf,u8 len);



extern volatile u8 ch2_rec_flag;
extern volatile u8 ch3_rec_flag;
extern volatile u8 ch4_rec_flag;

//
extern volatile u16 USART_CH2_RX_STA;
extern volatile u8 USART_CH2_RX_BUF[200];

 
#endif	   
















