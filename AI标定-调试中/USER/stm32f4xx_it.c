/**
  ******************************************************************************
  * @file    Project/STM32F4xx_StdPeriph_Templates/stm32f4xx_it.c 
  * @author  MCD Application Team
  * @version V1.4.0
  * @date    04-August-2014
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_it.h"


/** @addtogroup Template_Project
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_tim.h"
#include "rs485.h"
#include "string.h"



extern void UsartDevice485_InterProcess();
#define		USART_CH2_REC_MAX		200
/**
**@function:zlg600通信——中断接收函数
**@param:
**@ret:
**/
volatile u16 USART_CH2_RX_STA=0;
volatile u8 USART_CH2_RX_BUF[200];
//USART2中断程序
void USART6_IRQHandler()
{
	u8 temp_rec=0;
	//
	if( USART_GetITStatus( USART6,USART_IT_RXNE)!=RESET)//接受到数据
	{			
			if(0!=(USART_CH2_RX_STA&0x8000))
			{
					USART_CH2_RX_STA=0;//清除之前接收状态
					memset( (u8*)USART_CH2_RX_BUF,0,USART_CH2_REC_MAX);//清除之前接收数据
			}
			//
			if((USART_CH2_RX_STA & 0x8000) == 0) //接收未完成
			{
					TIM_Cmd(TIM4,DISABLE); //关闭定时器计时
					//存储数据到缓冲数组
					USART_CH2_RX_BUF[USART_CH2_RX_STA++]=USART_ReceiveData( USART6);
					TIM_SetCounter( TIM4,0 );//清零计数器
					TIM_Cmd(TIM4,ENABLE); //开启定时器计时
			}
		
	//清零接收中断标志		
			USART_ClearITPendingBit( USART6,USART_IT_RXNE) ;
	}
}

#define		tim4_debug		1
//通过判断接收连续2个字符之间的时间差不大于10ms来决定是不是一次连续的数据.
//如果2个字符接收间隔超过10ms,则认为不是1次连续数据.也就是超过10ms没有接收到
//任何数据,则表示此次接收完毕.
//定时器4中断服务程序--------10ms
void TIM4_IRQHandler(void)   //TIM4中断
{
	
#if tim4_debug
	static u16 tt = 0;
#endif
	
	//
	if(TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)  //检查TIM4更新中断发生
		{
#if tim4_debug
			
			//接收数据过程中超过10ms没有新数据则认为是一帧数据结束-置接收完成标志位
			USART_CH2_RX_STA |= 0x8000;
			//
			TIM_Cmd(TIM4,DISABLE); //关闭定时器计时-等待新的数据帧启动定时器
#else
		
			//定时器测试程序
			tt++;
			if( tt>=50)
			{
				tt=0;
			}
#endif
		}
		
		//清零接收中断标志		
		TIM_ClearITPendingBit( TIM4,TIM_IT_Update) ;
}



/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}


/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f4xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
