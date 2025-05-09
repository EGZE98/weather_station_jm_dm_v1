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
#include "dht22.h"

uint8_t wynik;

extern volatile uint8_t duty_cycle;

char ok [] = {"ok"};
char nieok [] = {"nieok"};
	
int main(void)
{
	led_pins_set_output();
	BUZZER_OFF;
	LCD_BACKLIGHT_OFF;
	LCD_OFF;
	USART0_init(MYUBRR);
	ADC_init();
	lcd_init();
	DHT22_Init();
	timer0_init(); 
	LCD_BACKLIGHT_ON;
	LCD_ON;
	lcd_intro();
	
	//_delay_ms(3000);
	lcd_cls();

	DHT22_Init();
	_delay_ms(1000);

	while(1) 
	{
		//lcd_brightness(ADC_measurement (3));
		if (DHT22_Read() == 0) 
		{
			DHT22_Print();
			lcd_locate(3,0);
			lcd_str(ok);
		} 
		else 
		{
			lcd_locate(3,0);
			lcd_str(nieok);
		}
		lcd_locate(2,0);

		_delay_ms(2000); // Opó?nienie 2 sekundy

	}
}
