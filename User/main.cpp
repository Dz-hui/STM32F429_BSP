#include "main.h"


int main(void){
    
    uint32_t flash_ID =0;

    HAL_Init();
    SystemClock_Config();
    LED_GPIO_Init();
    hal_debug_uart_init();
    hal_spi_init();
    hal_i2c_init();

    printf("Peripheral initialization complete!\n");
    flash_ID = w25qxx_raed_ID();
    printf("flash_ID = 0x%x\n",flash_ID);


    while (1){

     

    }

}



