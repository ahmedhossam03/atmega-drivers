#include "dc_motor.h"

void dc_motor_init(unsigned char initial_duty_cycle)
{
	//define motor pins as output
	DC_MOTOR_DIRC |= (1 << DC_MOTOR_PIN_RED) | (1 << DC_MOTOR_PIN_BLK);
	//set direction assuming red is high and black is low for clockwise
	DC_MOTOR_PORT |= (1 << DC_MOTOR_PIN_RED);
	DC_MOTOR_PORT &= ~(1 << DC_MOTOR_PIN_BLK);
	//initialize timer0
	tmr0_init(TMR0_MODE_FAST_PWM,
			  TMR0_FPWM_NON_INVERTING,
			  TMR0_OVERFLOW_INT_DIS,
			  TMR0_COMPARE_INT_DIS);
	//start timer, 1 tick = 1 us
	tmr0_start_timer(TMR0_PRESCALER_1024);
	//set duty cycle initially
	dc_motor_change_duty_cycle(initial_duty_cycle);
}

void dc_motor_change_duty_cycle(unsigned char duty_cycle)
{
	tmr0_set_duty_cycle(duty_cycle);
}

void dc_motor_change_direction()
{
	//save duty cycle
	unsigned char duty_cycle_value = OCR0;
	//stop motor
	dc_motor_change_duty_cycle(0);
	//toggle motor pins
	DC_MOTOR_PORT ^= (1 << DC_MOTOR_PIN_RED);
	DC_MOTOR_PORT ^= (1 << DC_MOTOR_PIN_BLK);
	//set back to prev duty cycle
	dc_motor_change_duty_cycle(duty_cycle_value);
}

void dc_motor_stop()
{
	dc_motor_change_duty_cycle(0);
}

void dc_motor_restart(unsigned char restart_duty_cycle)
{
	dc_motor_change_duty_cycle(restart_duty_cycle);
}
