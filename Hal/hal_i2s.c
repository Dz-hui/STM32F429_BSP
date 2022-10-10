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

void I2S_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

/**
	* I2S×ÜÏß´«ÊäÒôÆµÊý¾Ý¿ÚÏß
	* WM8978_LRC    -> PB12/I2S2_WS
	* WM8978_BCLK   -> PD3/I2S2_CK
	* WM8978_ADCDAT -> PC2/I2S2ext_SD
	* WM8978_DACDAT -> PI3/I2S2_SD
	* WM8978_MCLK   -> PC6/I2S2_MCK
	*/	
	/* Enable GPIO clock */
	WM8978_LRC_GPIO_CLK();
	WM8978_BCLK_GPIO_CLK();                         
	WM8978_ADCDAT_GPIO_CLK();
	WM8978_DACDAT_GPIO_CLK();
	WM8978_MCLK_GPIO_CLK();

	GPIO_InitStructure.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStructure.Speed = GPIO_SPEED_FAST;
	GPIO_InitStructure.Pull = GPIO_NOPULL;

	GPIO_InitStructure.Pin = I2S_LRC_PIN;
	GPIO_InitStructure.Alternate = I2S_LRC_AF;
	HAL_GPIO_Init(I2S_LRC_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.Pin = I2S_BCLK_PIN;
	GPIO_InitStructure.Alternate = I2S_BCLK_AF;
	HAL_GPIO_Init(I2S_BCLK_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.Pin = I2S_ADCDAT_PIN;
	GPIO_InitStructure.Alternate = I2S_ADCDAT_AF;
	HAL_GPIO_Init(I2S_ADCDAT_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.Pin = I2S_DACDAT_PIN;
	GPIO_InitStructure.Alternate = I2S_DACDAT_AF;
	HAL_GPIO_Init(I2S_DACDAT_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.Pin = I2S_MCLK_PIN;
	GPIO_InitStructure.Alternate = I2S_MCLK_AF;
	HAL_GPIO_Init(I2S_MCLK_PORT, &GPIO_InitStructure);
}



