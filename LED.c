/*
 * LED.c
 *
 * Created: 2022-08-14 오후 11:33:56
 *  Author: ehs19
 */ 

#include "MAIN.h"

extern int set_reset;
extern int set_mode;
extern int manual_mode;
extern int run_stop;

extern int water_time;
extern int rinse_time;
extern int machine_s_timer;
extern int wash_time;
extern int spindry_time;
extern int buzzer_time;

void LED_control()
{

	if(set_reset == ACTIVE && run_stop == RUN)
	{
		if(water_time > 0 && rinse_time > 0)
		{
			if(machine_s_timer >= 0 && machine_s_timer < water_time)
			{
				PORTA = 0b00000001; //세제쪽 급수
			}
			else if(machine_s_timer >= water_time && machine_s_timer < (water_time + wash_time))
			{
				PORTA = 0b00001000; //세탁중
			}
			else if(machine_s_timer >= water_time + wash_time && machine_s_timer < wash_time + 2*water_time)
			{
				PORTA = 0b00000100;//세탁 후 배수
			}
			else if(machine_s_timer >= wash_time + 2*water_time && machine_s_timer < wash_time + 3*water_time)
			{
				PORTA = 0b00000001; //세탁 후 급수
			}
			else if(machine_s_timer >= wash_time + 3*water_time && machine_s_timer < wash_time + 3*water_time + rinse_time)
			{
				PORTA = 0b00100000; // 헹굼
			}
			else if(machine_s_timer >= wash_time + 3*water_time + rinse_time && machine_s_timer < wash_time + 4*water_time + rinse_time)
			{
				PORTA = 0b00000100; // 헹굼 후 배수
			}
			else if(machine_s_timer >= wash_time + 4*water_time + rinse_time && machine_s_timer < wash_time + 4*water_time + rinse_time + spindry_time)
			{
				PORTA = 0b10000000; // 탈수
			}
			else if(machine_s_timer >= wash_time + 4*water_time + rinse_time + spindry_time && machine_s_timer < wash_time + 4*water_time + rinse_time + spindry_time + buzzer_time)
			{
				PORTA = 0b10101000; // 세탁 완료후 부저 울림
			}
		}
		
		else          // 건조만 하는 경우 (water_time = 0 & rinse_time = 0)
		{
			if(machine_s_timer >= 0 && machine_s_timer < spindry_time)
			{
				PORTA = 0b10000000; // 건조중
			}
			else if(machine_s_timer >= spindry_time && machine_s_timer < spindry_time + buzzer_time)
			{
				PORTA = 0b10101000; // 건조 완료 후 부저 울림
			}
		}
	}
}