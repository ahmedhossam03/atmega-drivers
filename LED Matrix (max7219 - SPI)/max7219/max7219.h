#ifndef MAX7219_H_
#define MAX7219_H_

#include "../spi/spi.h"
#include "util/delay.h"

#define MAX7219_REG_NO_OP               0x00
#define MAX7219_REG_DECODE_MODE			0x09
#define MAX7219_REG_INTENSITY			0x0A
#define MAX7219_REG_SCAN_LIMIT			0x0B
#define MAX7219_REG_SHUTDOWN			0x0C
#define MAX7219_REG_DISPLAY_TEST		0x0F

void max7219_init();
void max7219_send_cmd(unsigned char, unsigned char);
void max7219_scroll_chars(unsigned char[], unsigned char);

#endif
