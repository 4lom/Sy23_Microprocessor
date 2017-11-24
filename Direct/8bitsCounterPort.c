#include <msp430.h>
#include <legacymsp430.h>
// msp430g2553

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
	
	char counter = 0;
	
	while(1)
	{
		counter++;
		P1OUT = counter;
		P2OUT = counter; 
		delay(60000);
		
		
	}
	return 0;
}
