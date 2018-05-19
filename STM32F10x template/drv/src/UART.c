/***************************************************************************** 
Copyright: CodeGeek@Hu         
File name: UART.c         
Description: UART�������ļ�
Author: HuJiaBin            
Version:                 
Date:                 
History:        
*****************************************************************************/ 
#include "HAL.h"

#ifdef USE_STM32F103

#include "UART.h"

//��̬����
static uint8_t arrUART1SendBuf[UART1_SEND_MAXLEN]; //����1���Ͷ��л���
static uint8_t arrUART1RecvBuf[UART1_RECV_MAXLEN]; //����1���ն��л���
static uint32_t nUART1RecvLen = 0; //��ǰ���ջ��������ݳ���

//ȫ�ֱ���
UARTData_t sUART1Stru; //����1���ݽṹ
OS_SEM g_sSEM_Recv_UART1; //����1��������ź���

//��д��
OS_MUT g_sMut_Send_UART1; //����1������
OS_MUT g_sMut_Recv_UART1; //����1������

/*##############################################################################################
��������: void UARTDataStructInit(UARTDataStru_t *pData,uint8_t *pSendBuf,uint8_t *pRecvBuf)
��������: �������ݽṹ��ʼ��
�䡡  ��: 
�䡡  ��: 
ȫ�ֱ���:
����ģ��:
�޶���ʷ: 
##############################################################################################*/
static uint8_t UARTDataStructInit(UARTData_t *pData,uint8_t *pSendBuf,uint8_t *pRecvBuf)
{
    //������
    if((pSendBuf == NULL) || (pRecvBuf == NULL))
    {
        return 0;
    }
    pData->nRecvLen = 0;
    pData->nSendLen = 0;
    pData->pRecvBuf = pRecvBuf;
    pData->pSendBuf = pSendBuf;
    return 1;
}


/*##############################################################################################
��������: int ResetUARTCurrentRecvDataLen(uint8_t nCOMNum)
��������: ��յ�ǰ���ڻ�������������
�䡡  ��: 
�䡡  ��: 
ȫ�ֱ���:
����ģ��:
�޶���ʷ: 
##############################################################################################*/
uint8_t ResetUARTCurrentRecvDataIndex(uint8_t nCOMNum)
{
    //�����������
    switch(nCOMNum)
    {
        case UART_1:
            nUART1RecvLen = 0;
            return 1;
        default:
            break;
    }
    return 0;
}

/*##############################################################################################
��������: uint8_t UARTInit(uint8_t nComNum,uint32_t nBoundRate,uint16_t nDataLength,uint16_t nStopBit,uint16_t nParity)
��������: ���ڳ�ʼ��
�䡡  ��: 
�䡡  ��: 
ȫ�ֱ���:
����ģ��:
�޶���ʷ: 
##############################################################################################*/
uint8_t UARTInit(uint8_t nComNum,uint32_t nBoundRate,uint16_t nDataLength,uint16_t nStopBit,uint16_t nParity)
{
    GPIO_InitTypeDef GPIO_InitStructure; //GPIO����
    USART_InitTypeDef USART_InitStructure; //UART����
    NVIC_InitTypeDef NVIC_InitStructure; //NVIC�ж�����
    
    //�ж����ں�
    switch(nComNum)
    {
    case UART_1:
        //��ʼ���������ݽṹ
        UARTDataStructInit(&sUART1Stru,arrUART1SendBuf,arrUART1RecvBuf);
        //��ʼ�����ڽ����ź���
        os_sem_init (&g_sSEM_Recv_UART1, 0);
        //��ʼ�����ڻ�����
        os_mut_init (&g_sMut_Send_UART1);
        os_mut_init (&g_sMut_Recv_UART1);
        //��ʼ������
        USART_DeInit(USART1); //��λ���� 1
        //GPIO �˿�ģʽ����
        GPIO_InitStructure.GPIO_Pin = UART1_TX_PIN; //ISART1_TX PA.9
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
        GPIO_Init(UART1_TX_PIN_INDEX, &GPIO_InitStructure);  //��ʼ�� GPIOA.9
        GPIO_InitStructure.GPIO_Pin = UART1_RX_PIN; //USART1_RX PA.10
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //��������
        GPIO_Init(UART1_RX_PIN_INDEX, &GPIO_InitStructure);  //��ʼ�� GPIOA.10
        //���ڲ�����ʼ��
        USART_InitStructure.USART_BaudRate = nBoundRate;  //����������
        USART_InitStructure.USART_WordLength = nDataLength; //�ֳ�
        USART_InitStructure.USART_StopBits = nStopBit; //ֹͣλ
        USART_InitStructure.USART_Parity = nParity; //��żУ��λ
        USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //��Ӳ������������
        USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//�շ�ģʽ
        USART_Init(USART1, &USART_InitStructure); //��ʼ������
        //��ʼ�� NVIC
        //NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
        //NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2 ; //��ռ���ȼ� 3
        //NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ� 3
        //NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  //IRQ ͨ��ʹ��
        //NVIC_Init(&NVIC_InitStructure);   //�ж����ȼ���ʼ��
        //�����ж�
        //USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); //�����ж�
        //ʹ�ܴ���
        USART_Cmd(USART1, ENABLE);   //ʹ�ܴ���
        //�򿪴��ڳ�ʱӲ����ʱ��
        //TimerInit(TIMER_3,99,7199); //10ms��ʱ
        //�رն�ʱ��
        //TimerCtrl(TIMER_3,0);
        break;
    default:
        return UART_ERR; //ʧ��
    }
    return UART_OK;
}

/*##############################################################################################
��������: void USART1_IRQHandler(void)
��������: ����1�жϺ���
�䡡  ��: 
�䡡  ��: 
ȫ�ֱ���:
����ģ��:
�޶���ʷ: 
##############################################################################################*/
static void USART1_IRQHandler(void)
{
    uint8_t nData = 0; 

    if(USART_GetITStatus(USART1,USART_IT_RXNE) != RESET)
    {
        nData = USART_ReceiveData(USART1);
        if(nUART1RecvLen < UART1_RECV_MAXLEN)
        {
            sUART1Stru.pRecvBuf[nUART1RecvLen++] = nData; //��ȡ����
            sUART1Stru.nRecvLen++; 
            TimerCtrl(TIMER_3,1); //�򿪳�ʱ��ʱ��
            TimerClearCount(TIMER_3); //��ճ�ʱ��ʱ��
        }
        else
        {
            //�������������������
            ResetUARTCurrentRecvDataIndex(UART_1);
            //�����ź���
            isr_sem_send (&g_sSEM_Recv_UART1);
        }
    }
}

/*##############################################################################################
��������: uint8_t UARTSendByteBlcoking(uint8_t nCOMNum,uint8_t nData)
��������: ���ڷ����ֽ�
�䡡  ��: 
�䡡  ��: 
ȫ�ֱ���:
����ģ��:
�޶���ʷ: 
##############################################################################################*/
static uint8_t UARTSendByteBlcoking(uint8_t nComNum,uint8_t nData)
{
    switch(nComNum)
    {
    case UART_1:
        while(USART_GetFlagStatus(USART1,USART_FLAG_TC) == RESET); //ȷ����һ���ֽڷ������
        USART_SendData(USART1,nData); //��������
        return UART_OK; //�ɹ�
    default:
        break;
    }
    return UART_ERR;
}

/*##############################################################################################
��������: uint8_t UARTReceiveByteBlocking(uint8_t nCOMNum,uint8_t nData)
��������: ���ڷ������ֽ�
�䡡  ��: 
�䡡  ��: 
ȫ�ֱ���:
����ģ��:
�޶���ʷ: 
##############################################################################################*/
static uint8_t UARTReceiveByteBlocking(uint8_t nCOMNum,uint8_t *pData)
{
    switch(nCOMNum)
    {
    case UART_1:
        while(USART_GetFlagStatus(USART1,USART_FLAG_RXNE) == RESET); //ȷ���ֽڽ������
        *pData = USART_ReceiveData(USART1); //��������
        return UART_OK; //�ɹ�
    default:
        break;
    }
    return UART_ERR;
}


/*##############################################################################################
��������: uint8_t UARTSendDataBlocking(uint8_t nComNum,uint8_t *pSendData,uint32_t nLen)
��������: ���ڷ������ⳤ������ 
�䡡  ��: 
�䡡  ��: 
ȫ�ֱ���:
����ģ��:
�޶���ʷ: 
##############################################################################################*/
uint8_t UARTSendDataBlocking(uint8_t nComNum,uint8_t *pSendData,uint32_t nLen)
{
    uint32_t nLenTmp = nLen;

    if(pSendData == NULL)
    {
        return UART_ERR;
    }
    
    os_mut_wait (&g_sMut_Send_UART1, 0xffff);
    
    while(nLenTmp != 0)
    {
        if(UARTSendByteBlcoking(nComNum,*pSendData) == UART_OK)
        {
            pSendData++;
            nLenTmp--;
        }
        else
        {
            return UART_ERR;
        }
        
    }
    
    os_mut_release (&g_sMut_Send_UART1);
    
    return UART_OK;
}

/*##############################################################################################
��������: uint8_t UARTSendDataBlocking(uint8_t nComNum,uint8_t *pSendData,uint32_t nLen)
��������: ���ڷ������ⳤ������ 
�䡡  ��: 
�䡡  ��: 
ȫ�ֱ���:
����ģ��:
�޶���ʷ: 
##############################################################################################*/
uint8_t UARTReceiveDataBlocking(uint8_t nComNum,uint8_t *pReceiveData,uint32_t nLen)
{
    uint8_t data = 0;
    
    
    do {
         UARTReceiveByteBlocking(nComNum,&data);
        *pReceiveData = data;
        pReceiveData++;
        nLen--;
    }
    while(nLen);
 
    return UART_OK;
}


/*##############################################################################################
��������: 
��������: ���ڽ������ⳤ������
�䡡  ��: 
�䡡  ��: 
ȫ�ֱ���:
����ģ��:
�޶���ʷ: 
##############################################################################################*/
uint32_t UARTRecvData(uint8_t nComNum,uint8_t *pRecvData)
{    
    uint32_t nRecvLen = 0;

    if(pRecvData == NULL)
    {
        return UART_ERR;
    }
    
    os_mut_wait (&g_sMut_Recv_UART1, 0xffff);
    
    switch(nComNum)
    {
    case UART_1:
        //�ȴ��ź���
        os_sem_wait (&g_sSEM_Recv_UART1, 0xffff);
        memcpy(pRecvData,sUART1Stru.pRecvBuf,sUART1Stru.nRecvLen);
        nRecvLen = sUART1Stru.nRecvLen;
        //��ʼ���������ݽṹ
        UARTDataStructInit(&sUART1Stru,arrUART1SendBuf,arrUART1RecvBuf);
        os_mut_release (&g_sMut_Send_UART1);
        return nRecvLen;
    }
    
    os_mut_release (&g_sMut_Recv_UART1);
    
    return UART_ERR;
}

#endif
































