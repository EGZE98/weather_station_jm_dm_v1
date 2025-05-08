/*
 * main.c
 *
 * Created: 12/21/2022 6:08:25 AM
 *  Author: dawid
 */
 
#include <avr/io.h>
#include <xc.h>
#include <util/delay.h>
#include <stdbool.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>

#include "leds.h"
#include "usart0.h"
#include "adc.h"
#include "lcd.h"
#include "buzzer.h"
#include "keys.h"
#include "timer.h"

uint8_t wynik;

extern volatile uint8_t duty_cycle;

char name1 [] = {"Weather  Station"};
char name2 [] = {"by JM & DM"};
char version [] = {"alpha 0.1"};
char date [] = {"27.04.2023"};
	
int main(void)
{
	led_pins_set_output();
	BUZZER_OFF;
	LCD_BACKLIGHT_OFF;
	LCD_OFF;
	USART0_init(MYUBRR);
	ADC_init();
	lcd_init();
	timer0_init(); 
	LCD_BACKLIGHT_ON;
	LCD_ON;
	lcd_intro();
	
	lcd_locate(0,2);
	lcd_str(name1);

	lcd_locate(1,5);
	lcd_str(name2);

	lcd_locate(3,11);
	lcd_str(version);
	
	lcd_locate(3,0);
	lcd_str(date);
	
	_delay_ms(3000);
	lcd_cls();

	while(1) 
	{
		lcd_brightness(ADC_measurement (3));

	}
}
