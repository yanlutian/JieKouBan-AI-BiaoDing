
#include "stm32f4xx.h"
#include "ads1115.h"

//static void Confige1115 (unsigned char port);
//static void PointRegister (void);
//static u16 ReadData (unsigned char chn);
unsigned char WriteIntBuf[4], WritepointBuf[2], count = 6,ReadBuffer[64];;
void delay (unsigned int delay)
{
   while(delay--);  
}

/*******************************************************************************
* Function Name  : Confige1115
* Description    : �ӳ�ʱ��
* Input          : None
* Output         : None
* Return         : None
* Attention		 :��ȡADS1115ģ��ת�����
*******************************************************************************/
u16   data_get;
u16 dianya_value;
u16 Get_ATOD (unsigned char ch)
{
   unsigned char chn;
	
	  chn = ch; 
		
    Confige1115(chn);
    delay(100);
    PointRegister();
    delay(100);
    data_get=ReadData(chn);
    delay(100);
//		if(data_get>=0x8000)
//				dianya_value=0;//0xffff-data_get;//
//		else
//				dianya_value=data_get;//((float)data_get/32768.0)*4.096;
//		return dianya_value;   
		return data_get;    
}
/*******************************************************************************
* Function Name  : Confige1115
* Description    : �ӳ�ʱ��
* Input          : None
* Output         : None
* Return         : None
* Attention		 :����ADS1115
*******************************************************************************/
void Confige1115 (unsigned char port)
{
    static unsigned char chnel, i;
    switch (port)
    {
      case 0:               //0ͨ��
          chnel=0xC2;
      				break;
      
      case 1:               //1ͨ��  
          chnel=0xD2;
      				break;
          
      case 2:               //2ͨ��  
          chnel=0xE2;
      				break;
          
      case 3:               //3ͨ��
          chnel=0xF2;
      				break;
          
      default:
      				break;	
    }
    WriteIntBuf[0] = CMD_Write;
    WriteIntBuf[1] = CMD_CONF_REG;
    WriteIntBuf[2] = chnel;
    WriteIntBuf[3] = CONF_L;
    if(!(TWI_START()))
    {
        for(i=0;i<4;i++)
        {
            TWI_SendByte(WriteIntBuf[i]);
						delay(20);
        }
    }
    TWI_STOP();

}
/*******************************************************************************
* Function Name  : PointRegister
* Description    : �ӳ�ʱ��
* Input          : None
* Output         : None
* Return         : None
* Attention		 :ָ��ADS1115ָ��Ĵ�������׼����ȡ����
*******************************************************************************/
void PointRegister (void)
{
    unsigned char i;
    WritepointBuf[0] = CMD_Write;					//90
    WritepointBuf[1] = CMD_POINT_REG;	//00
    if(!(TWI_START()))
    {
        for(i=0;i<2;i++)
        {
          TWI_SendByte(WritepointBuf[i]);
          //�˴���ʱʱ�����Ҫ����Сʱ�����ͨ��ֵ�������󣡣���
					delay(50000);//��F407-168MHz�£��˴���ʱ1ms����
        }
    }
   TWI_STOP();
}
/*******************************************************************************
* Function Name  : I2C_delay
* Description    : �ӳ�ʱ��
* Input          : None
* Output         : None
* Return         : None
* Attention		 :  CH1 PA4  CH2 PA7 CH3 PA6 CH4 PA5
*******************************************************************************/

u16 ReadData (unsigned char chn)
{  
		u16 data_rece;
		if(!(TWI_START()))
		{  
				TWI_SendByte(CMD_Read);
				delay(20);
				ReadBuffer[0] = TWI_ReceiveByte(); 
				TWI_SendACK();
				ReadBuffer[1] = TWI_ReceiveByte();
				TWI_SendACK();
				TWI_STOP();
				data_rece=ReadBuffer[0]*256+ReadBuffer[1];
		} 
return data_rece;
}
