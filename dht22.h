/*
 * dht22.h
 *
 * Created: 5/9/2025 11:17:55 AM
 *  Author: dawid
 */ 

#ifndef DHT22_H_
#define DHT22_H_

void DHT22_Init(void); 
uint8_t DHT22_Read(void);
void DHT22_Print(void);

#endif /* DHT22_H_ */