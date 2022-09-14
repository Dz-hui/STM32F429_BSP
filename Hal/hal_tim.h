#ifndef __HAL_LED_H
#define __HAL_LED_H

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"


#define BASIC_TIM_PORT           		TIM6
#define BASIC_TIM_CLK_ENABLE()     	    __TIM6_CLK_ENABLE()

#define BASIC_TIM_IRQn				    TIM6_DAC_IRQn
#define BASIC_TIM_IRQHandler    	    TIM6_DAC_IRQHandler

void hal_basetim_init(void);

#ifdef __cplusplus
}
#endif
#endif /*__HAL_LED_H */
