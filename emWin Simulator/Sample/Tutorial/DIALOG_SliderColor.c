/*********************************************************************
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2015  SEGGER Microcontroller GmbH & Co. KG       *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

** emWin V5.32 - Graphical user interface for embedded applications **
emWin is protected by international copyright laws.   Knowledge of the
source code may not be used to write a similar product.  This file may
only  be used  in accordance  with  a license  and should  not be  re-
distributed in any way. We appreciate your understanding and fairness.
----------------------------------------------------------------------
File        : DIALOG_SliderColor.c
Purpose     : Example demonstrating the use of a DIALOG widget
Requirements: WindowManager - (x)
              MemoryDevices - (x)
              AntiAliasing  - ( )
              VNC-Server    - ( )
              PNG-Library   - ( )
              TrueTypeFonts - ( )
----------------------------------------------------------------------
*/

#include <stddef.h>
#include "GUI.h"
#include "DIALOG.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
//
// Recommended memory to run the sample with adequate performance
//
#define RECOMMENDED_MEMORY (1024L * 15)

/*********************************************************************
*
*       Static data, SeggerLogo
*
**********************************************************************
*/
/*********************************************************************
*
*       Bitmap SeggerLogo 
*/
static const GUI_COLOR ColorsSeggerLogoBlue16[] = {
     0x0000FF,0x000000,0x888888,0xFFFFFF
    ,0xFF0000,0xBBBBBB
};

static const GUI_LOGPALETTE PalSeggerLogoBlue16 = {
  6,	// number of entries
  1, 	// Has transparency
  &ColorsSeggerLogoBlue16[0]
};

static const unsigned char acSeggerLogoBlue16[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x01, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x10, 0x00,
  0x00, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x00,
  0x01, 0x11, 0x12, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x21, 0x11, 0x10,
  0x01, 0x11, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x11, 0x10,
  0x01, 0x12, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x11, 0x10,
  0x01, 0x12, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x21, 0x10,
  0x01, 0x12, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x21, 0x10,
  0x01, 0x12, 0x33, 0x33, 0x44, 0x44, 0x33, 0x33, 0x33, 0x33, 0x33, 0x44, 0x44, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x21, 0x10,
  0x01, 0x12, 0x33, 0x33, 0x44, 0x44, 0x33, 0x33, 0x33, 0x33, 0x33, 0x44, 0x44, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x21, 0x10,
  0x01, 0x12, 0x33, 0x33, 0x44, 0x44, 0x45, 0x33, 0x33, 0x33, 0x33, 0x44, 0x44, 0x45, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x21, 0x10,
  0x01, 0x12, 0x33, 0x33, 0x44, 0x44, 0x44, 0x33, 0x33, 0x33, 0x33, 0x44, 0x44, 0x44, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x21, 0x10,
  0x01, 0x12, 0x33, 0x33, 0x34, 0x44, 0x44, 0x43, 0x33, 0x33, 0x33, 0x34, 0x44, 0x44, 0x43, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x21, 0x10,
  0x01, 0x12, 0x33, 0x33, 0x33, 0x44, 0x44, 0x45, 0x33, 0x33, 0x33, 0x35, 0x44, 0x44, 0x45, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x21, 0x10,
  0x01, 0x12, 0x33, 0x33, 0x33, 0x54, 0x44, 0x44, 0x53, 0x33, 0x33, 0x33, 0x44, 0x44, 0x44, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x21, 0x10,
  0x01, 0x12, 0x33, 0x33, 0x33, 0x35, 0x44, 0x44, 0x43, 0x33, 0x33, 0x33, 0x34, 0x44, 0x44, 0x43, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x21, 0x10,
  0x01, 0x12, 0x33, 0x33, 0x33, 0x33, 0x44, 0x44, 0x44, 0x33, 0x33, 0x33, 0x33, 0x44, 0x44, 0x45, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x21, 0x10,
  0x01, 0x12, 0x33, 0x33, 0x33, 0x33, 0x34, 0x44, 0x44, 0x43, 0x33, 0x33, 0x33, 0x54, 0x44, 0x44, 0x53, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x21, 0x10,
  0x01, 0x12, 0x33, 0x33, 0x33, 0x33, 0x35, 0x44, 0x44, 0x45, 0x33, 0x33, 0x33, 0x34, 0x44, 0x44, 0x43, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x21, 0x10,
  0x01, 0x12, 0x33, 0x33, 0x33, 0x33, 0x33, 0x54, 0x44, 0x44, 0x33, 0x33, 0x33, 0x33, 0x44, 0x44, 0x44, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x21, 0x10,
  0x01, 0x12, 0x33, 0x33, 0x33, 0x33, 0x33, 0x34, 0x44, 0x44, 0x43, 0x33, 0x33, 0x33, 0x34, 0x44, 0x44, 0x53, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x21, 0x10,
  0x01, 0x12, 0x33, 0x34, 0x33, 0x33, 0x33, 0x33, 0x44, 0x44, 0x44, 0x33, 0x33, 0x33, 0x35, 0x44, 0x44, 0x43, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x21, 0x10,
  0x01, 0x12, 0x33, 0x34, 0x43, 0x33, 0x33, 0x33, 0x54, 0x44, 0x44, 0x53, 0x33, 0x33, 0x33, 0x44, 0x44, 0x44, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x21, 0x10,
  0x01, 0x12, 0x33, 0x34, 0x44, 0x33, 0x33, 0x33, 0x34, 0x44, 0x44, 0x43, 0x33, 0x33, 0x33, 0x34, 0x44, 0x44, 0x53, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x21, 0x10,
  0x01, 0x12, 0x33, 0x34, 0x44, 0x53, 0x33, 0x33, 0x33, 0x44, 0x44, 0x44, 0x33, 0x33, 0x33, 0x35, 0x44, 0x44, 0x45, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x21, 0x10,
  0x01, 0x12, 0x33, 0x34, 0x44, 0x43, 0x33, 0x33, 0x33, 0x34, 0x44, 0x44, 0x43, 0x33, 0x33, 0x33, 0x54, 0x44, 0x44, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x21, 0x10,
  0x01, 0x12, 0x33, 0x34, 0x44, 0x44, 0x33, 0x33, 0x33, 0x35, 0x44, 0x44, 0x45, 0x33, 0x33, 0x33, 0x34, 0x44, 0x44, 0x43, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x21, 0x10,
  0x01, 0x12, 0x33, 0x34, 0x44, 0x44, 0x43, 0x33, 0x33, 0x33, 0x54, 0x44, 0x44, 0x33, 0x33, 0x33, 0x33, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x43, 0x33, 0x33, 0x21, 0x10,
  0x01, 0x12, 0x33, 0x34, 0x44, 0x44, 0x45, 0x33, 0x33, 0x33, 0x34, 0x44, 0x44, 0x43, 0x33, 0x33, 0x33, 0x54, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x33, 0x33, 0x21, 0x10,
  0x01, 0x12, 0x33, 0x34, 0x44, 0x44, 0x44, 0x33, 0x33, 0x33, 0x33, 0x44, 0x44, 0x44, 0x33, 0x33, 0x33, 0x34, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x33, 0x33, 0x21, 0x10,
  0x01, 0x12, 0x33, 0x34, 0x44, 0x44, 0x44, 0x43, 0x33, 0x33, 0x33, 0x54, 0x44, 0x44, 0x53, 0x33, 0x33, 0x33, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x33, 0x33, 0x21, 0x10,
  0x01, 0x12, 0x33, 0x34, 0x44, 0x44, 0x44, 0x44, 0x33, 0x33, 0x33, 0x35, 0x44, 0x44, 0x45, 0x33, 0x33, 0x33, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x43, 0x33, 0x33, 0x21, 0x10,
  0x01, 0x12, 0x33, 0x34, 0x44, 0x44, 0x44, 0x44, 0x43, 0x33, 0x33, 0x33, 0x44, 0x44, 0x44, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x21, 0x10,
  0x01, 0x12, 0x33, 0x34, 0x44, 0x44, 0x44, 0x44, 0x33, 0x33, 0x33, 0x35, 0x44, 0x44, 0x45, 0x33, 0x33, 0x33, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x43, 0x33, 0x33, 0x21, 0x10,
  0x01, 0x12, 0x33, 0x34, 0x44, 0x44, 0x44, 0x43, 0x33, 0x33, 0x33, 0x54, 0x44, 0x44, 0x43, 0x33, 0x33, 0x33, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x33, 0x33, 0x21, 0x10,
  0x01, 0x12, 0x33, 0x34, 0x44, 0x44, 0x44, 0x33, 0x33, 0x33, 0x33, 0x44, 0x44, 0x44, 0x33, 0x33, 0x33, 0x34, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x33, 0x33, 0x21, 0x10,
  0x01, 0x12, 0x33, 0x34, 0x44, 0x44, 0x45, 0x33, 0x33, 0x33, 0x34, 0x44, 0x44, 0x43, 0x33, 0x33, 0x33, 0x54, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x33, 0x33, 0x21, 0x10,
  0x01, 0x12, 0x33, 0x34, 0x44, 0x44, 0x43, 0x33, 0x33, 0x33, 0x54, 0x44, 0x44, 0x33, 0x33, 0x33, 0x33, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x43, 0x33, 0x33, 0x21, 0x10,
  0x01, 0x12, 0x33, 0x34, 0x44, 0x44, 0x33, 0x33, 0x33, 0x35, 0x44, 0x44, 0x45, 0x33, 0x33, 0x33, 0x34, 0x44, 0x44, 0x43, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x21, 0x10,
  0x01, 0x12, 0x33, 0x34, 0x44, 0x43, 0x33, 0x33, 0x33, 0x34, 0x44, 0x44, 0x43, 0x33, 0x33, 0x33, 0x54, 0x44, 0x44, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x21, 0x10,
  0x01, 0x12, 0x33, 0x34, 0x44, 0x53, 0x33, 0x33, 0x33, 0x44, 0x44, 0x44, 0x33, 0x33, 0x33, 0x35, 0x44, 0x44, 0x43, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x21, 0x10,
  0x01, 0x12, 0x33, 0x34, 0x44, 0x33, 0x33, 0x33, 0x35, 0x44, 0x44, 0x43, 0x33, 0x33, 0x33, 0x34, 0x44, 0x44, 0x53, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x21, 0x10,
  0x01, 0x12, 0x33, 0x34, 0x43, 0x33, 0x33, 0x33, 0x54, 0x44, 0x44, 0x53, 0x33, 0x33, 0x33, 0x44, 0x44, 0x44, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x21, 0x10,
  0x01, 0x12, 0x33, 0x34, 0x33, 0x33, 0x33, 0x33, 0x44, 0x44, 0x44, 0x33, 0x33, 0x33, 0x35, 0x44, 0x44, 0x43, 0x33, 0x33, 0x33, 0x22, 0x11, 0x12, 0x23, 0x33, 0x33, 0x32, 0x11, 0x11, 0x11, 0x11, 0x11, 0x23, 0x33, 0x35, 0x22, 0x11, 0x12, 0x53, 0x33, 0x33, 0x33, 0x35, 0x22, 0x11, 0x12, 0x53, 0x33, 0x33, 0x33, 0x21, 0x11, 0x11, 0x11, 0x11, 0x12, 0x33, 0x21, 0x11, 0x11, 0x11, 0x12, 0x53, 0x33, 0x33, 0x33, 0x21, 0x10,
  0x01, 0x12, 0x33, 0x34, 0x33, 0x33, 0x33, 0x34, 0x44, 0x44, 0x43, 0x33, 0x33, 0x33, 0x34, 0x44, 0x44, 0x53, 0x33, 0x33, 0x31, 0x11, 0x11, 0x11, 0x11, 0x53, 0x33, 0x31, 0x11, 0x11, 0x11, 0x11, 0x11, 0x23, 0x33, 0x21, 0x11, 0x11, 0x11, 0x11, 0x33, 0x33, 0x33, 0x21, 0x11, 0x11, 0x11, 0x11, 0x33, 0x33, 0x33, 0x11, 0x11, 0x11, 0x11, 0x11, 0x12, 0x33, 0x11, 0x11, 0x11, 0x11, 0x11, 0x15, 0x33, 0x33, 0x33, 0x21, 0x10,
  0x01, 0x12, 0x33, 0x33, 0x33, 0x33, 0x33, 0x54, 0x44, 0x44, 0x33, 0x33, 0x33, 0x33, 0x44, 0x44, 0x44, 0x33, 0x33, 0x33, 0x21, 0x12, 0x33, 0x35, 0x11, 0x13, 0x33, 0x31, 0x11, 0x33, 0x33, 0x33, 0x33, 0x33, 0x32, 0x11, 0x25, 0x33, 0x52, 0x11, 0x13, 0x33, 0x32, 0x11, 0x25, 0x33, 0x52, 0x11, 0x13, 0x33, 0x33, 0x11, 0x13, 0x33, 0x33, 0x33, 0x33, 0x33, 0x11, 0x13, 0x33, 0x33, 0x21, 0x12, 0x33, 0x33, 0x33, 0x21, 0x10,
  0x01, 0x12, 0x33, 0x33, 0x33, 0x33, 0x35, 0x44, 0x44, 0x45, 0x33, 0x33, 0x33, 0x34, 0x44, 0x44, 0x43, 0x33, 0x33, 0x33, 0x11, 0x13, 0x33, 0x33, 0x51, 0x23, 0x33, 0x31, 0x11, 0x33, 0x33, 0x33, 0x33, 0x33, 0x51, 0x12, 0x33, 0x33, 0x33, 0x21, 0x23, 0x33, 0x51, 0x12, 0x33, 0x33, 0x33, 0x21, 0x23, 0x33, 0x33, 0x11, 0x13, 0x33, 0x33, 0x33, 0x33, 0x33, 0x11, 0x13, 0x33, 0x33, 0x31, 0x11, 0x33, 0x33, 0x33, 0x21, 0x10,
  0x01, 0x12, 0x33, 0x33, 0x33, 0x33, 0x34, 0x44, 0x44, 0x43, 0x33, 0x33, 0x33, 0x54, 0x44, 0x44, 0x53, 0x33, 0x33, 0x33, 0x21, 0x12, 0x53, 0x33, 0x33, 0x33, 0x33, 0x31, 0x11, 0x33, 0x33, 0x33, 0x33, 0x33, 0x21, 0x15, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x21, 0x15, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x11, 0x13, 0x33, 0x33, 0x33, 0x33, 0x33, 0x11, 0x13, 0x33, 0x33, 0x31, 0x11, 0x33, 0x33, 0x33, 0x21, 0x10,
  0x01, 0x12, 0x33, 0x33, 0x33, 0x33, 0x44, 0x44, 0x44, 0x33, 0x33, 0x33, 0x33, 0x44, 0x44, 0x45, 0x33, 0x33, 0x33, 0x33, 0x31, 0x11, 0x11, 0x12, 0x23, 0x33, 0x33, 0x31, 0x11, 0x11, 0x11, 0x11, 0x12, 0x33, 0x11, 0x13, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x11, 0x13, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x11, 0x11, 0x11, 0x11, 0x11, 0x23, 0x33, 0x11, 0x13, 0x33, 0x33, 0x21, 0x12, 0x33, 0x33, 0x33, 0x21, 0x10,
  0x01, 0x12, 0x33, 0x33, 0x33, 0x35, 0x44, 0x44, 0x43, 0x33, 0x33, 0x33, 0x34, 0x44, 0x44, 0x43, 0x33, 0x33, 0x33, 0x33, 0x33, 0x52, 0x21, 0x11, 0x11, 0x23, 0x33, 0x31, 0x11, 0x11, 0x11, 0x11, 0x12, 0x33, 0x11, 0x13, 0x33, 0x32, 0x11, 0x11, 0x12, 0x33, 0x11, 0x13, 0x33, 0x32, 0x11, 0x11, 0x12, 0x33, 0x33, 0x11, 0x11, 0x11, 0x11, 0x11, 0x23, 0x33, 0x11, 0x11, 0x11, 0x11, 0x11, 0x23, 0x33, 0x33, 0x33, 0x21, 0x10,
  0x01, 0x12, 0x33, 0x33, 0x33, 0x54, 0x44, 0x44, 0x53, 0x33, 0x33, 0x33, 0x54, 0x44, 0x44, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x52, 0x11, 0x12, 0x33, 0x31, 0x11, 0x33, 0x33, 0x33, 0x33, 0x33, 0x11, 0x13, 0x33, 0x32, 0x11, 0x11, 0x11, 0x33, 0x11, 0x13, 0x33, 0x32, 0x11, 0x11, 0x11, 0x33, 0x33, 0x11, 0x13, 0x33, 0x33, 0x33, 0x33, 0x33, 0x11, 0x11, 0x11, 0x11, 0x11, 0x23, 0x33, 0x33, 0x33, 0x21, 0x10,
  0x01, 0x12, 0x33, 0x33, 0x33, 0x44, 0x44, 0x45, 0x33, 0x33, 0x33, 0x35, 0x44, 0x44, 0x45, 0x33, 0x33, 0x33, 0x33, 0x33, 0x21, 0x53, 0x33, 0x33, 0x51, 0x11, 0x33, 0x31, 0x11, 0x33, 0x33, 0x33, 0x33, 0x33, 0x21, 0x15, 0x33, 0x33, 0x33, 0x31, 0x11, 0x33, 0x21, 0x15, 0x33, 0x33, 0x33, 0x31, 0x11, 0x33, 0x33, 0x11, 0x13, 0x33, 0x33, 0x33, 0x33, 0x33, 0x11, 0x13, 0x33, 0x33, 0x21, 0x12, 0x33, 0x33, 0x33, 0x21, 0x10,
  0x01, 0x12, 0x33, 0x33, 0x34, 0x44, 0x44, 0x43, 0x33, 0x33, 0x33, 0x34, 0x44, 0x44, 0x43, 0x33, 0x33, 0x33, 0x33, 0x33, 0x11, 0x13, 0x33, 0x33, 0x31, 0x11, 0x33, 0x31, 0x11, 0x33, 0x33, 0x33, 0x33, 0x33, 0x51, 0x12, 0x33, 0x33, 0x33, 0x21, 0x11, 0x33, 0x51, 0x12, 0x33, 0x33, 0x33, 0x21, 0x11, 0x33, 0x33, 0x11, 0x13, 0x33, 0x33, 0x33, 0x33, 0x33, 0x11, 0x13, 0x33, 0x33, 0x31, 0x11, 0x33, 0x33, 0x33, 0x21, 0x10,
  0x01, 0x12, 0x33, 0x33, 0x44, 0x44, 0x44, 0x33, 0x33, 0x33, 0x33, 0x44, 0x44, 0x44, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x21, 0x11, 0x53, 0x33, 0x21, 0x12, 0x33, 0x31, 0x11, 0x33, 0x33, 0x33, 0x33, 0x33, 0x32, 0x11, 0x25, 0x33, 0x32, 0x11, 0x11, 0x33, 0x32, 0x11, 0x25, 0x33, 0x32, 0x11, 0x11, 0x33, 0x33, 0x11, 0x13, 0x33, 0x33, 0x33, 0x33, 0x33, 0x11, 0x13, 0x33, 0x33, 0x31, 0x11, 0x33, 0x33, 0x33, 0x21, 0x10,
  0x01, 0x12, 0x33, 0x33, 0x44, 0x44, 0x45, 0x33, 0x33, 0x33, 0x33, 0x44, 0x44, 0x45, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x32, 0x11, 0x11, 0x11, 0x11, 0x23, 0x33, 0x31, 0x11, 0x11, 0x11, 0x11, 0x11, 0x23, 0x33, 0x21, 0x11, 0x11, 0x11, 0x12, 0x11, 0x33, 0x33, 0x21, 0x11, 0x11, 0x11, 0x12, 0x11, 0x33, 0x33, 0x11, 0x11, 0x11, 0x11, 0x11, 0x12, 0x33, 0x11, 0x13, 0x33, 0x33, 0x32, 0x11, 0x33, 0x33, 0x33, 0x21, 0x10,
  0x01, 0x12, 0x33, 0x33, 0x44, 0x44, 0x53, 0x33, 0x33, 0x33, 0x33, 0x44, 0x44, 0x53, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x52, 0x21, 0x11, 0x25, 0x33, 0x33, 0x32, 0x11, 0x11, 0x11, 0x11, 0x11, 0x23, 0x33, 0x35, 0x22, 0x11, 0x22, 0x35, 0x12, 0x33, 0x33, 0x35, 0x22, 0x11, 0x22, 0x35, 0x12, 0x33, 0x33, 0x21, 0x11, 0x11, 0x11, 0x11, 0x12, 0x33, 0x21, 0x23, 0x33, 0x33, 0x35, 0x12, 0x33, 0x33, 0x33, 0x21, 0x10,
  0x01, 0x12, 0x33, 0x33, 0x44, 0x44, 0x33, 0x33, 0x33, 0x33, 0x33, 0x44, 0x44, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x21, 0x10,
  0x01, 0x12, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x21, 0x10,
  0x01, 0x12, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x21, 0x10,
  0x01, 0x12, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x11, 0x10,
  0x01, 0x11, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x35, 0x11, 0x10,
  0x01, 0x11, 0x12, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x21, 0x11, 0x10,
  0x01, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x00,
  0x00, 0x01, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x10, 0x00,
  0x00, 0x00, 0x01, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x10, 0x00, 0x00
};

static const GUI_BITMAP bmSeggerLogoBlue = {
 138,                  // XSize
  65,                  // YSize
  69,                  // BytesPerLine
   4,                  // BitsPerPixel
 acSeggerLogoBlue16,   // Pointer to picture data (indices)
 &PalSeggerLogoBlue16  // Pointer to palette
};

/*********************************************************************
*
*       Static data, dialog resource
*
**********************************************************************
*/
/*********************************************************************
*
*       Dialog resource
*
* Function description
*   This table conatins the info required to create the dialog.
*   It has been created manually, but could also be created by a GUI-builder.
*/
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { FRAMEWIN_CreateIndirect, "Adjust color", 0,         10,  40, 300, 160, FRAMEWIN_CF_MOVEABLE},
  { TEXT_CreateIndirect,     "Red:" ,  0,                5,  20,  35,  20, TEXT_CF_LEFT },
  { TEXT_CreateIndirect,     "Green:", 0,                5,  50,  35,  20, TEXT_CF_LEFT },
  { TEXT_CreateIndirect,     "Blue:",  0,                5,  80,  35,  20, TEXT_CF_LEFT },
  { TEXT_CreateIndirect,     "Preview",0,              205,   4,  81,  15, TEXT_CF_HCENTER },
  { SLIDER_CreateIndirect,   NULL,     GUI_ID_SLIDER0,  40,  20, 100,  20 },
  { SLIDER_CreateIndirect,   NULL,     GUI_ID_SLIDER1,  40,  50, 100,  20 },
  { SLIDER_CreateIndirect,   NULL,     GUI_ID_SLIDER2,  40,  80, 100,  20 },
  { EDIT_CreateIndirect,     NULL,     GUI_ID_EDIT0,   145,  20,  30,  20, 0, 3 },
  { EDIT_CreateIndirect,     NULL,     GUI_ID_EDIT1,   145,  50,  30,  20, 0, 3 },
  { EDIT_CreateIndirect,     NULL,     GUI_ID_EDIT2,   145,  80,  30,  20, 0, 3 },
  { BUTTON_CreateIndirect,   "OK",     GUI_ID_OK,       10, 110,  60,  20 },
  { BUTTON_CreateIndirect,   "Cancel", GUI_ID_CANCEL,  230, 110,  60,  20 },
};

/*********************************************************************
*
*       Static data, colors
*
**********************************************************************
*/
static U8 _aColorSep[3] = {0, 127, 255};  // Red, green and blue components

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _OnPaint
*
* Function description
*   This routine draws the color rectangles.
*   The widgets are drawn automatically.
*/
static void _OnPaint(void) {
  //
  // Draw RGB values
  //
  GUI_SetColor(_aColorSep[0]);
  GUI_FillRect(180, 20, 199, 39);
  GUI_SetColor(_aColorSep[1] << 8);
  GUI_FillRect(180, 50, 199, 69);
  GUI_SetColor(((U32)_aColorSep[2]) << 16);
  GUI_FillRect(180, 80, 199, 99);
  //
  // Draw resulting color
  //
  GUI_SetColor(_aColorSep[0] | (((U32)_aColorSep[1]) << 8) | (((U32)_aColorSep[2]) << 16));
  GUI_FillRect(205, 20, 285, 99);
}

/*********************************************************************
*
*       _OnValueChanged
*/
static void _OnValueChanged(WM_HWIN hDlg, int Id) {
  unsigned Index;
  unsigned v;
  WM_HWIN  hSlider;
  WM_HWIN  hEdit;

  Index = 0;
  v     = 0;
  if ((Id >= GUI_ID_SLIDER0) && (Id <= GUI_ID_SLIDER2)) {
    Index = Id - GUI_ID_SLIDER0;
    //
    // SLIDER-widget has changed, update EDIT-widget
    //
    hSlider = WM_GetDialogItem(hDlg, GUI_ID_SLIDER0 + Index);
    hEdit   = WM_GetDialogItem(hDlg, GUI_ID_EDIT0 + Index);
    v = SLIDER_GetValue(hSlider);
    EDIT_SetValue(hEdit, v);
  } else if ((Id >= GUI_ID_EDIT0) && (Id <= GUI_ID_EDIT2)) {
    Index = Id - GUI_ID_EDIT0;
    //
    // If EDIT-widget has changed, update SLIDER-widget
    //
    hSlider = WM_GetDialogItem(hDlg, GUI_ID_SLIDER0 + Index);
    hEdit   = WM_GetDialogItem(hDlg, GUI_ID_EDIT0 + Index);
    v = EDIT_GetValue(hEdit);
    SLIDER_SetValue(hSlider, v);
  }
  _aColorSep[Index] = v;
  //
  // At last invalidate dialog client window
  //
  WM_InvalidateWindow(WM_GetClientWindow(hDlg));
}

/*********************************************************************
*
*       _cbBkWindow
*/
static void _cbBkWindow(WM_MESSAGE * pMsg) {
  int xPos;
  int yPos;

  xPos = LCD_GetXSize() / 2 - bmSeggerLogoBlue.XSize/2;
  yPos = LCD_GetYSize() / 2 - bmSeggerLogoBlue.YSize/2 ;
  switch (pMsg->MsgId) {
  case WM_PAINT:
    GUI_SetBkColor(GUI_BLUE);
    GUI_Clear();
    GUI_SetColor(GUI_WHITE);
    GUI_SetFont(&GUI_Font24_ASCII);
    GUI_DispStringHCenterAt("DIALOG_SliderColor - Sample", 160, 5);
    GUI_DrawBitmap(&bmSeggerLogoBlue, xPos, yPos );
  default:
    WM_DefaultProc(pMsg);
  }
}

/*********************************************************************
*
*       _cbCallback
*/
static void _cbCallback(WM_MESSAGE * pMsg) {
  WM_HWIN hDlg;
  WM_HWIN hItem;
  int     i;
  int     NCode;
  int     Id;

  hDlg = pMsg->hWin;
  switch (pMsg->MsgId) {
    case WM_PAINT:
      _OnPaint();
      return;
    case WM_INIT_DIALOG:
      for (i = 0; i < 3; i++) {
        hItem = WM_GetDialogItem(hDlg, GUI_ID_SLIDER0 + i);
        SLIDER_SetRange(hItem, 0, 255);
        SLIDER_SetValue(hItem, _aColorSep[i]);
        //
        // Init EDIT-widgets
        //
        hItem = WM_GetDialogItem(hDlg, GUI_ID_EDIT0 + i);
        EDIT_SetDecMode(hItem, _aColorSep[i],   0, 255, 0, 0);
      }
      break;
    case WM_KEY:
      switch (((WM_KEY_INFO*)(pMsg->Data.p))->Key) {
        case GUI_KEY_ESCAPE:
          ;
          break;
        case GUI_KEY_ENTER:
          GUI_EndDialog(hDlg, 0);
          break;
      }
      break;
    case WM_NOTIFY_PARENT:
      Id    = WM_GetId(pMsg->hWinSrc);      // Id of widget
      NCode = pMsg->Data.v;                 // Notification code
      switch (NCode) {
        case WM_NOTIFICATION_RELEASED:      // React only if released
          if (Id == GUI_ID_OK) {            // OK Button
            GUI_EndDialog(hDlg, 0);
          }
          if (Id == GUI_ID_CANCEL) {        // Cancel Button
            GUI_EndDialog(hDlg, 1);
          }
          break;
        case WM_NOTIFICATION_VALUE_CHANGED: // Value has changed
          _OnValueChanged(hDlg, Id);
          break;
      }
      break;
    default:
      WM_DefaultProc(pMsg);
  }
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       MainTask
*/
void MainTask(void) {
  WM_SetCreateFlags(WM_CF_MEMDEV);  // Use memory devices on all windows to avoid flicker
  GUI_Init();
  //
  // Check if recommended memory for the sample is available
  //
  if (GUI_ALLOC_GetNumFreeBytes() < RECOMMENDED_MEMORY) {
    GUI_ErrorOut("Not enough memory available."); 
    return;
  }
  GUI_CURSOR_Show();
  WM_SetCallback(WM_HBKWIN, _cbBkWindow);  
  while (1) {
    GUI_ExecDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), &_cbCallback, 0, 0, 0);
    GUI_Delay(1000);
  }
}

/*************************** End of file ****************************/

