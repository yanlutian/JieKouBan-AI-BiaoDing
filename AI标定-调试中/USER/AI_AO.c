#include "AI_AO.h"
#include "ADS1115.h"
#include "eep.h"
#include "delay.h"


/*******************************************************************************
* Function Name  : 设置mA输出——全输出——调试用
* Description    : 
* Input            : None
* Output         : None
* Return         : None
*******************************************************************************/
void SetmAOutput(float value)
{
    u16 t = 0;
    //设置AO1-DAC值
    t = (u16)((value - AO1_b) * AO1_K);
    DAC_SetChannel2Data(DAC_Align_12b_R, t);
    //设置AO2-DAC值
    t = (u16)((value - AO2_b) * AO2_K);
    DAC_SetChannel1Data(DAC_Align_12b_R, t);
}

/*******************************************************************************
* Function Name  : 设置mA输出
* Description    : 
* Input            : ch；输出通道
										 value；输出值（0-20mA）
* Output         : None
* Return         : None
*******************************************************************************/
void SetmAOutputByCh(u8 ch, float value)
{
    u16 t = 0;
    switch( ch)
    {
    case AO_CH1:
        //设置AO1-DAC值
        t = (u16)((value - AO1_b) * AO1_K);
        DAC_SetChannel2Data(DAC_Align_12b_R, t);
        break;

    case AO_CH2:
        //设置AO2-DAC值
        t = (u16)((value - AO2_b) * AO2_K);
        DAC_SetChannel1Data(DAC_Align_12b_R, t);
        break;
    }
}



/*******************************************************************************
* Function Name  : 获取输入电流值
* Description    : 
* Input            : 电流值数组变量首地址（浮点型0.0-20.0mA）
* Output         : None
* Return         : None
*******************************************************************************/
void GetmAInputFloat(float *t)
{
		u16 read_value[4];
    //
    read_value[0] = Get_ATOD(channel_AI1);
    delay_ms(5);//必须加延时且延时时间大于等于2ms
    read_value[1] = Get_ATOD(channel_AI2);
    delay_ms(5);
    read_value[2] = Get_ATOD(channel_AI3);
    delay_ms(5);
    read_value[3] = Get_ATOD(channel_AI4);
    delay_ms(5);
    //
    t[0] = ((float)(read_value[0] - AI1_b) / AI1_K) + AO2_b;
    t[1] = ((float)(read_value[1] - AI2_b) / AI2_K) + AO2_b;
    t[2] = ((float)(read_value[2] - AI3_b) / AI3_K) + AO2_b;
    t[3] = ((float)(read_value[3] - AI4_b) / AI4_K) + AO2_b;
}

/*******************************************************************************
* Function Name  : 获取输入电流值
* Description    : 
* Input            : 电流值数组变量首地址（整型0-65535）
* Output         : None
* Return         : None
*******************************************************************************/
void GetmAInputInteger(u16 *t)
{
    //
    t[0] = Get_ATOD(channel_AI1);
    delay_ms(5);//必须加延时且延时时间大于等于2ms
    t[1] = Get_ATOD(channel_AI2);
    delay_ms(5);
    t[2] = Get_ATOD(channel_AI3);
    delay_ms(5);
    t[3] = Get_ATOD(channel_AI4);
    delay_ms(5);
}



/*******************************************************************************
* Function Name  : 写入AI标定值-调试用
* Description    : 
* Input            : None
* Output         : None
* Return         : None
*******************************************************************************/
void AI_kb_WriteToFlash()
{
    //
    EepWrBuf[0] = (u16)AI1_K >> 8;//K1H
    EepWrBuf[1] = (u16)AI1_K;//K1L
    EepWrBuf[2] = (u16)AI1_b >> 8;//B1H
    EepWrBuf[3] = (u16)AI1_b;//B1L
    //
    EepWrBuf[4] = (u16)AI2_K >> 8;//K2H
    EepWrBuf[5] = (u16)AI2_K;//K2L
    EepWrBuf[6] = (u16)AI2_b >> 8;//B2H
    EepWrBuf[7] = (u16)AI2_b;//B2L
    //
    EepWrBuf[8] = (u16)AI3_K >> 8;//K3H
    EepWrBuf[9] = (u16)AI3_K;//K3L
    EepWrBuf[10] = (u16)AI3_b >> 8;//B3H
    EepWrBuf[11] = (u16)AI3_b;//B3L
    //
    EepWrBuf[12] = (u16)AI4_K >> 8;//K4H
    EepWrBuf[13] = (u16)AI4_K;//K4L
    EepWrBuf[14] = (u16)AI4_b >> 8;//B4H
    EepWrBuf[15] = (u16)AI4_b;//B4L
    //
    EepRd(StartAddr, SizeOfkb * NumOfkb); //
}

/*******************************************************************************
* Function Name  : 写入AI标定值-单通道
* Description    : 
* Input            : ch；要写入的通道号
										 k；该通道k值
										 b；该通道b值
* Output         : None
* Return         : None
*******************************************************************************/
void AI_kb_WriteToFlashByCh(u8 ch, u16 k, u16 b)
{
    u16 start_addr = 0;
    //
    EepWrBuf[0] = k >> 8;//K1H
    EepWrBuf[1] = k;//K1L
    EepWrBuf[2] = b >> 8;//B1H
    EepWrBuf[3] = b;//B1L
    //
    switch( ch)
    {
    case AI_CH1:
        start_addr = 0;
        break;

    case AI_CH2:
        start_addr = 4;
        break;

    case AI_CH3:
        start_addr = 8;
        break;

    case AI_CH4:
        start_addr = 12;
        break;
    }
    //
    EepWr(start_addr, SizeOfkb); //
}



























