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

//������
static OS_MUT g_sMut_Beep_Ctrl;

/*##############################################################################################
��������: uint8_t BeepInit(void)
��������: ��������ʼ��
�䡡  ��: 
�䡡  ��: 
ȫ�ֱ���:
����ģ��:
�޶���ʷ: 
##############################################################################################*/
uint8_t BeepInit(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    //��ʼ��������
    os_mut_init (&g_sMut_Beep_Ctrl);
    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin = BEEP_PIN;  
    GPIO_Init(BEEP_PIN_INDEX, &GPIO_InitStructure); 
    
    //��ʼ���رշ�����,�͵�ƽ
    GPIO_ResetBits(BEEP_PIN_INDEX,BEEP_PIN);
    
    return BEEP_OK;
}

/*##############################################################################################
��������: uint8_t BeepCtrl(BeepData_t *pData)
��������: ����������
�䡡  ��: 
�䡡  ��: 
ȫ�ֱ���:
����ģ��:
�޶���ʷ: 
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
��������: uint8_t Beep(uint8_t nBeepType)
��������: ����������
�䡡  ��: 
�䡡  ��: 
ȫ�ֱ���:
����ģ��:
�޶���ʷ: 
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

