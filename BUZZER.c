/*
 * BUZZER.c
 *
 * Created: 2022-08-13 오후 9:55:56
 *  Author: KIM JUNG HOON
 */ 

#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>



#define DO_01   1911
#define DO_01_H 1817
#define RE_01   1703
#define RE_01_H 1607
#define MI_01   1517
#define FA_01   1432
#define FA_01_H 1352
#define SO_01   1276
#define SO_01_H 1199
#define LA_01   1136
#define LA_01_H 1073
#define TI_01   1012
#define DO_02   956
#define DO_02_H 909
#define RE_02   851
#define RE_02_H 804
#define MI_02   758
#define FA_02   716
#define FA_02_H 676
#define SO_02   638
#define SO_02_H 602
#define LA_02   568
#define LA_02_H 536
#define TI_02   506
#define DO_03   478
#define DO_03_H 450
#define RE_03	425
#define RE_03_H 401
#define MI_03	378

#define F_CLK       16000000L //클럭
#define F_SCALER	8 //프리스케일러
#define BEAT_1_32	42
#define BEAT_1_16	86
#define BEAT_1_8	170
#define BEAT_1_4	341
#define BEAT_1_2	682
#define BEAT_1		1364

extern int wash_complete;
extern volatile int buzzer_button;
extern volatile int buzzer_delay;
extern volatile int buzzer_timer;
extern volatile int get_button_timer;
extern int get_button_press_detector;

extern void init_button();		// BTN 초기화

// Timer3 위상교정 PWM
void init_buzzer()
{
	DDRB |= 0x20;   // PWM CHANNEL  OC1A(PB5) 출력 모드로 설정 한다.
	TCCR1A = (1<<COM1A0); // COM3A0 : 비교일치시 PE3 출력 반전 (P328 표14-6 참고)
	TCCR1B = (1<<WGM12) | (1<<CS11);   // WGM32 : CTC 4(P327 표14-5) CS31: 8분주(P318)
	// CTC mode : 비교일치가 되면 카운터는 reset되면서 PWM 파형 출력 핀의 출력이 반전 됨.
	// 위상교정 PWM mode4  CTC 분주비8  16000000/8 ==> 2,000,000HZ(2000KHZ) :
	// up-dounting: 비교일치시 LOW, down-counting시 HIGH출력
	// 1/2000000 ==> 0.0000005sec (0.5us)
	// P599 TOP 값 계산 참고
	// fPWM(PWM주파수) = fOSC(16M) / ( 2(up.down)x N(분주율)xTOP )
	// TOP =  fOSC(16M) / (  2(up.down)x N(분주율)x 원하는주파수)
	TCCR1C = 0;  // P328 그림 14-11 참고
	OCR1A = 0;   // 비교 일치값을 OCR3A에 넣는다.
	return;
}

void button_buzzer_off()
{
	if(get_button_press_detector && get_button_timer >= 200)
	{
		get_button_press_detector = 0;
		OCR1A = 0;
	}
}

void button_buzzer_on()
{
	get_button_press_detector = 1;
	get_button_timer = 0;
	OCR1A = 650;
}

void complete_buzzer()		
{
	static char state1 = 0;
	static char state2 = 0;

	if(wash_complete)
	{
		if(buzzer_delay >= 500)
		{
			buzzer_delay = 0;
			state1 = !state1;
			if(state1)
			{
				if(buzzer_timer >= 125)
				{
					buzzer_timer = 0;
					state2 = !state2;
					if(state2)
					{
						OCR1A = 378;
					}
					else
					OCR1A = 0;
				}
			}
			else
				OCR1A = 0;
		}
		
	}
	else
	{
		state1 = 0;
		state2 = 0;
	}
}

