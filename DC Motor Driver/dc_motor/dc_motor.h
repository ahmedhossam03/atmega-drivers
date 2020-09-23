#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "../tmr0/tmr0.h"

#define DC_MOTOR_PORT		  PORTA
#define DC_MOTOR_DIRC		  DDRA
#define DC_MOTOR_PIN_RED	0
#define DC_MOTOR_PIN_BLK	1

void dc_motor_init(unsigned char);
void dc_motor_change_duty_cycle(unsigned char);
void dc_motor_change_direction();
void dc_motor_stop();
void dc_motor_restart(unsigned char);

#endif
