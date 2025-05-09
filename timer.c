/*
 * timer.c
 *
 * Created: 5/8/2025 4:44:21 PM
 *  Author: dawid
 */ 

#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>

#include "timer.h"

volatile uint8_t duty_cycle = 50;  // 50% w zakresie 0-255
volatile uint8_t counter = 0;

void timer0_init() 
{
	DDRC |= (1 << PC6);  
	TCCR0 = (1 << WGM01) | (1 << CS01) | (1 << CS00);
	OCR0 = 12;
	TIMSK |= (1 << OCIE0);
	sei();
}

ISR(TIMER0_COMP_vect) 
{
	counter++;
	if (counter < (255 - duty_cycle)) {
		PORTC |= (1 << PC6);  // Wysoki
		} else {
		PORTC &= ~(1 << PC6); // Niski
	}
	if (counter >= 255) counter = 0;
}