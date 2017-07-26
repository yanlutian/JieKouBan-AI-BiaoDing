#ifndef __DAC_H
#define __DAC_H	 
#include "sys.h"	     			    

//DACͨ��
typedef enum 
{
	DAC_CH1=0,
	DAC_CH2
}DAC_CHANNEL;

//
#define		AnalogOutput_RCC			RCC_AHB1Periph_GPIOA

#define		AnalogOutput_Port		GPIOA
#define		AnalogOutput_pin1		GPIO_Pin_4
#define		AnalogOutput_pin2		GPIO_Pin_5


void AnalogOutput_Init(void);		//DACͨ��1��ʼ��	
void AnalogOutput_SetBy_Vol(u8 ch,u16 vol);	//����ͨ��1�����ѹ
void AnalogOutput_SetBy_Percent(u8 ch,u8 val);	//����ͨ��1�����ѹ














#endif

















