/*
 * main.c
 *
 *  Created on: Feb 2, 2017
 *      Author: mizo
 */
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

static const double map_factor = 256/1024;

int map_adc_to_pwm(double adcval)
{
	return map_factor * (1024 - adcval);
}

int main(void)
{
	DDRB |= (1<<PB0); // output on PB0
	TCCR0A = (1 << COM0A1) | (1 << WGM00); //Phase-correct PWM
	TCCR0B = (1 << CS01); // clock with prescaler CLK/8

	ADMUX =
	            (1 << ADLAR) |     // left shift result
	            (1 << REFS2) |     // Sets ref. voltage to 2.56V, bit 2
	            (1 << REFS1) |     // Sets ref. voltage to 2.56V, bit 1
	            (0 << REFS0) |     // Sets ref. voltage to 2.56V, bit 0
	            (0 << MUX3)  |     // use ADC2 for input (PB4), MUX bit 3
	            (0 << MUX2)  |     // use ADC2 for input (PB4), MUX bit 2
	            (1 << MUX1)  |     // use ADC2 for input (PB4), MUX bit 1
	            (0 << MUX0);       // use ADC2 for input (PB4), MUX bit 0
	ADCSRA =
	            (1 << ADEN)  |     // Enable ADC
	            (0 << ADPS2) |     // set prescaler to 64, bit 2
	            (1 << ADPS1) |     // set prescaler to 64, bit 1
	            (1 << ADPS0);      // set prescaler to 64, bit 0
	uint8_t PWM_val = 0u;
	uint8_t dir = 0u;
	while(1)
	{
		if (0u > PWM_val)
			PWM_val = 0u;
		else if (255u < PWM_val)
			PWM_val = 255u;
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

