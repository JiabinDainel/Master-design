/***************************************************************************** 
Copyright: CodeGeek@Hu         
File name: RCC.c         
Description: 时钟文件
Author: HuJiaBin            
Version:                 
Date:                 
History:        
*****************************************************************************/ 
#include "HAL.h"

#ifdef USE_STM32F103

#include "RCC.h"

/*##############################################################################################
函数名称: 
功能描述: 外设时钟使能
输　  入: 
输　  出: 
全局变量:
调用模块:
修订历史: 
##############################################################################################*/
void RCCInit(void)
{
    //时钟使能
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); 
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOE | RCC_APB2Periph_GPIOB , ENABLE);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOF|RCC_APB2Periph_GPIOG,ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC,ENABLE);
  
}

#endif









