/***************************************************************************** 
Copyright: CodeGeek@Hu         
File name: UART.c         
Description: UART串口主文件
Author: HuJiaBin            
Version:                 
Date:                 
History:        
*****************************************************************************/ 
#include "HAL.h"

#ifdef USE_STM32F103

#include "UART.h"

//静态变量
static uint8_t arrUART1SendBuf[UART1_SEND_MAXLEN]; //串口1发送队列缓冲
static uint8_t arrUART1RecvBuf[UART1_RECV_MAXLEN]; //串口1接收队列缓冲
static uint32_t nUART1RecvLen = 0; //当前接收缓冲区数据长度

//全局变量
UARTData_t sUART1Stru; //串口1数据结构
OS_SEM g_sSEM_Recv_UART1; //串口1接受完毕信号量

//读写锁
OS_MUT g_sMut_Send_UART1; //串口1发送锁
OS_MUT g_sMut_Recv_UART1; //串口1接收锁

/*##############################################################################################
函数名称: void UARTDataStructInit(UARTDataStru_t *pData,uint8_t *pSendBuf,uint8_t *pRecvBuf)
功能描述: 串口数据结构初始化
输　  入: 
输　  出: 
全局变量:
调用模块:
修订历史: 
##############################################################################################*/
static uint8_t UARTDataStructInit(UARTData_t *pData,uint8_t *pSendBuf,uint8_t *pRecvBuf)
{
    //检查参数
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
函数名称: int ResetUARTCurrentRecvDataLen(uint8_t nCOMNum)
功能描述: 清空当前串口缓冲区数据索引
输　  入: 
输　  出: 
全局变量:
调用模块:
修订历史: 
##############################################################################################*/
uint8_t ResetUARTCurrentRecvDataIndex(uint8_t nCOMNum)
{
    //索引串口序号
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
函数名称: uint8_t UARTInit(uint8_t nComNum,uint32_t nBoundRate,uint16_t nDataLength,uint16_t nStopBit,uint16_t nParity)
功能描述: 串口初始化
输　  入: 
输　  出: 
全局变量:
调用模块:
修订历史: 
##############################################################################################*/
uint8_t UARTInit(uint8_t nComNum,uint32_t nBoundRate,uint16_t nDataLength,uint16_t nStopBit,uint16_t nParity)
{
    GPIO_InitTypeDef GPIO_InitStructure; //GPIO配置
    USART_InitTypeDef USART_InitStructure; //UART配置
    NVIC_InitTypeDef NVIC_InitStructure; //NVIC中断配置
    
    //判定串口号
    switch(nComNum)
    {
    case UART_1:
        //初始化串口数据结构
        UARTDataStructInit(&sUART1Stru,arrUART1SendBuf,arrUART1RecvBuf);
        //初始化串口接受信号量
        os_sem_init (&g_sSEM_Recv_UART1, 0);
        //初始化串口互斥锁
        os_mut_init (&g_sMut_Send_UART1);
        os_mut_init (&g_sMut_Recv_UART1);
        //初始化串口
        USART_DeInit(USART1); //复位串口 1
        //GPIO 端口模式设置
        GPIO_InitStructure.GPIO_Pin = UART1_TX_PIN; //ISART1_TX PA.9
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
        GPIO_Init(UART1_TX_PIN_INDEX, &GPIO_InitStructure);  //初始化 GPIOA.9
        GPIO_InitStructure.GPIO_Pin = UART1_RX_PIN; //USART1_RX PA.10
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //浮空输入
        GPIO_Init(UART1_RX_PIN_INDEX, &GPIO_InitStructure);  //初始化 GPIOA.10
        //串口参数初始化
        USART_InitStructure.USART_BaudRate = nBoundRate;  //波特率设置
        USART_InitStructure.USART_WordLength = nDataLength; //字长
        USART_InitStructure.USART_StopBits = nStopBit; //停止位
        USART_InitStructure.USART_Parity = nParity; //奇偶校验位
        USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //无硬件数据流控制
        USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//收发模式
        USART_Init(USART1, &USART_InitStructure); //初始化串口
        //初始化 NVIC
        //NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
        //NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2 ; //抢占优先级 3
        //NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //子优先级 3
        //NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  //IRQ 通道使能
        //NVIC_Init(&NVIC_InitStructure);   //中断优先级初始化
        //开启中断
        //USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); //开启中断
        //使能串口
        USART_Cmd(USART1, ENABLE);   //使能串口
        //打开串口超时硬件定时器
        //TimerInit(TIMER_3,99,7199); //10ms超时
        //关闭定时器
        //TimerCtrl(TIMER_3,0);
        break;
    default:
        return UART_ERR; //失败
    }
    return UART_OK;
}

/*##############################################################################################
函数名称: void USART1_IRQHandler(void)
功能描述: 串口1中断函数
输　  入: 
输　  出: 
全局变量:
调用模块:
修订历史: 
##############################################################################################*/
static void USART1_IRQHandler(void)
{
    uint8_t nData = 0; 

    if(USART_GetITStatus(USART1,USART_IT_RXNE) != RESET)
    {
        nData = USART_ReceiveData(USART1);
        if(nUART1RecvLen < UART1_RECV_MAXLEN)
        {
            sUART1Stru.pRecvBuf[nUART1RecvLen++] = nData; //获取数据
            sUART1Stru.nRecvLen++; 
            TimerCtrl(TIMER_3,1); //打开超时定时器
            TimerClearCount(TIMER_3); //清空超时定时器
        }
        else
        {
            //缓冲区已满，接收完毕
            ResetUARTCurrentRecvDataIndex(UART_1);
            //发送信号量
            isr_sem_send (&g_sSEM_Recv_UART1);
        }
    }
}

/*##############################################################################################
函数名称: uint8_t UARTSendByteBlcoking(uint8_t nCOMNum,uint8_t nData)
功能描述: 串口发送字节
输　  入: 
输　  出: 
全局变量:
调用模块:
修订历史: 
##############################################################################################*/
static uint8_t UARTSendByteBlcoking(uint8_t nComNum,uint8_t nData)
{
    switch(nComNum)
    {
    case UART_1:
        while(USART_GetFlagStatus(USART1,USART_FLAG_TC) == RESET); //确定上一个字节发送完毕
        USART_SendData(USART1,nData); //发送数据
        return UART_OK; //成功
    default:
        break;
    }
    return UART_ERR;
}

/*##############################################################################################
函数名称: uint8_t UARTReceiveByteBlocking(uint8_t nCOMNum,uint8_t nData)
功能描述: 串口发接收字节
输　  入: 
输　  出: 
全局变量:
调用模块:
修订历史: 
##############################################################################################*/
static uint8_t UARTReceiveByteBlocking(uint8_t nCOMNum,uint8_t *pData)
{
    switch(nCOMNum)
    {
    case UART_1:
        while(USART_GetFlagStatus(USART1,USART_FLAG_RXNE) == RESET); //确定字节接收完毕
        *pData = USART_ReceiveData(USART1); //接收数据
        return UART_OK; //成功
    default:
        break;
    }
    return UART_ERR;
}


/*##############################################################################################
函数名称: uint8_t UARTSendDataBlocking(uint8_t nComNum,uint8_t *pSendData,uint32_t nLen)
功能描述: 串口发送任意长度数据 
输　  入: 
输　  出: 
全局变量:
调用模块:
修订历史: 
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
函数名称: uint8_t UARTSendDataBlocking(uint8_t nComNum,uint8_t *pSendData,uint32_t nLen)
功能描述: 串口发送任意长度数据 
输　  入: 
输　  出: 
全局变量:
调用模块:
修订历史: 
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
函数名称: 
功能描述: 串口接受任意长度数据
输　  入: 
输　  出: 
全局变量:
调用模块:
修订历史: 
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
        //等待信号量
        os_sem_wait (&g_sSEM_Recv_UART1, 0xffff);
        memcpy(pRecvData,sUART1Stru.pRecvBuf,sUART1Stru.nRecvLen);
        nRecvLen = sUART1Stru.nRecvLen;
        //初始化串口数据结构
        UARTDataStructInit(&sUART1Stru,arrUART1SendBuf,arrUART1RecvBuf);
        os_mut_release (&g_sMut_Send_UART1);
        return nRecvLen;
    }
    
    os_mut_release (&g_sMut_Recv_UART1);
    
    return UART_ERR;
}

#endif
































