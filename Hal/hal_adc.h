#ifndef __HAL_DAC__H
#define __HAL_DAC__H

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"


#define ADC_GPIO_PORT                        GPIOC
#define ADC_GPIO_PIN                         GPIO_PIN_3
#define ADC_GPIO_CLK_ENABLE()                __GPIOC_CLK_ENABLE()

#define ADC                                 ADC1
#define ADC_CLK_ENABLE()                    __ADC1_CLK_ENABLE()
#define ADC_CHANNEL                         ADC_CHANNEL_13


#define ADC_IRQ                             ADC_IRQn
#define ADC_INT_FUNCTION                    ADC_IRQHandler


void hal_adc_init(void);


#ifdef __cplusplus
}
#endif

#endif /* __HAL_DAC__H */
