#ifndef __AT24CXX_H
#define __AT24CXX_H

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

#define AT24C02_WRITE_ADDR              0XA0
#define AT24C02_READ_ADDR               0XA1
#define AT24C02_PAGE_SIZE               8


void at24cxx_writebyte(uint8_t *pData, uint16_t addr);
void at24cxx_writepage(uint8_t *pData, uint16_t addr,uint8_t size);
void at24cxx_writebuff(uint8_t *pData, uint16_t addr,uint8_t size);
void at24cxx_readbuff(uint8_t *pData, uint16_t addr,uint8_t size);




#ifdef __cplusplus
}
#endif

#endif /* __AT24CXX_H */
