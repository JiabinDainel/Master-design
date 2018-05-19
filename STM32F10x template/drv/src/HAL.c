/***************************************************************************** 
Copyright: CodeGeek@Hu         
File name: BSPMiddleware.c  
Description: BSP�м��֧���ļ�
Author: HuJiaBin            
Version:                 
Date:                 
History:        
*****************************************************************************/
#include "HAL.h"

//osϵͳӦ��
static OS_MUT m_sMut_led_1;
static OS_MUT m_sMut_led_2;

/*##############################################################################################
��������: 
��������: 
�䡡  ��: 
�䡡  ��: 
ȫ�ֱ���:
����ģ��:
�޶���ʷ: 
##############################################################################################*/
unsigned int HAL_init(void)
{
    //ϵͳӦ�ó�ʼ��
    os_mut_init (&m_sMut_led_1);
    os_mut_init (&m_sMut_led_2);

    //LED������ʼ��
    //HAL_LEDInit(LED_1,);
}


/*##############################################################################################
��������: 
��������: 
�䡡  ��: 
�䡡  ��: 
ȫ�ֱ���:
����ģ��:
�޶���ʷ: 
##############################################################################################*/
unsigned int HAL_ClockInit(void)
{
    #ifdef USE_STM32F103
        RCCInit();
        return HAL_OK;
   
    #else
        return HAL_ERR;
    #endif
}

/*##############################################################################################
��������: unsigned int BSPLEDInit(unsigned int nLEDNum,unsigned char nLEDSta,void *pData)
��������: BSP��LED�Ƴ�ʼ��
�䡡  ��: 
�䡡  ��: 
ȫ�ֱ���:
����ģ��:
�޶���ʷ: 
##############################################################################################*/
unsigned int HAL_LEDInit(unsigned int nLEDNum,unsigned char nLEDSta)
{
    #ifdef USE_STM32F103
        LEDData_t sLEDData;
    
        switch(nLEDNum) 
        {
            case LED_1:
                os_mut_wait (&m_sMut_led_1, 0xffff);
                break;
            case LED_2:
                os_mut_wait (&m_sMut_led_2, 0xffff);
                break;
            default:
                break;
        }
    
        if (LEDInit(nLEDNum,nLEDSta,&sLEDData))
        {
            switch(nLEDNum) 
            {
                case LED_1:
                    os_mut_wait (&m_sMut_led_1, 0xffff);
                    break;
                case LED_2:
                    os_mut_wait (&m_sMut_led_2, 0xffff);
                    break;
                default:
                    break;
            }
            return HAL_OK;
        }
        else
        {
            switch(nLEDNum) 
            {
                case LED_1:
                    os_mut_wait (&m_sMut_led_1, 0xffff);
                    break;
                case LED_2:
                    os_mut_wait (&m_sMut_led_2, 0xffff);
                    break;
                default:
                    break;
            }
            return HAL_ERR;
        }
    #else
        return HAL_ERR;
    #endif
}

/*##############################################################################################
��������: 
��������: 
�䡡  ��: 
�䡡  ��: 
ȫ�ֱ���:
����ģ��:
�޶���ʷ: 
##############################################################################################*/
unsigned int HAL_LEDCtrl(unsigned int nLEDNum,unsigned char nLEDSta)
{
    #ifdef USE_STM32F103
        LEDData_t sLEDData;
    
        if (LEDCtrl(nLEDNum,nLEDSta,&sLEDData))
        {
            return HAL_OK;
        }
        else
        {
            return HAL_ERR;
        }
    #else
        return HAL_ERR;
    #endif
}

/*##############################################################################################
��������: 
��������: 
�䡡  ��: 
�䡡  ��: 
ȫ�ֱ���:
����ģ��:
�޶���ʷ: 
##############################################################################################*/
unsigned int HAL_UartInit(unsigned char nComNum,unsigned int nBoundRate,unsigned short nDataLength,unsigned short nStopBit,unsigned short nParity)
{
    #ifdef USE_STM32F103
        if (UARTInit(nComNum,nBoundRate,nDataLength,nStopBit,nParity))
        {
            return HAL_OK;
        }
        else
        {
            return HAL_ERR;
        }
    #else
        return HAL_ERR;
    #endif
}

/*##############################################################################################
��������: 
��������: 
�䡡  ��: 
�䡡  ��: 
ȫ�ֱ���:
����ģ��:
�޶���ʷ: 
##############################################################################################*/
unsigned int HAL_UartSendData(unsigned char nComNum,unsigned char *pSendData,unsigned int nLen)
{
    #ifdef USE_STM32F103
        UARTSendData(nComNum,pSendData,nLen);
        return HAL_OK;
    #else
        return HAL_ERR;
    #endif
}

/*##############################################################################################
��������: 
��������: 
�䡡  ��: 
�䡡  ��: 
ȫ�ֱ���:
����ģ��:
�޶���ʷ: 
##############################################################################################*/
unsigned int HAL_UartRecvData(unsigned char nComNum,unsigned char *pRecvData)
{  
    #ifdef USE_STM32F103
        unsigned int nLen = 0;
    
        nLen = UARTRecvData(nComNum,pRecvData);
        return nLen;
    #else
        return HAL_ERR;
    #endif
}



