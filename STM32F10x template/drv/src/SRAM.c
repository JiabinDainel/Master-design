/***************************************************************************** 
Copyright: CodeGeek@Hu         
File name: SRAM.c  
Description: 
Author: HuJiaBin            
Version:                 
Date:                 
History:        
*****************************************************************************/ 
#include "HAL.h"

#ifdef USE_STM32F103

#include "SRAM.h"

/*##############################################################################################
函数名称: 
功能描述: 
输　  入: 
输　  出: 
全局变量:
调用模块:
修订历史: 
##############################################################################################*/
void FSMC_SRAM_Init(void)
{    
    FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
    FSMC_NORSRAMTimingInitTypeDef  readWriteTiming;
    GPIO_InitTypeDef  GPIO_InitStructure;
 
    GPIO_InitStructure.GPIO_Pin = 0xFF33;                  //PORTD?????? 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;          //??????
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

 
    GPIO_InitStructure.GPIO_Pin = 0xFF83;                  //PORTE?????? 
    GPIO_Init(GPIOE, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = 0xF03F;                  //PORTD?????? 
    GPIO_Init(GPIOF, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = 0x043F;                  //PORTD?????? 
    GPIO_Init(GPIOG, &GPIO_InitStructure);
 
                         
     readWriteTiming.FSMC_AddressSetupTime = 0x00;     //??????(ADDSET)?1?HCLK 1/36M=27ns
    readWriteTiming.FSMC_AddressHoldTime = 0x00;     //??????(ADDHLD)??A???    
    readWriteTiming.FSMC_DataSetupTime = 0x03;         //??????(DATAST)?3?HCLK 4/72M=55ns(?EM?SRAM??)     
    readWriteTiming.FSMC_BusTurnAroundDuration = 0x00;
    readWriteTiming.FSMC_CLKDivision = 0x00;
    readWriteTiming.FSMC_DataLatency = 0x00;
    readWriteTiming.FSMC_AccessMode = FSMC_AccessMode_A;     //??A 
    

 
    FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM3;//  ??????NE3 ,????BTCR[4],[5]?
    FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable; 
    FSMC_NORSRAMInitStructure.FSMC_MemoryType =FSMC_MemoryType_SRAM;// FSMC_MemoryType_SRAM;  //SRAM   
    FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;//????????16bit  
    FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode =FSMC_BurstAccessMode_Disable;// FSMC_BurstAccessMode_Disable; 
    FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
    FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait=FSMC_AsynchronousWait_Disable;
    FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;   
    FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;  
    FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;    //?????? 
    FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;  
    FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable; // ?????????
    FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;  
    FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &readWriteTiming;
    FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &readWriteTiming; //??????

    FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);  //???FSMC??

    FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM3, ENABLE);  // ??BANK3                                          
                                            
}
#endif