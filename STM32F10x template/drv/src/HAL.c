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
#ifdef USE_RTX_RTOS
    static OS_MUT m_sMut_led_1;
    static OS_MUT m_sMut_led_2;
#endif

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
    //BUS clk��ʼ��
    HAL_ClockInit();

    //LED������ʼ��
    HAL_LEDInit(LED_1,LED_OFF);
    HAL_LEDInit(LED_2,LED_OFF);
    
    //UART������ʼ��
    HAL_UartInit(UART_1,9600,USART_WordLength_8b,USART_StopBits_1,USART_Parity_No);
    return HAL_OK;
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

        //ϵͳӦ�ó�ʼ��
        os_mut_init (&m_sMut_led_1);
        os_mut_init (&m_sMut_led_2);
    
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
                    os_mut_release (&m_sMut_led_1);
                    break;
                case LED_2:
                    os_mut_release (&m_sMut_led_2);
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
                    os_mut_release (&m_sMut_led_1);
                    break;
                case LED_2:
                    os_mut_release (&m_sMut_led_2);
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
    
        if (LEDCtrl(nLEDNum,nLEDSta,&sLEDData))
        {
            switch(nLEDNum) 
            {
                case LED_1:
                    os_mut_release (&m_sMut_led_1);
                    break;
                case LED_2:
                    os_mut_release (&m_sMut_led_2);
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
                    os_mut_release (&m_sMut_led_1);
                    break;
                case LED_2:
                    os_mut_release (&m_sMut_led_2);
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
        UARTSendDataBlocking(nComNum,pSendData,nLen);
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




