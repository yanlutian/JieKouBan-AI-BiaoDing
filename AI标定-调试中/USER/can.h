#ifndef __CAN_H
#define __CAN_H	 
#include "sys.h"	    


/**********CAN_CH1**********/
#define		CAN_CH1_DEVICE				CAN1
#define		CAN_CH1_DEVICE_RX			GPIO_Pin_8
#define		CAN_CH1_DEVICE_TX			GPIO_Pin_9
#define		CAN_CH1_DEVICE_RCC		RCC_APB1Periph_CAN1
#define		CAN_CH1_PORT_RCC			RCC_AHB1Periph_GPIOB
#define		CAN_CH1_DEVICE_PORT		GPIOB
#define		CAN_CH1_DEVICE_AF			GPIO_AF_CAN1
#define		CAN_CH1_DEVICE_RX_PS	GPIO_PinSource9
#define		CAN_CH1_DEVICE_TX_PS	GPIO_PinSource8
#define		CAN_CH1_IRQn					CAN1_RX0_IRQn
/**********************/

/**********CAN_CH2**********/
#define		CAN_CH2_DEVICE				CAN2
#define		CAN_CH2_DEVICE_RX			GPIO_Pin_5
#define		CAN_CH2_DEVICE_TX			GPIO_Pin_6
#define		CAN_CH2_DEVICE_RCC		RCC_APB1Periph_CAN2
#define		CAN_CH1_PORT_RCC			RCC_AHB1Periph_GPIOB
#define		CAN_CH2_DEVICE_PORT		GPIOB
#define		CAN_CH2_DEVICE_AF			GPIO_AF_CAN2
#define		CAN_CH2_DEVICE_RX_PS	GPIO_PinSource5
#define		CAN_CH2_DEVICE_TX_PS	GPIO_PinSource6
#define		CAN_CH2_IRQn					CAN2_RX0_IRQn
/**********************/















//CAN1����RX0�ж�ʹ��
#define CAN1_RX0_INT_ENABLE	0		//0,��ʹ��;1,ʹ��.								    
void CAN1_Mode_Init(u8 tsjw,u8 tbs2,u8 tbs1,u16 brp,u8 mode);//CAN��ʼ��
u8 CAN1_Send_Msg(u8* msg,u8 len);						//��������
u8 CAN1_Receive_Msg(u8 *buf);							//��������

	
//CAN2����RX0�ж�ʹ��
#define CAN2_RX0_INT_ENABLE	0		//0,��ʹ��;1,ʹ��.								    
void CAN2_Mode_Init(u8 tsjw,u8 tbs2,u8 tbs1,u16 brp,u8 mode);//CAN��ʼ��
u8 CAN2_Send_Msg(u8* msg,u8 len);						//��������
u8 CAN2_Receive_Msg(u8 *buf);							//��������



#endif

















