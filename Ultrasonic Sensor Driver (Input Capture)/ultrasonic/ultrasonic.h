#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#include "../tmr1/tmr1.h"
#include "util/delay.h"

#define ULTRASONIC_TRIG_DIRC		DDRD	
#define ULTRASONIC_TRIG_PORT		PORTD
#define ULTRASONIC_TRIG_PIN			7

void ultrasonic_init();
void ultrasonic_send_pulse();
unsigned short ultrasonic_get_distance_unblocking();
unsigned short ultrasonic_get_distance_blocking();

#endif
