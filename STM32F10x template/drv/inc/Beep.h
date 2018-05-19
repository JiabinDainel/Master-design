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

#ifndef _BEEP_H
#define _BEEP_H

#include "io.h"
#include "stm32f10x.h"
#include "RTL.h"

//蜂鸣器状态
#define BEEP_ON 1
#define BEEP_OFF 0

#define BEEP_OK 1
#define BEEP_ERR 0

//定义蜂鸣器发声样式
#define BEEP_TYPE_1 1 //刷卡短暂滴

//BEEP数据结构
__packed typedef struct
{
    uint8_t nBeepSta; //状态
}BeepData_t;

//函数声明
uint8_t BeepInit(void);
//uint8_t BeepCtrl(BeepData_t *pData);
uint8_t Beep(uint8_t nBeepType);

#endif






