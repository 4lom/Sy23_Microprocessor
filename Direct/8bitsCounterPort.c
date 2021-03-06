#include <msp430.h>
#include <legacymsp430.h>
// msp430g2553

void write_on_PORTA(char value);

void delay(unsigned int n)
{
	unsigned int i;
	for(i = 0; i < n; i++);
}

int main(void)
{
	WDTCTL = WDTPW + WDTHOLD;
	BCSCTL1 = CALBC1_1MHZ;
	BCSCTL2 |= DIVS_3;
	P1DIR |= 0xFF;
	P1OUT = 0x00;
	P2DIR |= 0xF;
	P2OUT = 0x0;
	
	// 8 bits counter
	char counter = 0;
	
	while(1)
	{
		counter++;
		write_on_PORTA(counter);
		delay(60000);
		
		
	}
	return 0;
}

// Function to simplify the assignment of values on port A
void write_on_PORTA(char value)
{
	P1OUT = (P1OUT & 0x0F) | (value & 0xF0);
	P2OUT = (P2OUT & 0xF0) | (value & 0x0F); 
}