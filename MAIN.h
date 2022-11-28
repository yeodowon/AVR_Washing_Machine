/*
 * MAIN.h
 *
 * Created: 2022-08-13 오후 4:11:41
 *  Author: ehs19
 */ 


#ifndef MAIN_H_
#define MAIN_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>

// 모드 설정을 위한 define 과 int형 변수 선언
#define RESET	0
#define SET		1
#define ACTIVE	2

#define AUTO	0
#define MANUAL	1

#define WASH	0
#define RINSE	1
#define SPINDRY	2

#define READY	0
#define RUN		1
#define STOP	2



#endif /* MAIN_H_ */