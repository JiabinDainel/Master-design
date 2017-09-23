#include "hal_led.h"
#include "hal_clk.h"
#include "io.h"

hal_status hal_led_init(hal_led_id led_id,hal_status led_sta)
{
    FunctionalState drv_sta;
    GPIO_InitTypeDef  GPIO_InitStructure;
    
    if(hal_open == led_sta)
    {
        drv_sta = ENABLE;
    }
    else if(hal_close == led_sta)
    {
        drv_sta = DISABLE;
    }
    else
    {
        
        return hal_ERR;
    }
    
    switch(led_id)
    {
        case hal_led_1:
            //init bus clk
            hal_clk_init(hal_led_1_clk,led_sta);
            //init io pin
            if(drv_sta == ENABLE)
            {
                GPIO_InitStructure.GPIO_Pin = LED_1_PIN;				 //LED0-->PB.5 端口配置
                GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
                GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
                GPIO_Init(LED_1_PIN_INDEX, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.5
                GPIO_SetBits(LED_1_PIN_INDEX,LED_1_PIN);						     //PB.5 输出高
            }
            break;
        case hal_led_2:
            //init bus clk
            hal_clk_init(hal_led_2_clk,led_sta);
            //init io pin
            if(drv_sta == ENABLE)
            {
                GPIO_InitStructure.GPIO_Pin = LED_2_PIN;	    		 //LED1-->PE.5 端口配置, 推挽输出
                GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
                GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
                GPIO_Init(LED_2_PIN_INDEX, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
                GPIO_SetBits(LED_2_PIN_INDEX,LED_2_PIN); 	                     //PE.5 输出高 	
            }
            break;
        default:
            
            return hal_ERR;
    }
    
    return hal_OK;
}

hal_status hal_led_ctrl(hal_led_id led_id,hal_status led_sta)
{
    switch(led_id)
    {
        case hal_led_1:
            if(led_sta == hal_on)
            {
                GPIO_SetBits(LED_1_PIN_INDEX,LED_1_PIN);
            }
            else if(led_sta == hal_off)
            {
                GPIO_ResetBits(LED_1_PIN_INDEX,LED_1_PIN);
            }
            break;
        case hal_led_2:
            if(led_sta == hal_on)
            {
                GPIO_SetBits(LED_2_PIN_INDEX,LED_2_PIN);
            }
            else if(led_sta == hal_off)
            {
                GPIO_ResetBits(LED_2_PIN_INDEX,LED_2_PIN);
            }
            break;
        default:
            
            return hal_ERR;
    }
    
    return hal_OK;
}


