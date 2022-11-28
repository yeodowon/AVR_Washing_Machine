/*
 * FAN.c
 *
 * Created: 2022-08-13 오후 10:48:06
 *  Author: ehs19
 */ 
#include "MAIN.h"

extern int set_reset;
extern int set_mode;
extern int manual_mode;
extern int run_stop;

extern int wash_time;
extern int rinse_time;
extern int spindry_strength;

extern int water_time;
extern int spindry_time;

extern volatile int machine_s_timer;

extern volatile int fan_timer;

void init_fan()
{
	DDRE |= ( 1 << 0) | ( 1 << 2) | ( 1 << 5);  // PE.0 PE.2 PE5 출력 모드로 설정
	
	// 모드5 : 8비트고속PWM모드 timer 3
	TCCR3A |= (1 << WGM30);
	TCCR3B |= (1 << WGM32);
	
	// 비반전 모드 TOP: 0xff 비교일치값 : OCR3C : PE5
	TCCR3A |= (1 << COM3C1);
	
	// 분주비 64  16000000/64  ==> 250000HZ(250KHZ)
	// 256 / 250000 ==> 1.02ms
	// 127 / 250000 ==> 0.5ms
	TCCR3B |= ( 1 << CS31)  | (1 << CS30);   // 분주비 64
	// 1600000HZ / 64분주 ==> 250000HZ (250KHZ)
	//
	
	OCR3C=0;  // PORTE.5
}

void fan_active()
{
	static char wash_state = 0;
	static char rinse_state = 0;
	
	if(set_reset == ACTIVE && run_stop == RUN)		// 세탁기 동작 중 
	{
		if(water_time > 0 && rinse_time > 0)
		{
			if(machine_s_timer >= 0 && machine_s_timer < water_time)
			{
				OCR3C = 0;
				if(machine_s_timer < water_time - 2)
					fan_timer = 0;
			}
			else if(machine_s_timer >= water_time && machine_s_timer < (water_time + wash_time))
			{
				if(fan_timer > 2000)		// 2초
				{
					fan_timer = 0;
					wash_state = !wash_state;
					if(wash_state)
					{
						// 정회전 PE2 : 0 / PE0 : 1
						PORTE &= 0b11111011;
						PORTE |= 0b00000001;
						OCR3C = 120;
					}
					else
					{
						// 역회전 PE2 : 1 / PE0 : 0
						PORTE &= 0b11111110;
						PORTE |= 0b00000100;
						OCR3C = 120;
					}
				}
				
			}
			else if(machine_s_timer >= water_time + wash_time && machine_s_timer < wash_time + 2*water_time)
			{
				OCR3C = 0;
			}
			else if(machine_s_timer >= wash_time + 2*water_time && machine_s_timer < wash_time + 3*water_time)
			{
				OCR3C = 0;
				if(machine_s_timer < wash_time + 3*water_time - 2)
					fan_timer = 0;
			}
			else if(machine_s_timer >= wash_time + 3*water_time && machine_s_timer < wash_time + 3*water_time + rinse_time)
			{
				if(fan_timer > 2000)		// 2초
				{
					fan_timer = 0;
					rinse_state = !rinse_state;
					if(rinse_state)
					{
						// 정회전 PE2 : 0 / PE0 : 1
						PORTE &= 0b11111011;
						PORTE |= 0b00000001;
						OCR3C = 100;
					}
					else
					{
						// 역회전 PE2 : 1 / PE0 : 0
						PORTE &= 0b11111110;
						PORTE |= 0b00000100;
						OCR3C = 100;
					}
				}
			}
			else if(machine_s_timer >= wash_time + 3*water_time + rinse_time && machine_s_timer < wash_time + 4*water_time + rinse_time)
			{
				OCR3C = 0;
			}
			else if(machine_s_timer >= wash_time + 4*water_time + rinse_time && machine_s_timer < wash_time + 4*water_time + rinse_time + spindry_time)
			{
				if(spindry_strength == 1)
				{
					PORTE &= 0b11111011;
					
					
					PORTE |= 0b00000001;
					OCR3C = 100;
				}
				else if(spindry_strength == 2)
				{
					PORTE &= 0b11111011;
					PORTE |= 0b00000001;
					OCR3C = 175;
				}
				else if(spindry_strength == 3)
				{
					PORTE &= 0b11111011;
					PORTE |= 0b00000001;
					OCR3C = 250;
				}
				
			}
			else if(machine_s_timer >= wash_time + 4*water_time + rinse_time + spindry_time)
			{
				fan_timer = 0;
				wash_state = 0;
				rinse_state = 0;
				OCR3C = 0;
			}
		}
		
		else          // 건조만 하는 경우 (water_time = 0 & rinse_time = 0)
		{
			if(machine_s_timer >= 0 && machine_s_timer < spindry_time)
			{
				if(spindry_strength == 1)
				{
					PORTE &= 0b11111011;
					PORTE |= 0b00000001;
					OCR3C = 100;
				}
				else if(spindry_strength == 2)
				{
					PORTE &= 0b11111011;
					PORTE |= 0b00000001;
					OCR3C = 175;
				}
				else if(spindry_strength == 3)
				{
					PORTE &= 0b11111011;
					PORTE |= 0b00000001;
					OCR3C = 250;
				}
			}
			else if(machine_s_timer >= spindry_time)
			{
				fan_timer = 0;
				wash_state = 0;
				rinse_state = 0;
				OCR3C = 0;
			}
		}
	}
	else if (set_reset == ACTIVE && run_stop == STOP)		// 세탁기 일시 정지
	{
		OCR3C = 0;
	}
}