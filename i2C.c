/*
Description :This function is used to initialize the I2c Module.
I/P Arguments: none
Return value : none

*/
#define F_CPU 16000000UL
#include "I2C.h"
#include <avr/io.h>
#include <util/delay.h>


void I2C_Init()
{
	TWSR=0x00; //set presca1er bits to zero
	TWBR=0x46; //SCL frequency is 100K for XTAL = 7.3728M
	TWCR=0x04; //enab1e TWI module
}

/*
Description  :This function is used to generate I2C Start Condition.
Start Condition: SDA goes low when SCL is High.
I/P Arguments: none
Return value : none
*/


void I2C_Start()
{
	TWCR = ((1<<TWINT) | (1<<TWSTA) | (1<<TWEN));
	while (!(TWCR & (1<<TWINT)));
}

/*
Description  :This function is used to generate I2C Stop Condition.
Stop Condition: SDA goes High when SCL is High.
I/P Arguments: none
Return value : none
*/

void I2C_Stop(void)
{
	TWCR = ((1<< TWINT) | (1<<TWEN) | (1<<TWSTO));
	_delay_us(10) ; //wait for a short time
}

/*
Description  :This function is used to send a byte on SDA line using I2C protocol
8bit data is sent bit-by-bit on each clock cycle.
MSB(bit) is sent first and LSB(bit) is sent at last.
Data is sent when SCL is low.
I/P Arguments: unsigned char-->8bit data to be sent.
Return value: none
*/

void I2C_Write(unsigned char dat)
{
	TWDR = dat ;
	TWCR = ((1<< TWINT) | (1<<TWEN));
	while (!(TWCR & (1 <<TWINT)));
}

/*
Description :This function is receives a byte on I2C SDA line
8bit data is received bit-by-bit each clock and finally packed into Byte.
MSB(bit) is received first and LSB(bit) is received at last.
Puts ACK on data line so subsequent I2C data reads can continue.
Return value : Unsigned char(received byte)
*/

unsigned char I2C_ReadACK(void)
{
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
	while ((TWCR & (1<<TWINT)) == 0);
	return TWDR;
}


//read byte with NACK
//used to indicate you are done with Reads
unsigned char I2C_ReadNACK(void)
{
	TWCR = (1<<TWINT)|(1<<TWEN);
	while ((TWCR & (1<<TWINT)) == 0);
	return TWDR;
}
