#include "hal_adc.h"

#ifdef ADC_SINGLE_CHANNEL_CONVERSION
__IO uint16_t ADC_ConvertedValue;
ADC_HandleTypeDef ADC_Handle;
ADC_ChannelConfTypeDef ADC_Config;

void hal_adc_nvic_init(void){

    HAL_NVIC_SetPriority(ADC_IRQn, 3, 1);
    HAL_NVIC_EnableIRQ(ADC_IRQn);
}

void hal_adc_gpio_init(void){
    
    GPIO_InitTypeDef ADC_GPIO_InitStructure;
    ADC_RHEOSTAT_GPIO_CLK_ENABLE();

    ADC_GPIO_InitStructure.Pin = ADC_RHEOSTAT_GPIO_PIN;
    ADC_GPIO_InitStructure.Mode = GPIO_MODE_ANALOG;	    
    ADC_GPIO_InitStructure.Pull = GPIO_NOPULL ; 
    HAL_GPIO_Init(ADC_RHEOSTAT_GPIO_PORT, &ADC_GPIO_InitStructure);

}

void hal_adc_init(void){

    ADC_RHEOSTAT_CLK_ENABLE();
    hal_adc_gpio_init();
    hal_adc_nvic_init();

    ADC_Handle.Instance = ADC_RHEOSTAT_PORT;	
    ADC_Handle.Init.ClockPrescaler = ADC_CLOCKPRESCALER_PCLK_DIV4;
    ADC_Handle.Init.Resolution = ADC_RESOLUTION_12B;
    ADC_Handle.Init.ScanConvMode = DISABLE; 
    ADC_Handle.Init.ContinuousConvMode = ENABLE;
    ADC_Handle.Init.DiscontinuousConvMode = DISABLE;
    ADC_Handle.Init.NbrOfDiscConversion   = 0; 
    ADC_Handle.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
    ADC_Handle.Init.ExternalTrigConv = ADC_EXTERNALTRIGCONV_T1_CC1;
    ADC_Handle.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    ADC_Handle.Init.NbrOfConversion = 1;
    ADC_Handle.Init.DMAContinuousRequests = DISABLE;
    ADC_Handle.Init.EOCSelection = DISABLE;    
	                          
    HAL_ADC_Init(&ADC_Handle);

    ADC_Config.Channel = ADC_RHEOSTAT_CHANNEL;
    ADC_Config.Rank = 1;
    ADC_Config.SamplingTime = ADC_SAMPLETIME_56CYCLES;
    ADC_Config.Offset  = 0;

    HAL_ADC_ConfigChannel(&ADC_Handle, &ADC_Config);
    HAL_ADC_Start_IT(&ADC_Handle);
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* AdcHandle){

  ADC_ConvertedValue = HAL_ADC_GetValue(AdcHandle);
}


void ADC_IRQHandler(void){

    HAL_ADC_IRQHandler(&ADC_Handle);

}
#endif

#ifdef ADC_MULIT_CHANNLE_CONVERSION
__IO uint16_t ADC_ConvertedValue[ADC_NUMBEROF_CHANNLE];
void hal_adc_gpio_init(void){
    
    GPIO_InitTypeDef ADC_GPIO_InitStructure;

    ADC_RHEOSTAT_GPIO_CLK_ENABLE();
    ADC_GPIO_InitStructure.Pin = ADC_RHEOSTAT_GPIO_PIN;
    ADC_GPIO_InitStructure.Mode = GPIO_MODE_ANALOG;	    
    ADC_GPIO_InitStructure.Pull = GPIO_NOPULL ; 
    HAL_GPIO_Init(ADC_RHEOSTAT_GPIO_PORT, &ADC_GPIO_InitStructure);

    ADC_LIGHTSENSOR_GPIO_CLK_ENABLE();
    ADC_GPIO_InitStructure.Pin = ADC_LIGHTSENSOR_GPIO_PIN;
    ADC_GPIO_InitStructure.Mode = GPIO_MODE_ANALOG;	    
    ADC_GPIO_InitStructure.Pull = GPIO_NOPULL ; 
    HAL_GPIO_Init(ADC_LIGHTSENSOR_GPIO_PORT, &ADC_GPIO_InitStructure);

}

void hal_adc_dma_init(void){

    DMA_HandleTypeDef  ADC_DMA_InitStructure;
		ADC_DMA_CLK_ENABLE();

		ADC_DMA_InitStructure.Instance = ADC_DMA_STREAM;
		ADC_DMA_InitStructure.Init.Direction = DMA_PERIPH_TO_MEMORY;
		ADC_DMA_InitStructure.Init.Channel = ADC_DMA_CHANNLE;
    ADC_DMA_InitStructure.Init.Mode = DMA_CIRCULAR;
		ADC_DMA_InitStructure.Init.MemDataAlignment = DMA_PDATAALIGN_HALFWORD;
		ADC_DMA_InitStructure.Init.MemInc =	DMA_MINC_ENABLE;	
		ADC_DMA_InitStructure.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
		ADC_DMA_InitStructure.Init.PeriphInc =	DMA_PINC_DISABLE;	
    ADC_DMA_InitStructure.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
		ADC_DMA_InitStructure.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_HALFFULL;
		ADC_DMA_InitStructure.Init.PeriphBurst = DMA_PBURST_SINGLE;
		ADC_DMA_InitStructure.Init.MemBurst = DMA_MBURST_SINGLE;
		ADC_DMA_InitStructure.Init.Priority = DMA_PRIORITY_HIGH;
    HAL_DMA_Init(&ADC_DMA_InitStructure);
    HAL_DMA_Start(&ADC_DMA_InitStructure,ADC1_DR_ADDR,(uint32_t)ADC_ConvertedValue,ADC_NUMBEROF_CHANNLE);

}

void hal_adc_init(void){

    ADC_HandleTypeDef ADC_Handle;
    ADC_ChannelConfTypeDef ADC_Config;

    hal_adc_gpio_init();
    hal_adc_dma_init();
    ADC_RHEOSTAT_CLK_ENABLE();
    ADC_LIGHTSENSOR_CLK_ENABLE();
		
		ADC_Handle.Instance = ADC_LIGHTSENSOR_PORT;
		ADC_Handle.Init.ClockPrescaler = ADC_CLOCKPRESCALER_PCLK_DIV4;
		ADC_Handle.Init.DataAlign = ADC_DATAALIGN_RIGHT;
		ADC_Handle.Init.Resolution = ADC_RESOLUTION_12B;
		ADC_Handle.Init.ScanConvMode = ENABLE;
		ADC_Handle.Init.ContinuousConvMode = ENABLE;
		ADC_Handle.Init.NbrOfConversion = ADC_NUMBEROF_CHANNLE;
		ADC_Handle.Init.DiscontinuousConvMode = DISABLE;
		ADC_Handle.Init.ExternalTrigConv = ADC_EXTERNALTRIGCONVEDGE_NONE;
		ADC_Handle.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONV_T1_CC1;
		ADC_Handle.Init.EOCSelection = DISABLE;
		ADC_Handle.Init.NbrOfDiscConversion = 0;
		ADC_Handle.Init.DMAContinuousRequests =	ENABLE;
		HAL_ADC_Init(&ADC_Handle);

    ADC_Config.Channel = ADC_RHEOSTAT_CHANNEL;
		ADC_Config.Rank = 1;
		ADC_Config.SamplingTime = ADC_SAMPLETIME_56CYCLES;
		ADC_Config.Offset = 0;
		HAL_ADC_ConfigChannel(&ADC_Handle,&ADC_Config);

    ADC_Config.Channel = ADC_LIGHTSENSOR_CHANNEL;
		ADC_Config.Rank = 2;
		ADC_Config.SamplingTime = ADC_SAMPLETIME_56CYCLES;
		ADC_Config.Offset = 0;
		HAL_ADC_ConfigChannel(&ADC_Handle,&ADC_Config);

    HAL_ADC_Start_DMA(&ADC_Handle, (uint32_t*)&ADC_ConvertedValue,1);
	
}
#endif

#ifdef ADC_TRIPLEMODE_SINGLE_CHANNEL_CONVERSION

__IO uint16_t ADC_ConvertedValue[ADC_NUMBEROF_CHANNLE];
DMA_HandleTypeDef  ADC_DMA_InitStructure;

void hal_adc_gpio_init(void){
    
    GPIO_InitTypeDef ADC_GPIO_InitStructure;
    ADC_RHEOSTAT_GPIO_CLK_ENABLE();

    ADC_GPIO_InitStructure.Pin = ADC_RHEOSTAT_GPIO_PIN;
    ADC_GPIO_InitStructure.Mode = GPIO_MODE_ANALOG;	    
    ADC_GPIO_InitStructure.Pull = GPIO_NOPULL ; 
    HAL_GPIO_Init(ADC_RHEOSTAT_GPIO_PORT, &ADC_GPIO_InitStructure);

}

void hal_adc_dma_init(void){

    DMA_HandleTypeDef  ADC_DMA_InitStructure;
		ADC_DMA_CLK_ENABLE();

		ADC_DMA_InitStructure.Instance = ADC_DMA_STREAM;
		ADC_DMA_InitStructure.Init.Direction = DMA_PERIPH_TO_MEMORY;
		ADC_DMA_InitStructure.Init.Channel = ADC_DMA_CHANNLE;
    ADC_DMA_InitStructure.Init.Mode = DMA_CIRCULAR;
		ADC_DMA_InitStructure.Init.MemDataAlignment = DMA_PDATAALIGN_HALFWORD;
		ADC_DMA_InitStructure.Init.MemInc =	DMA_MINC_ENABLE;	
		ADC_DMA_InitStructure.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
		ADC_DMA_InitStructure.Init.PeriphInc =	DMA_PINC_DISABLE;	
    ADC_DMA_InitStructure.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
		ADC_DMA_InitStructure.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_HALFFULL;
		ADC_DMA_InitStructure.Init.PeriphBurst = DMA_PBURST_SINGLE;
		ADC_DMA_InitStructure.Init.MemBurst = DMA_MBURST_SINGLE;
		ADC_DMA_InitStructure.Init.Priority = DMA_PRIORITY_HIGH;
    HAL_DMA_Init(&ADC_DMA_InitStructure);
    HAL_DMA_Start(&ADC_DMA_InitStructure,RHEOSTAT_ADC_DR_ADDR,(uint32_t)ADC_ConvertedValue,ADC_NUMBEROF_CHANNLE);

}

void hal_adc_init(void){

    ADC_HandleTypeDef ADC1_Handle;
    ADC_HandleTypeDef ADC2_Handle;
    ADC_HandleTypeDef ADC3_Handle;
    ADC_ChannelConfTypeDef ADC_Config;
    ADC_MultiModeTypeDef   mode;

    hal_adc_gpio_init();
    hal_adc_dma_init();
    ADC_RHEOSTAT_CLK_ENABLE();
		ADC2_RHEOSTAT_CLK_ENABLE();
    ADC3_RHEOSTAT_CLK_ENABLE();

		ADC1_Handle.Instance = ADC_RHEOSTAT_PORT;
		ADC1_Handle.Init.ClockPrescaler = ADC_CLOCKPRESCALER_PCLK_DIV4;
		ADC1_Handle.Init.DataAlign = ADC_DATAALIGN_RIGHT;
		ADC1_Handle.Init.Resolution = ADC_RESOLUTION_12B;
		ADC1_Handle.Init.ScanConvMode = DISABLE;
		ADC1_Handle.Init.ContinuousConvMode = ENABLE;
		ADC1_Handle.Init.NbrOfConversion = 1;
		ADC1_Handle.Init.DiscontinuousConvMode = DISABLE;
		ADC1_Handle.Init.ExternalTrigConv = ADC_EXTERNALTRIGCONVEDGE_NONE;
		ADC1_Handle.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONV_T1_CC1;
		ADC1_Handle.Init.EOCSelection = DISABLE;
		ADC1_Handle.Init.NbrOfDiscConversion = 0;
		ADC1_Handle.Init.DMAContinuousRequests =	ENABLE;
		HAL_ADC_Init(&ADC1_Handle);

    ADC_Config.Channel = ADC_RHEOSTAT_CHANNEL;
		ADC_Config.Rank = 1;
		ADC_Config.SamplingTime = ADC_SAMPLETIME_56CYCLES;
		ADC_Config.Offset = 0;
		HAL_ADC_ConfigChannel(&ADC1_Handle,&ADC_Config);

    ADC2_Handle.Instance = ADC2_RHEOSTAT_PORT;
		ADC2_Handle.Init.ClockPrescaler = ADC_CLOCKPRESCALER_PCLK_DIV4;
		ADC2_Handle.Init.DataAlign = ADC_DATAALIGN_RIGHT;
		ADC2_Handle.Init.Resolution = ADC_RESOLUTION_12B;
		ADC2_Handle.Init.ScanConvMode = DISABLE;
		ADC2_Handle.Init.ContinuousConvMode = ENABLE;
		ADC2_Handle.Init.NbrOfConversion = 1;
		ADC2_Handle.Init.DiscontinuousConvMode = DISABLE;
		ADC2_Handle.Init.ExternalTrigConv = ADC_EXTERNALTRIGCONVEDGE_NONE;
		ADC2_Handle.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONV_T1_CC1;
		ADC2_Handle.Init.EOCSelection = DISABLE;
		ADC2_Handle.Init.NbrOfDiscConversion = 0;
		ADC2_Handle.Init.DMAContinuousRequests =	ENABLE;
		HAL_ADC_Init(&ADC2_Handle);

    ADC_Config.Channel = ADC_RHEOSTAT_CHANNEL;
		ADC_Config.Rank = 1;
		ADC_Config.SamplingTime = ADC_SAMPLETIME_56CYCLES;
		ADC_Config.Offset = 0;
		HAL_ADC_ConfigChannel(&ADC2_Handle,&ADC_Config);

    ADC3_Handle.Instance = ADC3_RHEOSTAT_PORT;
		ADC3_Handle.Init.ClockPrescaler = ADC_CLOCKPRESCALER_PCLK_DIV4;
		ADC3_Handle.Init.DataAlign = ADC_DATAALIGN_RIGHT;
		ADC3_Handle.Init.Resolution = ADC_RESOLUTION_12B;
		ADC3_Handle.Init.ScanConvMode = DISABLE;
		ADC3_Handle.Init.ContinuousConvMode = ENABLE;
		ADC3_Handle.Init.NbrOfConversion = 1;
		ADC3_Handle.Init.DiscontinuousConvMode = DISABLE;
		ADC3_Handle.Init.ExternalTrigConv = ADC_EXTERNALTRIGCONVEDGE_NONE;
		ADC3_Handle.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONV_T1_CC1;
		ADC3_Handle.Init.EOCSelection = DISABLE;
		ADC3_Handle.Init.NbrOfDiscConversion = 0;
		ADC3_Handle.Init.DMAContinuousRequests =	ENABLE;
		HAL_ADC_Init(&ADC3_Handle);

    ADC_Config.Channel = ADC_RHEOSTAT_CHANNEL;
		ADC_Config.Rank = 1;
		ADC_Config.SamplingTime = ADC_SAMPLETIME_56CYCLES;
		ADC_Config.Offset = 0;
		HAL_ADC_ConfigChannel(&ADC3_Handle,&ADC_Config);
    mode.Mode = ADC_TRIPLEMODE_INTERL;
    mode.DMAAccessMode = ADC_DMAACCESSMODE_2;
    mode.TwoSamplingDelay = ADC_TWOSAMPLINGDELAY_5CYCLES;
    
    HAL_ADCEx_MultiModeConfigChannel(&ADC1_Handle, &mode);
    
    HAL_ADC_Start(&ADC2_Handle);
    HAL_ADC_Start(&ADC3_Handle);
    
    __HAL_LINKDMA(&ADC1_Handle, DMA_Handle, ADC_DMA_InitStructure);
    __HAL_LINKDMA(&ADC2_Handle, DMA_Handle, ADC_DMA_InitStructure);
    __HAL_LINKDMA(&ADC3_Handle, DMA_Handle, ADC_DMA_InitStructure); 
    HAL_ADCEx_MultiModeStart_DMA(&ADC1_Handle, (uint32_t*)&ADC_ConvertedValue,ADC_NUMBEROF_CHANNLE);
	
}



#endif





