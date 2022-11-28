/*
 * WASHING_MACHINE.c
 *
 * Created: 2022-08-13 오후 2:49:33
 * Author : KIM JUNG HOON
 */ 

#include "MAIN.h"

extern void LED_control();

extern void init_button();		// BTN 초기화
extern int get_button1();		// 전원 BTN
extern int get_button2();		// 자동 및 수동모드 BTN
extern int get_button3();		// 동작/일시정지 BTN
extern int get_button4();		// 세탁 BTN
extern int get_button5();		// 헹굼 BTN
extern int get_button6();		// 탈수 BTN

extern void I2C_LCD_init(void);		// I2C_LCD.c 에 있는 I2C_LCD_init 함수를 불러옴
extern void LCD_Display();

extern void init_fnd();
extern void display_active_fnd();
extern void not_display_fnd();
extern void display_complete();

extern void init_fan();
extern void fan_active();

extern void init_buzzer();
extern void button_buzzer_on();
extern void button_buzzer_off();
extern void button_buzzer();
extern void complete_buzzer();

volatile int lcd_display_clock = 0;		// lcd에 display하는 시간을 조절하는 변수
volatile int machine_ms_timer = 0;			// 물, 세제 넣고 다시 물 빼는 시간 2초
volatile int machine_s_timer = 0;

volatile int fnd_display_clock = 0;

volatile int fan_timer = 0;

volatile int buzzer_button = 0;
volatile int buzzer_delay = 0;
volatile int buzzer_timer = 0;
volatile int get_button_timer = 0;
int get_button_detector = 0;


volatile int machine_ms_timer_temp;
volatile int machine_s_timer_temp;

int set_reset = RESET;
int set_mode = AUTO;
int manual_mode = WASH;
int run_stop = READY;

int wash_time = 0;
int rinse_time = 0;
int spindry_strength = 1; // strength 1 ~ 3 (약 중 강)
extern int water_time;
extern int spindry_time;

int wash_complete = 0;		// 세팅 혹은 세탁 중(0) , 세탁 완료(1)

int get_button_press_detector = 0;

void mode_select();

// 약 1ms 마다 ISR(TIMER0_OVF_vect)로 들어온다.
ISR(TIMER0_OVF_vect)
{
	machine_ms_timer++;
	lcd_display_clock++;
	fnd_display_clock++;
	fan_timer++;
	get_button_timer++;
	buzzer_delay++;
	buzzer_timer++;
	
	
	if(machine_ms_timer >= 1000)
	{
		machine_ms_timer = 0;
		machine_s_timer++;
	}
	
	display_active_fnd();
	
}

void init_timer0()
{
	TCNT0 = 6;	// 정확히 1msec마다 인터럽트 하기 위해 정해진 값 (256-6 = 250)
	// 분주비를 64로 설정 -> 1msec 마다 인터럽트
	TCCR0 |= (1 << CS02) | (0 << CS01) | (0 << CS00);
	TIMSK |= (1 << TOIE0);
}

// 메인 함수
int main(void)
{
    init_button();
	I2C_LCD_init();
	init_fnd();
	init_buzzer();
	init_fan();
	init_timer0();
	sei();

	
	
	for (;;) 
    {
		
		button_buzzer_off();
		mode_select();
		LED_control();
		LCD_Display();
		fan_active();
		complete_buzzer();
	}

}
// 모드 선택 함수
void mode_select()
{
	if(set_reset == RESET)
	{
		if(get_button1())
		{
			button_buzzer_on();
			set_reset = SET;
			set_mode = AUTO;
			wash_time = 0;
			rinse_time = 0;
			spindry_strength = 1;
			not_display_fnd();
			
		}
	}
	else if(set_reset == SET)
	{
		if(set_mode == AUTO)
		{
			if(get_button1())
			{
				button_buzzer_on();
				set_reset = RESET;
				not_display_fnd();
			}
			else if(get_button2())
				button_buzzer_on();
			else if(get_button3())
			{
				button_buzzer_on();
				set_reset = ACTIVE;
				run_stop = RUN;
				machine_ms_timer = 0;
				machine_s_timer = 0;
				wash_time = 30;
				rinse_time = 15;
				spindry_strength = 2;
			}
			else if(get_button4())
			{
				button_buzzer_on();
				set_mode = MANUAL;
				manual_mode = WASH;
			}
			else if(get_button5())
			{
				button_buzzer_on();
				set_mode = MANUAL;
				manual_mode = RINSE;
			}
			else if(get_button6())
			{
				button_buzzer_on();
				set_mode = MANUAL;
				manual_mode = SPINDRY;
			}
		}
		else if(set_mode == MANUAL && manual_mode == WASH)
		{
			if(get_button1())
			{
				button_buzzer_on();
				set_reset = RESET;
				set_mode = AUTO;
				not_display_fnd();
			}
			else if(get_button2())
			{
				button_buzzer_on();
				set_mode = AUTO;
			}
			else if(get_button3())
			{
				button_buzzer_on();
				set_reset = ACTIVE;
				run_stop = RUN;
				machine_ms_timer = 0;
				machine_s_timer = 0;
			}
			else if(get_button4())
			{
				button_buzzer_on();
				wash_time += 10;
				if(wash_time > 50)
					wash_time = 0;
			}
			else if(get_button5())
			{
				button_buzzer_on();
				manual_mode = RINSE;
			}
			else if(get_button6())
			{
				button_buzzer_on();
				manual_mode = SPINDRY;
			}
		}
		else if(set_mode == MANUAL && manual_mode == RINSE)
		{
			if(get_button1())
			{
				button_buzzer_on();
				set_reset = RESET;
				set_mode = AUTO;
				manual_mode = WASH;
				not_display_fnd();
			}
			else if(get_button2())
			{
				button_buzzer_on();
				set_mode = AUTO;
			}
			else if(get_button3())
			{
				button_buzzer_on();
				set_reset = ACTIVE;
				run_stop = RUN;
				machine_ms_timer = 0;
				machine_s_timer = 0;
			}
			else if(get_button4())
			{
				button_buzzer_on();
				manual_mode = WASH;
			}
			else if(get_button5())
			{
				button_buzzer_on();
				rinse_time += 5;
				if(rinse_time > 30)
					rinse_time = 0;
			}
			else if(get_button6())
			{
				button_buzzer_on();
				manual_mode = SPINDRY;
				
			}
		}
		else if(set_mode == MANUAL && manual_mode == SPINDRY)
		{
			if(get_button1())
			{
				button_buzzer_on();
				set_reset = RESET;
				set_mode = AUTO;
				manual_mode = WASH;
				not_display_fnd();
			}
			else if(get_button2())
			{
				button_buzzer_on();
				set_mode = AUTO;
			}
			else if(get_button3())
			{
				button_buzzer_on();
				set_reset = ACTIVE;
				run_stop = RUN;
				machine_ms_timer = 0;
				machine_s_timer = 0;
			}
			else if(get_button4())
			{
				button_buzzer_on();
				manual_mode = WASH;
			}
			else if(get_button5())
			{
				button_buzzer_on();
				manual_mode = RINSE;
			}
			else if(get_button6())
			{
				button_buzzer_on();
				spindry_strength++;
				if(spindry_strength > 3)
					spindry_strength = 1;
			}
		}
	}
	else if(set_reset == ACTIVE && run_stop == RUN)
	{
		if(get_button1())
		{
			button_buzzer_on();
			set_reset = RESET;
			run_stop = READY;
			not_display_fnd();
			OCR3C = 0;
			wash_complete = 0;
		}
		else if(get_button3())
		{
			button_buzzer_on();
			run_stop = STOP;
			machine_ms_timer_temp = machine_ms_timer;
			machine_s_timer_temp = machine_s_timer;
		}
	}
	else if(set_reset == ACTIVE && run_stop == STOP)
	{
		if(get_button1())
		{
			button_buzzer_on();
			set_reset = RESET;
			run_stop = READY;
			not_display_fnd();
		}
		else if(get_button3())
		{
			button_buzzer_on();
			run_stop = RUN;
			machine_ms_timer = machine_ms_timer_temp;
			machine_s_timer = machine_s_timer_temp;
		}
	}
}