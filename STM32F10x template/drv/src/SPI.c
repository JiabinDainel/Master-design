/***************************************************************************** 
Copyright: CodeGeek@Hu         
File name: SPI.c         
Description: SPI文件
Author: HuJiaBin            
Version:                 
Date:                 
History:        
*****************************************************************************/ 
#include "SPI.h"

//SPI2总线控制锁
static OS_MUT g_sMut_Ctrl_SPI2; //SPI2

/*##############################################################################################
函数名称: uint8_t SPIInit(uint8_t nSPINum)
功能描述: SPI初始化
输　  入: 
输　  出: 
全局变量:
调用模块:
修订历史: 
##############################################################################################*/
uint8_t SPIInit(uint8_t nSPINum)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    SPI_InitTypeDef  SPI_InitStructure;

    static uint8_t nSPI2InitFlg = 0; //SPI初始化标志
    
    switch(nSPINum)
    {
        case SPI_2:
            if(nSPI2InitFlg == 1)
            {
                return SPI_OK;
            }
            //初始化控制锁
            os_mut_init (&g_sMut_Ctrl_SPI2);
            GPIO_InitStructure.GPIO_Pin = SPI2_MOSI_PIN | SPI2_MISO_PIN | SPI2_SCK_PIN;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //PB13/14/15复用推挽输出 
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_Init(SPI2_MOSI_PIN_INDEX, &GPIO_InitStructure);//初始化GPIOB
            GPIO_SetBits(SPI2_MOSI_PIN_INDEX,SPI2_MOSI_PIN | SPI2_MISO_PIN | SPI2_SCK_PIN);  //PB13/14/15上拉

            SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //设置SPI单向或者双向的数据模式:SPI设置为双线双向全双工
            SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		//设置SPI工作模式:设置为主SPI
            SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		//设置SPI的数据大小:SPI发送接收8位帧结构
            SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;		//串行同步时钟的空闲状态为高电平
            SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;	//串行同步时钟的第二个跳变沿（上升或下降）数据被采样
            SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		//NSS信号由硬件（NSS管脚）还是软件（使用SSI位）管理:内部NSS信号有SSI位控制
            SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;		//定义波特率预分频的值:波特率预分频值为256
            SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	//指定数据传输从MSB位还是LSB位开始:数据传输从MSB位开始
            SPI_InitStructure.SPI_CRCPolynomial = 7;	//CRC值计算的多项式
            SPI_Init(SPI2, &SPI_InitStructure);  //根据SPI_InitStruct中指定的参数初始化外设SPIx寄存器
 
            SPI_Cmd(SPI2, ENABLE); //使能SPI外设
            nSPI2InitFlg = 1; //设置初始化完毕标志
            return SPI_OK;
        default:
            break;
    }
    return SPI_ERR;
}

/*##############################################################################################
函数名称: uint8_t SPIWriteReadData(uint8_t nSPINum,uint8_t nTxData)
功能描述: SPI读写数据
输　  入: 
输　  出: 
全局变量:
调用模块:
修订历史: 
##############################################################################################*/
uint8_t SPIWriteReadData(uint8_t nSPINum,uint8_t nTxData)
{
    u8 retry=0;
    uint8_t nRxData = 0;	
    
    switch(nSPINum)
    {
        case SPI_2:
            os_mut_wait (&g_sMut_Ctrl_SPI2, 0xffff);
        
            while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET) //检查指定的SPI标志位设置与否:发送缓存空标志位
            {
                retry++;
                if(retry>200)return SPI_ERR;
            }			  
            SPI_I2S_SendData(SPI2, nTxData); //通过外设SPIx发送一个数据
            retry=0;
            while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET) //检查指定的SPI标志位设置与否:接受缓存非空标志位
            {
                retry++;
                if(retry>200)return SPI_ERR;
            }	
          
            nRxData = SPI_I2S_ReceiveData(SPI2);
            
            os_mut_release (&g_sMut_Ctrl_SPI2);
            
            return  nRxData; //返回通过SPIx最近接收的数据
        default:
            break;
    }
    return SPI_ERR;
}

/*##############################################################################################
函数名称: 
功能描述: SPI片选信号控制
输　  入: 
输　  出: 
全局变量:
调用模块:
修订历史: 
##############################################################################################*/
uint8_t SPI_CSCtrl(uint8_t nSPINum,uint8_t nCSNum,uint8_t nSta)
{
    switch(nSPINum)
    {
        case SPI_2:
            switch(nCSNum)
            {
                case W25Q16: //FLASH控制
                    //拉低FLASH，其他拉高
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
                case RC522: //射频控制
                    //拉低射频，其他拉高
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






