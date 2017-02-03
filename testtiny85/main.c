/*
 * main.c
 *
 *  Created on: Feb 2, 2017
 *      Author: mizo
 */
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB |= (1<<PB0); // output on PB0
	TCCR0A = (1 << COM0A1) | (1 << WGM00); //Phase-correct PWM
	TCCR0B = (1 << CS01); // clock with prescaler CLK/8
	while(1)
	{
		_delay_ms(200);
		OCR0A = 0x10; // set analog value
		_delay_ms(200);
		OCR0A = 0x30;
		_delay_ms(200);
		OCR0A = 0x50;
		_delay_ms(200);
		OCR0A = 0xA0;
	}

	return 0;
}

