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

extern OS_SEM g_sSEM_Recv_UART1; //串口1信号量

/*##############################################################################################
函数名称: uint8_t TimerInit(uint8_t nNum,uint16_t nArr,uint16_t nPSC)
功能描述: 定时器初始化
输　  入: 
输　  出:
全局变量:
调用模块:
修订历史: 
##############################################################################################*/
uint8_t TimerInit(uint8_t nNum,uint16_t nArr,uint16_t nPSC)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	switch(nNum)
	{
	case TIMER_3:
		//定时器TIM3初始化
		TIM_TimeBaseStructure.TIM_Period = nArr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
		TIM_TimeBaseStructure.TIM_Prescaler =nPSC; //设置用来作为TIMx时钟频率除数的预分频值
		TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
		TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位  
        TIM_ClearITPendingBit(TIM3,TIM_IT_Update); //屏蔽第一次初始化触发中断
		TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //使能指定的TIM3中断,允许更新中断
		//中断优先级NVIC设置
		NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3中断
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;  //先占优先级0级
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
		NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器	      
		return 1;
	default:
		break;
	}
	return 0;
}

/*##############################################################################################
函数名称: 
功能描述: 
输　  入: 
输　  出: 
全局变量:
调用模块:
修订历史: 
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
函数名称: 
功能描述:
输　  入: 
输　  出: 
全局变量:
调用模块:
修订历史: 
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
函数名称: void TIM3_IRQHandler(void)
功能描述: 定时器中断函数
输　  入: void
输　  出: void
全局变量:
调用模块:
修订历史: 
##############################################################################################*/
void TIM3_IRQHandler(void)   //TIM3中断
{
	if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //检查TIM3更新中断发生与否
	{
		//串口1定时器超时
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);  //清除TIMx更新中断标志 
		TimerCtrl(TIMER_3,0); //关闭定时器
		ResetUARTCurrentRecvDataIndex(UART_1);
		isr_sem_send (&g_sSEM_Recv_UART1);
	}
}

#endif







