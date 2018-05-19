/***************************************************************************** 
Copyright: CodeGeek@Hu         
File name: LED.h 
Description: 
Author: HuJiaBin            
Version:                 
Date:                 
History:        
*****************************************************************************/ 
#include "HAL.h"

#ifndef _LED_H
#define _LED_H

#ifdef USE_STM32F103

#include "stm32f10x.h"
#include "io.h"

//LED×´Ì¬
#define LED_ON 1
#define LED_OFF 0

#define LED_OK 1
#define LED_ERR 0

//LEDÐòºÅ
__packed typedef enum
{
    LED_1 = 0x0001, 
    LED_2,
}LEDNum_e;

//LEDÊý¾Ý½á¹¹
__packed typedef struct
{
    uint8_t nLEDSta; //×´Ì¬
    uint16_t nLEDNum; //LEDÐòºÅ
}LEDData_t;

//º¯ÊýÉùÃ÷
uint8_t LEDInit(uint16_t nLEDNum,uint8_t nLEDSta,LEDData_t *pData);
uint8_t LEDCtrl(uint16_t nLEDNum,uint8_t nLEDSta,LEDData_t *pLEDSta);

#endif

#endif

















