#include "main.h"


FATFS fs; //fatfs 文件系统对象
FIL fnew; //文件对象
FRESULT res_sd; //文件操作结果
UINT fnum; //文件成功读取数量
BYTE buffer[1024];
BYTE textfilebuffer[] = "Welcome here and wish you luck forever! This is the test program\r\n";
BYTE work[FF_MIN_SS];
int main(void){
    uint8_t sd_state;
    HAL_Init();
    SystemClock_Config();
    LED_GPIO_Init();
    hal_debug_uart_init();
    hal_i2c_init();

    res_sd = f_mount(&fs,"1:",1);
    
    if(res_sd == FR_NO_FILESYSTEM){
        printf("SD card not file systerm\n");
        res_sd = f_mkfs("1:",0,work,sizeof(work));
        if(res_sd == FR_OK){
            printf("SD card formatted successfully\n");
            res_sd = f_mount(NULL,"1:",1);
            res_sd = f_mount(&fs,"1:",1);
            if(res_sd == FR_OK){
                printf("The SD card was formatted and remounted successfully\n");
            }
            else{
                printf("SD card formatted successfully and failed to mount\n");
            }
        }
        else{
            printf("SD card format failed\n");
        }
    }
    else if(res_sd != FR_OK){
        printf("SD card mount failed, return parameter:%d\n",res_sd);
    }
    else{
        printf("SD card mount successfully\n");
    }

    

    res_sd = f_open(&fnew,"1:file.txt",FA_READ | FA_WRITE | FA_CREATE_ALWAYS);

    if(res_sd == FR_OK){
        res_sd = f_write(&fnew,textfilebuffer,sizeof(textfilebuffer),&fnum);

        if(res_sd == FR_OK) printf("write file successfully\n");
        else printf("write file failed\n");

        f_close(&fnew);
    }
    else{
        printf("Open file failed\n");
    }

    res_sd = f_open(&fnew,"1:file.txt",FA_OPEN_EXISTING|FA_READ);
    

    if(res_sd == FR_OK){
        res_sd = f_read(&fnew,buffer,sizeof(buffer),&fnum);

        if(res_sd == FR_OK){
            printf("read file successfully\n");
            printf("Read file data as: \n%s",buffer);
        } 
        else printf("read file failed\n");
    }
    else printf("Open file failed\n");

    f_close(&fnew);
    f_mount(NULL,"1:",1);
    

    while (1){

     

    }

}


