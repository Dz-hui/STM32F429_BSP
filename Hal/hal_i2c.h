#ifndef __HAL_I2C_H
#define __HAL_I2C_H

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"


#define I2C_PORT                            I2C1
#define I2C_SPEED                           100000
#define I2C_CLOCK_ENABLE()                  __HAL_RCC_I2C1_CLK_ENABLE()
#define I2C_SCL_GPIO_CLOCK_ENABLE()         __HAL_RCC_GPIOB_CLK_ENABLE()
#define I2C_SDA_GPIO_CLOCK_ENABLE()         __HAL_RCC_GPIOB_CLK_ENABLE()
#define I2C_SCL_GPIO_PORT                   GPIOB
#define I2C_SCL_PIN                         GPIO_PIN_6
#define I2C_SDA_GPIO_PORT                   GPIOB
#define I2C_SDA_PIN                         GPIO_PIN_7
#define I2C_OWN_ADDR                        0X0A   //与从机设备地址不同即可

extern I2C_HandleTypeDef eeprom_i2c;

void hal_i2c_gpio_init(void);
void hal_i2c_init(void);

#ifdef __cplusplus
}
#endif

#endif /* __HAL_I2C_H */

