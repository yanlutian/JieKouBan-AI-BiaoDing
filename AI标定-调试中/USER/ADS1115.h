
#ifndef __ADS1115_H
#define __ADS1115_H
#include "TWI.h"
#include "stm32f4xx_gpio.h"
#define CMD_Write     0x90
#define CMD_Read      0x91
#define CMD_CONF_REG  0x01
#define CMD_POINT_REG 0x00
#define CONF_L        0xe3
#define channel_0      0                //��ʾѡ��ͨ��0
#define channel_1      1                //��ʾѡ��ͨ��1
#define channel_2      2                //��ʾѡ��ͨ��2
#define channel_3      3                //��ʾѡ��ͨ��2
//
#define channel_AI1      channel_3		//��ʾѡ��ͨ��0
#define channel_AI2      channel_2		//��ʾѡ��ͨ��1
#define channel_AI3      channel_0		//��ʾѡ��ͨ��2
#define channel_AI4      channel_1		//��ʾѡ��ͨ��2
//
u16 Get_ATOD (unsigned char channel);
void Confige1115 (unsigned char port);
void PointRegister (void);
u16 ReadData (unsigned char chn);

#endif


