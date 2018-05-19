/***************************************************************************** 
Copyright: CodeGeek@Hu         
File name: io.h 
Description: 
Author: HuJiaBin            
Version:                 
Date:                 
History:        
*****************************************************************************/ 
#ifndef _IO_H
#define _IO_H

#include "stm32f10x.h"

//串口IO配置
#define UART1_TX_PIN_INDEX  (GPIOA)
#define UART1_RX_PIN_INDEX  GPIOA

#define UART1_TX_PIN GPIO_Pin_9 //UART1 发送IO
#define UART1_RX_PIN GPIO_Pin_10 //UART1 接收IO

//LED IO配置
#define LED1_PIN_INDEX GPIOB
#define LED2_PIN_INDEX GPIOE

#define LED1_PIN GPIO_Pin_5 
#define LED2_PIN GPIO_Pin_5 

//SPI1配置
#define SPI1_MOSI_PIN_INDEX 
#define SPI1_MOSI_PIN 

#define SPI1_MISO_PIN_INDEX 
#define SPI1_MISO_PIN 

#define SPI1_SCK_PIN_INDEX
#define SPI1_SCK_PIN

//SPI2配置
#define SPI2_MOSI_PIN_INDEX GPIOB
#define SPI2_MOSI_PIN GPIO_Pin_15

#define SPI2_MISO_PIN_INDEX GPIOB
#define SPI2_MISO_PIN GPIO_Pin_14

#define SPI2_SCK_PIN_INDEX GPIOB
#define SPI2_SCK_PIN GPIO_Pin_13

//SPI2片选信号控制的外设
#define W25Q16_CS_PIN_INDEX GPIOB
#define W25Q16_CS_PIN GPIO_Pin_12

#define RC522_CS_PIN_INDEX GPIOB
#define RC522_CS_PIN GPIO_Pin_10

//RC522 RST
#define RC522_RST_PIN_INDEX GPIOB
#define RC522_RST_PIN GPIO_Pin_11

//蜂鸣器
#define BEEP_PIN_INDEX GPIOB
#define BEEP_PIN GPIO_Pin_8

#endif







