/***************************************************************************** 
Copyright: CodeGeek@Hu         
File name: HAl.c  
Description: BSP中间件支持文件
Author: HuJiaBin            
Version:                 
Date:                 
History:        
*****************************************************************************/
#include "hal_uart.h"
#include "hal_clk.h"
#include "io.h"

/*##############################################################################################
函数名称: unsigned int HAL_ClockInit(void) 
功能描述: BSP时钟初始化
输　  入: 
输　  出: 
全局变量:
调用模块:
修订历史: 
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
        USART_Cmd(USART1, DISABLE); //关闭串口 
        return hal_OK;
    }
    else
    {
        
        return hal_ERR;
    }
    
    //init bus clk
    hal_clk_init(hal_uart_1_clk,uart_sta);
    
    //波特率配置 
    USART_InitStructure.USART_BaudRate = uart_param.bound_rate;//一般设置为9600;
    if(uart_8_bit_data == uart_param.data_length)
    {
        USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
    }
    else if(uart_9_bit_data == uart_param.data_length)
    {
        USART_InitStructure.USART_WordLength = USART_WordLength_9b;//字长为9位数据格式
    }
    //停止位配置 
    if(uart_stop_bit_1 == uart_param.stop_bit)
    {
        USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
    }
    else if(uart_stop_bit_2 == uart_param.stop_bit)
    {
        USART_InitStructure.USART_StopBits = USART_StopBits_2;//2个停止位
    }
    //校验位配置
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

    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
    USART_Init(USART1, &USART_InitStructure); //初始化串口
    
    switch(uart_param.id)
    {
        case hal_uart_1:
            //init io pin
            //USART1_TX   PA.9
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
            GPIO_Init(GPIOA, &GPIO_InitStructure); //初始化PA9       
            //USART1_RX	  PA.10
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
            GPIO_Init(GPIOA, &GPIO_InitStructure);  //初始化PA10
        
            //open/close uart
            USART_Cmd(USART1, drv_sta); //使能串口 
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
函数名称: unsigned int HAL_ClockInit(void) 
功能描述: BSP时钟初始化
输　  入: 
输　  出: 
全局变量:
调用模块:
修订历史: 
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
    
    USART_SendData(p_uart_typedef, write_data);//向串口1发送数据
    while(USART_GetFlagStatus(p_uart_typedef,USART_FLAG_TC)!=SET);//等待发送结束
    
    return hal_OK;
}

/*##############################################################################################
函数名称: unsigned int HAL_ClockInit(void) 
功能描述: BSP时钟初始化
输　  入: 
输　  出: 
全局变量:
调用模块:
修订历史: 
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
    
    while(USART_GetFlagStatus(p_uart_typedef,USART_FLAG_RXNE)!=SET);//等待data register数据
    *read_data = (uint8_t)USART_ReceiveData(p_uart_typedef);
    return hal_OK;
}

/*##############################################################################################
函数名称: unsigned int HAL_ClockInit(void) 
功能描述: BSP时钟初始化
输　  入: 
输　  出: 
全局变量:
调用模块:
修订历史: 
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
函数名称: unsigned int HAL_ClockInit(void) 
功能描述: BSP时钟初始化
输　  入: 
输　  出: 
全局变量:
调用模块:
修订历史: 
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
函数名称: unsigned int HAL_ClockInit(void) 
功能描述: BSP时钟初始化
输　  入: 
输　  出: 
全局变量:
调用模块:
修订历史: 
##############################################################################################*/
hal_status hal_uart_write_data_DMA(hal_uart_id uart_id,uint8_t *write_data,uint32_t nlen)
{
    
}

/*##############################################################################################
函数名称: unsigned int HAL_ClockInit(void) 
功能描述: BSP时钟初始化
输　  入: 
输　  出: 
全局变量:
调用模块:
修订历史: 
##############################################################################################*/
hal_status hal_uart_read_data_DMA(hal_uart_id uart_id,uint8_t *read_data,uint32_t nlen)
{
    
}
