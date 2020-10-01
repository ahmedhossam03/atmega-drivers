#ifndef SPI_H_
#define SPI_H_

#ifndef F_CPU
	#define F_CPU 8000000UL
#endif

#include "avr/io.h"
#include "avr/interrupt.h"

#define SPI_DIRC		DDRB
#define SPI_PORT		PORTB
#define SPI_PIN			PINB

#define SPI_SS			PB0
#define SPI_SCK			PB1
#define SPI_MOSI		PB2
#define SPI_MISO		PB3

#define SPI_MODE_MASTER 0
#define SPI_MODE_SLAVE	1

#define SPI_INT_EN		1
#define SPI_INT_DIS		0

#define SPI_DORD_LSB_FIRST		1
#define SPI_DORD_MSB_FIRST		0

#define SPI_CLK_4				0
#define SPI_CLK_16				1
#define SPI_CLK_64				2
#define SPI_CLK_128				3
#define SPI_CLK_2				0
#define SPI_CLK_8				1
#define SPI_CLK_32				2

#define SPI_BEGIN_TRANSMITION	( SPI_PORT |= (1 << SPI_SS) )
#define SPI_END_TRANSMITION		( SPI_PORT &= ~(1 << SPI_SS) )

void spi_init(unsigned char, unsigned char, unsigned char, unsigned char);
unsigned char spi_mstr_tranceive(unsigned char);
unsigned char spi_slav_tranceive(unsigned char);
unsigned char spi_slav_tranceive_int(unsigned char);

#endif
