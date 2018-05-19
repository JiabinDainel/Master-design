/***************************************************************************** 
Copyright: CodeGeek@Hu         
File name: LED.c  
Description: 
Author: HuJiaBin            
Version:                 
Date:                 
History:        
*****************************************************************************/ 
#include "HAL.h"

#ifdef USE_STM32F103

#include "LED.h"

/*##############################################################################################
函数名称: uint8_t LEDInit(uint16_t nLEDNum,uint8_t nLEDSta,LEDDataStru_t *pData)
功能描述: LED初始化
输　  入: 
输　  出: 
全局变量:
调用模块:
修订历史: 
##############################################################################################*/
uint8_t LEDInit(uint16_t nLEDNum,uint8_t nLEDSta,LEDData_t *pData)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    //检查参数
    if(pData == 0)
    {
        return LED_ERR;
    }
    //开启LED
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    
    switch(nLEDNum)
    {
        case LED_1:
            //测试
            //初始化GPIO
            GPIO_InitStructure.GPIO_Pin = LED1_PIN;  
            GPIO_Init(LED1_PIN_INDEX, &GPIO_InitStructure);       
            break;           
        case LED_2:
            //初始化GPIO
            GPIO_InitStructure.GPIO_Pin = LED2_PIN;  
            GPIO_Init(LED2_PIN_INDEX, &GPIO_InitStructure);            
            break;
        default:
            return LED_ERR;
    }
    LEDCtrl(nLEDNum,nLEDSta,pData);
    return LED_OK;
}

/*##############################################################################################
函数名称: uint8_t LEDCtrl(uint16_t nLEDNum,uint8_t nLEDSta)
功能描述: LED控制
输　  入: 
输　  出: 
全局变量:
调用模块:
修订历史: 
##############################################################################################*/
uint8_t LEDCtrl(uint16_t nLEDNum,uint8_t nLEDSta,LEDData_t *pLEDSta)
{ 
    switch(nLEDNum)
    {
        case LED_1:
            if(nLEDSta == LED_OFF)
            {
                GPIO_SetBits(LED1_PIN_INDEX,LED1_PIN);
                
            }
            else
            {
                GPIO_ResetBits(LED1_PIN_INDEX,LED1_PIN);
            }
            break;
        case LED_2:
            if(nLEDSta == LED_OFF)
            {
                GPIO_SetBits(LED2_PIN_INDEX,LED2_PIN);
            }
            else
            {
                GPIO_ResetBits(LED2_PIN_INDEX,LED2_PIN);
            }
            break;
        default:
            return LED_OK;
    }
    pLEDSta->nLEDNum = nLEDNum; //更新LED序号
    pLEDSta->nLEDSta = nLEDSta;  //更新LED状态      
    return LED_OK;
}

#endif




