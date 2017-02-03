/*
 * main.c
 *
 *  Created on: Feb 2, 2017
 *      Author: mizo
 */
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

int main(void)
{
	DDRB |= (1<<PB0); // output on PB0
	TCCR0A = (1 << COM0A1) | (1 << WGM00); //Phase-correct PWM
	TCCR0B = (1 << CS01); // clock with prescaler CLK/8

	ADCSRA |= (1 << ADEN); //ADC enable
	uint8_t PWM_val = 0u;
	uint8_t dir = 0u;
	while(1)
	{
		if ((0u == PWM_val) || (255u == PWM_val))
			dir ^= 0x01;
		OCR0A = PWM_val;
		_delay_ms(10);
		if (dir)
		{
			PWM_val++;
		}
		else
		{
			PWM_val--;
		}
	}

	return 0;
}

