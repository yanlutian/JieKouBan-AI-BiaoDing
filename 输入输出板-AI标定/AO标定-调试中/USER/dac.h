#ifndef __DAC_H
#define __DAC_H	 
#include "sys.h"	     			    

//DAC通道
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


void AnalogOutput_Init(void);		//DAC通道1初始化	
void AnalogOutput_SetBy_Vol(u8 ch,u16 vol);	//设置通道1输出电压
void AnalogOutput_SetBy_Percent(u8 ch,u8 val);	//设置通道1输出电压














#endif

















