/*
 * LEDS.c
 *
 * Created: 12/21/2022 6:21:45 AM
 *  Author: dawid
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <util/delay.h>
#include <stdio.h>

#include "leds.h"

void led_pins_set_output(void)			// Pins configuration function
{
	DDRB |= (1 << PB6) | (1 << PB7);	// Setting led pins as outputs
	DDRG |= (1 << PG3) | (1 << PG4);	// Setting led pins as outputs
	DDRD |= (1 << PD4);					// Setting buzzer pin as output
}