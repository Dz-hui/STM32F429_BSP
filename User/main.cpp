#include "main.h"

int main(void){
    uint8_t sd_state;
    HAL_Init();
    SystemClock_Config();
    LED_GPIO_Init();
    hal_debug_uart_init();
    hal_i2c_init();
    hal_adc_init();
    
    internalflash_test();

    while (1){

     adc_test();


    }

}


