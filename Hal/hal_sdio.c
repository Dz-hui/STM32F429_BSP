#include "hal_sdio.h"

SD_HandleTypeDef uSdHandle;

static void WIFI_PDN_INIT(void){

	  GPIO_InitTypeDef GPIO_InitStruct;
	  __HAL_RCC_GPIOG_CLK_ENABLE();

	  GPIO_InitStruct.Pin = GPIO_PIN_9;	
	  GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;      
	  GPIO_InitStruct.Pull  = GPIO_PULLUP;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FAST; 
	  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);	
	  HAL_GPIO_WritePin(GPIOG,GPIO_PIN_9,GPIO_PIN_RESET);  

}

static void hal_sd_gpio_init(void){

    GPIO_InitTypeDef SDIO_GPIO_InitStruct;

    SDIO_D0_CLOCK_ENABLE();
    SDIO_D1_CLOCK_ENABLE();
    SDIO_D2_CLOCK_ENABLE();
    SDIO_D3_CLOCK_ENABLE();
    SDIO_CLK_CLOCK_ENABLE();
    SDIO_CMD_CLOCK_ENABLE();

    WIFI_PDN_INIT();

    SDIO_GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    SDIO_GPIO_InitStruct.Pull = GPIO_NOPULL;
    SDIO_GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    SDIO_GPIO_InitStruct.Alternate = GPIO_AF12_SDIO;
    SDIO_GPIO_InitStruct.Pin = SDIO_D0_GPIO_PIN;
    HAL_GPIO_Init(SDIO_D0_GPIO_PORT, &SDIO_GPIO_InitStruct);

    SDIO_GPIO_InitStruct.Pin = SDIO_D1_GPIO_PIN;
    HAL_GPIO_Init(SDIO_D1_GPIO_PORT, &SDIO_GPIO_InitStruct);

    SDIO_GPIO_InitStruct.Pin = SDIO_D2_GPIO_PIN;
    HAL_GPIO_Init(SDIO_D2_GPIO_PORT, &SDIO_GPIO_InitStruct);

    SDIO_GPIO_InitStruct.Pin = SDIO_D3_GPIO_PIN;
    HAL_GPIO_Init(SDIO_D3_GPIO_PORT, &SDIO_GPIO_InitStruct);

    SDIO_GPIO_InitStruct.Pin = SDIO_CLK_GPIO_PIN;
    HAL_GPIO_Init(SDIO_CLK_GPIO_PORT, &SDIO_GPIO_InitStruct);

    SDIO_GPIO_InitStruct.Pin = SDIO_CMD_GPIO_PIN;
    HAL_GPIO_Init(SDIO_CMD_GPIO_PORT, &SDIO_GPIO_InitStruct);

}


void hal_sdio_init(void){

    SDIO_CLOCK_ENABLE();

    hal_sd_gpio_init();
    WIFI_PDN_INIT();

    uSdHandle.Instance = SDIO;
    uSdHandle.Init.ClockEdge = SDIO_CLOCK_EDGE_RISING;
    uSdHandle.Init.ClockBypass = SDIO_CLOCK_BYPASS_DISABLE;
    uSdHandle.Init.ClockPowerSave = SDIO_CLOCK_POWER_SAVE_DISABLE;
    uSdHandle.Init.BusWide = SDIO_BUS_WIDE_1B;
    uSdHandle.Init.HardwareFlowControl = SDIO_HARDWARE_FLOW_CONTROL_ENABLE;
    uSdHandle.Init.ClockDiv = 4;
  
    if(HAL_SD_Init(&uSdHandle) != HAL_OK){
        Error_Handler();
    }
    
    if(HAL_SD_ConfigWideBusOperation(&uSdHandle, SDIO_BUS_WIDE_4B) != HAL_OK){
        Error_Handler();
    }
      
}

void hal_sd_read_block(uint32_t *pData, uint32_t ReadAddr,uint32_t NumberOfBlocks) {
    
    if(HAL_SD_ReadBlocks(&uSdHandle,(uint8_t *)pData,ReadAddr,NumberOfBlocks,1000) != HAL_OK)
    {
        Error_Handler();
    }
    
}

void hal_sd_write_block(uint32_t *pData, uint32_t WriteAddr,uint32_t NumberOfBlocks) {
    
    if(HAL_SD_WriteBlocks(&uSdHandle,(uint8_t *)pData,WriteAddr,NumberOfBlocks,1000) != HAL_OK)
    {
        Error_Handler();
    }
    
}

uint8_t hal_sd_get_cardstate(void){
    
    return((HAL_SD_GetCardState(&uSdHandle) == HAL_SD_CARD_TRANSFER ) ? SD_TRANSFER_OK : SD_TRANSFER_BUSY);

}

uint8_t hal_sd_erase(uint32_t StartAddr, uint32_t EndAddr){
    if(HAL_SD_Erase(&uSdHandle, StartAddr, EndAddr) != HAL_OK)
    {
        Error_Handler();
    }

}

void hal_sd_get_cardinfo(HAL_SD_CardInfoTypeDef *CardInfo){

  HAL_SD_GetCardInfo(&uSdHandle, CardInfo);

}

void hal_sd_get_cardcsd(HAL_SD_CardCSDTypeDef *pCSD){

  HAL_SD_GetCardCSD(&uSdHandle, pCSD);

}


// void hal_sd_deinit(void) {

//     _SD_GPIO_CLK_DISABLE();
//     HAL_SD_DeInit(&uSdHandle);
// }



// void hal_sd_register(void) {    

//     hal_sd.sd_init = hal_sdio_init;
//     hal_sd.sd_trans_data = hal_sd_write_block;
//     hal_sd.sd_receive_data = hal_sd_read_block;
//     hal_sd.sd_get_status = hal_sd_get_cardstate;
//     hal_sd.sd_get_cardinfo = hal_sd_get_cardinfo;
//     hal_sd.sd_erase = hal_sd_erase;
//     hal_sd.sd_get_cardcsd = hal_sd_get_cardcsd;

//     hal_sd.sd_init();

// }

