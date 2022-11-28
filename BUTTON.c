/*
 * BUTTON.c
 *
 * Created: 2022-08-13 오후 3:24:43
 *  Author: ehs19
 */ 

#include "BUTTON.h"

void init_button()
{
	LED_DDR = 0xFF;				// DDRA = 0xFF > A를 모두 출력으로 사용한다.
	BUTTON_DDR &= ~((1 << BUTTON1) | (1 << BUTTON2) | (1 << BUTTON3) | (1 << BUTTON4) | (1 << BUTTON5) | (1 << BUTTON6));		// DDRD를 input mode로 설정
	// 수정에 용이하도록 이와 같이 코딩
}



int get_button1()											// 1번 버튼(PD2)을 읽어오는 함수
{
	static uint8_t previous_state = 0;						// 버튼의 이전 상태 : 0 (OFF), 1 (ON)		// static : 함수를 나가더라도 마지막 상태를 유지
	static uint8_t current_state;							// uint8_t = unsigned char (char 형 -> 8bits)
	
	current_state = BUTTON_PIN & (1 << BUTTON1);			// 1번 버튼의 버튼 값을 읽어 온다. 버튼이 눌린 경우 0x10
	
	if(previous_state == 0 && current_state != 0)			// 버튼이 처음 눌러진 상태
	{
		_delay_ms(60);										// 노이즈가 지나가기를 기다린다. (60ms)
		previous_state = 1;									// 처음 눌러진 상태가 아니다.
		return 0;											// 눌러지긴 했지만 아직 아니다.
	}
	else if(previous_state == 1 && current_state == 0)		// 버튼이 완전히 눌렀다(previous_state == 1) 뗀 상태(current_state == 0)
	{
		previous_state = 0;
		_delay_ms(30);
		return 1;											// 완전히 눌렀다가 뗀 상태이다.
	}
	return 0;												// 아직 완전히 버튼을 눌렀다 떼지 않은 상태
}

int get_button2()											// 2번 버튼(PD3)을 읽어오는 함수
{
	static uint8_t previous_state = 0;						// 버튼의 이전 상태 : 0 (OFF), 1 (ON)		// static : 함수를 나가더라도 마지막 상태를 유지
	static uint8_t current_state;							// uint8_t = unsigned char (char 형 -> 8bits)
	
	current_state = BUTTON_PIN & (1 << BUTTON2);			// 2번 버튼의 버튼 값을 읽어 온다. 버튼이 눌린 경우 0x10
	
	if(previous_state == 0 && current_state != 0)			// 버튼이 처음 눌러진 상태
	{
		_delay_ms(60);										// 노이즈가 지나가기를 기다린다. (60ms)
		previous_state = 1;									// 처음 눌러진 상태가 아니다.
		return 0;											// 눌러지긴 했지만 아직 아니다.
	}
	else if(previous_state == 1 && current_state == 0)		// 버튼이 완전히 눌렀다(previous_state == 1) 뗀 상태(current_state == 0)
	{
		previous_state = 0;
		_delay_ms(30);
		return 1;											// 완전히 눌렀다가 뗀 상태이다.
	}
	return 0;												// 아직 완전히 버튼을 눌렀다 떼지 않은 상태
}

int get_button3()											// 3번 버튼(PD4)을 읽어오는 함수
{
	static uint8_t previous_state = 0;						// 버튼의 이전 상태 : 0 (OFF), 1 (ON)		// static : 함수를 나가더라도 마지막 상태를 유지
	static uint8_t current_state;							// uint8_t = unsigned char (char 형 -> 8bits)
	
	current_state = BUTTON_PIN & (1 << BUTTON3);			// 3번 버튼의 버튼 값을 읽어 온다. 버튼이 눌린 경우 0x10
	
	if(previous_state == 0 && current_state != 0)			// 버튼이 처음 눌러진 상태
	{
		_delay_ms(60);										// 노이즈가 지나가기를 기다린다. (60ms)
		previous_state = 1;									// 처음 눌러진 상태가 아니다.
		return 0;											// 눌러지긴 했지만 아직 아니다.
	}
	else if(previous_state == 1 && current_state == 0)		// 버튼이 완전히 눌렀다(previous_state == 1) 뗀 상태(current_state == 0)
	{
		previous_state = 0;
		_delay_ms(30);
		return 1;											// 완전히 눌렀다가 뗀 상태이다.
	}
	return 0;												// 아직 완전히 버튼을 눌렀다 떼지 않은 상태
}

int get_button4()											// 4번 버튼(PD5)을 읽어오는 함수
{
	static uint8_t previous_state = 0;						// 버튼의 이전 상태 : 0 (OFF), 1 (ON)		// static : 함수를 나가더라도 마지막 상태를 유지
	static uint8_t current_state;							// uint8_t = unsigned char (char 형 -> 8bits)
	
	current_state = BUTTON_PIN & (1 << BUTTON4);			// 4번 버튼의 버튼 값을 읽어 온다. 버튼이 눌린 경우 0x10
	
	if(previous_state == 0 && current_state != 0)			// 버튼이 처음 눌러진 상태
	{
		_delay_ms(60);										// 노이즈가 지나가기를 기다린다. (60ms)
		previous_state = 1;									// 처음 눌러진 상태가 아니다.
		return 0;											// 눌러지긴 했지만 아직 아니다.
	}
	else if(previous_state == 1 && current_state == 0)		// 버튼이 완전히 눌렀다(previous_state == 1) 뗀 상태(current_state == 0)
	{
		previous_state = 0;
		_delay_ms(30);
		return 1;											// 완전히 눌렀다가 뗀 상태이다.
	}
	return 0;												// 아직 완전히 버튼을 눌렀다 떼지 않은 상태
}

int get_button5()											// 5번 버튼(PD6)을 읽어오는 함수
{
	static uint8_t previous_state = 0;						// 버튼의 이전 상태 : 0 (OFF), 1 (ON)		// static : 함수를 나가더라도 마지막 상태를 유지
	static uint8_t current_state;							// uint8_t = unsigned char (char 형 -> 8bits)
	
	current_state = BUTTON_PIN & (1 << BUTTON5);			// 5번 버튼의 버튼 값을 읽어 온다. 버튼이 눌린 경우 0x10
	
	if(previous_state == 0 && current_state != 0)			// 버튼이 처음 눌러진 상태
	{
		_delay_ms(60);										// 노이즈가 지나가기를 기다린다. (60ms)
		previous_state = 1;									// 처음 눌러진 상태가 아니다.
		return 0;											// 눌러지긴 했지만 아직 아니다.
	}
	else if(previous_state == 1 && current_state == 0)		// 버튼이 완전히 눌렀다(previous_state == 1) 뗀 상태(current_state == 0)
	{
		previous_state = 0;
		_delay_ms(30);
		return 1;											// 완전히 눌렀다가 뗀 상태이다.
	}
	return 0;												// 아직 완전히 버튼을 눌렀다 떼지 않은 상태
}

int get_button6()											// 6번 버튼(PD7)을 읽어오는 함수
{
	static uint8_t previous_state = 0;						// 버튼의 이전 상태 : 0 (OFF), 1 (ON)		// static : 함수를 나가더라도 마지막 상태를 유지
	static uint8_t current_state;							// uint8_t = unsigned char (char 형 -> 8bits)
	
	current_state = BUTTON_PIN & (1 << BUTTON6);			// 6번 버튼의 버튼 값을 읽어 온다. 버튼이 눌린 경우 0x10
	
	if(previous_state == 0 && current_state != 0)			// 버튼이 처음 눌러진 상태
	{
		_delay_ms(60);										// 노이즈가 지나가기를 기다린다. (60ms)
		previous_state = 1;									// 처음 눌러진 상태가 아니다.
		return 0;											// 눌러지긴 했지만 아직 아니다.
	}
	else if(previous_state == 1 && current_state == 0)		// 버튼이 완전히 눌렀다(previous_state == 1) 뗀 상태(current_state == 0)
	{
		previous_state = 0;
		_delay_ms(30);
		return 1;											// 완전히 눌렀다가 뗀 상태이다.
	}
	return 0;												// 아직 완전히 버튼을 눌렀다 떼지 않은 상태
}