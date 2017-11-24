#include <msp430.h>
#include <legacymsp430.h>
// msp430g2553

char counter = 0;

interrupt(TIMER0_A0_VECTOR) time_out(void) {
	counter++;
	P1OUT = counter;
	P2OUT = counter; 
}

int main(void)
{
	WDTCTL = WDTPW + WDTHOLD;
	BCSCTL1 = CALBC1_1MHZ;
	DCOCTL = CALDCO_1MHZ;
	BCSCTL2 |= DIVS_3;
	P1DIR |= 0xFF;
	P1OUT = 0x00;
	P2DIR |= 0xF;
	P2OUT = 0x0;
	
	//timer
	CCTL0 = CCIE;
	CCR0 = 32768;
	TACTL = TASSEL_2 + MC_1;
		
	eint();
	
	while(1);
	return 0;
}
