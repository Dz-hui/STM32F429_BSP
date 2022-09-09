#include "hal_adc.h"


__IO uint16_t ADC_ConvertedValue;
ADC_HandleTypeDef ADC_Handle;
ADC_ChannelConfTypeDef ADC_Config;

void hal_adc_nvic_init(void){

    HAL_NVIC_SetPriority(ADC_IRQ, 0, 0);
    HAL_NVIC_EnableIRQ(ADC_IRQ);
}

void hal_gpio_init(void){
    
    GPIO_InitTypeDef GPIO_InitStructure;
    ADC_GPIO_CLK_ENABLE();

    GPIO_InitStructure.Pin = ADC_GPIO_PIN;
    GPIO_InitStructure.Mode = GPIO_MODE_ANALOG;	    
    GPIO_InitStructure.Pull = GPIO_NOPULL ; 
    HAL_GPIO_Init(ADC_GPIO_PORT, &GPIO_InitStructure);

}

void hal_adc_init(void){

    ADC_CLK_ENABLE();
    hal_gpio_init();
    hal_adc_nvic_init();

    ADC_Handle.Instance = ADC;	
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
    ADC_Handle.Init.DMAContinuousRequests = ENABLE;
    ADC_Handle.Init.EOCSelection = DISABLE;    
	                          
    HAL_ADC_Init(&ADC_Handle);

    ADC_Config.Channel = ADC_CHANNEL;
    ADC_Config.Rank = 1;
    ADC_Config.SamplingTime = ADC_SAMPLETIME_56CYCLES;
    ADC_Config.Offset  = 0;

    HAL_ADC_ConfigChannel(&ADC_Handle, &ADC_Config);
    HAL_ADC_Start_IT(&ADC_Handle);
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* AdcHandle){

  ADC_ConvertedValue = HAL_ADC_GetValue(AdcHandle);
}

