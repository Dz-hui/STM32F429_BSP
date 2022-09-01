/*-----------------------------------------------------------------------*/
/* Low level disk I/O module SKELETON for FatFs     (C)ChaN, 2019        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "ff.h"			/* Obtains integer types */
#include "diskio.h"		/* Declarations of disk functions */
#include "hal_sdio.h"
/* Definitions of physical drive number for each drive */
#define DEV_RAM		0	/* Example: Map Ramdisk to physical drive 0 */
#define DEV_MMC		1	/* Example: Map MMC/SD card to physical drive 1 */
//#define DEV_USB		2	/* Example: Map USB MSD to physical drive 2 */


/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat;
	int result;

	switch (pdrv) {
	case DEV_RAM :
		result = w25qxx_readID();
		if(result == sFLASH_ID){
			stat = RES_OK;
		}

		return stat;

	case DEV_MMC :
		stat = RES_OK;
		return stat;

	// case DEV_USB :
	// 	result = USB_disk_status();

	// 	// translate the reslut code here

	// 	return stat;
	}
	return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat;
	int result;

	switch (pdrv) {
	case DEV_RAM :
		hal_spi_init();
		stat = disk_status(DEV_RAM);

		return stat;

	case DEV_MMC :
//		result = hal_sdio_init();
		if(result == MSD_OK){
			stat = RES_OK;
		}

		return stat;

	// case DEV_USB :
	// 	result = USB_disk_initialize();

	// 	// translate the reslut code here

	// 	return stat;
	}
	return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber to identify the drive */
	BYTE *buff,		/* Data buffer to store read data */
	LBA_t sector,	/* Start sector in LBA */
	UINT count		/* Number of sectors to read */
)
{
	DRESULT res;
	int result;

	switch (pdrv) {
	case DEV_RAM :
		w25qxx_readbuff(buff, sector*4096, count*4096);
		res = RES_OK;

		return res;

	case DEV_MMC :
//		result = hal_sd_read_blocks((uint8_t *)buff, sector, count);

		return res;

	// case DEV_USB :
	// 	// translate the arguments here

	// 	result = USB_disk_read(buff, sector, count);

	// 	// translate the reslut code here

	// 	return res;
	}

	return RES_PARERR;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if FF_FS_READONLY == 0

DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber to identify the drive */
	const BYTE *buff,	/* Data to be written */
	LBA_t sector,		/* Start sector in LBA */
	UINT count			/* Number of sectors to write */
)
{
	DRESULT res;
	int result;

	switch (pdrv) {
	case DEV_RAM :
		w25qxx_sectorerase(sector*4096);
		w25qxx_writebuff((uint8_t *)buff, sector*4096, count*4096);
		res = RES_OK;

		return res;

	case DEV_MMC :
//		result = hal_sd_write_blocks((uint8_t *)buff, sector, count);

		return res;

	// case DEV_USB :
	// 	// translate the arguments here

	// 	result = USB_disk_write(buff, sector, count);

	// 	// translate the reslut code here

	// 	return res;
	}

	return RES_PARERR;
}

#endif


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	DRESULT res;
	int result;
	HAL_SD_CardInfoTypeDef CardInfo;
	switch (pdrv) {
	case DEV_RAM :
		switch(cmd){

			case CTRL_SYNC: res = RES_OK; break;
			case GET_SECTOR_COUNT:
				*(DWORD*)buff = 2056; 
				res = RES_OK;
			break;

			case GET_SECTOR_SIZE:
				*(WORD*)buff = 4096;
				res = RES_OK;
				break;

			case GET_BLOCK_SIZE:
				*(DWORD*)buff = 1;
				res = RES_OK;
				break;
			
			default:
				res = RES_PARERR;
				break;
		}

		return res;

	case DEV_MMC :

		switch(cmd) {

			case CTRL_SYNC: res = RES_OK; break;

			case GET_SECTOR_SIZE:
				*(DWORD*)buff = 512; 
				res = RES_OK;
			break;
			
			case GET_BLOCK_SIZE:
				*(WORD*)buff = 8;
				res = RES_OK;
				break;

			case GET_SECTOR_COUNT:
				hal_sd_get_cardinfo(&CardInfo);
				*(DWORD*)buff = CardInfo.BlockNbr;
				res = RES_OK;
				break;

			default:
				res = RES_PARERR;
				break;
		}
		return res;

	// case DEV_USB :

	// 	// Process of the command the USB drive

	// 	return res;
	}

	return RES_PARERR;
}

__weak DWORD get_fattime(void){

}

