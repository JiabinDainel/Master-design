/***************************************************************************** 
Copyright: CodeGeek@Hu         
File name: HAl.c  
Description: BSP�м��֧���ļ�
Author: HuJiaBin            
Version:                 
Date:                 
History:        
*****************************************************************************/
#include "hal_uart.h"
#include "hal_clk.h"
#include "io.h"

/*##############################################################################################
��������: unsigned int HAL_ClockInit(void) 
��������: BSPʱ�ӳ�ʼ��
�䡡  ��: 
�䡡  ��: 
ȫ�ֱ���:
����ģ��:
�޶���ʷ: 
##############################################################################################*/
hal_status hal_uart_init(hal_uart_param uart_param,hal_status uart_sta)
{
    FunctionalState drv_sta;
    GPIO_InitTypeDef  GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    
    if(hal_open == uart_sta)
    {
        drv_sta = ENABLE;
    }
    else if(hal_close == uart_sta)
    {
        USART_Cmd(USART1, DISABLE); //�رմ��� 
        return hal_OK;
    }
    else
    {
        
        return hal_ERR;
    }
    
    //init bus clk
    hal_clk_init(hal_uart_1_clk,uart_sta);
    
    //���������� 
    USART_InitStructure.USART_BaudRate = uart_param.bound_rate;//һ������Ϊ9600;
    if(uart_8_bit_data == uart_param.data_length)
    {
        USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
    }
    else if(uart_9_bit_data == uart_param.data_length)
    {
        USART_InitStructure.USART_WordLength = USART_WordLength_9b;//�ֳ�Ϊ9λ���ݸ�ʽ
    }
    //ֹͣλ���� 
    if(uart_stop_bit_1 == uart_param.stop_bit)
    {
        USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
    }
    else if(uart_stop_bit_2 == uart_param.stop_bit)
    {
        USART_InitStructure.USART_StopBits = USART_StopBits_2;//2��ֹͣλ
    }
    //У��λ����
    if(uart_checksum_even == uart_param.checksum_type)
    {
        USART_InitStructure.USART_Parity = USART_Parity_Even;
    }
    if(uart_checksum_odd == uart_param.checksum_type)
    {
        USART_InitStructure.USART_Parity = USART_Parity_Odd;
    }
    else
    {
        USART_InitStructure.USART_Parity = USART_Parity_No;
    }

    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
    USART_Init(USART1, &USART_InitStructure); //��ʼ������
    
    switch(uart_param.id)
    {
        case hal_uart_1:
            //init io pin
            //USART1_TX   PA.9
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
            GPIO_Init(GPIOA, &GPIO_InitStructure); //��ʼ��PA9       
            //USART1_RX	  PA.10
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
            GPIO_Init(GPIOA, &GPIO_InitStructure);  //��ʼ��PA10
        
            //open/close uart
            USART_Cmd(USART1, drv_sta); //ʹ�ܴ��� 
            break;     
        default:
            
            return hal_ERR;
    }
    
    //DMA config
    if(uart_param.uart_dma_enable == hal_on)
    {
        
    }
    
    return hal_OK;
}

/*##############################################################################################
��������: unsigned int HAL_ClockInit(void) 
��������: BSPʱ�ӳ�ʼ��
�䡡  ��: 
�䡡  ��: 
ȫ�ֱ���:
����ģ��:
�޶���ʷ: 
##############################################################################################*/
hal_status hal_uart_write_byte(hal_uart_id uart_id,uint8_t write_data)
{
    USART_TypeDef *p_uart_typedef;
    
    switch(uart_id)
    {
        case hal_uart_1:
            p_uart_typedef = USART1;
            break;
        default:
            return hal_ERR;
        
    }
    
    USART_SendData(p_uart_typedef, write_data);//�򴮿�1��������
    while(USART_GetFlagStatus(p_uart_typedef,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
    
    return hal_OK;
}

/*##############################################################################################
��������: unsigned int HAL_ClockInit(void) 
��������: BSPʱ�ӳ�ʼ��
�䡡  ��: 
�䡡  ��: 
ȫ�ֱ���:
����ģ��:
�޶���ʷ: 
##############################################################################################*/
hal_status hal_uart_read_byte(hal_uart_id uart_id,uint8_t *read_data)
{
    USART_TypeDef *p_uart_typedef;
    
    switch(uart_id)
    {
        case hal_uart_1:
            p_uart_typedef = USART1;
            break;
        default:
            return hal_ERR;
        
    }
    
    while(USART_GetFlagStatus(p_uart_typedef,USART_FLAG_RXNE)!=SET);//�ȴ�data register����
    *read_data = (uint8_t)USART_ReceiveData(p_uart_typedef);
    return hal_OK;
}

/*##############################################################################################
��������: unsigned int HAL_ClockInit(void) 
��������: BSPʱ�ӳ�ʼ��
�䡡  ��: 
�䡡  ��: 
ȫ�ֱ���:
����ģ��:
�޶���ʷ: 
##############################################################################################*/
hal_status hal_uart_write_data_polling(hal_uart_id uart_id,uint8_t *write_data,uint32_t nlen)
{    
    uint8_t *p_write_data = write_data;
    
    while(nlen > 0)
    {
        hal_uart_write_byte(uart_id,*p_write_data);
        p_write_data++;
        nlen--;
    }
    
    return hal_OK;
}

/*##############################################################################################
��������: unsigned int HAL_ClockInit(void) 
��������: BSPʱ�ӳ�ʼ��
�䡡  ��: 
�䡡  ��: 
ȫ�ֱ���:
����ģ��:
�޶���ʷ: 
##############################################################################################*/
hal_status hal_uart_read_data_polling(hal_uart_id uart_id,uint8_t *read_data,uint32_t nlen)
{
   uint8_t *p_read_data = read_data;
    
    while(nlen > 0)
    {
        hal_uart_read_byte(uart_id,p_read_data);
        p_read_data++;
        nlen--;
    }
    
    return hal_OK;
}

/*##############################################################################################
��������: unsigned int HAL_ClockInit(void) 
��������: BSPʱ�ӳ�ʼ��
�䡡  ��: 
�䡡  ��: 
ȫ�ֱ���:
����ģ��:
�޶���ʷ: 
##############################################################################################*/
hal_status hal_uart_write_data_DMA(hal_uart_id uart_id,uint8_t *write_data,uint32_t nlen)
{
    
}

/*##############################################################################################
��������: unsigned int HAL_ClockInit(void) 
��������: BSPʱ�ӳ�ʼ��
�䡡  ��: 
�䡡  ��: 
ȫ�ֱ���:
����ģ��:
�޶���ʷ: 
##############################################################################################*/
hal_status hal_uart_read_data_DMA(hal_uart_id uart_id,uint8_t *read_data,uint32_t nlen)
{
    
}
