#include "hal_led.h"

void LED_GPIO_Init(void){

    LED_B_CLOCK_ENABLE();
    GPIO_InitTypeDef LED_GPIO_InitStruct = {0};
  
    LED_GPIO_InitStruct.Pin = LED_R_PIN|LED_G_PIN|LED_B_PIN;
    LED_GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    LED_GPIO_InitStruct.Pull = GPIO_NOPULL;
    LED_GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(LED_B_GPIO_PORT, &LED_GPIO_InitStruct);

    LED_R_OFF();
    LED_G_OFF();
    LED_B_OFF();

}

