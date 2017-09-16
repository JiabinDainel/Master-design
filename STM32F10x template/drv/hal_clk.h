#ifndef _HAL_CLK_H
#define _HAL_CLK_H

#include "hal.h"

typedef enum
{
    hal_uart_1_clk = 1,
    hal_led_1_clk,
    hal_led_2_clk,
}hal_clk_id;

hal_status hal_clk_init(hal_clk_id clk_id,hal_status clk_sta);

#endif

