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
	TCCR0 = (1 << WGM01) | (1 << CS01) | (1 << CS00); // CTC, prescaler 64
	OCR0 = 18;  // daje ~12.75 kHz (czyli pe?ny cykl 50 Hz)
	TIMSK |= (1 << OCIE0);              // Enable compare match interrupt
	sei();                              // Enable global interrupts
}

ISR(TIMER0_COMP_vect) {
	counter++;
	if (counter < (255 - duty_cycle)) {
		PORTC |= (1 << PC6);  // Wysoki
		} else {
		PORTC &= ~(1 << PC6); // Niski
	}
	if (counter >= 255) counter = 0;
}