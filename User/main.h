#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stdio.h"
#include "string.h"

#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "stm32f429_hal_system.h"
#include "hal_led.h"
#include "hal_uart.h"
#include "hal_spi.h"
#include "hal_i2c.h"
#include "w25qxx.h"
#include "at24cxx.h"

void Error_Handler(void);


#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

