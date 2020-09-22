#include "servo.h"

void servo_init()
{
	//initialize timer 1 for servo pwm
	tmr1_init(TMR1_MODE_FAST_PWM_OCR_TOP,	//fast pwm mode, with top ocr
			  TMR1_OCRC,					//servo will be connected to ocr output
			  TMR1_FPWM_NON_INVERTING,		//clear on compare
			  TMR1_ICU_DIS,					//no capture
			  TMR1_OVERFLOW_INT_DIS,		//no overflow interrupt
			  TMR1_COMPARE_INT_DIS);		//no compare interrupt
	//servo work on 20khz, period every 20000ms
	tmr1_set_ocr(TMR1_OCRA, 19999);
	//the servo works from 0 to 180 so the neutral position is at 90
	//0 = 600us, 180 = 2400us, 90 = 1500us
	tmr1_set_ocr(TMR1_OCRC, 1499);
	//start timer
	tmr1_start_timer(TMR1_PRESCALER_8);
}

void servo_go_to_angle(unsigned char angle)
{
	unsigned short angle_ocr_val = 0;
	if(angle < 0 || angle > 180)
	{
		//out of boundary, do nothing
	}
	else if(angle >= 0 && angle <= 180)
	{
		angle_ocr_val = ( (angle * 1800UL) / 180 ) + 599;
		tmr1_set_ocr(TMR1_OCRC, angle_ocr_val);
	}
}
