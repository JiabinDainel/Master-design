/***************************************************************************** 
Copyright: CodeGeek@Hu         
File name:           
Description: 
Author: HuJiaBin            
Version:                 
Date:                 
History:        
*****************************************************************************/ 
#include "HAL.h"

#ifdef USE_STM32F103

#include "Timer.h"

extern OS_SEM g_sSEM_Recv_UART1; //����1�ź���

/*##############################################################################################
��������: uint8_t TimerInit(uint8_t nNum,uint16_t nArr,uint16_t nPSC)
��������: ��ʱ����ʼ��
�䡡  ��: 
�䡡  ��:
ȫ�ֱ���:
����ģ��:
�޶���ʷ: 
##############################################################################################*/
uint8_t TimerInit(uint8_t nNum,uint16_t nArr,uint16_t nPSC)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	switch(nNum)
	{
	case TIMER_3:
		//��ʱ��TIM3��ʼ��
		TIM_TimeBaseStructure.TIM_Period = nArr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
		TIM_TimeBaseStructure.TIM_Prescaler =nPSC; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
		TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
		TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ  
        TIM_ClearITPendingBit(TIM3,TIM_IT_Update); //���ε�һ�γ�ʼ�������ж�
		TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM3�ж�,��������ж�
		//�ж����ȼ�NVIC����
		NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3�ж�
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;  //��ռ���ȼ�0��
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
		NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���	      
		return 1;
	default:
		break;
	}
	return 0;
}

/*##############################################################################################
��������: 
��������: 
�䡡  ��: 
�䡡  ��: 
ȫ�ֱ���:
����ģ��:
�޶���ʷ: 
##############################################################################################*/
uint8_t TimerCtrl(uint8_t nNum,uint8_t nSta)
{
	if(nSta)
	{
		switch(nNum)
		{
		case TIMER_3:
			TIM_Cmd(TIM3,ENABLE);    
			return 1;
		default:
			return 0;
		}
	}
	else
	{
		switch(nNum)
		{
		case TIMER_3:
			TIM_Cmd(TIM3,DISABLE);    
			return 1;
		default:
			return 0;
		}
	}
}

/*##############################################################################################
��������: 
��������:
�䡡  ��: 
�䡡  ��: 
ȫ�ֱ���:
����ģ��:
�޶���ʷ: 
##############################################################################################*/
uint8_t TimerClearCount(uint8_t nTimerNum)
{
	switch(nTimerNum)
	{
	case TIMER_3:
		TIM_SetCounter(TIM3,0);
		return 1;
	default:
		return 0;
	}
}

/*##############################################################################################
��������: void TIM3_IRQHandler(void)
��������: ��ʱ���жϺ���
�䡡  ��: void
�䡡  ��: void
ȫ�ֱ���:
����ģ��:
�޶���ʷ: 
##############################################################################################*/
void TIM3_IRQHandler(void)   //TIM3�ж�
{
	if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //���TIM3�����жϷ������
	{
		//����1��ʱ����ʱ
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);  //���TIMx�����жϱ�־ 
		TimerCtrl(TIMER_3,0); //�رն�ʱ��
		ResetUARTCurrentRecvDataIndex(UART_1);
		isr_sem_send (&g_sSEM_Recv_UART1);
	}
}

#endif







