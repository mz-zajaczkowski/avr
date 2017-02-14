/*
 * main.c
 *
 *  Created on: Feb 2, 2017
 *      Author: mizo
 */
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <math.h>


int main(void)
{
	DDRB |= (1 << PB0); // output on PB0
	TCCR0A = (1 << COM0A1) | (1 << WGM00); //Phase-correct PWM
	TCCR0B = (1 << CS01); // clock with prescaler CLK/8

	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (0 << ADPS0); // prescaler = 64

	ADMUX  |= (0 << REFS1) | (0 << REFS0); // AVCC as reference voltage
	ADMUX  |= (1 << ADLAR); // left adjust ADC conversion result, now we need only ADCH to be read
	ADMUX  |= (0 << MUX3) | (0 << MUX2) | (1 << MUX1) | (0 << MUX0); // use ADC2 for input (PB4)


	ADCSRA |= (1 << ADEN); // ADC enable
	ADCSRA |= (1 << ADSC); // ADC start conversions

	while(1)
	{

		if (ADCH < 0)
		{
			OCR0A = 0;
			_delay_ms(10);
		}
		else if(ADCH > 255)
		{
			OCR0A = 255;
			_delay_ms(10);
		}
		else
		{
			OCR0A = ADCH;
			_delay_ms(10);
		}
		ADCSRA |= (1 << ADSC);
	}

	return 0;
}

