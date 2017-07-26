#ifndef __DIGITAL_H
#define __DIGITAL_H	 
#include "sys.h"

void DigitalOutput_Init(void);//数字输出初始化
void DigitalInput_Init(void);


//数字输出端口
#define		DigitalOutput_Port					GPIOD
#define		DigitalOutput_RCC						RCC_AHB1Periph_GPIOD
#define		DigitalOutputControl_Port		GPIOA
#define		DigitalOutputControl_RCC		RCC_AHB1Periph_GPIOA
//
#define		DigitalOutputControl_Pin1		GPIO_Pin_1
#define		DoControlEnable			PAout(1)

////数字输出管脚
//#define		DigitalOutput_Pin1		GPIO_Pin_7
//#define		DigitalOutput_Pin2		GPIO_Pin_8
//#define		DigitalOutput_Pin3		GPIO_Pin_9
//#define		DigitalOutput_Pin4		GPIO_Pin_10
//#define		DigitalOutput_Pin5		GPIO_Pin_11
//#define		DigitalOutput_Pin6		GPIO_Pin_12
//#define		DigitalOutput_Pin7		GPIO_Pin_13
//#define		DigitalOutput_Pin8		GPIO_Pin_14
//数字输出管脚
#define		DigitalOutput_Pin1		GPIO_Pin_4
#define		DigitalOutput_Pin2		GPIO_Pin_5
#define		DigitalOutput_Pin3		GPIO_Pin_6
#define		DigitalOutput_Pin4		GPIO_Pin_7
#define		DigitalOutput_Pin5		GPIO_Pin_3
#define		DigitalOutput_Pin6		GPIO_Pin_2
#define		DigitalOutput_Pin7		GPIO_Pin_1
#define		DigitalOutput_Pin8		GPIO_Pin_0
////数字输出
//#define		DO1		PEout(7)
//#define		DO2		PEout(8)
//#define		DO3		PEout(9)
//#define		DO4		PEout(10)
//#define		DO5		PEout(11)
//#define		DO6		PEout(12)
//#define		DO7		PEout(13)
//#define		DO8		PEout(14)
//数字输出
#define		DO1		PDout(4)
#define		DO2		PDout(5)
#define		DO3		PDout(6)
#define		DO4		PDout(7)
#define		DO5		PDout(3)
#define		DO6		PDout(2)
#define		DO7		PDout(1)
#define		DO8		PDout(0)
//置位
#define		Set_DO1()		(DO1=1)	
#define		Set_DO2()		(DO2=1)	
#define		Set_DO3()		(DO3=1)	
#define		Set_DO4()		(DO4=1)	
#define		Set_DO5()	  (DO5=1)	
#define		Set_DO6()		(DO6=1)	
#define		Set_DO7()		(DO7=1)	
#define		Set_DO8()   (DO8=1)	
//复位
#define		Reset_DO1()		(DO1=0)	
#define		Reset_DO2()		(DO2=0)	
#define		Reset_DO3()		(DO3=0)	
#define		Reset_DO4()		(DO4=0)	
#define		Reset_DO5()		(DO5=0)	
#define		Reset_DO6()		(DO6=0)	
#define		Reset_DO7()		(DO7=0)	
#define		Reset_DO8()		(DO8=0)	
/********************************************************/
/********************************************************/

//#define		DigitalInput_RCC			(RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOD|RCC_AHB1Periph_GPIOE)
////数字输入管脚
//#define		DigitalInput_Port1		GPIOD
//#define		DigitalInput_Pin1			GPIO_Pin_4

//#define		DigitalInput_Port2		GPIOD
//#define		DigitalInput_Pin2			GPIO_Pin_5

//#define		DigitalInput_Port3		GPIOD
//#define		DigitalInput_Pin3			GPIO_Pin_6

//#define		DigitalInput_Port4		GPIOD
//#define		DigitalInput_Pin4			GPIO_Pin_7

//#define		DigitalInput_Port5		GPIOD
//#define		DigitalInput_Pin5			GPIO_Pin_0

//#define		DigitalInput_Port6		GPIOD
//#define		DigitalInput_Pin6			GPIO_Pin_1

//#define		DigitalInput_Port7		GPIOD
//#define		DigitalInput_Pin7			GPIO_Pin_2

//#define		DigitalInput_Port8		GPIOD
//#define		DigitalInput_Pin8			GPIO_Pin_3

//#define		DigitalInput_Port9		GPIOE
//#define		DigitalInput_Pin9			GPIO_Pin_2

//#define		DigitalInput_Port10		GPIOE
//#define		DigitalInput_Pin10		GPIO_Pin_3

//#define		DigitalInput_Port11		GPIOE
//#define		DigitalInput_Pin11		GPIO_Pin_4

//#define		DigitalInput_Port12		GPIOE
//#define		DigitalInput_Pin12		GPIO_Pin_5

//#define		DigitalInput_Port13		GPIOB
//#define		DigitalInput_Pin13		GPIO_Pin_3

//#define		DigitalInput_Port14		GPIOB
//#define		DigitalInput_Pin14		GPIO_Pin_4

//#define		DigitalInput_Port15		GPIOE
//#define		DigitalInput_Pin15		GPIO_Pin_0

//#define		DigitalInput_Port16		GPIOE
//#define		DigitalInput_Pin16		GPIO_Pin_1
////数字输入
//#define		DI1			PDin(4)		
//#define		DI2			PDin(5)	
//#define		DI3			PDin(6)	
//#define		DI4			PDin(7)	

//#define		DI5			PDin(0)	
//#define		DI6			PDin(1)		
//#define		DI7			PDin(2)	
//#define		DI8			PDin(3)	

//#define		DI9			PEin(2)		
//#define		DI10		PEin(3)	
//#define		DI11		PEin(4)	
//#define		DI12		PEin(5)	

//#define		DI13		PBin(3)		
//#define		DI14		PBin(4)	
//#define		DI15		PEin(0)	
//#define		DI16		PEin(1)	
#define		DigitalInput_RCC			(RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOE)
//数字输入管脚
#define		DigitalInput_Port1		GPIOE
#define		DigitalInput_Pin1			GPIO_Pin_9

#define		DigitalInput_Port2		GPIOE
#define		DigitalInput_Pin2			GPIO_Pin_8

#define		DigitalInput_Port3		GPIOE
#define		DigitalInput_Pin3			GPIO_Pin_7

#define		DigitalInput_Port4		GPIOE
#define		DigitalInput_Pin4			GPIO_Pin_12

#define		DigitalInput_Port5		GPIOE
#define		DigitalInput_Pin5			GPIO_Pin_11

#define		DigitalInput_Port6		GPIOE
#define		DigitalInput_Pin6			GPIO_Pin_10

#define		DigitalInput_Port7		GPIOE
#define		DigitalInput_Pin7			GPIO_Pin_0

#define		DigitalInput_Port8		GPIOB
#define		DigitalInput_Pin8			GPIO_Pin_4

#define		DigitalInput_Port9		GPIOB
#define		DigitalInput_Pin9			GPIO_Pin_3

#define		DigitalInput_Port10		GPIOE
#define		DigitalInput_Pin10		GPIO_Pin_3

#define		DigitalInput_Port11		GPIOE
#define		DigitalInput_Pin11		GPIO_Pin_2

#define		DigitalInput_Port12		GPIOE
#define		DigitalInput_Pin12		GPIO_Pin_1
//数字输入
#define		DI1			PEin(9)		
#define		DI2			PEin(8)	
#define		DI3			PEin(7)	
#define		DI4			PEin(12)	

#define		DI5			PEin(11)	
#define		DI6			PEin(10)		
#define		DI7			PEin(0)	
#define		DI8			PBin(4)	

#define		DI9			PBin(3)		
#define		DI10		PEin(3)	
#define		DI11		PEin(2)	
#define		DI12		PEin(1)



extern void DigitalOutput_Set(uint8_t value);
extern void DigitalOutput_Get(void);
extern uint16_t DigitalInput_Get(void);



extern void UsbPower_Init();










#endif







