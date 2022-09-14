#include "hal_tim.h"


TIM_HandleTypeDef TIM_TimeBaseStructure;
 
void hal_tim_nvic_init(void){

	HAL_NVIC_SetPriority(BASIC_TIM_IRQn, 0, 3);
	HAL_NVIC_EnableIRQ(BASIC_TIM_IRQn);
}

void hal_basetim_init(void){
	
	BASIC_TIM_CLK_ENABLE(); 
    hal_tim_nvic_init();

	TIM_TimeBaseStructure.Instance = BASIC_TIM_PORT;
	TIM_TimeBaseStructure.Init.Period = 5000-1;       
	TIM_TimeBaseStructure.Init.Prescaler = 10800-1;	
	HAL_TIM_Base_Init(&TIM_TimeBaseStructure);
	HAL_TIM_Base_Start_IT(&TIM_TimeBaseStructure);	
}

void  BASIC_TIM_IRQHandler (void){

	HAL_TIM_IRQHandler(&TIM_TimeBaseStructure);	 	
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
    
    if(htim==(&TIM_TimeBaseStructure)){
        LED_B_TOGGLE(); 
    }
}

