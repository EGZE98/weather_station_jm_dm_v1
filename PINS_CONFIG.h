/*
 * PINS_CONFIG.h
 *
 * Created: 12/21/2022 6:13:27 AM
 *  Author: dawid
 */ 

#ifndef PINS_CONFIG_H_
#define PINS_CONFIG_H_

#define LED_GREEN_ON		PORTB |=  (1 << PB6)	// Turn on the green diode
#define LED_GREEN_OFF		PORTB &= ~(1 << PB6)	// Turn off the green diode
#define LED_RED_ON			PORTB |=  (1 << PB7)	// Turn on the red diode
#define LED_RED_OFF			PORTB &= ~(1 << PB7)	// Turn off the red diode
#define LED_BLUE_ON			PORTG |=  (1 << PG3)	// Turn on the blue diode
#define LED_BLUE_OFF		PORTG &= ~(1 << PG3)	// Turn off the blue diode
#define LED_YELLOW_ON		PORTG |=  (1 << PG4)	// Turn on the yellow diode
#define LED_YELLOW_OFF		PORTG &= ~(1 << PG4)	// Turn off the yellow diode

#define BUZZER_ON			PORTD &= ~(1 << PD4)	// Turn on the buzzer
#define BUZZER_OFF			PORTD |=  (1 << PD4)	// Turn off the buzzer

#define KEY1_PRESSED		(PINC & (1 << PC0))		// Checking if a key1 is pressed - VCC
#define KEY2_PRESSED		(PINC & (1 << PC1))		// Checking if a key2 is pressed - VCC
#define KEY3_PRESSED		(PINC & (1 << PC2))		// Checking if a key3 is pressed - VCC

#define LCD_OFF				PORTC |=  (1 << PC7)	// Turn off LCD
#define LCD_ON				PORTC &= ~(1 << PC7)	// Turn on LCD

#define LCD_BACKLIGHT_OFF	PORTC |=  (1 << PC6)	// Turn off LCD backlight
#define LCD_BACKLIGHT_ON	PORTC &= ~(1 << PC6)	// Turn on LCD backlight

void pins_configuration (void);						// Pins configuration function declaration
void flash_and_play (void);							// Turn on / off beep function declaration
void LCD_ON_OFF (void);								// Turn on / off LCD function declaration

#endif /* PINS_CONFIG_H_ */