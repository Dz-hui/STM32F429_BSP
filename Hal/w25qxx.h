#ifndef __W25QXX_H
#define __W25QXX_H

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

#define W25Q128

#ifdef W25X16
#define  sFLASH_ID                       0xEF3015     //W25X16
#endif
#ifdef W25Q16
#define  sFLASH_ID                       0xEF4015	    //W25Q16
#endif
#ifdef W25Q64
#define  sFLASH_ID                       0XEF4017     //W25Q64
#endif 
#ifdef W25Q128
#define  sFLASH_ID                       0XEF4018     //W25Q128
#endif 
#ifdef W25Q256
#define  sFLASH_ID                       0XEF4019     //W25Q256
#endif

#define W25QXX_WritePageSize            256
#define W25X_WriteEnable		        0x06 
#define W25X_WriteDisable		        0x04 
#define W25X_ReadStatusReg		        0x05 
#define W25X_WriteStatusReg		        0x01 
#define W25X_ReadData			        0x03 
#define W25X_FastReadData		        0x0B 
#define W25X_FastReadDual		        0x3B 
#define W25X_PageProgram		        0x02 
#define W25X_BlockErase			        0xD8 
#define W25X_SectorErase		        0x20 
#define W25X_ChipErase			        0xC7 
#define W25X_PowerDown			        0xB9 
#define W25X_ReleasePowerDown	        0xAB 
#define W25X_DeviceID			        0xAB 
#define W25X_ManufactDeviceID   	    0x90 
#define W25X_JedecDeviceID		        0x9F 
#define W25X_Enter4ByteMode		        0xB7
#define W25X_ReadStatusRegister3        0x15

#define WIP_Flag                  0x01  /* Write In Progress (WIP) flag */
#define Dummy_Byte                0xFF

uint32_t w25qxx_readID(void);
void w25qxx_mode_init(void);
void w25qxx_write_enable(void);
void w25qxx_chiperase(void);
void w25qxx_sectorerase(uint32_t addr);
uint8_t w25qxx_waitforwriteend(void);
void w25qxx_pagewrite(uint8_t *pbuff,uint32_t addr,uint8_t numofpage);
void w25qxx_writebuff(uint8_t *pbuff,uint32_t addr,uint32_t size);
void w25qxx_readbuff(uint8_t *pbuff,uint32_t addr,uint32_t size);

#ifdef __cplusplus
}
#endif

#endif /* __W25QXX_H */

