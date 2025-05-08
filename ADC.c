/*
 * CFile1.c
 *
 * Created: 2/9/2023 6:50:07 PM
 *  Author: dawid
 */ 

#include <avr/io.h>
#include "ADC.h"

void ADC_init(void)
{
	ADMUX	|= (1 << REFS0) | (0 << REFS1);						/* <- Voltage reference selections for ADC as AVCC with external capacitor at AREF pin, it must be set that for measure voltage over the entire range (5V) */
	ADCSRA	|= (1 << ADEN) | (1 << ADPS1) | (1 << ADPS0);
}

uint16_t ADC_measurement(uint8_t canal)
{
	ADMUX = (ADMUX & 0xF8) | canal;		
	ADCSRA |= (1 << ADSC);					
	while (ADCSRA & (1 << ADSC));			
	return ADCW;
}