
#include "stm32f4xx.h"
#include "TWI.h"
#define TWI_NOP TWI_Delay()
/*******************************************************************************
 * 函数名称:TWI_Delay                                                                     
 * 描    述:延时函数                                                                     
 *******************************************************************************/
void TWI_Delay(void)
{
  //根据手册规定时序要求设置延时时间！！！
  u32 i=55;//在F407-168MHz下，此处延时1.25us左右
  while(i--); 
}
/*******************************************************************************
 * 函数名称:TWI_Initialize                                                                     
 * 描    述:I2C初始化函数                                                                    
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
 * 函数名称:TWI_START                                                                     
 * 描    述:发送启动                                                                      
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
 * 函数名称:TWI_STOP                                                                     
 * 描    述:发送停止位                                                                    
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
 * 函数名称:TWI_SendACK                                                                     
 * 描    述:收到数据,发送ACK                                                                     
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
 * 函数名称:TWI_SendNACK                                                                     
 * 描    述:收到数据,发送NACK                                                                  
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
 * 函数名称:TWI_SendByte                                                                     
 * 描    述:发送一个字节                                                                    
 *******************************************************************************/
u8 TWI_SendByte(u8 Data)
{
 u8 i;
 TWI_SCL_0;
 for(i=0;i<8;i++)
 {  
  //---------数据建立----------
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
  //---数据建立保持一定延时----
  
  //----产生一个上升沿[正脉冲] 
  TWI_SCL_1;
  TWI_NOP;
  TWI_SCL_0;
  TWI_NOP;//延时,防止SCL还没变成低时改变SDA,从而产生START/STOP信号
  //---------------------------   
 }
 //接收从机的应答 
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
 * 函数名称:TWI_ReceiveByte                                                                     
 * 描    述:接收一个字节                                                                       
 *******************************************************************************/
u8 TWI_ReceiveByte(void)
{
 u8 i,Dat;
 TWI_SDA_1;
 TWI_SCL_0; 
 Dat=0;
 for(i=0;i<8;i++)
 {
  TWI_SCL_1;//产生时钟上升沿[正脉冲],让从机准备好数据 
  TWI_NOP; 
  Dat<<=1;
  if(TWI_SDA_STATE) //读引脚状态
  {
   Dat|=0x01; 
  }   
  TWI_SCL_0;//准备好再次接收数据  
  TWI_NOP;//等待数据准备好         
 }
 //////DebugPrint("TWI_Dat:%x\n",Dat);
 return Dat;
}
