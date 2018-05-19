/***************************************************************************** 
Copyright: CodeGeek@Hu         
File name: SPI.c         
Description: SPI�ļ�
Author: HuJiaBin            
Version:                 
Date:                 
History:        
*****************************************************************************/ 
#include "SPI.h"

//SPI2���߿�����
static OS_MUT g_sMut_Ctrl_SPI2; //SPI2

/*##############################################################################################
��������: uint8_t SPIInit(uint8_t nSPINum)
��������: SPI��ʼ��
�䡡  ��: 
�䡡  ��: 
ȫ�ֱ���:
����ģ��:
�޶���ʷ: 
##############################################################################################*/
uint8_t SPIInit(uint8_t nSPINum)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    SPI_InitTypeDef  SPI_InitStructure;

    static uint8_t nSPI2InitFlg = 0; //SPI��ʼ����־
    
    switch(nSPINum)
    {
        case SPI_2:
            if(nSPI2InitFlg == 1)
            {
                return SPI_OK;
            }
            //��ʼ��������
            os_mut_init (&g_sMut_Ctrl_SPI2);
            GPIO_InitStructure.GPIO_Pin = SPI2_MOSI_PIN | SPI2_MISO_PIN | SPI2_SCK_PIN;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //PB13/14/15����������� 
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_Init(SPI2_MOSI_PIN_INDEX, &GPIO_InitStructure);//��ʼ��GPIOB
            GPIO_SetBits(SPI2_MOSI_PIN_INDEX,SPI2_MOSI_PIN | SPI2_MISO_PIN | SPI2_SCK_PIN);  //PB13/14/15����

            SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //����SPI�������˫�������ģʽ:SPI����Ϊ˫��˫��ȫ˫��
            SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		//����SPI����ģʽ:����Ϊ��SPI
            SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		//����SPI�����ݴ�С:SPI���ͽ���8λ֡�ṹ
            SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;		//����ͬ��ʱ�ӵĿ���״̬Ϊ�ߵ�ƽ
            SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;	//����ͬ��ʱ�ӵĵڶ��������أ��������½������ݱ�����
            SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		//NSS�ź���Ӳ����NSS�ܽţ����������ʹ��SSIλ������:�ڲ�NSS�ź���SSIλ����
            SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;		//���岨����Ԥ��Ƶ��ֵ:������Ԥ��ƵֵΪ256
            SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	//ָ�����ݴ����MSBλ����LSBλ��ʼ:���ݴ����MSBλ��ʼ
            SPI_InitStructure.SPI_CRCPolynomial = 7;	//CRCֵ����Ķ���ʽ
            SPI_Init(SPI2, &SPI_InitStructure);  //����SPI_InitStruct��ָ���Ĳ�����ʼ������SPIx�Ĵ���
 
            SPI_Cmd(SPI2, ENABLE); //ʹ��SPI����
            nSPI2InitFlg = 1; //���ó�ʼ����ϱ�־
            return SPI_OK;
        default:
            break;
    }
    return SPI_ERR;
}

/*##############################################################################################
��������: uint8_t SPIWriteReadData(uint8_t nSPINum,uint8_t nTxData)
��������: SPI��д����
�䡡  ��: 
�䡡  ��: 
ȫ�ֱ���:
����ģ��:
�޶���ʷ: 
##############################################################################################*/
uint8_t SPIWriteReadData(uint8_t nSPINum,uint8_t nTxData)
{
    u8 retry=0;
    uint8_t nRxData = 0;	
    
    switch(nSPINum)
    {
        case SPI_2:
            os_mut_wait (&g_sMut_Ctrl_SPI2, 0xffff);
        
            while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET) //���ָ����SPI��־λ�������:���ͻ���ձ�־λ
            {
                retry++;
                if(retry>200)return SPI_ERR;
            }			  
            SPI_I2S_SendData(SPI2, nTxData); //ͨ������SPIx����һ������
            retry=0;
            while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET) //���ָ����SPI��־λ�������:���ܻ���ǿձ�־λ
            {
                retry++;
                if(retry>200)return SPI_ERR;
            }	
          
            nRxData = SPI_I2S_ReceiveData(SPI2);
            
            os_mut_release (&g_sMut_Ctrl_SPI2);
            
            return  nRxData; //����ͨ��SPIx������յ�����
        default:
            break;
    }
    return SPI_ERR;
}

/*##############################################################################################
��������: 
��������: SPIƬѡ�źſ���
�䡡  ��: 
�䡡  ��: 
ȫ�ֱ���:
����ģ��:
�޶���ʷ: 
##############################################################################################*/
uint8_t SPI_CSCtrl(uint8_t nSPINum,uint8_t nCSNum,uint8_t nSta)
{
    switch(nSPINum)
    {
        case SPI_2:
            switch(nCSNum)
            {
                case W25Q16: //FLASH����
                    //����FLASH����������
                    if(nSta == CS_HIGH)
                    {
                        GPIO_SetBits(W25Q16_CS_PIN_INDEX,W25Q16_CS_PIN);
                        GPIO_SetBits(RC522_CS_PIN_INDEX,RC522_CS_PIN);
                    }
                    else
                    {
                        GPIO_ResetBits(W25Q16_CS_PIN_INDEX,W25Q16_CS_PIN);
                        GPIO_SetBits(RC522_CS_PIN_INDEX,RC522_CS_PIN);
                    }                  
                    return SPI_OK;
                case RC522: //��Ƶ����
                    //������Ƶ����������
                    if(nSta == CS_HIGH)
                    {
                        GPIO_SetBits(RC522_CS_PIN_INDEX,RC522_CS_PIN);
                        GPIO_SetBits(W25Q16_CS_PIN_INDEX,W25Q16_CS_PIN);
                    }
                    else
                    {
                        GPIO_ResetBits(RC522_CS_PIN_INDEX,RC522_CS_PIN);
                        GPIO_SetBits(W25Q16_CS_PIN_INDEX,W25Q16_CS_PIN);
                    }
                   
                    return SPI_OK;  
                default:
                    break;
            }
            return SPI_ERR;
        default:
            break;  
    }
    
    return SPI_ERR;
}






