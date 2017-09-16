#include "stm32f10x.h"
#include "RTL.h"
#include "hal_led.h"
#include "hal_uart.h"

__task void init_task (void *argv);
__task void task1 (void *argv);
__task void task2 (void *argv);

OS_TID tsk1, tsk2;

int main(void)
{
    hal_led_init(hal_led_1,hal_open);
    hal_led_init(hal_led_2,hal_open);
    os_sys_init ((void *)init_task);  /* start the kernel     */
    while(1);             /* will never come here */
}

__task void init_task (void *argv)
{
    tsk1 = os_tsk_create ((void *)task1, 5);
    tsk2 = os_tsk_create ((void *)task2, 10);
    
    while(1)
    {
         os_tsk_pass();
    }
}

__task void task1 (void *argv)
{
    while(1)
    {
        hal_led_ctrl(hal_led_1,hal_on);
        os_dly_wait (100);
        hal_led_ctrl(hal_led_1,hal_off);
        os_dly_wait (100);
    }
}


static uint8_t buffer[512];

__task void task2 (void *argv)
{
    hal_uart_param uart_param;
    uint8_t test_data = 0;
    
    uart_param.bound_rate = 9600;
    uart_param.data_length = uart_8_bit_data;
    uart_param.id = hal_uart_1;
    uart_param.stop_bit = uart_stop_bit_1;
    uart_param.checksum_type = uart_checksum_none;
    
    hal_uart_init(uart_param,hal_open);
    
    while(1)
    {
        os_dly_wait (100);
    }
}

