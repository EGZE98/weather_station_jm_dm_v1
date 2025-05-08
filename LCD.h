/*
 * LCD.h
 *
 * Created: 5/8/2025 4:00:28 PM
 *  Author: dawid
 */ 

#ifndef LCD_H_
#define LCD_H_

#define LCD_OFF				PORTC |=  (1 << PC7)	// Turn off LCD
#define LCD_ON				PORTC &= ~(1 << PC7)	// Turn on LCD

#define LCD_BACKLIGHT_OFF	PORTC |=  (1 << PC6)	// Turn off LCD backlight
#define LCD_BACKLIGHT_ON	PORTC &= ~(1 << PC6)	// Turn on LCD backlight

/* LCD resolution */
#define LCD_ROWS 4
#define LCD_COLS 20

/*	0 - pin RW -> GND; 1 - pin RW -> uC */
#define USE_RW 1

/* LCD D7-D4 connection */
#define LCD_D7PORT  A
#define LCD_D7 7
#define LCD_D6PORT  A
#define LCD_D6 6
#define LCD_D5PORT  A
#define LCD_D5 5
#define LCD_D4PORT  A
#define LCD_D4 4

/* LCD RS connection */
#define LCD_RSPORT C
#define LCD_RS 5

/* LCD RW connection */
#define LCD_RWPORT C
#define LCD_RW 4

/* LCD E connection */
#define LCD_EPORT C
#define LCD_E 3

/* addresses of the first characters of lines */
#define LCD_LINE1 0x00		// address of the 1st character of the 1st line
#define LCD_LINE2 0x40		// address of the 2nd character of the 2nd line (24 - 43)
#define LCD_LINE3 0x14  	// address of the 3rd character of the 3rd line
#define LCD_LINE4 0x54  	// address of the 4th character of the 4th line

/* macros simplifying access to ports */
// *** PORT
#define PORT(x) SPORT(x)
#define SPORT(x) (PORT##x)
// *** PIN
#define PIN(x) SPIN(x)
#define SPIN(x) (PIN##x)
// *** DDR
#define DDR(x) SDDR(x)
#define SDDR(x) (DDR##x)

/* control commands */
#define LCDC_CLS					0x01
#define LCDC_HOME					0x02
#define LCDC_ENTRY					0x04
	#define LCDC_ENTRYR					0x02
	#define LCDC_ENTRYL					0
	#define LCDC_MOVE					0x01
#define LCDC_ONOFF					0x08
	#define LCDC_DISPLAYON				0x04
	#define LCDC_CURSORON				0x02
	#define LCDC_CURSOROFF				0
	#define LCDC_BLINKON				0x01
#define LCDC_SHIFT					0x10
	#define LCDC_SHIFTDISP				0x08
	#define LCDC_SHIFTR					0x04
	#define LCDC_SHIFTL					0
#define LCDC_FUNC					0x20
	#define LCDC_FUNC8B					0x10
	#define LCDC_FUNC4B					0
	#define LCDC_FUNC2L					0x08
	#define LCDC_FUNC1L					0
	#define LCDC_FUNC5x10				0x04
	#define LCDC_FUNC5x7				0
#define LCDC_SET_CGRAM				0x40
#define LCDC_SET_DDRAM				0x80

/* function declarations */
void lcd_init(void);								// initialize the display
void lcd_char(char c);								// send the character
void lcd_int(int val);								// send the integer
void lcd_str(char * str);							// send the string
void lcd_locate(uint8_t y, uint8_t x);				// position on the display
void lcd_cls(void);									// clear the LCD
void LCD_ON_OFF (void);								// Turn on / off LCD function declaration
void lcd_intro(void);
void lcd_brightness(uint8_t);

#endif /* LCD_H_ */
