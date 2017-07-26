
#include "stm32f4xx.h"
#include "TWI.h"
#define TWI_NOP TWI_Delay()
/*******************************************************************************
 * ��������:TWI_Delay                                                                     
 * ��    ��:��ʱ����                                                                     
 *******************************************************************************/
void TWI_Delay(void)
{
  //�����ֲ�涨ʱ��Ҫ��������ʱʱ�䣡����
  u32 i=55;//��F407-168MHz�£��˴���ʱ1.25us����
  while(i--); 
}
/*******************************************************************************
 * ��������:TWI_Initialize                                                                     
 * ��    ��:I2C��ʼ������                                                                    
 *******************************************************************************/
void TWI_Initialize(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOB,ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_CLK|GPIO_SDA;
  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;             
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
	
  TWI_SDA_1;
  TWI_SCL_1;  
  GPIO_Init(GPIO_PORT_I2C, &GPIO_InitStructure);
}
/*******************************************************************************
 * ��������:TWI_START                                                                     
 * ��    ��:��������                                                                      
 *******************************************************************************/
u8 TWI_START(void)
{ 
 TWI_SDA_1; 
 TWI_NOP;
   
 TWI_SCL_1; 
 TWI_NOP;    
// if(!TWI_SDA_STATE)//0
// {
//  ////DebugPrint("TWI_START:BUSY\n");
//  return TWI_BUS_BUSY;
// }
 TWI_SDA_0;
 TWI_NOP;
  
// TWI_SCL_0;  
 TWI_NOP; 
// if(TWI_SDA_STATE)
// {
//  ////DebugPrint("TWI_START:BUS ERROR\n");
//  return TWI_BUS_ERROR;
// } 
 
 return TWI_READY;
}
/*******************************************************************************
 * ��������:TWI_STOP                                                                     
 * ��    ��:����ֹͣλ                                                                    
 *******************************************************************************/
void TWI_STOP(void)
{
 TWI_SDA_0; 
 TWI_NOP;
   
 TWI_SCL_1; 
 TWI_NOP;    
 TWI_SDA_1;
 TWI_NOP;
  
// TWI_SCL_0;  
// TWI_NOP;  
 //////DebugPrint("TWI_STOP\n");   
}
/*******************************************************************************
 * ��������:TWI_SendACK                                                                     
 * ��    ��:�յ�����,����ACK                                                                     
 *******************************************************************************/
void TWI_SendACK(void)
{
 TWI_SDA_0;
 TWI_NOP;
 TWI_SCL_1;
 TWI_NOP;
 TWI_SCL_0; 
 TWI_NOP; 
 //////DebugPrint("TWI_SendACK\n");   
}
/*******************************************************************************
 * ��������:TWI_SendNACK                                                                     
 * ��    ��:�յ�����,����NACK                                                                  
 *******************************************************************************/
void TWI_SendNACK(void)
{
 TWI_SDA_1;
 TWI_NOP;
 TWI_SCL_1;
 TWI_NOP;
 TWI_SCL_0; 
 TWI_NOP;
 //////DebugPrint("TWI_SendNACK\n");    
}
/*******************************************************************************
 * ��������:TWI_SendByte                                                                     
 * ��    ��:����һ���ֽ�                                                                    
 *******************************************************************************/
u8 TWI_SendByte(u8 Data)
{
 u8 i;
 TWI_SCL_0;
 for(i=0;i<8;i++)
 {  
  //---------���ݽ���----------
  if(Data&0x80)
  {
   TWI_SDA_1;
  }
  else
  {
   TWI_SDA_0;
  } 
  Data<<=1;
  TWI_NOP;
  //---���ݽ�������һ����ʱ----
  
  //----����һ��������[������] 
  TWI_SCL_1;
  TWI_NOP;
  TWI_SCL_0;
  TWI_NOP;//��ʱ,��ֹSCL��û��ɵ�ʱ�ı�SDA,�Ӷ�����START/STOP�ź�
  //---------------------------   
 }
 //���մӻ���Ӧ�� 
 TWI_SDA_1; 
 TWI_NOP;
 TWI_SCL_1;
 TWI_NOP;   
 if(TWI_SDA_STATE)
 {
  TWI_SCL_0;
  //////DebugPrint("TWI_NACK!\n");
  return TWI_NACK;
 }
 else
 {
  TWI_SCL_0;
  //////DebugPrint("TWI_ACK!\n");
  return TWI_ACK;  
 }    
}
/*******************************************************************************
 * ��������:TWI_ReceiveByte                                                                     
 * ��    ��:����һ���ֽ�                                                                       
 *******************************************************************************/
u8 TWI_ReceiveByte(void)
{
 u8 i,Dat;
 TWI_SDA_1;
 TWI_SCL_0; 
 Dat=0;
 for(i=0;i<8;i++)
 {
  TWI_SCL_1;//����ʱ��������[������],�ôӻ�׼�������� 
  TWI_NOP; 
  Dat<<=1;
  if(TWI_SDA_STATE) //������״̬
  {
   Dat|=0x01; 
  }   
  TWI_SCL_0;//׼�����ٴν�������  
  TWI_NOP;//�ȴ�����׼����         
 }
 //////DebugPrint("TWI_Dat:%x\n",Dat);
 return Dat;
}
