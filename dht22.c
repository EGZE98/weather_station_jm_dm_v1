/*
 * dht22.c
 *
 * Created: 5/9/2025 11:17:43 AM
 *  Author: dawid
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#include "LCD.h"

#define DHT_PIN PB5        // Ustaw pin, do którego pod??czony jest czujnik DHT22
#define DHT_DDR DDRB       // Rejestr kierunku portu (port D)
#define DHT_PORT PORTB     // Rejestr portu (port D)
#define DHT_PINR PINB      // Rejestr odczytu stanu pinu (port D)

unsigned char data[5]; // Tablica do przechowywania danych odczytanych z czujnika

void DHT22_Init() 
{
	DHT_DDR |= (1 << DHT_PIN);  // Ustaw pin jako wyj?cie (do wys?ania sygna?u startowego)
	DHT_PORT |= (1 << DHT_PIN); // Ustaw stan wysoki na pinie
}

uint8_t DHT22_Read() 
{
	 unsigned char i, j;
	 uint16_t timeout;
	 data[0] = data[1] = data[2] = data[3] = data[4] = 0;

	 // Sygna? startowy
	 DHT_DDR |= (1 << DHT_PIN);   // Ustaw jako wyj?cie
	 DHT_PORT &= ~(1 << DHT_PIN); // Ustaw niski stan
	 _delay_ms(18);               // Minimum 1 ms, najlepiej 18
	 DHT_PORT |= (1 << DHT_PIN);  // Wysoki stan
	 _delay_us(30);               // Krótka przerwa
	 DHT_DDR &= ~(1 << DHT_PIN);  // Ustaw jako wej?cie

	 // Oczekiwanie na odpowied? (stan niski)
	 timeout = 0;
	 while ((DHT_PINR & (1 << DHT_PIN))) {
		 if (++timeout > 10000) return 1; // timeout
		 _delay_us(1);
	 }

	 // Oczekiwanie na stan wysoki
	 timeout = 0;
	 while (!(DHT_PINR & (1 << DHT_PIN))) {
		 if (++timeout > 10000) return 2; // timeout
		 _delay_us(1);
	 }

	 // Oczekiwanie na stan niski (pocz?tek transmisji)
	 timeout = 0;
	 while ((DHT_PINR & (1 << DHT_PIN))) {
		 if (++timeout > 10000) return 3; // timeout
		 _delay_us(1);
	 }

	 // Odczyt 40 bitów danych (5 bajtów)
	 for (j = 0; j < 5; j++) {
		 for (i = 0; i < 8; i++) {
			 // Oczekiwanie na stan wysoki
			 timeout = 0;
			 while (!(DHT_PINR & (1 << DHT_PIN))) {
				 if (++timeout > 10000) return 4; // timeout
				 _delay_us(1);
			 }

			 // Czekaj 30 us, aby sprawdzi? d?ugo?? impulsu
			 _delay_us(30);
			 if (DHT_PINR & (1 << DHT_PIN))
			 data[j] |= (1 << (7 - i));

			 // Oczekiwanie na koniec impulsu (stan niski)
			 timeout = 0;
			 while ((DHT_PINR & (1 << DHT_PIN))) {
				 if (++timeout > 10000) return 5; // timeout
				 _delay_us(1);
			 }
		 }
	 }

	 // Weryfikacja sumy kontrolnej
	 if (data[4] != ((data[0] + data[1] + data[2] + data[3]) & 0xFF)) {
		 return 6; // B??d sumy kontrolnej
	 }

	 return 0; // Sukces
}

void DHT22_Print() 
{
	int humidity = (data[0] << 8) + data[1]; // Wilgotno??
	int temperature = (data[2] << 8) + data[3]; // Temperatura
	//printf("Wilgotno??: %d.%d %%\n", humidity / 10, humidity % 10);
	//printf("Temperatura: %d.%d C\n", temperature / 10, temperature % 10);
	int humidity1 = humidity/10;
	int temperature1 = temperature/10;
	lcd_locate(0,0);
	lcd_int(humidity1);
	lcd_locate(1,0);
	lcd_int(temperature1);
}