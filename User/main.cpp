#include "main.h"


FATFS fs; //fatfs 文件系统对象
FIL fnew; //文件对象
FRESULT res_sd; //文件操作结果
UINT fnum; //文件成功读取数量
uint32_t writebuff[14] = {1,2,3,4,5,6,7,8,9,11,12,13,14,15};
uint32_t readbuff[14];
BYTE work[FF_MIN_SS];
int main(void){
    uint8_t sd_state;
    HAL_Init();
    SystemClock_Config();
    LED_GPIO_Init();
    hal_debug_uart_init();
    hal_i2c_init();

    //SD_Test();
    hal_sdio_init();

	hal_sd_erase(0,1);
    while(hal_sd_get_cardstate() != SD_TRANSFER_OK);
	
    hal_sd_write_block(writebuff,0x00,1);
    while(hal_sd_get_cardstate() != SD_TRANSFER_OK);
    hal_sd_read_block(readbuff,0x00,1);
    while(hal_sd_get_cardstate() != SD_TRANSFER_OK);
	for(int i=14;i>0;i--){
		printf("readdata:%d\n",readbuff[i-1]);
	}
    
    // res_sd = f_mount(&fs,"1:",1);
    // if(res_sd == FR_NO_FILESYSTEM){
    //     res_sd = f_mkfs("1:",0,work,sizeof(work));
    //     if(res_sd == FR_OK){
    //         printf("SD card formatted successfully\n");
    //         res_sd = f_mount(NULL,"1:",1);
    //         res_sd = f_mount(&fs,"1:",1);
    //         if(res_sd == FR_OK){
    //             printf("The SD card was formatted and remounted successfully\n");
    //         }
    //         else{
    //             printf("SD card formatted successfully and failed to mount\n");
    //         }
    //     }
    //     else{
    //         printf("SD card format failed\n");
    //     }
    // }
    // else if(res_sd != FR_OK){
    //     printf("SD card mount failed, return parameter:%d\n",res_sd);
    // }
    // else{
    //     printf("SD card mount successfully\n");
    // }
    

    while (1){

     

    }

}


