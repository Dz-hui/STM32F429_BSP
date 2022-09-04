#ifndef __HAL_INTERNALFLASH__H
#define __HAL_INTERNALFLASH__H

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

/* Base address of the Flash sectors */ 
#define ADDR_FLASH_SECTOR_0     ((uint32_t)0x08000000) /* Base address of Sector 0, 16 Kbytes   */
#define ADDR_FLASH_SECTOR_1     ((uint32_t)0x08004000) /* Base address of Sector 1, 16 Kbytes   */
#define ADDR_FLASH_SECTOR_2     ((uint32_t)0x08008000) /* Base address of Sector 2, 16 Kbytes   */
#define ADDR_FLASH_SECTOR_3     ((uint32_t)0x0800C000) /* Base address of Sector 3, 16 Kbytes   */
#define ADDR_FLASH_SECTOR_4     ((uint32_t)0x08010000) /* Base address of Sector 4, 64 Kbytes   */
#define ADDR_FLASH_SECTOR_5     ((uint32_t)0x08020000) /* Base address of Sector 5, 128 Kbytes  */
#define ADDR_FLASH_SECTOR_6     ((uint32_t)0x08040000) /* Base address of Sector 6, 128 Kbytes  */
#define ADDR_FLASH_SECTOR_7     ((uint32_t)0x08060000) /* Base address of Sector 7, 128 Kbytes  */
#define ADDR_FLASH_SECTOR_8     ((uint32_t)0x08080000) /* Base address of Sector 7, 128 Kbytes  */	
#define ADDR_FLASH_SECTOR_9    ((uint32_t)0x080A0000)  /* Base address of Sector 7, 128 Kbytes  */
#define ADDR_FLASH_SECTOR_10    ((uint32_t)0x080C0000) /* Base address of Sector 7, 128 Kbytes  */
#define ADDR_FLASH_SECTOR_11    ((uint32_t)0x080E0000) /* Base address of Sector 7, 128 Kbytes  */

#define INTERNALFLASH_TIMEOUT   5000U
#define DATA_32                 ((uint32_t)0x87654321)

void hal_internal_flash_erase(uint32_t firstsector,uint32_t endsector);
void hal_internalflash_write(uint32_t addr ,uint16_t *buff, uint32_t num);
uint32_t hal_get_internalflash_sector(uint32_t addr);

#ifdef __cplusplus
}
#endif

#endif /* __HAL_INTERNALFLASH__H */
