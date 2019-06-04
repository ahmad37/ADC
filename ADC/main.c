
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

void adc_init()
{
	// AREF = AVcc
	ADMUX = (1<<REFS0);
	
	// ADC Enable and prescaler of 128
	// 16000000/128 = 125000
	ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
}

uint16_t adc_read(uint8_t ch)
{
	// select the corresponding channel 0~7
	// ANDing with ’7? will always keep the value
	// of ‘ch’ between 0 and 7
	ch &= 0b00000111;  // AND operation with 7
	ADMUX = (ADMUX & 0xF8)|ch; // clears the bottom 3 bits before ORing
	
	// start single convertion
	// write ’1? to ADSC
	ADCSRA |= (1<<ADSC);
	
	// wait for conversion to complete
	// ADSC becomes ’0? again
	// till then, run loop continuously
	while(ADCSRA & (1<<ADSC));
	
	return (ADC);   //ADC IS THE RETURNED VALUE
	
	
	
	
/*
	while (!(ADCSRA & (1<<ADIF)));     / * Wait until end of conversion by polling ADC interrupt flag * /
	ADCSRA |= (1<<ADIF);               / * Clear interrupt flag * /
	_delay_ms(1);                      / * Wait a little bit * /
	return ADCW;                       / * Return ADC word * /
*/
}


int main(void)
{
    adc_init(); 
	
	DDRB |=(1<<PD3); // oc0 pin is o/p 
	TCCR0 = 0x61; // fast pwm - no prescaler - oc0 pin cleared on top  
	
	 
	
 

    while (1) 
    {
		OCR0= adc_read(0); 
		
    }
}

