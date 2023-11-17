#include <reg51.h>
#include "PORTS.h"
#include "EEPROM.h"
#include "UART.h"
#include "I2C.h"

code bit_8 write[]={"WRITE: "};
code bit_8 read[] ={"READ : "};
	bit_8  RD_DATA[16];

void EEPROM_WR_DATA(unsigned char SLAVE_WR_ADD,unsigned char LOC_ADD,unsigned char *DATA_SEND)
{
	unsigned char i;
	I2C_START();
	I2C_Slave_Address(SLAVE_WR_ADD & 0XFE);
	I2C_Slave_Address(LOC_ADD);
	for(i=0;DATA_SEND[i] != '\0';i++)
	{
		I2C_Slave_Address(DATA_SEND[i]);
	}
	I2C_STOP();
}
void SEND_WR_DATA_TO_UART(bit_8 SLAVE_WR_ADD,bit_8 LOC_ADD,unsigned char *DATA_SEND)
{
	unsigned char i,j;
	for(j=0;j<16;j++)
	{
		for(i=0;write[i] != '\0';i++)
		{
			UART_TX(write[i]);
		}
		UART_HEX_PRINTER1(SLAVE_WR_ADD);
		UART_TX(':');
		UART_TX(' ');
		UART_HEX_PRINTER2(LOC_ADD+j);
		UART_TX(':');
		UART_TX(' ');
		//for(i=0;DATA_SEND[i] != '\0';i++)
		//{
		UART_TX(DATA_SEND[j]);
		//}
	
		UART_TX(0x0d);
	}
}


unsigned char *EEPROM_RD_DATA(unsigned char SLAVE_WR_ADD,unsigned char LOC_ADD,unsigned char SLAVE_RD_ADD)
{
	unsigned char i;
	I2C_START();
	I2C_Slave_Address(SLAVE_WR_ADD & 0XFE);
	I2C_Slave_Address(LOC_ADD);
	I2C_START();
	I2C_Slave_Address(SLAVE_RD_ADD | 0x01);
	for(i=0;i<16;i++)
	{
		RD_DATA[i] = I2C_RECIEVE_DATA(1);
	}
	I2C_STOP();
	return RD_DATA;
	
}
	

void SEND_RD_DATA_TO_UART(unsigned char SLAVE_RD_ADD,unsigned char LOC_ADD,unsigned char *RD_DATA)
{
	unsigned char i,j;
	for(j=0;j<16;j++)
	{
		for(i=0;read[i] != '\0';i++)
		{
			UART_TX(read[i]);
		}
		UART_HEX_PRINTER1(SLAVE_RD_ADD );
		UART_TX(':');
		UART_TX(' ');
		UART_HEX_PRINTER2(LOC_ADD+j);
		UART_TX(':');
		UART_TX(' ');
		//for(i=0;RD_DATA[i] != '\0';i++)
		//{
		UART_TX(RD_DATA[j]);
		//}
		UART_TX(0x0d);
	}
	
} 
