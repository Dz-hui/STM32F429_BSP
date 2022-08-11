#ifndef __HAL_SPI_H
#define __HAL_SPI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

extern SPI_HandleTypeDef flash_spi;

#define SPI_CLOCK_ENABLE()                    __HAL_RCC_SPI5_CLK_ENABLE()
#define SPI_CS_GPIO_CLOCK_ENABLE()            __HAL_RCC_GPIOF_CLK_ENABLE()
#define SPI_CLK_GPIO_CLOCK_ENABLE()           __HAL_RCC_GPIOF_CLK_ENABLE()
#define SPI_MISO_GPIO_CLOKC_ENABLE()          __HAL_RCC_GPIOF_CLK_ENABLE()
#define SPI_MOSI_GPIO_CLOCK_ENABLE()          __HAL_RCC_GPIOF_CLK_ENABLE()
#define SPI_PORT                              SPI5
#define SPI_CS_GPIO_PORT                      GPIOF
#define SPI_CS_PIN                            GPIO_PIN_6
#define SPI_CLK_GPIO_PORT                     GPIOF
#define SPI_CLK_PIN                           GPIO_PIN_7
#define SPI_MISO_GPIO_PORT                    GPIOF
#define SPI_MISO_PIN                          GPIO_PIN_8
#define SPI_MOSI_GPIO_PORT                    GPIOF
#define SPI_MOSI_PIN                          GPIO_PIN_9

#define SPI_CS_LOW()                          HAL_GPIO_WritePin(SPI_CS_GPIO_PORT,SPI_CS_PIN,GPIO_PIN_RESET)
#define SPI_CS_HIGH()                         HAL_GPIO_WritePin(SPI_CS_GPIO_PORT,SPI_CS_PIN,GPIO_PIN_SET)

void hal_spi_init(void);
uint8_t hal_spi_write_data(uint8_t pData);
uint8_t hal_spi_read_data(uint8_t pData);



#ifdef __cplusplus
}
#endif

#endif /* __HAL_SPI_H */

