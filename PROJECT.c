#include "COMMON.h"

#define SLAVE_WR_ADD  0XA0
#define SLAVE_RD_ADD  0XA1



void main()
{
	unsigned char * DATA_SEND = {"NARENDRA VARMA"} ;
	bit_8 LOC_ADD   = 0X00;
	bit_8 *RD_DATA;
	//bit_8 PAGE = 0,COUNT=0;
	//unsigned char i;
	//Initialsing the uart
	UART_Init(); //
	
	while(1)
	{	
		//Writing dta into EEPROM slave of (0XA0) at location (0x00)and writing ('A')dta
		EEPROM_WR_DATA(SLAVE_WR_ADD,LOC_ADD,DATA_SEND);
		Delay_1ms(2);	
		//send dta written in eeprom location to uart
		SEND_WR_DATA_TO_UART(SLAVE_WR_ADD,LOC_ADD,DATA_SEND);
		Delay_1ms(2);
		//reading from slave of(0xA1) at location 0x00 by setting the pointer

		RD_DATA=EEPROM_RD_DATA(SLAVE_WR_ADD,LOC_ADD,SLAVE_RD_ADD);
		Delay_1ms(2);
		//send dta read from eeprom to uart
		SEND_RD_DATA_TO_UART(SLAVE_RD_ADD,LOC_ADD,RD_DATA);
		
	}
}

void Delay_1ms(unsigned int count)
{
	unsigned int i,j;
	for(i=0;	i<count;	i++)
	{
		for(j=0;	j<1000;	j++);
	}
}