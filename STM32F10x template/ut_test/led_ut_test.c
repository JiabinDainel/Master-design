#include "hal.h"
#include "RTL.h"

/*##############################################################################################
��������: 
��������: LED���������ȷ�ĳ�ʼ����init����led������3s��initϨ��led
�䡡  ��: 
�䡡  ��: 
ȫ�ֱ���:
����ģ��:
�޶���ʷ: 
##############################################################################################*/
void led_test(void)
{
    //BUS clk��ʼ��
    HAL_ClockInit();

    //LED������ʼ��
    HAL_LEDInit(LED_1,LED_ON);
    HAL_LEDInit(LED_2,LED_ON);

    //delay 3s
    os_dly_wait (300);

    //LED������ʼ��
    HAL_LEDInit(LED_1,LED_OFF);
    HAL_LEDInit(LED_2,LED_OFF);

}