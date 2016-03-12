#include<avr/io.h>
#include"def.h"
/***************
* usart0
***************/
void usart0_init(uint baud)
{
	UBRR0H=baud<<8;
	UBRR0L=baud;
	UCSR0B|=(1<<7)|(1<<4)|(1<<3);
	UCSR0C|=(3<<0);
}

void usart0_transmit(uchar data)
{
	while(!(UCSR0A&(1<<5)));
	UDR0=data;
}

/*#pragma interrupt_handler usart0_receive_isr:19
void usart0_receive_isr()
{
	uchar data_rx;
	data_rx=UDR0;
}*/


/***************
* usart1
***************/
void usart1_init(uint baud)
{
	UBRR1H=baud<<8;
	UBRR1L=baud;
	UCSR1B|=(1<<7)|(1<<4)|(1<<3);
	UCSR1C|=(3<<0);
}

void usart1_transmit(uchar data)
{
	while(!(UCSR1A&(1<<5)));
	UDR1=data;
}

/*#pragma interrupt_handler usart1_receive_isr:31
void usart1_receive_isr()
{
	uchar data_rx;
	data_rx=UDR1;
}*/

