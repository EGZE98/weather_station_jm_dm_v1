/*
 * LEDS.h
 *
 * Created: 12/21/2022 6:13:27 AM
 *  Author: dawid
 */ 

#ifndef LEDS_H_
#define LEDS_H_

#define LED_GREEN_ON		PORTB |=  (1 << PB6)
#define LED_GREEN_OFF		PORTB &= ~(1 << PB6)
#define LED_RED_ON			PORTB |=  (1 << PB7)
#define LED_RED_OFF			PORTB &= ~(1 << PB7)
#define LED_BLUE_ON			PORTG |=  (1 << PG3)
#define LED_BLUE_OFF		PORTG &= ~(1 << PG3)
#define LED_YELLOW_ON		PORTG |=  (1 << PG4)
#define LED_YELLOW_OFF		PORTG &= ~(1 << PG4)

void led_pins_set_output(void);						// Pins configuration function declaration

#endif /* LEDS_H_ */