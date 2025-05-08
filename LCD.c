/*
 * LCD.c
 *
 * Created: 5/8/2025 4:00:28 PM
 *  Author: dawid
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <util/delay.h>
#include <stdio.h>

#include "lcd.h"
#include "keys.h"
#include "leds.h"
#include "buzzer.h"

/* macro definitions of operations on control signals RS,RW and E */
#define SET_RS 	PORT(LCD_RSPORT) |= (1<<LCD_RS)			// high state on RS line
#define CLR_RS 	PORT(LCD_RSPORT) &= ~(1<<LCD_RS)		// low state on RS line

#define SET_RW 	PORT(LCD_RWPORT) |= (1<<LCD_RW)			// high state on RW line
#define CLR_RW 	PORT(LCD_RWPORT) &= ~(1<<LCD_RW)		// low state on RW line

#define SET_E 	PORT(LCD_EPORT) |= (1<<LCD_E)			// high state on E line
#define CLR_E 	PORT(LCD_EPORT) &= ~(1<<LCD_E)			// low state on E line

uint8_t check_BF(void);			// definition of the busy flag check function

/* all 4 lines as outputs */
static inline void data_dir_out(void)
{
	DDR(LCD_D7PORT)	|= (1<<LCD_D7);
	DDR(LCD_D6PORT)	|= (1<<LCD_D6);
	DDR(LCD_D5PORT)	|= (1<<LCD_D5);
	DDR(LCD_D4PORT)	|= (1<<LCD_D4);
}

/* all 4 lines as inputs */
static inline void data_dir_in(void)
{
	DDR(LCD_D7PORT)	&= ~(1<<LCD_D7);
	DDR(LCD_D6PORT)	&= ~(1<<LCD_D6);
	DDR(LCD_D5PORT)	&= ~(1<<LCD_D5);
	DDR(LCD_D4PORT)	&= ~(1<<LCD_D4);
}


/* send a half byte to LCD */
static inline void lcd_sendHalf(uint8_t data)
{
	if (data&(1<<0)) PORT(LCD_D4PORT) |= (1<<LCD_D4); else PORT(LCD_D4PORT) &= ~(1<<LCD_D4);
	if (data&(1<<1)) PORT(LCD_D5PORT) |= (1<<LCD_D5); else PORT(LCD_D5PORT) &= ~(1<<LCD_D5);
	if (data&(1<<2)) PORT(LCD_D6PORT) |= (1<<LCD_D6); else PORT(LCD_D6PORT) &= ~(1<<LCD_D6);
	if (data&(1<<3)) PORT(LCD_D7PORT) |= (1<<LCD_D7); else PORT(LCD_D7PORT) &= ~(1<<LCD_D7);
}

/* read a half byte from LCD */
#if USE_RW == 1
static inline uint8_t lcd_readHalf(void)
{
	uint8_t result=0;

	if(PIN(LCD_D4PORT)&(1<<LCD_D4)) result |= (1<<0);
	if(PIN(LCD_D5PORT)&(1<<LCD_D5)) result |= (1<<1);
	if(PIN(LCD_D6PORT)&(1<<LCD_D6)) result |= (1<<2);
	if(PIN(LCD_D7PORT)&(1<<LCD_D7)) result |= (1<<3);

	return result;
}
#endif

/* write a byte to LCD */
void _lcd_write_byte(unsigned char _data)
{
	// Ustawienie pinów portu LCD D4..D7 jako wyjœcia
	data_dir_out();

#if USE_RW == 1
	CLR_RW;
#endif

	SET_E;
	lcd_sendHalf(_data >> 4);			// wys³anie starszej czêœci bajtu danych D7..D4
	CLR_E;

	SET_E;
	lcd_sendHalf(_data);				// wys³anie m³odszej czêœci bajtu danych D3..D0
	CLR_E;

#if USE_RW == 1
	while( (check_BF() & (1<<7)) );
#else
	_delay_us(120);
#endif
}

/* read a byte from LCD */
#if USE_RW == 1
uint8_t _lcd_read_byte(void)
{
	uint8_t result=0;
	data_dir_in();

	SET_RW;

	SET_E;
	result = (lcd_readHalf() << 4);	// odczyt starszej czêœci bajtu z LCD D7..D4
	CLR_E;

	SET_E;
	result |= lcd_readHalf();			// odczyt m³odszej czêœci bajtu z LCD D3..D0
	CLR_E;

	return result;
}
#endif

/* check busy flag state */
#if USE_RW == 1
uint8_t check_BF(void)
{
	CLR_RS;
	return _lcd_read_byte();
}
#endif

/* save a command to LCD */
void lcd_write_cmd(uint8_t cmd)
{
	CLR_RS;
	_lcd_write_byte(cmd);
}

/* save data to LCD */
void lcd_write_data(uint8_t data)
{
	SET_RS;
	_lcd_write_byte(data);
}

/* send char to LCD */
void lcd_char(char c)
{
	lcd_write_data( ( c>=0x80 && c<=0x87 ) ? (c & 0x07) : c);
}

/* send string to LCD from RAM */
void lcd_str(char * str)
{
	register char znak;
	while ( (znak=*(str++)) ) lcd_char( znak );
}

/* show int on LCD */
void lcd_int(int val)
{
	char bufor[17];
	sprintf(bufor, "%i", val);
	lcd_str(bufor);
}

/* cursor position */
void lcd_locate(uint8_t y, uint8_t x)
{
	switch(y)
	{
		case 0: y = LCD_LINE1; break;

#if (LCD_ROWS>1)
	    case 1: y = LCD_LINE2; break; // adres 1 znaku 2 wiersza
#endif
#if (LCD_ROWS>2)
    	case 2: y = LCD_LINE3; break; // adres 1 znaku 3 wiersza
#endif
#if (LCD_ROWS>3)
    	case 3: y = LCD_LINE4; break; // adres 1 znaku 4 wiersza
#endif
	}

	lcd_write_cmd( (0x80 + y + x) );
}

/* clear LCD */
void lcd_cls(void)
{
	lcd_write_cmd( LCDC_CLS );

	#if USE_RW == 0
		_delay_ms(4.9);
	#endif
}

/* LCD initialization */
void lcd_init(void)
{
	DDRC |= (1 << PC7);					// Setting pin for LCD turning on / off as output
	DDRC |= (1 << PC6);					// Setting pin for LCD backlight turning on / off as output
	
	// inicjowanie pinów portów ustalonych do pod³¹czenia z wyœwietlaczem LCD
	// ustawienie wszystkich jako wyjœcia
	data_dir_out();
	DDR(LCD_RSPORT) |= (1<<LCD_RS);
	DDR(LCD_EPORT) |= (1<<LCD_E);
	#if USE_RW == 1
		DDR(LCD_RWPORT) |= (1<<LCD_RW);
	#endif

	PORT(LCD_RSPORT) |= (1<<LCD_RS);
	PORT(LCD_EPORT) |= (1<<LCD_E);
	#if USE_RW == 1
		PORT(LCD_RWPORT) |= (1<<LCD_RW);
	#endif

	_delay_ms(15);
	PORT(LCD_EPORT) &= ~(1<<LCD_E);
	PORT(LCD_RSPORT) &= ~(1<<LCD_RS);
	#if USE_RW == 1	
    	PORT(LCD_RWPORT) &= ~(1<<LCD_RW);
	#endif

	// jeszcze nie mo¿na u¿ywaæ Busy Flag
	SET_E;
	lcd_sendHalf(0x03);	// tryb 8-bitowy
	CLR_E;
	_delay_ms(4.1);

	SET_E;
	lcd_sendHalf(0x03);	// tryb 8-bitowy
	CLR_E;
	_delay_us(100);

	SET_E;
	lcd_sendHalf(0x03);	// tryb 8-bitowy
	CLR_E;
	_delay_us(100);

	SET_E;
	lcd_sendHalf(0x02);// tryb 4-bitowy
	CLR_E;
	_delay_us(100);

	// ju¿ mo¿na u¿ywaæ Busy Flag
	// tryb 4-bitowy, 2 wiersze, znak 5x7
	lcd_write_cmd( LCDC_FUNC|LCDC_FUNC4B|LCDC_FUNC2L|LCDC_FUNC5x7 );
	// wy³¹czenie kursora
	lcd_write_cmd( LCDC_ONOFF|LCDC_CURSOROFF );
	// w³¹czenie wyœwietlacza
	lcd_write_cmd( LCDC_ONOFF|LCDC_DISPLAYON );
	// przesuwanie kursora w prawo bez przesuwania zawartoœci ekranu
	lcd_write_cmd( LCDC_ENTRY|LCDC_ENTRYR );

	// kasowanie ekranu
	lcd_cls();
}

void LCD_ON_OFF (void)					// LCD turn on / off function
{
	if (KEY1_PRESSED)					// Condition for turning on LCD
	_delay_ms(20);					// Wait 20ms
	if (KEY1_PRESSED)				// If KEY1 still pressed
	{
		LCD_BACKLIGHT_ON;		// Turn on LCD backlight
		LCD_ON;					// LCD on
		sound_and_blink();		// Blink and sound function
	}
	
	if (KEY2_PRESSED)					// Condition for turning off LCD
	_delay_ms(20);					// Wait 20ms
	if (KEY2_PRESSED)				// If KEY2 still pressed
	{
		LCD_BACKLIGHT_OFF;		// Turn off LCD backlight
		LCD_OFF;				// LCD off
		sound_and_blink();		// Blink and sound function
	}
}