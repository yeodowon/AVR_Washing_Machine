/*
 * BUTTON.h
 *
 * Created: 2022-08-13 오후 3:24:57
 *  Author: KIM JUNG HOON
 */ 


#ifndef BUTTON_H_
#define BUTTON_H_

#define F_CPU 16000000UL		// UL : Unsigned Long (16MHz 설정)
#include <avr/io.h>
#include <util/delay.h>

#define LED_DDR DDRA			// A DDR을 LED_DDR에 alias (A 포트 : LED 부분)
#define LED_PORT PORTA			// A 포트를 LED_PORT에 alias (A 포트 : LED 부분)

#define BUTTON_DDR DDRD			// D DDR을 BUTTON_DDR에 alias (D 포트 : BUTTON 부분)
#define BUTTON_PORT PORTD		// D 포트를 BUTTON_PORT에 alias (D 포트 : BUTTON 부분)
#define BUTTON_PIN PIND			// D 핀을 BUTTON_PIN에 alias (D 포트 : BUTTON 부분)
// 전압 5V -> 1 / 0V -> 0

#define BUTTON1		2			// PORTD.2
#define BUTTON2		3			// PORTD.3
#define BUTTON3		4			// PORTD.4
#define BUTTON4		5			// PORTD.5
#define BUTTON5		6			// PORTD.6
#define BUTTON6		7			// PORTD.7

#define WATCH 0						// WATCH 모드 -> 0
#define STOPWATCH 1					// STOPWATCH 모드 -> 1
#define STOP 0						// STOPWATCH의 STOP -> 0
#define RUN 1						// STOPWATCH의 RUN -> 1
#define RESET 2						// STOPWATCH의 RESET -> 2



#endif /* BUTTON_H_ */