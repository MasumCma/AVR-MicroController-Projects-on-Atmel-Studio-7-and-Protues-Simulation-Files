/*
 * slave.c
 *
 * Created: 9/19/2018 9:08:37 PM
 * Author : MD MASUM BILLAH
 */ 

#include <avr/io.h>
#include <stdio.h>
#include "lcd.h"

void SPI_SlaveInit(void)
{
	DDRB = (1<<6);
	SPCR = (1<<SPE);
}
char SPI_SlaveReceive(void)
{
	/* Wait for reception complete */
	while(!(SPSR & (1<<SPIF)))
	;
	/* Return Data Register */
	return SPDR;
}

char lcd[16];
int main(void)
{
    LCDInit();
	SPI_SlaveInit();
	
	sprintf(lcd,"Receiving ");
	LCDGotoXY(1,1);
	LCDString(lcd);
	
	int i;
    while (1) 
    {
		i = SPI_SlaveReceive();
		sprintf(lcd,"%d ",i);
		LCDGotoXY(13,1);
		LCDString(lcd);
		i++;
		_delay_ms(500);
    }
}

