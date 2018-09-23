#include "hal.h"
#include "RTL.h"

/*##############################################################################################
函数名称: 
功能描述: LED可以完成正确的初始化，init点亮led，并在3s后init熄灭led
输　  入: 
输　  出: 
全局变量:
调用模块:
修订历史: 
##############################################################################################*/
void led_test(void)
{
    //BUS clk初始化
    HAL_ClockInit();

    //LED驱动初始化
    HAL_LEDInit(LED_1,LED_ON);
    HAL_LEDInit(LED_2,LED_ON);

    //delay 3s
    os_dly_wait (300);

    //LED驱动初始化
    HAL_LEDInit(LED_1,LED_OFF);
    HAL_LEDInit(LED_2,LED_OFF);

}