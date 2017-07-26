//#include "stm32f10x.h"
#include "stm32f4xx.h"
#ifndef __EEP_H
#define __EEP_H

#define	SPI_FLASH_CS PAout(2)  //ѡ��FLASH	
#define FLASHE_WRITE_EN  //����д����				 
////////////////////////////////////////////////////////////////////////////
//W25X16��д
#define FLASH_ID 0XEF14
//ָ���
//WREN
#define AT25X_WriteEnable				0x06 
//WRDI
#define AT25X_WriteDisable			0x04 
//RDSR
#define AT25X_ReadStatusReg			0x05 
//WRSR
#define AT25X_WriteStatusReg		0x01 
//READ
#define AT25X_ReadData					0x03 
//WRITE
#define AT25X_WriteData					0x02

//#define AT25X_FastReadData			0x0B 
//#define AT25X_FastReadDual			0x3B 
//#define AT25X_PageProgram			0x02 
//#define AT25X_BlockErase				0xD8 
//#define AT25X_SectorErase			0x20 
//#define AT25X_ChipErase				0xC7 
//#define AT25X_PowerDown				0xB9 
//#define AT25X_ReleasePowerDown	0xAB 
//#define AT25X_DeviceID					0xAB 
//#define AT25X_ManufactDeviceID	0x90 
//#define AT25X_JedecDeviceID		0x9F 

extern void delay_us(u32 Nus);


extern unsigned char EepWrBuf[200];
extern unsigned char EepRdBuf[200];

void EEP_init(void);
void EEP_CS_HIGH(void);
void EEP_CS_LOW(void);
unsigned char EEP_Flash_ReadSR(void);   
unsigned char EEP_ReadWriteByte(u8 TxData);
void EEP_FLASH_Write_SR(u8 sr);   
void EEP_FLASH_Write_Enable(void);   
void EEP_FLASH_Write_Disable(void);
void EEP_Flash_Wait_Busy(void);   
unsigned char Read_Data_byte(unsigned int address);
void Write_Data_byte(unsigned int address, unsigned char input_byte);   
void EEP_WriteByte(u8 TxData);
  u8 EEP_ReadByte(void);
void EepRd(unsigned int ReadAddr,unsigned int NumByteToWrite);
void EepWr(unsigned int ReadAddr,unsigned int NumByteToWrite);

//unsigned short int  SPI2_Flash_ReadID(void);  	    //��ȡFLASH ID
//unsigned char	 SPI2_Flash_ReadSR(void);        //��ȡ״̬�Ĵ��� 
//void SPI2_FLASH_Write_SR(unsigned char sr);  	//д״̬�Ĵ���
//void SPI2_FLASH_Write_Enable(void);  //дʹ�� 
//void SPI2_FLASH_Write_Disable(void);	//д����
//void SPI2_Flash_Erase_Chip(void);    	  //��Ƭ����
//void SPI2_Flash_Wait_Busy(void);           //�ȴ�����
//void SPI2_Flash_PowerDown(void);           //�������ģʽ
//void SPI2_Flash_WAKEUP(void);			  //����
//void SPI2_Flash_Erase_Sector(u32 Dst_Addr);
//void SPI2_Flash_Read(char *pBuffer,u32 ReadAddr,u16 NumByteToRead);
//void SPI2_Flash_Write(char *pBuffer,u32 WriteAddr,u16 NumByteToWrite);
//
#endif
















