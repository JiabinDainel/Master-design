
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
    //uart ≤‚ ‘
    /*uint8_t receive_data[64];

    memset(receive_data,0,sizeof(receive_data));
    
    HAL_init();
    
    while(1)
    {
        UARTReceiveDataBlocking(UART_1,receive_data,sizeof("hello world stm32 platform\r\n"));
        HAL_UartSendData(UART_1,receive_data,sizeof("hello world stm32 platform\r\n"));
        os_dly_wait (10);
    }*/

    //sram ≤‚ ‘
    /*volatile uint8_t test_data = 0;
    
    FSMC_SRAM_Init();
    
    fsmc_sram_test_write(0xaa,0);
    test_data = fsmc_sram_test_read(0);*/
    
    //spi flash ≤‚ ‘
    static uint8_t write_buf[256];
    static uint8_t read_buf[256];
    
    memset(write_buf,0xaa,sizeof(write_buf));
    memset(read_buf,0x0,sizeof(read_buf));
    SPI_Flash_Init();
    SPI_Flash_Write(write_buf,0,sizeof(write_buf));
    SPI_Flash_Read(read_buf,0,sizeof(read_buf));
    
    
    while(1)
    {
         os_tsk_pass();
    }
}

__task void task2 (void *argv)
{
    while(1)
    {
        os_dly_wait (200);
    }
}

