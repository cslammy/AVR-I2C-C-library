#include <stdint.h>

/*
 * I2C.h
 *
 * Created: 2/19/2021 5:55:48 AM
 *  Author: clamm
 */ 
#ifndef I2C_H_ 
#define I2C_H_

void I2C_Init(void);

void I2C_Start(void);

void I2C_Stop(void);

void I2C_Write(uint8_t dat);

uint8_t I2C_ReadACK(void);


uint8_t I2C_ReadNACK(void);

#endif /* I2C_H_  */