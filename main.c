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

#include "PINS_CONFIG.h"
#include "USART0.h"
#include "ADC.h"
#include "LCD.h"

uint8_t wynik;

char tab0 [] = {"Weather  Station"};	// First writing
char tab1 [] = {"by JM & DM"};		// Second writing
char tab2 [] = {"alpha 0.1"};		// Third writing
char date [] = {"27.04.2023"};		// Fourth writing
	
int main(void)
{
	pins_configuration();		// Pins definitions
	BUZZER_OFF;					// Turn off buzzer
	LCD_BACKLIGHT_OFF;			// Turn off LCD backlight
	LCD_OFF;					// Turn off LCD
	USART0_init(MYUBRR);		// USART0 initialization
	ADC_init();					// ADC initialization
	lcd_init();					// LCD initialization
	
	lcd_locate(0,2);
	lcd_str(tab0);

	lcd_locate(1,5);
	lcd_str(tab1);

	lcd_locate(3,11);
	lcd_str(tab2);
	
	lcd_locate(3,0);
	lcd_str(date);
	
	LCD_BACKLIGHT_ON;
	LCD_ON;
	
	_delay_ms(1000);
	lcd_cls();

	while(1) 
	{
		LCD_ON_OFF();				// Turn on / off LCD
		flash_and_play();			// Sound when key is pushed
		
		wynik = (ADC_measurement (3) * (2.56/1024) * 2);
		
		lcd_locate(0,0);
		char tab3 [] = {"Pr = "};
		lcd_str(tab3);
		lcd_int(wynik);
		
		_delay_ms(1000);

	}
}
