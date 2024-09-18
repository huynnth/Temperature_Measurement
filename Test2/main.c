#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "LCD.h"

#define DEGREE_SYMBOL 0xDF

void ADC_Init(){
	ADMUX = (1 << REFS0);             /* Vref: Avcc, ADC channel: 0 */
	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); /* Ena
	
	
	ble ADC, with freq/128  */
}

int ADC_Read(int channel)
{
	ADMUX &= 0xF0;                    /* Clear the previous channel selection */
	ADMUX |= channel & 0x0F;          /* set input channel to read */
	ADCSRA |= (1<<ADSC);              /* Start ADC conversion */
	while (ADCSRA & (1 << ADSC));     /* Wait until end of conversion by polling ADC interrupt flag */
	return ADCW;                      /* Return ADC word */
}

int main()
{
	char Temperature[10];
	int Temp;

	LCD_Init();                 /* initialize 16x2 LCD*/
	ADC_Init();                 /* initialize ADC*/
	LCD_Clear();
	LCD_String_xy(1, 0, "Nhiet do:");

	while(1)
	{
		_delay_ms(1000);
		Temp = (ADC_Read(7) * 5.0 / 1024.0) * 100.0;           /* convert ADC value to temperature in Celsius */
		sprintf(Temperature, "%d%cC", 70-Temp, DEGREE_SYMBOL); /* format temperature value as a string */
		LCD_String_xy(1, 12, Temperature);
		_delay_ms(500);
	}
	return 0;
}
