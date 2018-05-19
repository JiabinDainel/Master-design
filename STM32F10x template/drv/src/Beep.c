/***************************************************************************** 
Copyright: CodeGeek@Hu         
File name:     
Description: 
Author: HuJiaBin            
Version:                 
Date:                 
History:        
*****************************************************************************/ 
#include "Beep.h"

//控制锁
static OS_MUT g_sMut_Beep_Ctrl;

/*##############################################################################################
函数名称: uint8_t BeepInit(void)
功能描述: 蜂鸣器初始化
输　  入: 
输　  出: 
全局变量:
调用模块:
修订历史: 
##############################################################################################*/
uint8_t BeepInit(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    //初始化控制锁
    os_mut_init (&g_sMut_Beep_Ctrl);
    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin = BEEP_PIN;  
    GPIO_Init(BEEP_PIN_INDEX, &GPIO_InitStructure); 
    
    //初始化关闭蜂鸣器,低电平
    GPIO_ResetBits(BEEP_PIN_INDEX,BEEP_PIN);
    
    return BEEP_OK;
}

/*##############################################################################################
函数名称: uint8_t BeepCtrl(BeepData_t *pData)
功能描述: 蜂鸣器控制
输　  入: 
输　  出: 
全局变量:
调用模块:
修订历史: 
##############################################################################################*/
uint8_t BeepCtrl(BeepData_t *pData)
{
    if(!pData)
    {
        return BEEP_ERR;
    }
    
    os_mut_wait (&g_sMut_Beep_Ctrl, 0xffff);
    
    if(pData->nBeepSta == BEEP_ON)
    {
         GPIO_SetBits(BEEP_PIN_INDEX,BEEP_PIN);
    }
    else if(pData->nBeepSta == BEEP_OFF)
    {
         GPIO_ResetBits(BEEP_PIN_INDEX,BEEP_PIN);
    }
    else
    {
        os_mut_release (&g_sMut_Beep_Ctrl);
        return BEEP_ERR;
    }
    
    os_mut_release (&g_sMut_Beep_Ctrl);
    
    return BEEP_OK;
}

/*##############################################################################################
函数名称: uint8_t Beep(uint8_t nBeepType)
功能描述: 蜂鸣器发声
输　  入: 
输　  出: 
全局变量:
调用模块:
修订历史: 
##############################################################################################*/
uint8_t Beep(uint8_t nBeepType)
{
    switch(nBeepType)
    {
        case BEEP_TYPE_1:
        
            os_mut_wait (&g_sMut_Beep_Ctrl, 0xffff);
        
            GPIO_ResetBits(BEEP_PIN_INDEX,BEEP_PIN);
            GPIO_SetBits(BEEP_PIN_INDEX,BEEP_PIN);
            os_dly_wait(20);
            GPIO_ResetBits(BEEP_PIN_INDEX,BEEP_PIN);
        
            os_mut_release (&g_sMut_Beep_Ctrl);
        
            return BEEP_OK;
        default:
            break;
    }
    return BEEP_ERR;
}

