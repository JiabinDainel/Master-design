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

//使用NOR/SRAM的 Bank1.sector3,地址位HADDR[27,26]=10 
//对IS61LV25616/IS62WV25616,地址线范围为A0~A17 
//对IS61LV51216/IS62WV51216,地址线范围为A0~A18
#define Bank1_SRAM3_ADDR    ((u32)(0x68000000))		

#endif

#endif

