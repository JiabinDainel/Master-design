/***************************************************************************** 
Copyright: CodeGeek@Hu         
File name: SRAM.h    
Description: 
Author: HuJiaBin            
Version:                 
Date:                 
History:        
*****************************************************************************/ 
#include "HAL.h"

#ifndef _SRAM_H
#define _SRAM_H

#ifdef USE_STM32F103

#include "stm32f10x.h"

//ʹ��NOR/SRAM�� Bank1.sector3,��ַλHADDR[27,26]=10 
//��IS61LV25616/IS62WV25616,��ַ�߷�ΧΪA0~A17 
//��IS61LV51216/IS62WV51216,��ַ�߷�ΧΪA0~A18
#define Bank1_SRAM3_ADDR    ((u32)(0x68000000))		

#endif

#endif

