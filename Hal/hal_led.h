#ifndef __HAL_LED_H
#define __HAL_LED_H

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

#define LED_R_CLOCK_ENABLE()      __HAL_RCC_GPIOH_CLK_ENABLE()
#define LED_G_CLOCK_ENABLE()      __HAL_RCC_GPIOH_CLK_ENABLE()
#define LED_B_CLOCK_ENABLE()      __HAL_RCC_GPIOH_CLK_ENABLE()
#define LED_R_GPIO_PORT           GPIOH
#define LED_G_GPIO_PORT           GPIOH
#define LED_B_GPIO_PORT           GPIOH
#define LED_R_PIN                 GPIO_PIN_10
#define LED_G_PIN                 GPIO_PIN_11
#define LED_B_PIN                 GPIO_PIN_12
#define LED_R_OFF()               HAL_GPIO_WritePin(LED_R_GPIO_PORT,LED_R_PIN,GPIO_PIN_SET)
#define LED_R_ON()                HAL_GPIO_WritePin(LED_R_GPIO_PORT,LED_R_PIN,GPIO_PIN_RESET)
#define LED_R_TOGGLE()            HAL_GPIO_TogglePin(LED_R_GPIO_PORT,LED_R_PIN)
#define LED_G_OFF()               HAL_GPIO_WritePin(LED_G_GPIO_PORT,LED_G_PIN,GPIO_PIN_SET)
#define LED_G_ON()                HAL_GPIO_WritePin(LED_G_GPIO_PORT,LED_G_PIN,GPIO_PIN_RESET)
#define LED_G_TOGGLE()            HAL_GPIO_TogglePin(LED_G_GPIO_PORT,LED_G_PIN)
#define LED_B_OFF()               HAL_GPIO_WritePin(LED_B_GPIO_PORT,LED_B_PIN,GPIO_PIN_SET)
#define LED_B_ON()                HAL_GPIO_WritePin(LED_B_GPIO_PORT,LED_B_PIN,GPIO_PIN_RESET)
#define LED_B_TOGGLE()            HAL_GPIO_TogglePin(LED_B_GPIO_PORT,LED_B_PIN)


void LED_GPIO_Init(void);


#ifdef __cplusplus
}
#endif
#endif /*__HAL_LED_H */
