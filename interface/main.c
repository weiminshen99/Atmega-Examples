/**
 * \file main.c
 * \author Mark Moll (moll@isi.edu), Wei-Min Shen (weiminshen99@gmail.com)
 * \brief provide a menu interface for interactive testing w terminal
 * calibration functions
 */

#include <avr/wdt.h>
#include <stdio.h>

#define DEFAULT_UART 0
//#define BAUD     68 /* 9600 BAUD at 8 MHz XTAL*/
#define BAUD     25 /* 19200 BAUD at 8 MHz XTAL*/
//#define BAUD     12 /* 38400 BAUD at 8 MHz XTAL*/

#define soft_reset() { wdt_enable(WDTO_15MS); for(;;); }

void uart_putc(uint8_t uart, char c)
{
    if (uart == 0) {
    // UDRE bit tells that UDR is empty and ready to be written to.
    // UControlStatusReg(UCSR) contains control bits
        loop_until_bit_is_set(UCSR0A, UDRE);
        UDR0 = c;
    } else if (uart == 1) {
        loop_until_bit_is_set(UCSR1A, UDRE);
        UDR1 = c;
    }
}


//int def_putc(char ch) //handler for the printf
int def_putc(char ch, FILE *f) //handler for the printf
{
        uart_putc(DEFAULT_UART, ch);
        return ch;
}

/**
 * \brief character output routine for default UART called by stdio routines
 */
int def_getc() //handler for the printf
{
        //wait for new data in the receive buffer : its a FIFO of length 2
        while  (!(UCSR0A & _BV(RXC0))); 
        return UDR0;
}

char get_char() {
        char c;
        c = (char)def_getc();
        printf("%c\n\r",c);
        return c;
}

void initializeDebug(void)
{
        /*
         * enable UART0
         */
        UBRR0H = 0;//UBRRnH , UBRRnL are regs used to set the baud rate.
        UBRR0L = BAUD;
        UCSR0B = _BV(TXEN) | _BV(RXEN); /* enable transmitter and receiver */

        //extern FILE *fdevopen(int (*__put)(char, FILE*), int (*__get)(FILE*));
        fdevopen(def_putc, def_getc); //stdout is the UART0 TXD pin
}

int main() {

	char cmd;

    	initializeDebug();

	printf("\n\rOptions for tests:\n\r");
	printf("1. LED tests\n\r");
	printf("2. motor 0 test\n\r");
	printf("3. motor 1 test (slave only)\n\r");
	printf("4. 3D-ACC accelerometer test (master only)\n\r");
	printf("5. voltage/current sensor test (master only)\n\r");
	printf("6. radio test\n\r");
	printf("7. I2C receive test\n\r");
	printf("8. I2C send test\n\r");
	printf("9. FACE testing menu \n\r");
	printf("0. Calibration menu \n\r");
	printf("a. Combo test of LED, IV sensors, and accelerometer\n\r");
	printf("b. Combo IR self-loop test\n\r");
	printf("c. Test Mag Encoder (slave only)\n\r");
	printf("\n\rChoose a test:\n\r");
	cmd = get_char();
	switch(cmd) {
		case '1': printf("\n\r1 \n\r"); break;
		case '2': printf("\n\r2 \n\r"); break;
		case '3': printf("\n\r3 \n\r"); break;
		case 'a':
		case 'A': printf("\n\rA or a \n\r"); break;
		case 'b':
		case 'B': printf("\n\rB or b \n\r"); break;
		default: ;// do nothing
	}

        printf("\n\r\n\r******* Soft Reset *******\n\r");
	soft_reset();
}
