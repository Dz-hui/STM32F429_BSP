#include "w25qxx.h"

uint32_t w25qxx_readID(void){

    uint32_t temp = 0;
    uint8_t temp0 = 0,temp1 = 0,temp2 = 0;

    w25qxx_mode_init();
    
    SPI_CS_LOW();
    hal_spi_write_data(W25X_JedecDeviceID);
    temp0 = hal_spi_write_data(Dummy_Byte);
    temp1 = hal_spi_write_data(Dummy_Byte);
    temp2 = hal_spi_write_data(Dummy_Byte);
    SPI_CS_HIGH();
    temp = (temp0<<16)|(temp1<<8)|(temp2);

    return temp;

}

void w25qxx_mode_init(void)
{
	uint8_t Temp;

	SPI_CS_LOW();
	hal_spi_write_data(W25X_ReadStatusRegister3); 
	Temp = hal_spi_write_data(Dummy_Byte);
	SPI_CS_HIGH();
	
	if((Temp&0x01) == 0)
	{
		SPI_CS_LOW();
		hal_spi_write_data(W25X_Enter4ByteMode);
		SPI_CS_HIGH();
	}
}

void w25qxx_write_enable(void){

    SPI_CS_LOW();
    hal_spi_write_data(W25X_WriteEnable);
    SPI_CS_HIGH();

}

void w25qxx_chiperase(void){

    w25qxx_write_enable();
    SPI_CS_LOW();
    hal_spi_write_data(W25X_ChipErase);
    SPI_CS_HIGH();
    w25qxx_waitforwriteend();

}

void w25qxx_sectorerase(uint32_t addr){

    w25qxx_write_enable();
    w25qxx_waitforwriteend();

    SPI_CS_LOW();
    hal_spi_write_data(W25X_SectorErase);
    hal_spi_write_data((addr & 0XFF000000)>>24);
    hal_spi_write_data((addr & 0XFF0000)>>16);
    hal_spi_write_data((addr & 0XFF00)>>8);
    hal_spi_write_data((addr & 0XFF));
    SPI_CS_HIGH();

    w25qxx_waitforwriteend();
}

uint8_t w25qxx_waitforwriteend(void){
    
    uint8_t flag = 0;
    uint16_t timeout = 10000;

    SPI_CS_LOW();
    hal_spi_write_data(W25X_ReadStatusReg);
    do{
        flag = hal_spi_write_data(Dummy_Byte);
        {
            if((timeout --) == 0){
                return 0;
            }
        }    
    }
    while((flag & WIP_Flag) == SET);
    SPI_CS_HIGH();
}

void w25qxx_pagewrite(uint8_t *pbuff,uint32_t addr,uint8_t numofpage){

    w25qxx_write_enable();
    w25qxx_waitforwriteend();
    SPI_CS_LOW();
    hal_spi_write_data(W25X_PageProgram);
    hal_spi_write_data((addr & 0XFF000000)>>24);
    hal_spi_write_data((addr & 0XFF0000)>>16);
    hal_spi_write_data((addr & 0XFF00)>>8);
    hal_spi_write_data((addr & 0XFF));

    if(numofpage > W25QXX_WritePageSize){
        numofpage = W25QXX_WritePageSize;
        printf("w25qxx_pagewrite error\n");
    }

    while(numofpage--){
        hal_spi_write_data(*pbuff);
        pbuff ++;
    }
    SPI_CS_HIGH();

    w25qxx_waitforwriteend();

}

void w25qxx_writebuff(uint8_t *pbuff,uint32_t addr,uint32_t size){

    uint16_t sectoroffset = 0;
    uint8_t numofpage = 0;
    uint16_t sectorcount = 0;
    uint8_t numofsingle = 0;

    w25qxx_write_enable();
    w25qxx_waitforwriteend();

    sectoroffset = size % W25QXX_WritePageSize;
    sectorcount = size - sectoroffset;
    numofpage = sectorcount / W25QXX_WritePageSize;
    numofsingle = sectorcount % W25QXX_WritePageSize;

    if(sectoroffset == 0){
        if(numofpage == 0){
            w25qxx_pagewrite(pbuff,addr,size);
        }
        else{
            while(numofpage --){
                w25qxx_pagewrite(pbuff,addr,W25QXX_WritePageSize);
                pbuff += W25QXX_WritePageSize;
                addr += W25QXX_WritePageSize;
            }
            w25qxx_pagewrite(pbuff,addr,numofsingle);
        }
    }
    else{
        if(numofpage == 0){
            if(size < sectoroffset){
                w25qxx_pagewrite(pbuff,addr,size); 
            }
            else{
                w25qxx_pagewrite(pbuff,addr,sectoroffset);
                addr += sectoroffset;
                pbuff += sectoroffset;
                w25qxx_pagewrite(pbuff,addr,sectorcount);
            }
            
        }
        else{
            w25qxx_pagewrite(pbuff,addr,sectoroffset);
            addr += sectoroffset;
            pbuff += sectoroffset;
            while(numofpage --){
                w25qxx_pagewrite(pbuff,addr,W25QXX_WritePageSize);
                pbuff += W25QXX_WritePageSize;
                addr += W25QXX_WritePageSize;
            }
            if(numofsingle != 0){
                w25qxx_pagewrite(pbuff,addr,numofsingle);
            }
        }
        
    }
} 
    
void w25qxx_readbuff(uint8_t *pbuff,uint32_t addr,uint32_t size){

    SPI_CS_LOW();
    hal_spi_write_data(W25X_ReadData);
    hal_spi_write_data((addr & 0XFF000000)>>24);
    hal_spi_write_data((addr & 0XFF0000)>>16);
    hal_spi_write_data((addr & 0XFF00)>>8);
    hal_spi_write_data((addr & 0XFF));
    while(size --){
        *pbuff = hal_spi_write_data(Dummy_Byte);
        pbuff++;
    }
    SPI_CS_HIGH();
    
} 
  


