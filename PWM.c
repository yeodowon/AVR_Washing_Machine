/*
 * PWM.c
 *
 * Created: 2022-08-13 오후 10:46:11
 *  Author: KIM JUNG HOON
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>

void init_pwm()
{
	DDRE |= (1 << 3) | (1 << 4) | (1 << 5);
	// 모드 5 : 8비트 고속 PWM
	TCCR3A |= (1 << WGM30);
	TCCR3B |= (1 << WGM32);
	// 비반전 모드 top : 0xFF / 비교일치값 OCR3C
	TCCR3A |= (1 << COM3C1);
	// 분주비 64 -> 16000000 / 64 = 250000 Hz (250kHz)
	// 256 / 2500000 = 1.02ms
	// 127 / 2500000 = 0.5ms
	TCCR3B |= (1 << CS31) | (1 << CS30);
	OCR3C = 0;			// p321 check
}