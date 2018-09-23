/***************************************************************************** 
Copyright: CodeGeek@Hu         
File name: SPI.c         
Description: SPI文件
Author: HuJiaBin            
Version:                 
Date:                 
History:        
*****************************************************************************/ 
#ifndef _SPI_H
#define _SPI_H

#include "stm32f10x.h"
#include "io.h" 
#include "RTL.h"

//定义状态
#define SPI_OK 1
#define SPI_ERR 0

#define CS_HIGH 1
#define CS_LOW 0

//定义SPI序号
__packed typedef enum
{
    SPI_1 = 1,
    SPI_2,
}SPINum_e;

//定义SPI2控制的外设片选信号CS
__packed typedef enum
{
    W25Q64 = 1, //FLASH
    RC522, //射频
}SPI2_CS_e;

uint8_t SPIInit(uint8_t nSPINum);
uint8_t SPIWriteReadData(uint8_t nSPINum,uint8_t nTxData);
uint8_t SPI_SetSpeed(uint8_t nSPINum,u8 SPI_BaudRatePrescaler);
uint8_t SPI_CSCtrl(uint8_t nSPINum,SPI2_CS_e nCSNum,uint8_t nSta);

#endif

