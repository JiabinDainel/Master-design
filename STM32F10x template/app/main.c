
#include "stm32f10x.h"
#include "RTL.h"
#include "hal.h"

__task void init_task (void *argv);
__task void task1 (void *argv);
__task void task2 (void *argv);

OS_TID tsk1, tsk2;

int main(void)
{
    os_sys_init ((void *)init_task);  /* start the kernel     */
    while(1);             /* will never come here */
}

__task void init_task (void *argv)
{
    tsk1 = os_tsk_create ((void *)task1, 5);
    //tsk2 = os_tsk_create ((void *)task2, 10);
    
    while(1)
    {
         os_tsk_pass();
    }
}

__task void task1 (void *argv)
{
    uint8_t receive_data[64];

    memset(receive_data,0,sizeof(receive_data));
    
    HAL_init();
    
    while(1)
    {
        UARTReceiveDataBlocking(UART_1,receive_data,sizeof("hello world stm32 platform\r\n"));
        HAL_UartSendData(UART_1,receive_data,sizeof("hello world stm32 platform\r\n"));
        os_dly_wait (10);
    }
}

__task void task2 (void *argv)
{
    while(1)
    {
        os_dly_wait (200);
    }
}

