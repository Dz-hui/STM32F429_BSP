#include "hal_spi.h"

SPI_HandleTypeDef flash_spi;

void hal_spi_gpio_init(void){

    SPI_CS_GPIO_CLOCK_ENABLE();
    GPIO_InitTypeDef SPI_GPIO_InitStruct = {0};

    SPI_GPIO_InitStruct.Pin = SPI_CS_PIN;
    SPI_GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    SPI_GPIO_InitStruct.Pull = GPIO_NOPULL;
    SPI_GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(SPI_CS_GPIO_PORT, &SPI_GPIO_InitStruct);
    SPI_CS_HIGH();

    SPI_GPIO_InitStruct.Pin = SPI_CLK_PIN;
    SPI_GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    SPI_GPIO_InitStruct.Alternate = GPIO_AF5_SPI5;
    HAL_GPIO_Init(SPI_CLK_GPIO_PORT, &SPI_GPIO_InitStruct);

    SPI_GPIO_InitStruct.Pin = SPI_MISO_PIN;
    HAL_GPIO_Init(SPI_MISO_GPIO_PORT, &SPI_GPIO_InitStruct);

    SPI_GPIO_InitStruct.Pin = SPI_MOSI_PIN;
    HAL_GPIO_Init(SPI_MOSI_GPIO_PORT, &SPI_GPIO_InitStruct);

}

void hal_spi_init(void){

    hal_spi_gpio_init();
    SPI_CLOCK_ENABLE();

    flash_spi.Instance = SPI_PORT;
    flash_spi.Init.Mode = SPI_MODE_MASTER;
    flash_spi.Init.Direction = SPI_DIRECTION_2LINES;
    flash_spi.Init.DataSize = SPI_DATASIZE_8BIT;
    flash_spi.Init.CLKPolarity = SPI_POLARITY_HIGH;
    flash_spi.Init.CLKPhase = SPI_PHASE_2EDGE;
    flash_spi.Init.NSS = SPI_NSS_SOFT;
    flash_spi.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
    flash_spi.Init.FirstBit = SPI_FIRSTBIT_MSB;
    flash_spi.Init.TIMode = SPI_TIMODE_DISABLE;
    flash_spi.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    flash_spi.Init.CRCPolynomial = 7;

    HAL_SPI_Init(&flash_spi);
    __HAL_SPI_ENABLE(&flash_spi);
    w25qxx_mode_init();
}

uint8_t hal_spi_write_data(uint8_t pData){

    uint16_t SPITimeout = 1000;

    while (__HAL_SPI_GET_FLAG( &flash_spi, SPI_FLAG_TXE ) == RESET){
        if((SPITimeout--) == 0) return 0;
    }
    WRITE_REG(flash_spi.Instance->DR, pData);
    SPITimeout = 1000;
    while (__HAL_SPI_GET_FLAG( &flash_spi, SPI_FLAG_RXNE ) == RESET){
        if((SPITimeout--) == 0) return 0;
    }

    return READ_REG(flash_spi.Instance->DR);

}

uint8_t hal_spi_read_data(uint8_t pData){

    return hal_spi_write_data(pData);

}

