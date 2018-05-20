/***************************************************************************** 
Copyright: CodeGeek@Hu         
File name: RCC.c         
Description: ʱ���ļ�
Author: HuJiaBin            
Version:                 
Date:                 
History:        
*****************************************************************************/ 
#include "HAL.h"

#ifdef USE_STM32F103

#include "RCC.h"

/*##############################################################################################
��������: 
��������: ����ʱ��ʹ��
�䡡  ��: 
�䡡  ��: 
ȫ�ֱ���:
����ģ��:
�޶���ʷ: 
##############################################################################################*/
void RCCInit(void)
{
    //ʱ��ʹ��
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); 
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOE | RCC_APB2Periph_GPIOB , ENABLE);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOF|RCC_APB2Periph_GPIOG,ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC,ENABLE);
  
}

#endif









