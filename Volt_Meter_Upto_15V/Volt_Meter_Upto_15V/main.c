/*
 * Volt_Meter_Upto_15V.c
 *
 * Created: 2/10/2018 10:46:59 AM
 * Author : MD MASUM BILLAH
 * The code is only for educational purpose and is written by MD MASUM BILLAH. May be it will help you.
 */ 


#define F_CPU 8000000UL
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include "lcd.h"

char line[16];
float adc_value = 0;
float adc_volt = 0;


void adc_init(void)
{
	ADMUX |= (1<<REFS0);
	ADMUX &= ~(1<<REFS1);
	
	ADCSRA &= ~(1<<ADPS0);
	ADCSRA |= (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1);
}

uint16_t adc_read(void)
{
	
	ADMUX |= (1<<MUX0);
	ADCSRA |= (1<<ADSC);
	return ADCW;
}


int main(void)
{
	LCDInit();
	
	adc_init();
	sprintf(line," Value:");
	LCDGotoXY(1,1);
	LCDString(line);
	sprintf(line," Volt:");
	LCDGotoXY(1,2);
	LCDString(line);
	
	
	while(1)
	{
		adc_value = adc_read();
		adc_volt = ((adc_value*15.0)/1024);
		sprintf(line,"%.2f",adc_value);
		LCDGotoXY(11,1);
		LCDString(line);
		sprintf(line,"%.2f",adc_volt);
		LCDGotoXY(11,2);
		LCDString(line);
		_delay_ms(50);
		
		
	}
}

