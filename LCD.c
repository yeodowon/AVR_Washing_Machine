/*
 * LCD.c
 *
 * Created: 2022-08-13 오후 4:33:08
 *  Author: ehs19
 */ 

#include "MAIN.h"

char sbuff[40];

extern volatile int lcd_display_clock;
extern volatile int machine_ms_timer;
extern volatile int machine_s_timer;

extern int set_reset;
extern int set_mode;
extern int manual_mode;
extern int run_stop;

extern int wash_time;
extern int rinse_time;
extern int spindry_strength;

extern volatile int buzzer_delay;
extern volatile int buzzer_timer;

int water_time = 5;
int spindry_time = 15;
int buzzer_time = 5;

extern int wash_complete;		// 세팅 혹은 세탁 중(0) , 세탁 완료(1)

void LCD_Display()
{
	if(set_reset == RESET)
	{
		if(lcd_display_clock > 100)
		{
			lcd_display_clock = 0;
			sprintf(sbuff, "Washing  Machine");
			I2C_LCD_write_string_XY(0, 0, sbuff);
			sprintf(sbuff, "Press Power BTN ");
			I2C_LCD_write_string_XY(1, 0, sbuff);
		}
	}
	
	else if(set_reset == SET && set_mode == AUTO)
	{
		if(lcd_display_clock > 100)
		{
			lcd_display_clock = 0;
			sprintf(sbuff, "Washing  Machine");
			I2C_LCD_write_string_XY(0, 0, sbuff);
			sprintf(sbuff, "MODE : Standard ");
			I2C_LCD_write_string_XY(1, 0, sbuff);
		}
	}
	
	else if(set_reset == SET && set_mode == MANUAL && manual_mode == WASH)
	{
		if(lcd_display_clock > 100)
		{
			lcd_display_clock = 0;
			sprintf(sbuff, "MODE : SELF WASH");
			I2C_LCD_write_string_XY(0, 0, sbuff);
			sprintf(sbuff, "Wash Time :  %d  ", wash_time);
			I2C_LCD_write_string_XY(1, 0, sbuff);
		}
	}
	
	else if(set_reset == SET && set_mode == MANUAL && manual_mode == RINSE)
	{
		if(lcd_display_clock > 100)
		{
			lcd_display_clock = 0;
			sprintf(sbuff, "MODE : SELF WASH");
			I2C_LCD_write_string_XY(0, 0, sbuff);
			sprintf(sbuff, "Rinse Time : %d  ", rinse_time);
			I2C_LCD_write_string_XY(1, 0, sbuff);
		}
	}
	
	else if(set_reset == SET && set_mode == MANUAL && manual_mode == SPINDRY)
	{
		if(lcd_display_clock > 100)
		{
			lcd_display_clock = 0;
			sprintf(sbuff, "MODE : SELF WASH");
			I2C_LCD_write_string_XY(0, 0, sbuff);
			switch(spindry_strength)
			{
				case 1:
					I2C_LCD_write_string_XY(1, 0, "Spin Level: LOW ");
				break;
				
				case 2:
					I2C_LCD_write_string_XY(1, 0, "Spin Level: MID ");
				break;
				
				case 3:
					I2C_LCD_write_string_XY(1, 0, "Spin Level: HIGH");
				break;
			}
			
		}
	}
	
	else if(set_reset == ACTIVE && run_stop == RUN)
	{
		if(water_time > 0 && rinse_time > 0)
		{
			if(machine_s_timer >= 0 && machine_s_timer < water_time)
			{
				if(lcd_display_clock > 100)
				{
					lcd_display_clock = 0;
					sprintf(sbuff, " SYSTEM RUNNING ");
					I2C_LCD_write_string_XY(0, 0, sbuff);
					sprintf(sbuff, "Wash Loading... ");
					I2C_LCD_write_string_XY(1, 0, sbuff);
				}
			}
			else if(machine_s_timer >= water_time && machine_s_timer < (water_time + wash_time))
			{
				if(lcd_display_clock > 100)
				{
					lcd_display_clock = 0;
					sprintf(sbuff, " SYSTEM RUNNING ");
					I2C_LCD_write_string_XY(0, 0, sbuff);
					sprintf(sbuff, "Washing....wait ");
					I2C_LCD_write_string_XY(1, 0, sbuff);
				}
			}
			else if(machine_s_timer >= water_time + wash_time && machine_s_timer < wash_time + 2*water_time)
			{
				if(lcd_display_clock > 100)
				{
					lcd_display_clock = 0;
					sprintf(sbuff, " SYSTEM RUNNING ");
					I2C_LCD_write_string_XY(0, 0, sbuff);
					sprintf(sbuff, "Rinse Loading.. ");
					I2C_LCD_write_string_XY(1, 0, sbuff);
				}
			}
			else if(machine_s_timer >= wash_time + 2*water_time && machine_s_timer < wash_time + 3*water_time)
			{
				if(lcd_display_clock > 100)
				{
					lcd_display_clock = 0;
					sprintf(sbuff, " SYSTEM RUNNING ");
					I2C_LCD_write_string_XY(0, 0, sbuff);
					sprintf(sbuff, "Rinse Loading.. ");
					I2C_LCD_write_string_XY(1, 0, sbuff);
				}
			}
			else if(machine_s_timer >= wash_time + 3*water_time && machine_s_timer < wash_time + 3*water_time + rinse_time)
			{
				if(lcd_display_clock > 100)
				{
					lcd_display_clock = 0;
					sprintf(sbuff, " SYSTEM RUNNING ");
					I2C_LCD_write_string_XY(0, 0, sbuff);
					sprintf(sbuff, "Rinsing....wait     ");
					I2C_LCD_write_string_XY(1, 0, sbuff);
				}
			}
			else if(machine_s_timer >= wash_time + 3*water_time + rinse_time && machine_s_timer < wash_time + 4*water_time + rinse_time)
			{
				if(lcd_display_clock > 100)
				{
					lcd_display_clock = 0;
					sprintf(sbuff, " SYSTEM RUNNING ");
					I2C_LCD_write_string_XY(0, 0, sbuff);
					sprintf(sbuff, "Spinning Loading.... ");
					I2C_LCD_write_string_XY(1, 0, sbuff);
				}
			}
			else if(machine_s_timer >= wash_time + 4*water_time + rinse_time && machine_s_timer < wash_time + 4*water_time + rinse_time + spindry_time)
			{
				buzzer_delay = 0;
				buzzer_timer = 0;
				if(lcd_display_clock > 100)
				{
					lcd_display_clock = 0;
					sprintf(sbuff, " SYSTEM RUNNING ");
					I2C_LCD_write_string_XY(0, 0, sbuff);
					sprintf(sbuff, "Spinning....wait");
					I2C_LCD_write_string_XY(1, 0, sbuff);
				}
			}
			else if(machine_s_timer >= wash_time + 4*water_time + rinse_time + spindry_time && machine_s_timer < wash_time + 4*water_time + rinse_time + spindry_time + buzzer_time)
			{
				wash_complete = 1;	// 세탁 혹은 건조 완료 (부저가 울림)
				if(lcd_display_clock > 100)
				{
					lcd_display_clock = 0;
					sprintf(sbuff, " Wash Complete !!!");
					I2C_LCD_write_string_XY(0, 0, sbuff);
					sprintf(sbuff, "Press Power BTN ");
					I2C_LCD_write_string_XY(1, 0, sbuff);
				}
			}
			else if(machine_s_timer >= wash_time + 4*water_time + rinse_time + spindry_time + buzzer_time)
			{
				wash_complete = 0;
				set_reset = RESET;
				not_display_fnd();
				OCR1A = 0;
				PORTA = 0x00;
			}
		}
		
		else          // 건조만 하는 경우 (water_time = 0 & rinse_time = 0)
		{
			if(machine_s_timer >= 0 && machine_s_timer < spindry_time)
			{
				buzzer_delay = 0;
				buzzer_timer = 0;
				if(lcd_display_clock > 100)
				{
					lcd_display_clock = 0;
					
					sprintf(sbuff, " SYSTEM RUNNING ");
					I2C_LCD_write_string_XY(0, 0, sbuff);
					sprintf(sbuff, "Spinning....wait");
					I2C_LCD_write_string_XY(1, 0, sbuff);
				}
			}
			else if(machine_s_timer >= spindry_time && machine_s_timer < spindry_time + buzzer_time)
			{
				wash_complete = 1;	// 세탁 혹은 건조 완료 (부저가 4초간 유지)
				if(lcd_display_clock > 100)
				{
					lcd_display_clock = 0;
					sprintf(sbuff, "Spin Complete!!!");
					I2C_LCD_write_string_XY(0, 0, sbuff);
					sprintf(sbuff, "Press Power BTN ");
					I2C_LCD_write_string_XY(1, 0, sbuff);
				}
			}
			else if(machine_s_timer >= spindry_time + buzzer_time)
			{
				wash_complete = 0;
				set_reset = RESET;
				not_display_fnd();
				OCR1A = 0;
				PORTA = 0x00;
			}
		}
	}
	else if (set_reset == ACTIVE && run_stop == STOP)
	{
		if(lcd_display_clock > 100)
		{
			lcd_display_clock = 0;
			sprintf(sbuff, "Washing  Machine");
			I2C_LCD_write_string_XY(0, 0, sbuff);
			sprintf(sbuff, "    PAUSE...      ");
			I2C_LCD_write_string_XY(1, 0, sbuff);
		}
	}
}