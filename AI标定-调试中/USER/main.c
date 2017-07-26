#include "sys.h"
#include "delay.h"

#include "dac.h"
#include "Digital.h"
#include "ads1115.h"
#include "timer.h"
#include "can.h"
#include "rs485.h"

#include "eep.h"
#include "AI_AO.h"



float ao_float = 5.8;
float ai_float[4];
u16 ai_integer[4];

u16 dacval = 0;
u8 temp = 0x55;
u16 temp2;
u16 read_value[4];

u8 i = 0;
u8 canbuf[8];
u8 rs485buf[5];

u8 bit_state = 0;

u8 writeonce = 0;
u16 integer_k = 0, integer_b = 0;
u8 ret_buf[8];
u8 demarcate_ch = 0;
u8 rec_cmd = 0;

//
int main(void)
{
//	NVIC_SetVectorTable(NVIC_VectTab_FLASH,0x08010000-NVIC_VectTab_FLASH);
    //
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2

    EEP_init();


    delay_init(168);      //��ʼ����ʱ����

//	AnalogOutput_Init();		 		//AO��ʼ��
////
//	DigitalOutput_Init();				//DO��ʼ��
//
// 	DigitalInput_Init();				//DI��ʼ��
////
    TWI_Initialize( );				//AI���ų�ʼ��

//	TIM3_Init( );//Ƶ�ʲ���-�ⲿ����ģʽ-TIM3-PA6
//	TIM4_Init( );//Ƶ�ʲ���-�ⲿ����ģʽ-TIM4-PD12
//	TIM2_Init( Scan_Cycle_ms*10,8400-1);//xms�����¼�

//	CAN1_Mode_Init(CAN_SJW_1tq,CAN_BS2_6tq,CAN_BS1_7tq,60,CAN_Mode_Normal);//CAN��ʼ������ģʽ,������500Kbps
//
//	CAN2_Mode_Init(CAN_SJW_1tq,CAN_BS2_6tq,CAN_BS1_7tq,60,CAN_Mode_Normal);//CAN��ʼ������ģʽ,������500Kbps

    MB_CH2_Init(9600);//AO SET
//		MB_CH3_Init(9600);
//		MB_CH4_Init(9600);
////
//		UsbPower_Init();

    while(1)
    {

        //
        GetmAInputInteger( ai_integer);
        //
        ret_buf[0] = ai_integer[0] >> 8;
        ret_buf[1] = ai_integer[0];
        ret_buf[2] = ai_integer[1] >> 8;
        ret_buf[3] = ai_integer[1];
        ret_buf[4] = ai_integer[2] >> 8;
        ret_buf[5] = ai_integer[2];
        ret_buf[6] = ai_integer[3] >> 8;
        ret_buf[7] = ai_integer[3];
        MB_CH2_SendData(ret_buf, 8); //����8���ֽ�
        delay_ms(200);

        //useful
        if((USART_CH2_RX_STA & 0x8000) == 0x8000) //����δ���
        {
            rec_cmd = USART_CH2_RX_BUF[0];
            //
            if( rec_cmd == 0)
            {
                ret_buf[0] = 0;
                ret_buf[1] = 0xaa;
                ret_buf[7] = 0xbb;
                //
                MB_CH2_SendData(ret_buf, 8); //����8���ֽ�
            }
            else
            {
                demarcate_ch = USART_CH2_RX_BUF[3];//�궨��ͨ����
                //
                integer_k = USART_CH2_RX_BUF[4];
                integer_k <<= 8;
                integer_k += USART_CH2_RX_BUF[5];
                //
                integer_b = USART_CH2_RX_BUF[6];
                integer_b <<= 8;
                integer_b += USART_CH2_RX_BUF[7];
                //
                AI_kb_WriteToFlashByCh(demarcate_ch, integer_k, integer_b);
            }
            //
            USART_CH2_RX_STA = 0;
        }

//		EepRd(0,16);//



//
//		SetmAOutput( ao_float);
//		delay_ms(200);
////
//		GetmAInputFloat( ai_float);
//		delay_ms(200);


        //DAC available
//		dacval+=200;		if(dacval>4095)dacval=0;
//		DAC_SetChannel1Data(DAC_Align_12b_R, dacval);//����AO2-DACֵ
////		delay_ms(100);
//		DAC_SetChannel2Data(DAC_Align_12b_R, dacval);//����AO1-DACֵ
//		delay_ms(200);
//		dacval += 100;
//
        //DO available
//		DigitalOutput_Set( temp);
//    temp=~temp;
//		delay_ms(500);
//		temp=0xaa;
//		DigitalOutput_Set( temp);
//		temp<<=1;
//		if(temp==0)temp=0x01;
//		delay_ms(500);
//		temp=0x55;
//		DigitalOutput_Set( temp);
//		delay_ms(500);



        //DI available
//		temp2=DigitalInput_Get();
//
        //ADC available
//	  read_value[0]=Get_ATOD(0);delay_ms(5);//�������ʱ����ʱʱ����ڵ���2ms
//		read_value[1]=Get_ATOD(1);delay_ms(5);
//		read_value[2]=Get_ATOD(2);delay_ms(5);
//		read_value[3]=Get_ATOD(3);delay_ms(5);

//		canbuf[0]=read_value[0]>>8;//��䷢�ͻ�����
//		canbuf[1]=read_value[0];//��䷢�ͻ�����
//		canbuf[2]=read_value[1]>>8;
//		canbuf[3]=read_value[1];
//		canbuf[4]=read_value[2]>>8;
//		canbuf[5]=read_value[2];
//		canbuf[6]=read_value[3]>>8;
//		canbuf[7]=read_value[3];


        //CAN1 available
//		for(i=0;i<8;i++)
//		{
//			canbuf[0]=temp2>>8;//��䷢�ͻ�����
//			canbuf[1]=temp2;//��䷢�ͻ�����
//
//			canbuf[2]=F1Count_Value>>8;
//			canbuf[3]=F1Count_Value>>0;
//
//			canbuf[4]=F2Count_Value>>8;
//			canbuf[5]=F2Count_Value>>0;
//		}

//		canbuf[0]=temp2>>8;
//		canbuf[1]=temp2;
//		CAN1_Send_Msg(canbuf,8);//����8���ֽ�
//		delay_ms(300);

//
//		MB_CH1_SendData(canbuf,8);//����5���ֽ�
//		MB_CH3_SendData(canbuf,8);//����5���ֽ�
//		delay_ms(500);

        //CAN2 available
//		for(i=0;i<8;i++)
//		{
//				canbuf[0]=temp3>>8;
//				canbuf[1]=temp3>>0;

//				canbuf[2]=temp4>>8;
//				canbuf[3]=temp4>>0;

//				canbuf[4]=temp5>>8;
//				canbuf[5]=temp5>>0;
//
//				canbuf[6]=temp6>>8;
//				canbuf[7]=temp6>>0;
//		}
//		CAN2_Send_Msg(canbuf,8);//����8���ֽ�
//		delay_ms(300);

        //MB available
//	for(i=0;i<5;i++)bit_state
//	{
//		rs485buf[i]=i;//��䷢�ͻ�����
//	}

//	MB_CH2_SendData(canbuf,8);//����5���ֽ�
//	MB_CH3_SendData(canbuf,8);//����5���ֽ�
//	MB_CH4_SendData(canbuf,8);//����5���ֽ�
//	//
//	GPIO_WriteBit( GPIOD,GPIO_Pin_15,bit_state);

//	DO1 = 0;
//	DO2 = 1;
//	DO7 = 0;
//	DO8 = 1;
//	bit_state=!bit_state;
        //
//	delay_ms(100);



        //

    }
}





//500ms��ʱ����
//��ʱ��2�жϷ�����
//�����Զ�ȡ����ͨ����Ƶ�ʼ���ֵ
void TIM2_IRQHandler(void)
{
    if(TIM_GetITStatus(CycleEvent_TIMX, TIM_IT_Update) == SET) //����ж�
    {
        /************************1S����������******************************/
        /**************Ƶ��ͨ��1******************/
        if( ( F1Count_State & 0x80)) //�ѿ�ʼ
        {
            F1Count_State = 0;
            TIM_Cmd(F1Count_TIMX, DISABLE);  //�رն�ʱ��
            F1Count_Value = TIM_GetCounter( F1Count_TIMX) * PNums_Of_PerS;	//*2�õ�1SƵ��
        }
        else//δ��ʼ
        {
            F1Count_State = 0;
            F1Count_Value = 0;
            F1Count_State |= 0x80; //�����ѿ�ʼ
            TIM_SetCounter(F1Count_TIMX, 0);//����������
            TIM_Cmd(F1Count_TIMX, ENABLE);  //�򿪶�ʱ��
        }
        /**************Ƶ��ͨ��2******************/
        if( ( F2Count_State & 0x80)) //�ѿ�ʼ
        {
            F2Count_State = 0;
            TIM_Cmd(F2Count_TIMX, DISABLE);  //�رն�ʱ��
            F2Count_Value = TIM_GetCounter( F2Count_TIMX) * PNums_Of_PerS;	//*2�õ�1SƵ��
        }
        else//δ��ʼ
        {
            F2Count_State = 0;
            F2Count_Value = 0;
            F2Count_State |= 0x80; //�����ѿ�ʼ
            TIM_SetCounter(F2Count_TIMX, 0);//����������
            TIM_Cmd(F2Count_TIMX, ENABLE);  //�򿪶�ʱ��
        }
    }
    TIM_ClearITPendingBit(CycleEvent_TIMX, TIM_IT_Update); //����жϱ�־λ
}






