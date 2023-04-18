#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int main(void)
{
    DDRB  = 0x20; // (1<<PB5);   // B5 output: 00100000

    while (1)
    {
	_delay_ms(500);
    	PORTB = 0x20; // (1<<PB5);	// PB5 high
	_delay_ms(500);
    	PORTB = 0x00; // (0<<PB5);	// PB5 low
    }
}
