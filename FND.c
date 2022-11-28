/*
 * FND.c
 *
 * Created: 2022-08-14 오후 7:45:58
 *  Author: ehs19
 */ 

#include "FND.h"
#include "MAIN.h"

extern int set_reset;
extern int run_stop;
extern int machine_s_timer;
extern int water_time;
extern int wash_time;
extern int rinse_time;
extern int spindry_time;
extern int buzzer_time;

extern volatile int fnd_display_clock;


int digit_position=0;			// 출력할 자리수

void init_fnd()
{
	FND_DATA_DDR = 0xff;	// PC0 ~ PC7 까지 출력으로 설정
	FND_DIGHT_DDR |= 0b00011110;  // 4567만 1로 3210은 그대로 유지
	FND_DATA_PORT = ~0x00;  // Common Cathode FND를 ALL OFF
}

void not_display_fnd()
{
	switch(digit_position)
	{
		case 0:										 // 1의 자리(FND4)
		FND_DIGHT_PORT = 0b00000010;				 // 1의 자리 출력
		FND_DATA_PORT = ~0x00;						 // FND ALL OFF
		break;
		
		case 1:										 // 10의 자리(FND3)
		FND_DIGHT_PORT = 0b00000100;				 // 10의 자리 출력
		FND_DATA_PORT = ~0x00;						 // FND ALL OFF
		break;
		
		case 2:									     // 100의 자리(FND2)
		FND_DIGHT_PORT = 0b00001000;                 // 100의 자리 출력
		FND_DATA_PORT = ~0x00;						 // FND ALL OFF
		break;
		
		case 3:										 // 1000의 자리(FND1)
		FND_DIGHT_PORT = 0b00010000;				 // 1000의 자리 출력
		FND_DATA_PORT = ~0x00;						 // FND ALL OFF
		break;
		
	}
	digit_position++;      // 다음 표시할 자릿수
	digit_position %= 4;
}

void display_fnd(int time)
{
	unsigned char fnd_font[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x27, 0x7F, 0x67};   // Common Anode 0 ~ 9
	
	switch(digit_position)
	{
		case 0:										 // 1의 자리(FND4)
		FND_DIGHT_PORT = 0b00000010;				 // 1의 자리 출력
		FND_DATA_PORT = ~fnd_font[time%10];	 // 0 ~ 9초로 1초 단위로 출력 (Common Cathode -> ~(not) 사용
		break;
		
		case 1:										 // 10의 자리(FND3)
		FND_DIGHT_PORT = 0b00000100;				 // 10의 자리 출력
		FND_DATA_PORT = ~fnd_font[(time/10)%6]; // 10 ~ 60초로 10초 단위로 출력
		break;
		
		case 2:									     // 100의 자리(FND2)
		FND_DIGHT_PORT = 0b00001000;                 // 100의 자리 출력
		FND_DATA_PORT = ~(fnd_font[(time/60)%10] | 0x80);
		break;
		
		case 3:										  // 1000의 자리(FND1)
		FND_DIGHT_PORT = 0b00010000;				  // 1000의 자리 출력
		FND_DATA_PORT = ~fnd_font[(time/600)%6];
		break;
		
	}
	digit_position++;      // 다음 표시할 자릿수
	digit_position %= 4;
}

void display_stop()		// 일시 정지의 경우 "0000"을 FND에 출력한다.
{
	switch(digit_position)
	{
		case 0:						 // 1의 자리
		FND_DIGHT_PORT = 0b00000010; // 1의 자리 출력
		FND_DATA_PORT = ~0b00111111; // "0"
		break;
		
		case 1:						 // 10의 자리
		FND_DIGHT_PORT = 0b00000100; // 10의 자리 출력
		FND_DATA_PORT = ~0b00111111; // "0"
		break;
		
		case 2:						 // 100의 자리
		FND_DIGHT_PORT = 0b00001000; // 100의 자리 출력
		FND_DATA_PORT = ~0b00111111; // "0"
		break;
		
		case 3:						 // 1000의 자리
		FND_DIGHT_PORT = 0b00010000; // 1000의 자리 출력
		FND_DATA_PORT = ~0b00111111; // "0"
		break;
	}
	digit_position++;               // 다음 표시할 자릿수
	digit_position %= 4;
}

void display_complete()
{
	switch(digit_position)
	{
		case 0:						 // 1의 자리
		FND_DIGHT_PORT = 0b00000010; // 1의 자리 출력
		FND_DATA_PORT = ~0b00001111;
		break;
		
		case 1:						 // 10의 자리
		FND_DIGHT_PORT = 0b00000100; // 10의 자리 출력
		FND_DATA_PORT = ~0b00001001;
		break;
		
		case 2:						 // 100의 자리
		FND_DIGHT_PORT = 0b00001000; // 100의 자리 출력
		FND_DATA_PORT = ~0b00001001;
		break;
		
		case 3:						 // 1000의 자리
		FND_DIGHT_PORT = 0b00010000; // 1000의 자리 출력
		FND_DATA_PORT = ~0b00111001;
		break;
	}
	digit_position++;               // 다음 표시할 자릿수
	digit_position %= 4;
}

void display_active_fnd()
{
	if(set_reset == ACTIVE && run_stop == RUN)
	{
		if(water_time > 0 && rinse_time > 0)
		{
			if(machine_s_timer >= 0 && machine_s_timer < wash_time + 4*water_time + rinse_time + spindry_time)
			{
				display_fnd((wash_time + 4*water_time + rinse_time + spindry_time - machine_s_timer));
			}
			else if(machine_s_timer >= wash_time + 4*water_time + rinse_time + spindry_time)
			{
				display_complete();
			}
		}
		
		else          // 건조만 하는 경우 (water_time = 0 & rinse_time = 0)
		{
			if(machine_s_timer >= 0 && machine_s_timer < spindry_time)
			{
				display_fnd((spindry_time - machine_s_timer));
			}
			else if(machine_s_timer >= spindry_time)
			{
				display_complete();
			}
		}
	}
	else if (set_reset == ACTIVE && run_stop == STOP)
	{
		display_stop();
	}
}
