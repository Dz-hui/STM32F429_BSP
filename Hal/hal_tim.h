#ifndef __HAL_TIM_H
#define __HAL_TIM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"


#define BASIC_TIM_PORT           		    TIM6
#define BASIC_TIM_CLK_ENABLE()     	        __TIM6_CLK_ENABLE()
#define BASIC_TIM_IRQn				        TIM6_DAC_IRQn
#define BASIC_TIM_IRQHandler    	        TIM6_DAC_IRQHandler

#define PWM_TIM_PORT           		        TIM2
#define PWM_TIM_CLK_ENABLE()       		    __TIM2_CLK_ENABLE()
#define PWM_GPIO_PIN            		    GPIO_PIN_5              
#define PWM_GPIO_PORT      		            GPIOA                      
#define PWM__GPIO_CLK_ENABLE()		        __GPIOA_CLK_ENABLE()
#define PWM_GPIO_AF					        GPIO_AF1_TIM2

void hal_basetim_init(void);
void hal_timpwm_init(void);

#ifdef __cplusplus
}
#endif
#endif /*__HAL_TIM_H */
