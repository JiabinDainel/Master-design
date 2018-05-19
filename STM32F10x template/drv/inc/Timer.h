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

#ifndef _TIME_H
#define _TIME_H

#ifdef USE_STM32F103

#include "stm32f10x.h"
#include "rtl.h"
#include "UART.h"

//定时器序号索引
__packed typedef enum
{
	TIMER_3 = 0x01, //定时器3

}TimerNum_e;

uint8_t TimerInit(uint8_t nNum,uint16_t arr,uint16_t psc);
uint8_t TimerCtrl(uint8_t nNum,uint8_t nSta);
uint8_t TimerClearCount(uint8_t nNum);

#endif

#endif







