/***************************************************************************** 
Copyright: CodeGeek@Hu         
File name: UART.c          
Description: UART����ͷ�ļ�
Author: HuJiaBin            
Version:                 
Date:                 
History:        
*****************************************************************************/ 
#include "HAL.h"

#ifndef _UART_H
#define _UART_H

#ifdef USE_STM32F103

#include "stm32f10x.h"
#include "Timer.h"
#include "rtl.h"
#include "io.h"
#include <string.h>

//����״̬
#define UART_OK 1
#define UART_ERR 0

//�����������
__packed typedef enum
{
	UART_1 = 0x01,

}UARTNum_e;

//�������ݽṹ
__packed typedef struct
{
    uint8_t *pRecvBuf; //���ݽ���ָ��
    uint8_t *pSendBuf; //���ݷ���ָ��
    uint32_t nSendLen; //�������ݳ���
    uint32_t nRecvLen; //�������ݳ���
}UARTData_t;

//�������ݶ��г���
#define UART1_SEND_MAXLEN 64
#define UART1_RECV_MAXLEN 64

//��������
uint8_t UARTDataStructInit(UARTData_t *pData,uint8_t *pSendBuf,uint8_t *pRecvBuf);
uint8_t ResetUARTCurrentRecvDataIndex(uint8_t nCOMNum);
uint8_t UARTInit(uint8_t nComNum,uint32_t nBoundRate,uint16_t nDataLength,uint16_t nStopBit,uint16_t nParity);
uint8_t UARTSendData(uint8_t nComNum,uint8_t *pSendData,uint32_t nLen);
uint32_t UARTRecvData(uint8_t nComNum,uint8_t *pRecvData);


#endif

#endif

