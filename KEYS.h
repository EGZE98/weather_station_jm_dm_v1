/*
 * KEYS.h
 *
 * Created: 5/8/2025 4:00:28 PM
 *  Author: dawid
 */ 

#ifndef KEYS_H_
#define KEYS_H_

#define KEY1_PRESSED		(PINC & (1 << PC0))		// Checking if a key1 is pressed - VCC
#define KEY2_PRESSED		(PINC & (1 << PC1))		// Checking if a key2 is pressed - VCC
#define KEY3_PRESSED		(PINC & (1 << PC2))		// Checking if a key3 is pressed - VCC

#endif /* KEYS_H_ */