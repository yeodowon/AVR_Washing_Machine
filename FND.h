/*
 * FND.h
 *
 * Created: 2022-08-14 오후 7:46:09
 *  Author: ehs19
 */ 


#ifndef FND_H_
#define FND_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define FND_DATA_DDR   DDRC
#define FND_DATA_PORT  PORTC

#define FND_DIGHT_DDR  DDRB
#define FND_DIGHT_PORT PORTB
#define FND_DIGHT_D1   4
#define FND_DIGHT_D2   5
#define FND_DIGHT_D3   6
#define FND_DIGHT_D4   7

#endif /* FND_H_ */