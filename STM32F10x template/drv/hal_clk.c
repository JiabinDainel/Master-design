#include "hal_clk.h"

hal_status hal_clk_init(hal_clk_id clk_id,hal_status clk_sta)
{
    FunctionalState drv_sta;
    
    if(hal_open == clk_sta)
    {
        drv_sta = ENABLE;
    }
    else if(hal_close == clk_sta)
    {
        drv_sta = DISABLE;
    }
    else
    {
        
        return hal_ERR;
    }
    
    switch(clk_id)
    {
        case hal_uart_1_clk:
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, drv_sta);
            break;
        case hal_led_1_clk:
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, drv_sta);	
            break;
        case hal_led_2_clk:
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, drv_sta);	
            break;
        default:
            
            return hal_ERR;
    }
    
    return hal_OK;
}

