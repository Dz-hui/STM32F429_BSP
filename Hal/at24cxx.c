#include "at24cxx.h"

void at24cxx_writebyte(uint8_t *pData, uint16_t addr){

    HAL_I2C_Mem_Write(&eeprom_i2c,AT24C02_WRITE_ADDR,addr,I2C_MEMADD_SIZE_8BIT,pData,1,100);


    while(HAL_I2C_GetState(&eeprom_i2c) != HAL_I2C_STATE_READY);

    while(HAL_I2C_IsDeviceReady(&eeprom_i2c,AT24C02_WRITE_ADDR,300,300) == HAL_TIMEOUT);

    while(HAL_I2C_GetState(&eeprom_i2c) != HAL_I2C_STATE_READY);

}

void at24cxx_writepage(uint8_t *pData, uint16_t addr,uint8_t size){

    HAL_I2C_Mem_Write(&eeprom_i2c,AT24C02_WRITE_ADDR,addr,I2C_MEMADD_SIZE_8BIT,pData,size,100);

    while(HAL_I2C_GetState(&eeprom_i2c) != HAL_I2C_STATE_READY);

    while(HAL_I2C_IsDeviceReady(&eeprom_i2c,AT24C02_WRITE_ADDR,300,300) == HAL_TIMEOUT);

    while(HAL_I2C_GetState(&eeprom_i2c) != HAL_I2C_STATE_READY);

}

void at24cxx_writebuff(uint8_t *pData, uint16_t addr,uint8_t size){

    uint8_t addroffset = 0,count = 0,numofsingle = 0,numofpage = 0;
    
    addroffset = addr % AT24C02_PAGE_SIZE;
    count = AT24C02_PAGE_SIZE - addroffset;
    numofpage = size / AT24C02_PAGE_SIZE;
    numofsingle = size % AT24C02_PAGE_SIZE;

    if(addroffset == 0){
        if(numofpage == 0){
            at24cxx_writepage(pData,addr,size);
        }
        else{
            while(numofpage --){
                at24cxx_writepage(pData,addr,AT24C02_PAGE_SIZE);
                pData += AT24C02_PAGE_SIZE;
                addr += AT24C02_PAGE_SIZE;
            }
            if(numofsingle != 0){
                at24cxx_writepage(pData,addr,numofsingle);
            }
        }
    }
    else{
        if(numofpage == 0){
            at24cxx_writepage(pData,addr,numofsingle);
        }
        else{
            size -= count;
            numofpage = size / AT24C02_PAGE_SIZE;
            numofsingle = size % AT24C02_PAGE_SIZE;

            if(count != 0){
                at24cxx_writepage(pData,addr,count);
                pData += count;
                addr += count;
            }
            while(numofpage --){
                at24cxx_writepage(pData,addr,AT24C02_PAGE_SIZE);
                pData += AT24C02_PAGE_SIZE;
                addr += AT24C02_PAGE_SIZE;
            }
            if(numofsingle != 0){
                at24cxx_writepage(pData,addr,numofsingle);
            }
        }
        
    }

}

void at24cxx_readbuff(uint8_t *pData, uint16_t addr,uint8_t size){

    HAL_I2C_Mem_Read(&eeprom_i2c,AT24C02_WRITE_ADDR,addr,I2C_MEMADD_SIZE_8BIT,pData,size,100);

}