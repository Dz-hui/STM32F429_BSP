#ifndef __HAL_DAC__H
#define __HAL_DAC__H

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

#define ADC_MULIT_CHANNLE_CONVERSION
#define ADC_NUMBEROF_CHANNLE                             2

#define ADC_RHEOSTAT_GPIO_PORT                           GPIOC
#define ADC_RHEOSTAT_GPIO_PIN                            GPIO_PIN_3
#define ADC_RHEOSTAT_GPIO_CLK_ENABLE()                   __GPIOC_CLK_ENABLE()
#define ADC_RHEOSTAT_PORT                                ADC1
#define ADC_RHEOSTAT_CLK_ENABLE()                        __ADC1_CLK_ENABLE()
#define ADC_RHEOSTAT_CHANNEL                             ADC_CHANNEL_13

#define ADC_LIGHTSENSOR_GPIO_PORT                        GPIOA
#define ADC_LIGHTSENSOR_GPIO_PIN                         GPIO_PIN_4
#define ADC_LIGHTSENSOR_GPIO_CLK_ENABLE()                __GPIOA_CLK_ENABLE()
#define ADC_LIGHTSENSOR_PORT                             ADC1
#define ADC_LIGHTSENSOR_CLK_ENABLE()                     __ADC1_CLK_ENABLE()
#define ADC_LIGHTSENSOR_CHANNEL                          ADC_CHANNEL_4

#define ADC_DMA_CLK_ENABLE()                             __DMA2_CLK_ENABLE()
#define ADC_DMA_STREAM                                   DMA2_Stream0
#define ADC_DMA_CHANNLE                                  DMA_CHANNEL_0
#define ADC1_DR_ADDR                                     ((uint32_t)ADC1+0x4c)

void hal_adc_init(void);


#ifdef __cplusplus
}
#endif

#endif /* __HAL_DAC__H */
