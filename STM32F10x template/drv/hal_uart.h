/***************************************************************************** 
Copyright: CodeGeek@Hu         
File name: HAl.c  
Description: BSP中间件支持文件
Author: HuJiaBin            
Version:                 
Date:                 
History:        
*****************************************************************************/
#ifndef _HAL_UART_H
#define _HAL_UART_H

#include "hal.h"

typedef enum 
{
    hal_uart_1 = 1,
}hal_uart_id;

typedef enum 
{
    hal_event_uart_transfer_done = 1,
    hal_event_uart_transfer_err,
}hal_uart_event;

typedef enum
{
    uart_8_bit_data = 1,
    uart_9_bit_data,
}hal_uart_data_length;

typedef enum
{
    uart_stop_bit_1 = 1,
    uart_stop_bit_2,
}hal_uart_stop_bit;

typedef enum
{
    uart_checksum_odd = 1,
    uart_checksum_even,
    uart_checksum_none,
}hal_uart_checksum_type;

typedef struct
{
    hal_uart_id id; //uart序号
    uint32_t bound_rate; //波特率
    hal_uart_data_length data_length; //数据长度
    hal_uart_stop_bit stop_bit; //停止位
    hal_uart_checksum_type checksum_type; //校验位 
    void (*uart_event_callback)(hal_uart_event event ,void *data); //uart callback
    hal_status uart_dma_enable; //uart dma enable
}hal_uart_param;


//API
hal_status hal_uart_init(hal_uart_param uart_param,hal_status uart_sta);
hal_status hal_uart_write_byte(hal_uart_id uart_id,uint8_t write_data);
hal_status hal_uart_read_byte(hal_uart_id uart_id,uint8_t *read_data);
hal_status hal_uart_write_data_polling(hal_uart_id uart_id,uint8_t *write_data,uint32_t nlen);

#endif

