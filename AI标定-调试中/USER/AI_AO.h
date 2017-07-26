#ifndef __AI_AO_H
#define __AI_AO_H	 
#include "sys.h"

/**********//**********//**********//**********/
/**********//**********//**********//**********/

/**
**需要仿真调试k、b时，将其定义为变量，便于修改来调整输出精度；
**实际使用时使用宏定义即可。
**/
#if		AO_DEBUG
float AO1_b = 0.3	;
float AO1_K = 196.0	;
//
float AO2_b = 0.32	;
float AO2_K = 195.0	;
#else
#define		AO1_b		0.3			//mA
#define		AO1_K		196.0		//int/mA
//
#define		AO2_b		0.32			//mA
#define		AO2_K		195.0		//int/mA
#endif

#define		AO_CH1		1
#define		AO_CH2		2

/**********//**********//**********//**********/
/**********//**********//**********//**********/

#if		AI_DEBUG
u16 AI1_b = 277	;
float AI1_K = 994.0	;
//
u16 AI2_b = 277	;
float AI2_K = 994.0	;
//
u16 AI3_b = 277	;
float AI3_K = 994.0	;
//
u16 AI4_b = 313	;
float AI4_K = 1011.0	;
#else
#define		AI1_b		277			//mA
#define		AI1_K		994.0		//int/mA
//
#define		AI2_b		277			//mA
#define		AI2_K		994.0		//int/mA
//
#define		AI3_b		277			//mA
#define		AI3_K		994.0		//int/mA
//
#define		AI4_b		313			//mA
#define		AI4_K		1011.0		//int/mA
#endif

//
#define		StartAddr		0x00
#define		SizeOfkb		0x04
#define		NumOfkb			0x04
//
#define		AI_CH1		1
#define		AI_CH2		2
#define		AI_CH3		3
#define		AI_CH4		4

/**********//**********//**********//**********/
/**********//**********//**********//**********/

extern void SetmAOutput(float value);
extern void SetmAOutputByCh(u8 ch, float value);
extern void GetmAInputFloat(float *t);
extern void GetmAInputInteger(u16 *t);
extern void AI_kb_WriteToFlash();
extern void AI_kb_WriteToFlashByCh(u8 ch, u16 k, u16 b);



/**********//**********//**********//**********/
/**********//**********//**********//**********/










#endif







