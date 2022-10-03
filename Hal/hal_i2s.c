#include "hal_i2s.h"

void hal_i2s_gpio_init(void){

	GPIO_InitTypeDef I2S_GPIO_InitStructure;

	I2S_LRC_GPIO_CLK();
	I2S_BCLK_GPIO_CLK();                         
	I2S_DACDAT_GPIO_CLK();
	I2S_MCLK_GPIO_CLK();

	I2S_GPIO_InitStructure.Mode = GPIO_MODE_AF_PP;
	I2S_GPIO_InitStructure.Speed = GPIO_SPEED_FAST;
	I2S_GPIO_InitStructure.Pull = GPIO_NOPULL;

	I2S_GPIO_InitStructure.Pin = I2S_LRC_PIN;
	I2S_GPIO_InitStructure.Alternate = I2S_LRC_AF;
	HAL_GPIO_Init(I2S_LRC_PORT, &I2S_GPIO_InitStructure);

	I2S_GPIO_InitStructure.Pin = I2S_BCLK_PIN;
	I2S_GPIO_InitStructure.Alternate = I2S_BCLK_AF;
	HAL_GPIO_Init(I2S_BCLK_PORT, &I2S_GPIO_InitStructure);
	
	I2S_GPIO_InitStructure.Pin = I2S_ADCDAT_PIN;
	I2S_GPIO_InitStructure.Alternate = I2S_ADCDAT_AF;
	HAL_GPIO_Init(I2S_ADCDAT_PORT, &I2S_GPIO_InitStructure);
	
	I2S_GPIO_InitStructure.Pin = I2S_DACDAT_PIN;
	I2S_GPIO_InitStructure.Alternate = I2S_DACDAT_AF;
	HAL_GPIO_Init(I2S_DACDAT_PORT, &I2S_GPIO_InitStructure);
	
	I2S_GPIO_InitStructure.Pin = I2S_MCLK_PIN;
	I2S_GPIO_InitStructure.Alternate = I2S_MCLK_AF;
	HAL_GPIO_Init(I2S_MCLK_PORT, &I2S_GPIO_InitStructure);
}


