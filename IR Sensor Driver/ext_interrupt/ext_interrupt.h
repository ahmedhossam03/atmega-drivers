#ifndef EXT_INTERRUPT_H_
#define EXT_INTERRUPT_H_

#define	EXTI_ON_CHANGE		1
#define EXTI_FALLING		  2
#define EXTI_RISING		    3

#ifndef EXTI_PULLUP_INPUT
	#define EXTI_PULLUP_INPUT	0
#endif

void exti_init(unsigned char);
void exti_onoff(unsigned char, unsigned char);
void exti_change_mode(unsigned char, unsigned char);
void exti_callback(void (*ptr_service_func)(void), unsigned char exti_select);

#endif /* EXT_INTERRUPT_H_ */
