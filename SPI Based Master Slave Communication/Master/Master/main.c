/*
 * SPI me.c
 *
 * Created: 9/19/2018 3:42:43 PM
 * Author : MD MASUM BILLAH
 */ 



#include <avr/io.h>
#include <stdio.h>
#include "lcd.h"

char lcd[16];
void SPI_Master_Init()
{
	DDRB |= (1<<4)|(1<<5)|(1<<7);
	SPCR |= (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}

void Master_Tx( unsigned char data)
{
	SPDR = data;
	while(!(SPSR & (1<<SPIF)));
}

int main(void)
{
	
	SPI_Master_Init();
	LCDInit();
	
	int count = 0;
	
	while (1)
	{
		Master_Tx(count);
		sprintf(lcd,"Sending Data: %d",count);
		LCDGotoXY(1,1);
		LCDString(lcd);
		count++;
		_delay_ms(500);
	}
   
	
}
