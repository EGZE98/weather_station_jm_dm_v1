/*
 * USART.c
 *
 * Created: 1/10/2023 6:02:38 PM
 *  Author: dawid
 */ 

#include <util/atomic.h>
#include <stdio.h>

void USART0_init(unsigned int ubrr)		// USART0 initialization
{
	/* Set baud rate */
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	/* Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	/* Set frame format: 8 data, 1 stop bit */
	UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}

void USART0_putchar(char data) 
{
	// Wait for empty transmit buffer
	while ( !(UCSR0A & (1<<UDRE0)) );
	// Start transmission
	UDR0 = data;
}

void USART0_putstring(char *s) 
{
	// loop through entire string
	while (*s) 
	{
		USART0_putchar(*s);
		s++;
	}
}

void USART0_putint(int value)		// USART0 send int
{
	char string[17];
	sprintf (string, "%d\n", value);
	USART0_putstring(string);		
}