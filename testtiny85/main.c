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

static const double map_factor = 256/1024;

double map_adc_to_pwm(uint8_t adcval)
{
	return map_factor * (1024 - adcval);
}

int main(void)
{
	DDRB |= (1 << PB0); // output on PB0
	TCCR0A = (1 << COM0A1) | (1 << WGM00); //Phase-correct PWM
	TCCR0B = (1 << CS01); // clock with prescaler CLK/8

	ADCSRA |= (0 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // prescaler = 64

	ADMUX  |= (1 << REFS0); // AVCC as reference voltage
	ADMUX  |= (1 << ADLAR); // left adjust ADC conversion result, now we need only ADCH to be read
	ADMUX  |= (0 << MUX3) | (0 << MUX2) | (1 << MUX1) | (0 << MUX0); // use ADC2 for input (PB4)

	ADCSRA |= (1 << ADFR); // free-running mode
	ADCSRA |= (1 << ADEN); // ADC enable
	ADCSRA |= (1 << ADSC); // ADC start conversions

	uint8_t PWM_val = 0u;
	uint8_t adc_val = 0u;
	while(1)
	{
		if (ADCH < 255)
		{
		  double adc_mapped = map_adc_to_pwm(ADCH);
		  PWM_val = floor(adc_mapped + 0.5);
		  if (0u > PWM_val)
		  	PWM_val = 0u;
		  else if (255u < PWM_val)
		  	PWM_val = 255u;
		  OCR0A = PWM_val;
		  _delay_ms(10);
		}
	}

	return 0;
}

