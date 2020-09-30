#include "spi.h"

void spi_init(unsigned char mode, unsigned char int_en, unsigned char data_order, unsigned char clock_rate)
{
	switch (mode)
	{
		case SPI_MODE_MASTER:
			//define slave select, clock and master out as output
			SPI_DIRC |= (1 << SPI_SS);
			SPI_DIRC |= (1 << SPI_SCK);
			SPI_DIRC |= (1 << SPI_MOSI);
			//define master in as input
			SPI_DIRC &= ~(1 << SPI_MISO);
			//set master bit
			SPCR |= (1 << MSTR);
		break;
		
		case SPI_MODE_SLAVE:
			//define slave select, clock and master out as input
			SPI_DIRC &= ~(1 << SPI_SS);
			SPI_DIRC &= ~(1 << SPI_SCK);
			SPI_DIRC &= ~(1 << SPI_MOSI);
			//define master in as output
			SPI_DIRC |= (1 << SPI_MISO);
			//clear master bit
			SPCR &= ~(1 << MSTR);
		break;
	}
	//enable interrupt
	if(int_en == SPI_INT_EN)
	{
		SPCR = (1 << SPIE);
	}
	//data order config
	if(data_order == SPI_DORD_LSB_FIRST)
	{
		SPCR |= (1 << DORD);
	}
	else if(data_order == SPI_DORD_MSB_FIRST)
	{
		SPCR &= ~(1 << DORD);
	}
	//clock rate
	if(clock_rate == SPI_CLK_4 || clock_rate == SPI_CLK_16 || clock_rate == SPI_CLK_64 || clock_rate == SPI_CLK_128)
	{
		SPCR |= (clock_rate << SPR0);
	}
	else if(clock_rate == SPI_CLK_2 || clock_rate == SPI_CLK_8 || clock_rate == SPI_CLK_32)
	{
		//set SPI2X
		SPSR |= (1 << SPI2X);
		SPCR |= (clock_rate << SPR0);
	}
	else
	{
		
	}
	//enable spi
	SPCR |= (1 << SPE);
}

unsigned char spi_mstr_tranceive(unsigned char data)
{
	//put data in data reg
	SPDR = data;
	//wait for flag to be zero, to make sure no operation is taking place
	while( !( SPSR & (1 << SPIF) ) );
	return SPDR;
}

unsigned char spi_slave_tranceive(unsigned char data)
{
	//check slave select is low
	if( ( (SPI_PIN >> SPI_SS) & 0x01 ) == 0 )
	{
		//put data in data reg
		SPDR = data;
		//wait for flag to be zero, to make sure no operation is taking place
		while( !( SPSR & (1 << SPIF) ) );
	}
	return SPDR;
}

ISR(SPI_STC_vect)
{
	
}
