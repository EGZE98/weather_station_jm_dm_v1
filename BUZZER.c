/*
 * BUZZER.c
 *
 * Created: 5/8/2025 3:48:11 PM
 *  Author: dawid
 */ 

#include <xc.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <util/delay.h>

#include "buzzer.h"
#include "keys.h"
#include "leds.h"
#include "lcd.h"

void sound_and_blink(void)				// Blink and sound for key function
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