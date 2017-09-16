#ifndef _LED_H
#define _LED_H

#include "hal.h"

typedef enum 
{
    hal_led_1 = 1,
    hal_led_2,
}hal_led_id;

hal_status hal_led_init(hal_led_id led_id,hal_status led_sta);
hal_status hal_led_ctrl(hal_led_id led_id,hal_status led_sta);

#endif

