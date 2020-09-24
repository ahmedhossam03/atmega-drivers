#include "ultrasonic.h"

unsigned char steps = 0;
unsigned char overflow_counter = 0;
unsigned short first_capture_time = 0;
unsigned short secnd_capture_time = 0;

static void ultrasonic_icu_callback();
static void ultrasonic_ovf_callback();

void ultrasonic_init()
{
	//initialize trig pin as output
	ULTRASONIC_TRIG_DIRC |= (1 << ULTRASONIC_TRIG_PIN);
	//initialize timer
	tmr1_init(TMR1_MODE_NORMAL, 
			  TMR1_DISCONNECT_OCR, 
			  TMR1_DISCONNECT_OCR, 
			  TMR1_ICU_EN_RISING, 
			  TMR1_OVERFLOW_INT_EN, 
			  TMR1_COMPARE_INT_DIS);
	//start timer
	tmr1_start_timer(TMR1_PRESCALER_8);
	//function for icu & overflow interrupt
	tmr1_capture_isr_callback(ultrasonic_icu_callback);
	tmr1_overflow_isr_callback(ultrasonic_ovf_callback);
}

void ultrasonic_send_pulse()
{
	if(steps == 0)
	{
		//set trig pin for 10us then clear it
		ULTRASONIC_TRIG_PORT |= (1 << ULTRASONIC_TRIG_PIN);
		_delay_us(10);
		ULTRASONIC_TRIG_PORT &= ~(1 << ULTRASONIC_TRIG_PIN);
		//reset overflow counter
		overflow_counter = 0;
		//make input capture edge rising
		tmr1_change_capture_edge(TMR1_ICU_EN_RISING);
	}
}

unsigned short ultrasonic_get_distance_unblocking()
{
	unsigned int travel_time = 0;
	unsigned short distance = 0;
	if(steps == 2)
	{
		//get travel time
		travel_time = (secnd_capture_time - first_capture_time) + (overflow_counter * 65535);
		//get distance, d = sound_speed / (travel_time) * 2, simplified in the eqn below
		distance = travel_time / 58;
		//move to step 0
		steps = 0;
	}
	return distance;
}

unsigned short ultrasonic_get_distance_blocking()
{
	//send pulse
	ultrasonic_send_pulse();
	//wait until a pulse is received in the icu
	while(steps < 2)
	{
		//this delay is the maximum time for a pulse to and comeback
		//this should be used as well if you're using the unblocking function and the send pulse separately
		_delay_ms(25);
	}
	//calculate distance and return it
	return ultrasonic_get_distance_unblocking();
}

static void ultrasonic_icu_callback()
{
	if(steps == 0)
	{
		//get the time of the first capture, rising edge of the ultrasonic
		first_capture_time = ICR1;
		//move to next step
		steps = 1;
		//change input capture trigger to falling
		tmr1_change_capture_edge(TMR1_ICU_EN_FALLING);
	}
	else if(steps == 1)
	{
		//get the time of the second capture, falling edge of the ultrasonic
		secnd_capture_time = ICR1;
		//move to next step
		steps = 2;
	}
}

static void ultrasonic_ovf_callback()
{
	overflow_counter++;
}
