#include "hal_sdio.h"

SD_HandleTypeDef uSdHandle;

uint8_t hal_sdio_init(void){

    uint8_t sd_state = MSD_OK;
    hal_sd_gpio_init();
    SDIO_CLOCK_ENABLE();

    uSdHandle.Instance = SDIO;
    uSdHandle.Init.ClockEdge           = SDIO_CLOCK_EDGE_RISING;
    uSdHandle.Init.ClockBypass         = SDIO_CLOCK_BYPASS_DISABLE;
    uSdHandle.Init.ClockPowerSave      = SDIO_CLOCK_POWER_SAVE_DISABLE;
    uSdHandle.Init.BusWide             = SDIO_BUS_WIDE_1B;
    uSdHandle.Init.HardwareFlowControl = SDIO_HARDWARE_FLOW_CONTROL_ENABLE;
    uSdHandle.Init.ClockDiv            = SDIO_TRANSFER_CLK_DIV;
  
    if(HAL_SD_Init(&uSdHandle) != HAL_OK){
      sd_state = MSD_ERROR;
    }

#ifdef STM32  
    BSP_SD_Detect_MspInit(&uSdHandle, NULL); 
    if(hal_sd_isdetected() != SD_PRESENT)   /* Check if SD card is present */
    {
      return MSD_ERROR_SD_NOT_PRESENT;
    }
#endif     

    if(sd_state == MSD_OK){
      if(HAL_SD_ConfigWideBusOperation(&uSdHandle, SDIO_BUS_WIDE_4B) != HAL_OK){
        sd_state = MSD_ERROR;
      }
      else{
        sd_state = MSD_OK;
      }
    }
    return  sd_state;
}

uint8_t hal_sd_read_blocks(uint32_t *pData, uint32_t ReadAddr, uint32_t NumOfBlocks){

    if(HAL_SD_ReadBlocks(&uSdHandle, (uint8_t *)pData, ReadAddr, NumOfBlocks, 1000) != HAL_OK){
      return MSD_ERROR;
    }
    else{
      return MSD_OK;
    }
}

uint8_t hal_sd_write_blocks(uint32_t *pData, uint32_t WriteAddr, uint32_t NumOfBlocks){

    if(HAL_SD_WriteBlocks(&uSdHandle, (uint8_t *)pData, WriteAddr, NumOfBlocks, 1000) != HAL_OK){
      return MSD_ERROR;
    }
    else{
      return MSD_OK;
    }
}

uint8_t hal_sd_read_blocks_dma(uint32_t *pData, uint32_t ReadAddr, uint32_t NumOfBlocks){  
  
    if(HAL_SD_ReadBlocks_DMA(&uSdHandle, (uint8_t *)pData, ReadAddr, NumOfBlocks) != HAL_OK){
      return MSD_ERROR;
    }
    else{
      return MSD_OK;
    }
}

uint8_t hal_sd_write_blocks_dma(uint32_t *pData, uint32_t WriteAddr, uint32_t NumOfBlocks){ 

    if(HAL_SD_WriteBlocks_DMA(&uSdHandle, (uint8_t *)pData, WriteAddr, NumOfBlocks) != HAL_OK){
      return MSD_ERROR;
    }
    else{
      return MSD_OK;
    }
}


uint8_t hal_sd_sectorerase(uint32_t StartAddr, uint32_t EndAddr)
{
  if(HAL_SD_Erase(&uSdHandle, StartAddr, EndAddr) != HAL_OK)
  {
    return MSD_ERROR;
  }
  else
  {
    return MSD_OK;
  }
}

#ifdef YH_STM32F4XX
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
#endif 

void hal_sd_gpio_init(void){

    GPIO_InitTypeDef SDIO_GPIO_InitStruct;

    SDIO_D0_CLOCK_ENABLE();
    SDIO_D1_CLOCK_ENABLE();
    SDIO_D2_CLOCK_ENABLE();
    SDIO_D3_CLOCK_ENABLE();
    SDIO_CLK_CLOCK_ENABLE();
    SDIO_CMD_CLOCK_ENABLE();

#ifdef YH_STM32F4XX
    WIFI_PDN_INIT();
#endif 
    
    SDIO_GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    SDIO_GPIO_InitStruct.Pull = GPIO_NOPULL;
    SDIO_GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
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

#ifdef SDIO_USE_DMA
    static DMA_HandleTypeDef dma_rx_handle;
    static DMA_HandleTypeDef dma_tx_handle;

    __DMAx_TxRx_CLK_ENABLE();

    HAL_NVIC_SetPriority(SDIO_IRQn, 0x0E, 0);
    HAL_NVIC_EnableIRQ(SDIO_IRQn);

    dma_rx_handle.Init.Channel             = SD_DMAx_Rx_CHANNEL;
    dma_rx_handle.Init.Direction           = DMA_PERIPH_TO_MEMORY;
    dma_rx_handle.Init.PeriphInc           = DMA_PINC_DISABLE;
    dma_rx_handle.Init.MemInc              = DMA_MINC_ENABLE;
    dma_rx_handle.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    dma_rx_handle.Init.MemDataAlignment    = DMA_MDATAALIGN_WORD;
    dma_rx_handle.Init.Mode                = DMA_PFCTRL;
    dma_rx_handle.Init.Priority            = DMA_PRIORITY_VERY_HIGH;
    dma_rx_handle.Init.FIFOMode            = DMA_FIFOMODE_ENABLE;
    dma_rx_handle.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
    dma_rx_handle.Init.MemBurst            = DMA_MBURST_INC4;
    dma_rx_handle.Init.PeriphBurst         = DMA_PBURST_INC4;

    dma_rx_handle.Instance = SD_DMAx_Rx_STREAM;

    __HAL_LINKDMA(hsd, hdmarx, dma_rx_handle);

    HAL_DMA_DeInit(&dma_rx_handle);

    HAL_DMA_Init(&dma_rx_handle);

    dma_tx_handle.Init.Channel             = SD_DMAx_Tx_CHANNEL;
    dma_tx_handle.Init.Direction           = DMA_MEMORY_TO_PERIPH;
    dma_tx_handle.Init.PeriphInc           = DMA_PINC_DISABLE;
    dma_tx_handle.Init.MemInc              = DMA_MINC_ENABLE;
    dma_tx_handle.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    dma_tx_handle.Init.MemDataAlignment    = DMA_MDATAALIGN_WORD;
    dma_tx_handle.Init.Mode                = DMA_PFCTRL;
    dma_tx_handle.Init.Priority            = DMA_PRIORITY_VERY_HIGH;
    dma_tx_handle.Init.FIFOMode            = DMA_FIFOMODE_ENABLE;
    dma_tx_handle.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
    dma_tx_handle.Init.MemBurst            = DMA_MBURST_INC4;
    dma_tx_handle.Init.PeriphBurst         = DMA_PBURST_INC4;

    dma_tx_handle.Instance = SD_DMAx_Tx_STREAM;

    __HAL_LINKDMA(hsd, hdmatx, dma_tx_handle);

    HAL_DMA_DeInit(&dma_tx_handle);

    HAL_DMA_Init(&dma_tx_handle);

    HAL_NVIC_SetPriority(SD_DMAx_Rx_IRQn, 0x0F, 0);
    HAL_NVIC_EnableIRQ(SD_DMAx_Rx_IRQn);

    HAL_NVIC_SetPriority(SD_DMAx_Tx_IRQn, 0x0F, 0);
    HAL_NVIC_EnableIRQ(SD_DMAx_Tx_IRQn);
#endif
}

#ifdef STM32
void hal_sd_detect_init(SD_HandleTypeDef *hsd, void *Params){

    GPIO_InitTypeDef  gpio_init_structure;

    SD_DETECT_GPIO_CLK_ENABLE();

    gpio_init_structure.Pin       = SD_DETECT_PIN;
    gpio_init_structure.Mode      = GPIO_MODE_INPUT;
    gpio_init_structure.Pull      = GPIO_PULLUP;
    gpio_init_structure.Speed     = GPIO_SPEED_HIGH;
    HAL_GPIO_Init(SD_DETECT_GPIO_PORT, &gpio_init_structure);

}

uint8_t hal_sd_isdetected(void){

    __IO uint8_t  status = SD_PRESENT;

    if (HAL_GPIO_ReadPin(SD_DETECT_GPIO_PORT, SD_DETECT_PIN) == GPIO_PIN_SET){
      status = SD_NOT_PRESENT;
    }
    return status;

}

uint8_t hal_sd_ITonfig(void){

    GPIO_InitTypeDef gpio_init_structure;

    gpio_init_structure.Pin = SD_DETECT_PIN;
    gpio_init_structure.Pull = GPIO_PULLUP;
    gpio_init_structure.Speed = GPIO_SPEED_FAST;
    gpio_init_structure.Mode = GPIO_MODE_IT_RISING_FALLING;
    HAL_GPIO_Init(SD_DETECT_GPIO_PORT, &gpio_init_structure);

    HAL_NVIC_SetPriority((IRQn_Type)(SD_DETECT_EXTI_IRQn), 0x0F, 0x00);
    HAL_NVIC_EnableIRQ((IRQn_Type)(SD_DETECT_EXTI_IRQn));

    return MSD_OK;
    
}
#endif

#ifdef SDIO_USE_DMA
__weak void BSP_SD_MspDeInit(SD_HandleTypeDef *hsd, void *Params){

    static DMA_HandleTypeDef dma_rx_handle;
    static DMA_HandleTypeDef dma_tx_handle;


    HAL_NVIC_DisableIRQ(SD_DMAx_Rx_IRQn);
    HAL_NVIC_DisableIRQ(SD_DMAx_Tx_IRQn);

    dma_rx_handle.Instance = SD_DMAx_Rx_STREAM;
    HAL_DMA_DeInit(&dma_rx_handle);

    dma_tx_handle.Instance = SD_DMAx_Tx_STREAM;
    HAL_DMA_DeInit(&dma_tx_handle);

    HAL_NVIC_DisableIRQ(SDIO_IRQn);


    __HAL_RCC_SDIO_CLK_DISABLE();

}
#endif

uint8_t hal_sd_get_cardstate(void){

  return((HAL_SD_GetCardState(&uSdHandle) == HAL_SD_CARD_TRANSFER ) ? SD_TRANSFER_OK : SD_TRANSFER_BUSY);
}
  


void hal_sd_get_cardinfo(HAL_SD_CardInfoTypeDef *CardInfo){
  
  HAL_SD_GetCardInfo(&uSdHandle, CardInfo);
}


void HAL_SD_AbortCallback(SD_HandleTypeDef *hsd){

    BSP_SD_AbortCallback();
}


void HAL_SD_TxCpltCallback(SD_HandleTypeDef *hsd){

    BSP_SD_WriteCpltCallback();
}


void HAL_SD_RxCpltCallback(SD_HandleTypeDef *hsd){

    BSP_SD_ReadCpltCallback();
}


__weak void BSP_SD_AbortCallback(void){

}


__weak void BSP_SD_WriteCpltCallback(void){

}


__weak void BSP_SD_ReadCpltCallback(void){

}


