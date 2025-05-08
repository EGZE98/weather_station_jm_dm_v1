/*
 * USART.h
 *
 * Created: 1/10/2023 6:02:21 PM
 *  Author: dawid
 */ 

#ifndef USART0_H_
#define USART0_H_

/* Clock Speed */
#define FOSC 11059200

/* UART speed */
#define BAUD 9600

/* Calculate UBRR for U2X=0 - asynchronous transmission */
#define MYUBRR FOSC/16/BAUD-1

void USART0_init(unsigned int ubrr);
void USART0_putchar(char data);
void USART0_putstring(char *s);
void USART0_putint(int value);

#endif /* USART_H_ */