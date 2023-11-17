#include<reg51.h>
#include "UART.h"



void UART_Init()
{
	TMOD = 0X20;
	TH1 = -3;
	SCON = 0X40;
	TR1 = 1;
	//IE = 0X90;
}

void UART_TX(unsigned char value)
 {
	 SBUF = value;
	 while(TI==0);
	 TI = 0;
 }

/*void UART_RXTX_INTERRUPT_HANDLER() interrupt 4
{
	if(TI==1)
	{
		TI = 0;
	} 
}*/
 

void UART_HEX_PRINTER1(unsigned char NV)
{
	unsigned char		temp;
	UART_TX('0');
	UART_TX('x');
	temp = NV /0x10;
	UART_TX(temp+55);
	temp = NV%0x10;
	UART_TX(temp+48);
 }

void UART_HEX_PRINTER2(unsigned char NV)
{
	unsigned char		temp;
	UART_TX('0');
	UART_TX('x');
	temp = NV;
	temp = NV / 0x10;
	if(temp>=10)
	{
		temp = temp+55;
		UART_TX(temp);
	}
	else
	{
	UART_TX(temp+48);
	}
	temp = NV % 0x10;
	if(temp>=10)
	{
		temp = temp+55;
		UART_TX(temp);
	}
	else
	{
	UART_TX(temp+48);
	}
	//UART_TX(temp+48);
	
 }