#ifndef _HAL_H
#define _HAL_H

#include "stm32f10x.h"

typedef enum
{
    hal_OK = 1,
    hal_ERR,
    hal_open,
    hal_close,
    hal_on,
    hal_off,
}hal_status;

#endif

