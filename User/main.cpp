#include "main.h"

uint8_t flash_data[10]="HeJiahui";
uint8_t flash_readdata[10];

int main(void){
    
    uint32_t flash_ID =0;

    HAL_Init();
    SystemClock_Config();
    LED_GPIO_Init();
    hal_debug_uart_init();
    hal_spi_init();

    printf("Peripheral initialization complete!\n");
    flash_ID = w25qxx_raed_ID();
    printf("flash_ID = 0x%x\n",flash_ID);

//    w25qxx_sector_erase(0x00);
//    w25qxx_pagewrite(flash_data,0x00,10);
//    w25qxx_buffread(flash_readdata,0x00,10);
//    printf("flash_data:%s\n",flash_readdata);

    while (1){

     

    }

}



