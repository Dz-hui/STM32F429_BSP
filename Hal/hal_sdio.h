
#ifndef __HAL_SDIO_H
#define __HAL_SDIO_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"

#define YH_STM32F4XX

#define SDIO_D0_CLOCK_ENABLE()                  __HAL_RCC_GPIOC_CLK_ENABLE()
#define SDIO_D1_CLOCK_ENABLE()                  __HAL_RCC_GPIOC_CLK_ENABLE()
#define SDIO_D2_CLOCK_ENABLE()                  __HAL_RCC_GPIOC_CLK_ENABLE()
#define SDIO_D3_CLOCK_ENABLE()                  __HAL_RCC_GPIOC_CLK_ENABLE()
#define SDIO_CLK_CLOCK_ENABLE()                 __HAL_RCC_GPIOC_CLK_ENABLE()
#define SDIO_CMD_CLOCK_ENABLE()                 __HAL_RCC_GPIOD_CLK_ENABLE()
#define SDIO_CLOCK_ENABLE()                     __HAL_RCC_SDIO_CLK_ENABLE()
#define SDIO_PORT                               SDIO
#define SDIO_D0_GPIO_PORT                       GPIOC
#define SDIO_D0_GPIO_PIN                        GPIO_PIN_8
#define SDIO_D1_GPIO_PORT                       GPIOC
#define SDIO_D1_GPIO_PIN                        GPIO_PIN_9
#define SDIO_D2_GPIO_PORT                       GPIOC
#define SDIO_D2_GPIO_PIN                        GPIO_PIN_10
#define SDIO_D3_GPIO_PORT                       GPIOC
#define SDIO_D3_GPIO_PIN                        GPIO_PIN_11
#define SDIO_CLK_GPIO_PORT                      GPIOC
#define SDIO_CLK_GPIO_PIN                       GPIO_PIN_12
#define SDIO_CMD_GPIO_PORT                      GPIOD
#define SDIO_CMD_GPIO_PIN                       GPIO_PIN_2
#define BSP_SD_CardInfo                         HAL_SD_CardInfoTypeDef


#define MSD_OK                                  ((uint8_t)0x00)
#define MSD_ERROR                               ((uint8_t)0x01)
#define MSD_ERROR_SD_NOT_PRESENT                ((uint8_t)0x02)


#define SD_TRANSFER_OK                          ((uint8_t)0x00)
#define SD_TRANSFER_BUSY                        ((uint8_t)0x01)

#define SD_PRESENT                              ((uint8_t)0x01)
#define SD_NOT_PRESENT                          ((uint8_t)0x00)

#define SD_DATATIMEOUT                          ((uint32_t)100000000)

#define __DMAx_TxRx_CLK_ENABLE                  __HAL_RCC_DMA2_CLK_ENABLE
#define SD_DMAx_Tx_CHANNEL                      DMA_CHANNEL_4
#define SD_DMAx_Rx_CHANNEL                      DMA_CHANNEL_4
#define SD_DMAx_Tx_STREAM                       DMA2_Stream6
#define SD_DMAx_Rx_STREAM                       DMA2_Stream3
#define SD_DMAx_Tx_IRQn                         DMA2_Stream6_IRQn
#define SD_DMAx_Rx_IRQn                         DMA2_Stream3_IRQn
#define BSP_SD_IRQHandler                       SDIO_IRQHandler
#define BSP_SD_DMA_Tx_IRQHandler                DMA2_Stream6_IRQHandler
#define BSP_SD_DMA_Rx_IRQHandler                DMA2_Stream3_IRQHandler
#define SD_DetectIRQHandler()                   HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_8)

static void WIFI_PDN_INIT(void);
static void hal_sd_gpio_init(void);
void hal_sdio_init(void);
void hal_sd_read_block(uint8_t *pData, uint32_t ReadAddr,uint32_t NumberOfBlocks);
void hal_sd_write_block(uint8_t *pData, uint32_t WriteAddr,uint32_t NumberOfBlocks);
uint8_t hal_sd_get_cardstate(void);
uint8_t hal_sd_erase(uint32_t StartAddr, uint32_t EndAddr);
void hal_sd_get_cardinfo(HAL_SD_CardInfoTypeDef *CardInfo);
void hal_sd_get_cardcsd(HAL_SD_CardCSDTypeDef *pCSD);

#ifdef __cplusplus
}
#endif

#endif 
