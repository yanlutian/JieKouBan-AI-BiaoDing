#include "eep.h"
#include "delay.h"
//#include "systick.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h" 
#define FLASH_NSS_PIN		GPIO_Pin_12
#define FLASH_MISO_PIN		GPIO_Pin_14
#define FLASH_MOSI_PIN		GPIO_Pin_15
#define FLASH_SCK_PIN		GPIO_Pin_13
#define FLASH_GPIO  	GPIOB
#define FLASH_SET_NSS 	GPIO_SetBits(FLASH_GPIO,FLASH_NSS_PIN)
#define FLASH_RESET_NSS GPIO_ResetBits(FLASH_GPIO,FLASH_NSS_PIN)
#define FLASH_SPI SPI2
#define FLASH_SPI_RCC RCC_APB1Periph_SPI2
#define FLASH_GPIO_RCC RCC_AHB1Periph_GPIOB
#define FLASH_NSS_PINSOURCE		GPIO_PinSource12
#define FLASH_MISO_PINSOURCE		GPIO_PinSource14
#define FLASH_MOSI_PINSOURCE		GPIO_PinSource15
#define FLASH_SCK_PINSOURCE		GPIO_PinSource13 
#define FLASH_AF					GPIO_AF_SPI2


//
unsigned char EepWrBuf[200];
unsigned char EepRdBuf[200];





//void delay_us(unsigned long nCount)
//{
////	sysTickDelayus(nCount);
//	delay_us( nCount);
//}
	//Flash2��������
//u8 EEP_ReadByte(void)
//{
//	u8 retry=0;				 
//	while((SPI2->SR&1<<0)==0) //�ȴ�������һ��byte  
//	{
//		retry++;
//		if(retry>200)return 0;
//	}	  						    
//	return SPI2->DR;          //�����յ�������				    
//}
//void EEP_WriteByte(u8 TxData)
//{
//	u8 retry=0;	
//	vu8 tDat;
//	tDat=TxData;			 
//	while(((SPI2->SR)&(1<<1))==0);//�ȴ���������	
////	{
////		retry++;
////		if(retry>200)break;
////	}			  
//	SPI2->DR=tDat;	 	  //����һ��byte 
//}
//
u8 EEP_ReadWriteByte(u8 TxData)
{		
	u8 retry=0;				 
	while((SPI2->SR&1<<1)==0)//�ȴ���������	
	{
		retry++;
		if(retry>200)return 0;
	}			  
	SPI2->DR=TxData;	 	  //����һ��byte 
	retry=0;
	while((SPI2->SR&1<<0)==0) //�ȴ�������һ��byte  
	{
		retry++;
		if(retry>200)return 0;
	}	  						    
	return SPI2->DR;          //�����յ�������				    
}


//u8 Read_Data_byte(u16 address)
//{
//	u8 tDat;
//	EEP_CS_LOW();                            //ʹ������   
//	EEP_ReadWriteByte(0x03);   //����дȡ״̬�Ĵ������� 
//	   
//	while();
//}
//Ƭѡ�ߺ���
void EEP_CS_HIGH(void)
{											 
	delay_us(200);
	GPIO_SetBits(GPIOB,GPIO_Pin_12);
}

void EEP_CS_LOW(void)
{
	GPIO_ResetBits(GPIOB,GPIO_Pin_12);
	delay_us(200);
}


//EEPROM SPI��ʼ��
//void FlashHardwareConfig(void)
void EEP_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef  SPI_InitStruct;

	//F407������
	RCC_APB1PeriphClockCmd(FLASH_SPI_RCC , ENABLE);	  //SPIʱ������
	RCC_AHB1PeriphClockCmd(FLASH_GPIO_RCC, ENABLE);
	SPI_Cmd(FLASH_SPI,DISABLE);

  	GPIO_PinAFConfig(FLASH_GPIO, FLASH_MISO_PINSOURCE, FLASH_AF);
  	GPIO_PinAFConfig(FLASH_GPIO, FLASH_MOSI_PINSOURCE, FLASH_AF);
  	GPIO_PinAFConfig(FLASH_GPIO, FLASH_SCK_PINSOURCE, FLASH_AF);

	GPIO_InitStructure.GPIO_Pin = FLASH_MISO_PIN |FLASH_MOSI_PIN |FLASH_SCK_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	GPIO_Init(FLASH_GPIO, &GPIO_InitStructure);


	GPIO_InitStructure.GPIO_Pin = FLASH_NSS_PIN;           //SPI NSS���ó�Ƭѡ��
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	GPIO_Init(FLASH_GPIO, &GPIO_InitStructure);

	//��ʼ��SPI�ṹ��
	//SPI_StructInit(&SPI_InitStruct);
	//SPI_Init(FLASH_SPI,&SPI_InitStruct);//��ʼ��SPI
	SPI_InitStruct.SPI_Direction =SPI_Direction_2Lines_FullDuplex;  //����ȫ˫��
	SPI_InitStruct.SPI_Mode =SPI_Mode_Master;       //��
	SPI_InitStruct.SPI_DataSize =SPI_DataSize_8b;      //8λ
	SPI_InitStruct.SPI_CPOL =SPI_CPOL_High;        //CPOL=1ʱ�����ո�
	//   SPI_InitStruct.SPI_CPOL =SPI_CPOL_Low;        //CPOL=1ʱ�����ո�
	SPI_InitStruct.SPI_CPHA =SPI_CPHA_2Edge;       //CPHA=1 ���ݲ����2��
	//   SPI_InitStruct.SPI_CPHA =SPI_CPHA_1Edge;       //CPHA=1 ���ݲ����2��
	SPI_InitStruct.SPI_NSS =SPI_NSS_Soft;        //���NSS
	SPI_InitStruct.SPI_BaudRatePrescaler =SPI_BaudRatePrescaler_8;  //2��Ƶ
	//   SPI_InitStruct.SPI_BaudRatePrescaler =SPI_BaudRatePrescaler_64;  //2��Ƶ
	SPI_InitStruct.SPI_FirstBit =SPI_FirstBit_MSB;      //��λ��ǰ
	SPI_InitStruct.SPI_CRCPolynomial =7;        //CRC7
	SPI_SSOutputCmd(FLASH_SPI, ENABLE);//ʹ��NSS���

	SPI_Init(FLASH_SPI,&SPI_InitStruct);

	SPI_Cmd(FLASH_SPI,ENABLE);

	FLASH_SET_NSS;
}

unsigned char SPI_MSTRS(unsigned char cData)
{
	u16 retry=0;				 
	while((SPI2->SR&1<<1)==0)//�ȴ���������	
	{
		retry++;
		if(retry>200)return 0;
	}			  
	SPI2->DR=cData;	 	  //����һ��byte 
	retry=0;
	while((SPI2->SR&1<<0)==0) //�ȴ�������һ��byte  
	{
		retry++;
		if(retry>200)return 0;
	}	  						    
	return SPI2->DR;          //�����յ�������				    
////�������ݴ���
//  SPDR = cData;
////�ȴ����ݴ������
//  while(!(SPSR&(1<<SPIF)));
////������ɺ�������ͱ�־
////  SPSR&=~(1<<SPIF);
//  return SPDR;
////ÿ�η������ݵ�ͬʱ��Ҳ����յ����ݡ�
}

//дʹ��
void EEPROM_WREN()
{
	EEP_CS_LOW();
	SPI_MSTRS(0x06);
	EEP_CS_HIGH();
}
//д��ֹ
void EEPROM_WRDI()
{
	EEP_CS_LOW();
	SPI_MSTRS(0x04);
	EEP_CS_HIGH();
}
//д״̬
void EEPROM_WRSR()
{
  EEPROM_WREN();
  EEP_CS_LOW(); //ʹ��
  SPI_MSTRS(0x01);  //0x01Ϊд״̬�Ĵ�����ָ��
  SPI_MSTRS(0x82);  //��0x82д��״̬�Ĵ���
  EEP_CS_HIGH(); //̧��Ƭѡ������
}

/*
��״̬�Ĵ�������SPI�ӻ�����ʱ������Ҫ���ӻ������������ݣ������յ��ӻ����ص�����.
��0x00�������κ����ݣ����ǲ�����25256��ָ�����0x01,0x04֮��ģ�
*/
unsigned char EEPROM_RDSR()
{
  unsigned char StatusReg;
  EEPROM_WREN();
//  EEPROM_WRDI();  //��ʹ�ô˾䣬��ʹ��EEPROM_WREN()�������0x80
  EEP_CS_LOW(); //ʹ��
  SPI_MSTRS(0x05); //0x05Ϊ��״̬�Ĵ���ָ��
  StatusReg=SPI_MSTRS(0x00); //��25256������������
/*
�˴�ԭΪ��
SPDR = 0x00;
while(!(SPSR&(1<<SPIF)));
StatusReg=SPDR;
ʱ�����������ݶ�Ϊ0xff���벻���Ϊʲô
*/
  EEP_CS_HIGH();
  return StatusReg;
}
//25256�ֽ�д
void EEPROM_ByteWrite(unsigned int Address,unsigned char Data)
{
	u8 ti;
 	EEPROM_WREN();
  EEP_CS_LOW(); //ʹ��
  SPI_MSTRS(0x02); //0x02Ϊдָ��
  SPI_MSTRS(Address/256); //��ַ��λ
  SPI_MSTRS(Address%256); //��ַ��λ
  SPI_MSTRS(Data); //д������  
  EEP_CS_HIGH();
	do{
	ti=EEPROM_RDSR();
	 }while((ti&0x01)==0x01);
	//delay_us(5000);
}

//25256ҳд����������ֻ������д�������ֽ�
void EEPROM_PageWrite(unsigned int Address,unsigned char *Data,unsigned char NData)
{
  unsigned char i;
  EEPROM_WREN();
  EEP_CS_LOW(); //ʹ��
  SPI_MSTRS(0x02);//ҳдָ��
  SPI_MSTRS(Address/256); //��ַ��λ
  SPI_MSTRS(Address%256); //��ַ��λ
  for(i=0;i<NData;i++)
   {
     SPI_MSTRS(*Data); //д������ 
  		Data++;
   } 
  EEP_CS_HIGH();
}

//25256��
unsigned char EEPROM_Read(unsigned int Address)
{
  unsigned char dataa;
  EEP_CS_LOW(); //ʹ��
  SPI_MSTRS(0x03); //0x03Ϊ��25256��ָ��
  SPI_MSTRS(Address/256); //��ַ��λ
  SPI_MSTRS(Address%256); //��ַ��λ
  dataa=SPI_MSTRS(0x00);//������������
  EEP_CS_HIGH();
  return dataa;  //���ض���������
}



//��ȡSPI_FLASH��״̬�Ĵ���
//BIT7  6   5   4   3   2   1   0
//SPR   RV  TB BP2 BP1 BP0 WEL BUSY
//SPR:Ĭ��0,״̬�Ĵ�������λ,���WPʹ��
//TB,BP2,BP1,BP0:FLASH����д��������
//WEL:дʹ������
//BUSY:æ���λ(1,æ;0,����)
//Ĭ��:0x00
u8 EEP_Flash_ReadSR(void)   
{  
	u8 byte=0;   
	EEP_CS_LOW();                            //ʹ������   
	EEP_ReadWriteByte(AT25X_ReadStatusReg);    //���Ͷ�ȡ״̬�Ĵ�������    
	byte=EEP_ReadWriteByte(0xFF);             //��ȡһ���ֽ�  
	EEP_CS_HIGH();                            //ȡ��Ƭѡ     
	return byte;   
} 
//дSPI_FLASH״̬�Ĵ���
//ֻ��SPR,TB,BP2,BP1,BP0(bit 7,5,4,3,2)����д!!!
void EEP_FLASH_Write_SR(u8 sr)   
{   
	EEP_CS_LOW();                            //ʹ������   
	EEP_ReadWriteByte(AT25X_WriteStatusReg);   //����дȡ״̬�Ĵ�������    
	EEP_ReadWriteByte(sr);               //д��һ���ֽ�  
	EEP_CS_HIGH();                            //ȡ��Ƭѡ     	      
}   
//SPI_FLASHдʹ��	
//��WEL��λ   
void EEP_FLASH_Write_Enable(void)   
{
	EEP_CS_LOW();                            //ʹ������   
  EEP_ReadWriteByte(AT25X_WriteEnable);      //����дʹ��  
	EEP_CS_HIGH();                            //ȡ��Ƭѡ     	      
} 
//SPI_FLASHд��ֹ	
//��WEL����  
void EEP_FLASH_Write_Disable(void)   
{  
	EEP_CS_LOW();                            //ʹ������   
    EEP_ReadWriteByte(AT25X_WriteDisable);     //����д��ָֹ��    
	EEP_CS_HIGH();                            //ȡ��Ƭѡ     	      
} 			    

void EEP_Flash_Wait_Busy(void)   
{   
	while ((EEP_Flash_ReadSR()&0x01)==0x01);   // �ȴ�BUSYλ���
}  

unsigned char Read_Data_byte(unsigned int address)
{
	//read sequence 
	u8 tDat;
	u8 ri;
	EEP_CS_LOW();                            //ʹ������   
	for(ri=0;ri<8;ri++);
	EEP_ReadWriteByte(AT25X_ReadData); // read instruction
 	EEP_ReadWriteByte(address >> 8); // send out 8-bit higher address 
 	EEP_ReadWriteByte(address&0xFF); // send out 8-bit lower address
 	tDat=	EEP_ReadWriteByte(0xFF);
	EEP_Flash_Wait_Busy();
	EEP_CS_HIGH();                            //ȡ��Ƭѡ     	      
 	return tDat;

}

void Write_Data_byte(unsigned int address, unsigned char input_byte) 
{
//	unsigned char ri;
	EEP_FLASH_Write_Enable();
	delay_us(100);
	EEP_Flash_ReadSR(); // this is necessary for write
	delay_us(100);

	//write byte sequence 
 	EEP_CS_LOW();
	//for(ri=0;ri<8;ri++);
 	delay_us(100);
	EEP_ReadWriteByte(0x02);   // write instruction
 	delay_us(100);
 	EEP_ReadWriteByte(address >> 8);  // send out high 8-bit address 
 	delay_us(100);
 	EEP_ReadWriteByte((u8)address);  // send out low 8-bit address 
 	delay_us(100);
 	EEP_ReadWriteByte(input_byte);
	delay_us(2000);
	//while(SSC0_CON_AREN_BSY)_srvwdt_(); // wait until transfer complete 

 	//EEP_Flash_Wait_Busy();
 	EEP_CS_HIGH();
 	delay_us(100);
	//EEP_FLASH_Write_Disable();

}
void EepRd(unsigned int ReadAddr,unsigned int NumByteToWrite)
{
	u16 i;
	for(i=0;i<NumByteToWrite;i++)
	{
	  EepRdBuf[i]=EEPROM_Read(ReadAddr+i);
	}
}
//void EEP_Read(char *pBuffer,u16 ReadAddr,u16 NumByteToRead) 
//{
//	u16 i;
//	for(i=0;i<NumByteToRead;i++)
//	{
//	 pBuffer[i]=Read_Data_byte(ReadAddr+i);
//	}
//
//}
void EEP_Read(char *pBuffer,u16 ReadAddr,u16 NumByteToRead) 
{
	u16 i;
	for(i=0;i<NumByteToRead;i++)
	{	 pBuffer[i]=Read_Data_byte(ReadAddr+i);	}

}
void EepWr(unsigned int ReadAddr,unsigned int NumByteToWrite)
{
	u16 i;
	for(i=0;i<NumByteToWrite;i++)
	{	 EEPROM_ByteWrite(ReadAddr+i,EepWrBuf[i]);	}
}
void EEP_Write(char *pBuffer,u16 ReadAddr,u16 NumByteToWrite) 
{
	u16 i;
	for(i=0;i<NumByteToWrite;i++)
	{  Write_Data_byte(ReadAddr+i,pBuffer[i]);	}
}
////������ȡSPI FLASH  
////��ָ����ַ��ʼ��ȡָ�����ȵ�����
////pBuffer:���ݴ洢��
////ReadAddr:��ʼ��ȡ�ĵ�ַ(15bit)
////NumByteToRead:Ҫ��ȡ���ֽ���(���65535)
//void EEP_Read(char *pBuffer,u16 ReadAddr,u16 NumByteToRead)   
//{ 
// 	u16 i;    												    
//	EEP_CS_LOW();                            //ʹ������   
//	for(i=0;i<8;i++);
//	EEP_ReadWriteByte(AT25X_ReadData); // read instruction
// 	EEP_ReadWriteByte(ReadAddr >> 8); // send out 8-bit higher address 
// 	EEP_ReadWriteByte((u8)ReadAddr); // send out 8-bit lower address
// 	for(i=0;i<NumByteToRead;i++)
//	{
//		pBuffer[i]=	EEP_ReadWriteByte(0xFF);
//	}
//	EEP_CS_HIGH();                            //ȡ��Ƭѡ     	      
//	EEP_Flash_Wait_Busy();
//}  
//
//void EEP_Write(char *pBuffer,u16 ReadAddr,u16 NumByteToWrite) 
//{
//	u16 i;
//	char tBuf[1000];
// 	for(i=0;i<NumByteToWrite;i++)
//		tBuf[i]=pBuffer[i];
//	EEP_FLASH_Write_Enable();
//	EEP_Flash_ReadSR(); // this is necessary for write
//
//
//	//write byte sequence 
// 	EEP_CS_LOW();
//	for(i=0;i<8;i++);
//
// 	EEP_ReadWriteByte(0x02);   // write instruction
// 	EEP_ReadWriteByte(ReadAddr >> 8);  // send out high 8-bit address 
// 	EEP_ReadWriteByte((u8)ReadAddr);  // send out low 8-bit address 
// 	for(i=0;i<NumByteToWrite;i++)
// 	{	
//		EEP_ReadWriteByte(tBuf[i]);
// 		EEP_Flash_Wait_Busy();
// 	}
//	EEP_CS_HIGH();
//	delay_us(2000);
//
// 	EEP_Flash_Wait_Busy();
//}


