#ifndef ENCODER_H_
#define ENCODER_H_

#ifndef	ENC_RES
	#define ENC_RES 10
#endif

#ifndef ENC_PIN_INPUT
	#define ENC_PIN_INPUT PIND
#endif

#ifndef ENC_PIN_INPUT_DIR
	#define ENC_PIN_INPUT_DIR DDRD
#endif

#define ENC_MODE_INT 0
#define ENC_MODE_PIN 1

void encoder_init(unsigned char, unsigned char, unsigned char);
unsigned short int encoder_get_angle(unsigned char);

#endif /* ENCODER_H_ */
