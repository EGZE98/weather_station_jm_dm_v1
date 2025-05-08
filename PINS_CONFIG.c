/*
 * PINS_CONFIG.c
 *
 * Created: 12/21/2022 6:21:45 AM
 *  Author: dawid
 */

#include <xc.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <util/delay.h>

#include "PINS_CONFIG.h"

void pins_configuration (void)			// Pins configuration function
{
	DDRB |= (1 << PB6) | (1 << PB7);	// Setting led pins as outputs
	DDRG |= (1 << PG3) | (1 << PG4);	// Setting led pins as outputs
	DDRD |= (1 << PD4);					// Setting buzzer pin as output
	DDRC |= (1 << PC7);					// Setting pin for LCD turning on / off as output
	DDRC |= (1 << PC6);					// Setting pin for LCD backlight turning on / off as output
}

void flash_and_play (void)				// Blink and sound for key function
{
	if (KEY1_PRESSED || KEY2_PRESSED || KEY3_PRESSED)	// Condition for all keys
	{
		BUZZER_ON;						// Sound on
		LED_BLUE_ON;					// Blink on
		_delay_ms(50);					// Wait 50ms
		BUZZER_OFF;						// Sound off
		LED_BLUE_OFF;					// Blink off
		_delay_ms(500);					// Wait 500ms
	}
}

void LCD_ON_OFF (void)					// LCD turn on / off function
{
	if (KEY1_PRESSED)					// Condition for turning on LCD
		_delay_ms(20);					// Wait 20ms
		if (KEY1_PRESSED)				// If KEY1 still pressed
			{
				LCD_BACKLIGHT_ON;		// Turn on LCD backlight
				LCD_ON;					// LCD on
				flash_and_play();		// Blink and sound function
			}
			
	if (KEY2_PRESSED)					// Condition for turning off LCD
		_delay_ms(20);					// Wait 20ms
		if (KEY2_PRESSED)				// If KEY2 still pressed
			{
				LCD_BACKLIGHT_OFF;		// Turn off LCD backlight
				LCD_OFF;				// LCD off
				flash_and_play();		// Blink and sound function
			}
}