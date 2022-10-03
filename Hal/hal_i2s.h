#ifndef __HAL_I2S_H
#define __HAL_I2S_H

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

#define I2S_CLK_ENABLE()            __SPI2_CLK_ENABLE()
#define I2S_CLK_DISABLE()           __SPI2_CLK_DISABLE()
#define I2S_I2Sx_SPI                SPI2
#define I2S_I2Sx_ext                I2S2ext

#define I2S_LRC_GPIO_CLK()          __HAL_RCC_GPIOB_CLK_ENABLE()
#define I2S_LRC_PORT            	GPIOB
#define I2S_LRC_PIN             	GPIO_PIN_12
#define I2S_LRC_AF                  GPIO_AF5_SPI2

#define I2S_BCLK_GPIO_CLK()         __HAL_RCC_GPIOD_CLK_ENABLE()
#define I2S_BCLK_PORT            	GPIOD
#define I2S_BCLK_PIN             	GPIO_PIN_3
#define I2S_BCLK_AF                 GPIO_AF5_SPI2

#define I2S_ADCDAT_GPIO_CLK()       __HAL_RCC_GPIOC_CLK_ENABLE()
#define I2S_ADCDAT_PORT             GPIOC
#define I2S_ADCDAT_PIN              GPIO_PIN_2
#define I2S_ADCDAT_AF               GPIO_AF6_I2S2ext

#define I2S_DACDAT_GPIO_CLK()       __HAL_RCC_GPIOI_CLK_ENABLE()
#define I2S_DACDAT_PORT             GPIOI
#define I2S_DACDAT_PIN              GPIO_PIN_3
#define I2S_DACDAT_AF               GPIO_AF5_SPI2

#define I2S_MCLK_GPIO_CLK()         __HAL_RCC_GPIOC_CLK_ENABLE()
#define I2S_MCLK_PORT            	GPIOC
#define I2S_MCLK_PIN             	GPIO_PIN_6
#define I2S_MCLK_AF                 GPIO_AF5_SPI2



#ifdef __cplusplus
}
#endif

#endif /* __HAL_I2S_H */