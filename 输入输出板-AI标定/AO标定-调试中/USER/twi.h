#include "stm32f4xx.h"

#ifndef _TWI_H_
#define _TWI_H_

#define GPIO_CLK				GPIO_Pin_10
#define GPIO_SDA				GPIO_Pin_11
#define GPIO_PORT_I2C		GPIOB

//条件编译 1:使用软件模拟I2C
#define TWI_ENABLE	1
#define TWI_SCL_0		GPIO_ResetBits(GPIO_PORT_I2C, GPIO_CLK)							//scl
#define TWI_SCL_1		GPIO_SetBits(GPIO_PORT_I2C, GPIO_CLK)
#define TWI_SDA_0		GPIO_ResetBits(GPIO_PORT_I2C, GPIO_SDA)									//sda
#define TWI_SDA_1		GPIO_SetBits(GPIO_PORT_I2C, GPIO_SDA)
#define TWI_SDA_STATE		GPIO_ReadInputDataBit(GPIO_PORT_I2C,GPIO_SDA)

enum ENUM_TWI_REPLY
{
	TWI_NACK=0,
	TWI_ACK=1
};
enum ENUM_TWI_BUS_STATE
{
	TWI_READY=0,
	TWI_BUS_BUSY=1,
	TWI_BUS_ERROR=2
};

#define TWI_RETRY_COUNT 3       //重试次数
//#define DELAY Delay_mS(40)
//#define RETRY_DELAY Delay_mS(50) 

u8   TWI_START(void);
u8   TWI_SendByte(u8 Data);
u8   TWI_ReceiveByte(void);
void TWI_SendACK(void);
void TWI_STOP(void);
void TWI_Initialize(void);
void TWI_SendNACK(void);
//extern void delay_ms(u32 n);
#endif
