#ifndef __HAL_UART_H
#define __HAL_UART_H

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

#define DEBUG_UART_CLOCK_ENALE()                __HAL_RCC_USART1_CLK_ENABLE()
#define DEDBUG_UART_TX_GPIO_CLOCK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()
#define DEDBUG_UART_RX_GPIO_CLOCK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()
#define DEBUG_UART_TX_GPIO_PORT                 GPIOA
#define DEBUG_UART_RX_GPIO_PORT                 GPIOA
#define DEBUG_UART_TX_PIN                       GPIO_PIN_9
#define DEBUG_UART_RX_PIN                       GPIO_PIN_10
#define DEBUG_UART                              USART1
#define DEBUG_UART_BAUDRATE                     115200

extern UART_HandleTypeDef debug_huart;

void hal_debug_uart_init(void);


#ifdef __cplusplus
}
#endif

#endif /* __USART_H__ */

