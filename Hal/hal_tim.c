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

void hal_timpwm_gpio_init(void) {

	GPIO_InitTypeDef TIM_GPIO_InitStructure;
	PWM__GPIO_CLK_ENABLE();

	TIM_GPIO_InitStructure.Pin = PWM_GPIO_PIN;	
	TIM_GPIO_InitStructure.Mode = GPIO_MODE_AF_PP;    
	TIM_GPIO_InitStructure.Pull = GPIO_NOPULL;
	TIM_GPIO_InitStructure.Speed = GPIO_SPEED_HIGH; 	
	TIM_GPIO_InitStructure.Alternate = PWM_GPIO_AF;
	HAL_GPIO_Init(PWM_GPIO_PORT, &TIM_GPIO_InitStructure);

}

void hal_timpwm_init(void){

	TIM_OC_InitTypeDef TIM_OCInitStructure;
	TIM_HandleTypeDef  TIM_PWMOUTPUT_Handle;
	PWM_TIM_CLK_ENABLE(); 
	hal_timpwm_gpio_init();

	TIM_PWMOUTPUT_Handle.Instance = PWM_TIM_PORT;
	TIM_PWMOUTPUT_Handle.Init.Period = 10000-1;
	TIM_PWMOUTPUT_Handle.Init.Prescaler = 108-1;	
	TIM_PWMOUTPUT_Handle.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;
	TIM_PWMOUTPUT_Handle.Init.CounterMode=TIM_COUNTERMODE_UP;
	TIM_PWMOUTPUT_Handle.Init.RepetitionCounter=0;	
	HAL_TIM_PWM_Init(&TIM_PWMOUTPUT_Handle);

	TIM_OCInitStructure.OCMode = TIM_OCMODE_PWM1;
	TIM_OCInitStructure.Pulse = 5000;
	TIM_OCInitStructure.OCPolarity = TIM_OCPOLARITY_HIGH;
	TIM_OCInitStructure.OCNPolarity = TIM_OCNPOLARITY_HIGH;
	TIM_OCInitStructure.OCIdleState = TIM_OCIDLESTATE_SET;
	TIM_OCInitStructure.OCNIdleState = TIM_OCNIDLESTATE_RESET;
	HAL_TIM_PWM_ConfigChannel(&TIM_PWMOUTPUT_Handle,&TIM_OCInitStructure,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&TIM_PWMOUTPUT_Handle,TIM_CHANNEL_1);

}
		
void  BASIC_TIM_IRQHandler (void){

	HAL_TIM_IRQHandler(&TIM_TimeBaseStructure);	 	
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
    
    if(htim==(&TIM_TimeBaseStructure)){
        LED_R_TOGGLE(); 
    }
}
