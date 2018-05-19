/***************************************************************************** 
Copyright: CodeGeek@Hu         
File name: BSPMiddleware.h  
Description: BSP中间件支持文件
Author: HuJiaBin            
Version:                 
Date:                 
History:        
*****************************************************************************/
#ifndef _BSPMIDDLEWARE_H
#define _BSPMIDDLEWARE_H

//使用STM32F103的主控IC
#define USE_STM32F103 

//引用BSP头文件
#include "stm32f10x.h"
#include "LED.h"
#include "Timer.h"
#include "UART.h"
#include "io.h"
#include "RCC.h"

//定义状态
#define HAL_OK 1
#define HAL_ERR 0

#define HAL_ON 1
#define HAL_OFF 0

#ifdef USE_STM32F103
//定义串口参数
__packed typedef enum
{
    HAL_UART_DATALENGTH_8 = USART_WordLength_8b,
    HAL_UART_DATALENGTH_9 = USART_WordLength_9b,
    
    HAL_UART_STOP_1 = USART_StopBits_1,
    
    HAL_PARITY_EVEN = USART_Parity_Even,
    HAL_PARITY_ODD = USART_Parity_Odd,
    HAL_PARITY_NO = USART_Parity_No,    
}HAL_UART_Param_e;

//定义外设ID
__packed typedef enum
{
	HAL_LED_1 = LED_1, //LED1
	HAL_LED_2 = LED_2, //LED2
	HAL_UART_1 = UART_1, //UART1
}HAL_Device_ID_e;

#else 
//定义串口参数（架构预留）
__packed typedef enum
{
    HAL_UART_DATALENGTH_8,
    HAL_UART_DATALENGTH_9,
    
    HAL_UART_STOP_11,
    
    HAL_PARITY_EVEN,
    HAL_PARITY_ODD,
    HAL_PARITY_NO,    
}HAL_UART_Param_e;

//定义外设ID（架构预留）
__packed typedef enum
{
	HAL_LED_1, //LED1
	HAL_LED_2, //LED2
	HAL_UART_1, //UART1
}HAL_Device_ID_e;

#endif

unsigned int HAL_ClockInit(void);

unsigned int HAL_LEDInit(unsigned int nLEDNum,unsigned char nLEDSta);
unsigned int HAL_LEDCtrl(unsigned int nLEDNum,unsigned char nLEDSta);

unsigned int HAL_UartInit(unsigned char nComNum,unsigned int nBoundRate,unsigned short nDataLength,unsigned short nStopBit,unsigned short nParity);
unsigned int HAL_UartSendData(unsigned char nComNum,unsigned char *pSendData,unsigned int nLen);
unsigned int HAL_UartRecvData(unsigned char nComNum,unsigned char *pRecvData);

#endif





