#include "Digital.h"


//���������ʼ��
void DigitalOutput_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(DigitalOutput_RCC, ENABLE);//ʹ��GPIOAʱ��

	GPIO_InitStructure.GPIO_Pin = DigitalOutput_Pin1|DigitalOutput_Pin2|DigitalOutput_Pin3|DigitalOutput_Pin4|
																DigitalOutput_Pin5|DigitalOutput_Pin6|DigitalOutput_Pin7|DigitalOutput_Pin8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(DigitalOutput_Port, &GPIO_InitStructure);//��ʼ��
	//control bit
	RCC_AHB1PeriphClockCmd(DigitalOutputControl_RCC, ENABLE);//ʹ��GPIOAʱ��
	GPIO_InitStructure.GPIO_Pin = DigitalOutputControl_Pin1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(DigitalOutputControl_Port, &GPIO_InitStructure);//��ʼ��
	DoControlEnable=1;
}


//���������ʼ��
void DigitalInput_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(DigitalInput_RCC, ENABLE);//ʹ��GPIOʱ��

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
	
	GPIO_InitStructure.GPIO_Pin = DigitalInput_Pin1;															
  GPIO_Init(DigitalInput_Port1, &GPIO_InitStructure);//��ʼ��
	
	GPIO_InitStructure.GPIO_Pin = DigitalInput_Pin2;															
  GPIO_Init(DigitalInput_Port2, &GPIO_InitStructure);//��ʼ��
	
	GPIO_InitStructure.GPIO_Pin = DigitalInput_Pin3;															
  GPIO_Init(DigitalInput_Port3, &GPIO_InitStructure);//��ʼ��
	
	GPIO_InitStructure.GPIO_Pin = DigitalInput_Pin4;															
  GPIO_Init(DigitalInput_Port4, &GPIO_InitStructure);//��ʼ��
	
	GPIO_InitStructure.GPIO_Pin = DigitalInput_Pin5;															
  GPIO_Init(DigitalInput_Port5, &GPIO_InitStructure);//��ʼ��
	
	GPIO_InitStructure.GPIO_Pin = DigitalInput_Pin6;															
  GPIO_Init(DigitalInput_Port6, &GPIO_InitStructure);//��ʼ��
	
	GPIO_InitStructure.GPIO_Pin = DigitalInput_Pin7;															
  GPIO_Init(DigitalInput_Port7, &GPIO_InitStructure);//��ʼ��
	
	GPIO_InitStructure.GPIO_Pin = DigitalInput_Pin8;															
  GPIO_Init(DigitalInput_Port8, &GPIO_InitStructure);//��ʼ��
	
	GPIO_InitStructure.GPIO_Pin = DigitalInput_Pin9;															
  GPIO_Init(DigitalInput_Port9, &GPIO_InitStructure);//��ʼ��
	
	GPIO_InitStructure.GPIO_Pin = DigitalInput_Pin10;															
  GPIO_Init(DigitalInput_Port10, &GPIO_InitStructure);//��ʼ��
	
	GPIO_InitStructure.GPIO_Pin = DigitalInput_Pin11;															
  GPIO_Init(DigitalInput_Port11, &GPIO_InitStructure);//��ʼ��
	
	GPIO_InitStructure.GPIO_Pin = DigitalInput_Pin12;															
  GPIO_Init(DigitalInput_Port12, &GPIO_InitStructure);//��ʼ��
	
//	GPIO_InitStructure.GPIO_Pin = DigitalInput_Pin13;															
//  GPIO_Init(DigitalInput_Port13, &GPIO_InitStructure);//��ʼ��
//	
//	GPIO_InitStructure.GPIO_Pin = DigitalInput_Pin14;															
//  GPIO_Init(DigitalInput_Port14, &GPIO_InitStructure);//��ʼ��
//	
//	GPIO_InitStructure.GPIO_Pin = DigitalInput_Pin15;															
//  GPIO_Init(DigitalInput_Port15, &GPIO_InitStructure);//��ʼ��
//	
//	GPIO_InitStructure.GPIO_Pin = DigitalInput_Pin16;															
//  GPIO_Init(DigitalInput_Port16, &GPIO_InitStructure);//��ʼ��
	
}


/*
*��ȡ���������ֵ
*MSB:DO8		LSB:DO1
*/
void DigitalOutput_Set(uint8_t value)
{
	
	DO8=value&0x80?1:0;
	DO7=value&0x40?1:0;
	DO6=value&0x20?1:0;
	DO5=value&0x10?1:0;
	DO4=value&0x08?1:0;
	DO3=value&0x04?1:0;
	DO2=value&0x02?1:0;
	DO1=value&0x01?1:0;
	
}
/*
*��ȡ���������ֵ
*/
void DigitalOutput_Get(void)
{
	
	
}
/*
*��ȡ����������ֵ
*MSB:DI16		LSB:DI1
*/
uint16_t DigitalInput_Get(void)
{
	uint16_t ret=0;
	
//	ret|=(DI16?1:0)<<15;
//	ret|=(DI15?1:0)<<14;
//	ret|=(DI14?1:0)<<13;
//	ret|=(DI13?1:0)<<12;
	ret|=(DI12?1:0)<<11;
	ret|=(DI11?1:0)<<10;
	ret|=(DI10?1:0)<<9;
	ret|=(DI9?1:0)<<8;
	
	ret|=(DI8?1:0)<<7;
	ret|=(DI7?1:0)<<6;
	ret|=(DI6?1:0)<<5;
	ret|=(DI5?1:0)<<4;
	ret|=(DI4?1:0)<<3;
	ret|=(DI3?1:0)<<2;
	ret|=(DI2?1:0)<<1;
	ret|=(DI1?1:0)<<0;
	
return ret;
}



void UsbPower_Init()
{
  GPIO_InitTypeDef  GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);//ʹ��GPIOAʱ��

	
	//POWER PIN
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;//PA11/12���ù������	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//���ù���
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; 
  GPIO_Init(GPIOD, &GPIO_InitStructure);//��ʼ��
	
	//
	GPIO_WriteBit( GPIOD,GPIO_Pin_15,0);

	
}


























