#include <msp430.h>
#include <legacymsp430.h>
// msp430g2553

void write_on_PORTA(char value);

int unitecounter = 0;
int tencounter = 0;

char to_segments(int value)
{
	
	switch(value) {
		case 0:
		default:
			return 0b11110011;
		break;
		case 1:
			return 0b01100000;
		break;
		case 2:
			return 0b10110101;
		break;
		case 3:
			return 0b11110100;
		break;
		case 4:
			return 0b01100110;
		break;
		case 5:
			return 0b11010110;
		break;
		case 6:
			return 0b11010111;
		break;
		case 7:
			return 0b01110000;
		break;
		case 8:
			return 0b11110111;
		break;
		case 9:
			return 0b11110110;
		break;
	}
}

interrupt(TIMER0_A0_VECTOR) time_out(void) {
	if(unitecounter >= 9)
	{
		tencounter++;
		unitecounter = 0;
	}
	else
	{	
		unitecounter++;
	}
	write_on_PORTA(to_segments(tencounter) | 0b00001000);
	write_on_PORTA(to_segments(unitecounter));
	
		
}

int main(void)
{
	WDTCTL = WDTPW + WDTHOLD;
	BCSCTL1 = CALBC1_1MHZ;
	DCOCTL = CALDCO_1MHZ;
	BCSCTL2 |= DIVS_3;
	P1DIR |= 0xFF;
	P1OUT = 0x00;
	P2DIR |= 0x0F;
	P2OUT = 0x00;
	
	//timer
	CCTL0 = CCIE;
	CCR0 = 32768;
	TACTL = TASSEL_2 + MC_1;
		
	eint();
	
	while(1);
	return 0;
}

void write_on_PORTA(char value)
{
	P1OUT = (P1OUT & 0x0F) | (value & 0xF0);
	P2OUT = (P2OUT & 0xF0) | (value & 0x0F); 
}

void write_on_PORTB(char value)
{

}

