#include "hal_uart.h"

UART_HandleTypeDef debug_uart;

void hal_debug_uart_gpio_init(void){

    DEDBUG_UART_TX_GPIO_CLOCK_ENABLE();
    GPIO_InitTypeDef UART_GPIO_InitStruct = {0};
    
    UART_GPIO_InitStruct.Pin = DEBUG_UART_TX_PIN|DEBUG_UART_RX_PIN;
    UART_GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    UART_GPIO_InitStruct.Pull = GPIO_NOPULL;
    UART_GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    UART_GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
    HAL_GPIO_Init(DEBUG_UART_TX_GPIO_PORT, &UART_GPIO_InitStruct);

}

void hal_debug_uart_init(void){

    DEBUG_UART_CLOCK_ENALE();
    hal_debug_uart_gpio_init();
    
    debug_uart.Instance = DEBUG_UART;
    debug_uart.Init.BaudRate = DEBUG_UART_BAUDRATE;
    debug_uart.Init.WordLength = UART_WORDLENGTH_8B;
    debug_uart.Init.StopBits = UART_STOPBITS_1;
    debug_uart.Init.Parity = UART_PARITY_NONE;
    debug_uart.Init.Mode = UART_MODE_TX_RX;
    debug_uart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    debug_uart.Init.OverSampling = UART_OVERSAMPLING_16;
    HAL_UART_Init(&debug_uart);

}

#ifdef __CC_ARM
int fputc(int ch,FILE *f)
{
    uint32_t temp = ch;
    HAL_UART_Transmit(&debug_uart, (uint8_t *)&temp, 1, 1000);        
    return ch;
}
#else 
int _write(int fd, char *ptr, int len)
{	
	HAL_UART_Transmit(&debug_uart, (uint8_t *)ptr, len, 1000);        
	return len;
}
#endif




