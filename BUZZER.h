/*
 * BUZZER.h
 *
 * Created: 5/8/2025 3:48:36 PM
 *  Author: dawid
 */ 

#ifndef BUZZER_H_
#define BUZZER_H_

#define BUZZER_ON	PORTD &= ~(1 << PD4)
#define BUZZER_OFF	PORTD |=  (1 << PD4)

void sound_and_blink(void);							// Turn on / off beep function declaration

#endif /* BUZZER_H_ */