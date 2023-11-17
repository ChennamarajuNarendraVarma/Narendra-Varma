#include <reg51.h>
#include "I2C.h"
#include "PORTS.h"

bit_8 bdata a;
sbit LSB=a ^ 0;
sbit MSB=a ^ 7;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~
**** I2C start condition ****
~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void I2C_START(void)
{
	scl=0;
	sda=1;
	DELAY;
	scl=1;
	DELAY;
	sda=0;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*****I2C stop condition******
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void I2C_STOP(void)
{
	DELAY;
	sda=0;
	scl=1;
	DELAY;
	sda=1;
	DELAY;
	scl=0;
}


//sending byte to eeprom slave
void I2C_Slave_Address(bit_8 x)			
{
	bit_8 j;
	a=x;
	for(j=0;j<8;j++)
	{
		scl=0;
		DELAY;
		sda=MSB;
		a<<=1;				/*sending bits by bits*/
		_nop_();
		scl=1;
		DELAY;
		scl=0;
	}
	sda=1;			 /*acknowledgement	*/
	scl=1;
	DELAY;
	scl=0;
	DELAY;
}

// reading dta from eeprom slave
unsigned char I2C_RECIEVE_DATA(unsigned char ACK_FLAG)	
{
	bit_8 j;
	for(j=0;j<8;j++)
	{
		sda=1;
		scl=1;
		DELAY;
		LSB=sda;
		if(j<7)
			a<<=1;		 /*sending one bits of datqa*/
		DELAY;
		scl=0;
		DELAY;
	}
if (ACK_FLAG)
	{
		sda=1;				  /* acknowledgement*/
		scl=0;
		DELAY;
		sda=0;
		scl=1;
		DELAY;																						   
		scl=0;
		DELAY;
	}
else
	{
		sda=1;				  /* acknowledgement*/
		scl=0;
		DELAY;
		sda=1;
		scl=1;
		DELAY;																						   
		scl=0;
		DELAY;
	}
	return a;
}
