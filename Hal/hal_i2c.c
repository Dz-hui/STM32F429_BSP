#include "hal_i2c.h"


I2C_HandleTypeDef eeprom_i2c;


void hal_i2c_gpio_init(void){

    GPIO_InitTypeDef I2C_GPIO_InitStruct = {0};

    I2C_SCL_GPIO_CLOCK_ENABLE();
    I2C_SDA_GPIO_CLOCK_ENABLE();
    
    I2C_GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    I2C_GPIO_InitStruct.Pull = GPIO_NOPULL;
    I2C_GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    I2C_GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
    I2C_GPIO_InitStruct.Pin = I2C_SCL_PIN;
    HAL_GPIO_Init(I2C_SCL_GPIO_PORT, &I2C_GPIO_InitStruct);

    I2C_GPIO_InitStruct.Pin = I2C_SDA_PIN;
    HAL_GPIO_Init(I2C_SDA_GPIO_PORT, &I2C_GPIO_InitStruct);
    
}


void hal_i2c_init(void){

    I2C_CLOCK_ENABLE();
    hal_i2c_gpio_init();

    eeprom_i2c.Instance = I2C_PORT;
    eeprom_i2c.Init.ClockSpeed = I2C_SPEED;
    eeprom_i2c.Init.DutyCycle = I2C_DUTYCYCLE_2;
    eeprom_i2c.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    eeprom_i2c.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    eeprom_i2c.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    eeprom_i2c.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
    eeprom_i2c.Init.OwnAddress1 = I2C_OWN_ADDR;
    eeprom_i2c.Init.OwnAddress2 = 0;

    HAL_I2C_Init(&eeprom_i2c);
    
    HAL_I2CEx_ConfigAnalogFilter(&eeprom_i2c, I2C_ANALOGFILTER_ENABLE);
    HAL_I2CEx_ConfigDigitalFilter(&eeprom_i2c, 0);
  
}

