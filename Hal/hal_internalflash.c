#include "hal_internalflash.h"


void hal_internal_flash_erase(uint32_t firstsector,uint32_t endsector){

	HAL_StatusTypeDef flashstatus = HAL_OK;
	uint32_t SectorError =0;
	FLASH_EraseInitTypeDef FLASH_EraseInitStruct;

	HAL_FLASH_Unlock();

	FLASH_EraseInitStruct.TypeErase = FLASH_TYPEERASE_SECTORS;
	FLASH_EraseInitStruct.VoltageRange = FLASH_VOLTAGE_RANGE_3;
	FLASH_EraseInitStruct.Sector = hal_get_internalflash_sector(firstsector);
	FLASH_EraseInitStruct.NbSectors = hal_get_internalflash_sector(endsector)-hal_get_internalflash_sector(firstsector)+1;
	flashstatus = HAL_FLASHEx_Erase(&FLASH_EraseInitStruct,&SectorError);
	if(flashstatus != HAL_OK){
		#ifdef DEBUG
		printf("flash erase error\n");
		#endif
	}

	flashstatus = FLASH_WaitForLastOperation(INTERNALFLASH_TIMEOUT);
	if(flashstatus != HAL_OK){
		#ifdef DEBUG
		printf("flash waitforerase error\n");
		#endif
	}

	HAL_FLASH_Lock();

}

void hal_internalflash_write(uint32_t addr ,uint16_t *buff, uint32_t num){

	HAL_StatusTypeDef flashstatus = HAL_OK;
	uint32_t firstaddr = addr;			  //写入起始地址
	uint32_t endaddr = firstaddr+(num*2); //写入结束地址：半字写入（16位），num*2

	if(addr < ADDR_FLASH_SECTOR_0 || addr % 4 ) return ; //地址必须大于flash的基地址且是4的整数倍 

	HAL_FLASH_Unlock();
	while(addr<endaddr){
		flashstatus = HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD,addr,*buff);
		if(flashstatus != HAL_OK){
		#ifdef DEBUG
		printf("flash program error\n");
		#endif
	}
		addr = addr + 2 ;
		buff++;

	}
	HAL_FLASH_Lock();

}

uint32_t hal_get_internalflash_sector(uint32_t addr){

    if((addr < ADDR_FLASH_SECTOR_1) ) return FLASH_SECTOR_0;  
    else if(addr < ADDR_FLASH_SECTOR_2) return FLASH_SECTOR_1;  
    else if(addr < ADDR_FLASH_SECTOR_3) return FLASH_SECTOR_2;  
    else if(addr < ADDR_FLASH_SECTOR_4) return FLASH_SECTOR_3;  
    else if(addr < ADDR_FLASH_SECTOR_5) return FLASH_SECTOR_4;     
    else if(addr < ADDR_FLASH_SECTOR_6) return FLASH_SECTOR_5;  
    else if(addr < ADDR_FLASH_SECTOR_7) return FLASH_SECTOR_6;  
	else if(addr < ADDR_FLASH_SECTOR_8) return FLASH_SECTOR_7; 
	else if(addr < ADDR_FLASH_SECTOR_9) return FLASH_SECTOR_8; 
	else if(addr < ADDR_FLASH_SECTOR_10) return FLASH_SECTOR_9; 
	else if(addr < ADDR_FLASH_SECTOR_11) return FLASH_SECTOR_10; 
    else return FLASH_SECTOR_11;  
 
}