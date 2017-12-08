#include <msp430.h>
#include <legacymsp430.h>
#include <stdint.h>
// msp430g2553

void write_on_PORTA(char value);
char read_on_PORTB();
uint16_t convert_temperature(uint16_t);


//Counter which divide the timer frequency
int frequencedivider 	= 0;

//Unit and tenth counter
char unite_counter 	= 0;
char ten_counter	= 0;


volatile uint16_t temp;

//Boolean which save if the double 7 segments display show the unit(1) value or the tenth(0)
int unit_show 			= 1;

//Convert a unit value into 8 bits for the 7 segments display
char to_segments(char value)
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

interrupt(TIMER0_A1_VECTOR) time_out(void) {

	char unit_to_show = 0;
	char ten_to_show  = 0;
	if((read_on_PORTB() & 0x01) == 0)
	{
		if(frequencedivider == 1024)
		{
			if(unite_counter >= 9)
			{
				if(ten_counter >= 9)
				{
					ten_counter = 0;
				}
				else
				{
					ten_counter++;
				}
				unite_counter = 0;
			}
			else
			{	
				unite_counter++;
			}
			frequencedivider = 0;
		}
		else
		{
			frequencedivider++;
		}
		unit_to_show = unite_counter;
		ten_to_show  = ten_counter;
	}
	else
	{
		uint16_t temperature = convert_temperature(temp);
		unit_to_show = (temperature%10);
		ten_to_show  = (char)(((uint32_t)temperature*(uint32_t)0xCCCD) >> 16) >> 3;
	}
	if(unit_show == 0)
	{
		write_on_PORTA(to_segments(ten_to_show) | 0b00001000);
		unit_show = 1;
	}
	else
	{
		write_on_PORTA(to_segments(unit_to_show));
		unit_show = 0;
	}
}

int main(void)
{
	WDTCTL = WDTPW + WDTHOLD;
	// calibration source DCO
	BCSCTL1 = CALBC1_1MHZ;
	DCOCTL = CALDCO_1MHZ;
	// division de frequence par 1
	BCSCTL2 |= DIVS_1;
	P1DIR |= 0b11110110;
	P1OUT = 0x00;
	P2DIR |= 0b11001111;
	P2OUT = 0x0F;	
	
	// interruption sur valeur CCR0
	CCTL0 = CCIE | OUTMOD_4; // OUT0 for ADC10
	CCTL1 = CCIE;

	//ADC
	ADC10CTL0 = SREF_1 | ADC10SHT_3 | REFON | ADC10ON | ADC10IE;
	ADC10CTL1 = ADC10SSEL_0 | ADC10DIV_0 | INCH_10 | SHS_2 | CONSEQ_2;	
	ADC10CTL0 |= ENC ;
	
	//timer
	CCR0 = 10000;
	CCR1 = 512;
	TACTL = TASSEL_2 | MC_1 | TACLR;
		
	eint();
	
	while(1);
	return 0;
}

//Write the 8bits of PORTA
void write_on_PORTA(char value)
{
	P1OUT = (P1OUT & 0x0F) | (value & 0xF0);
	P2OUT = (P2OUT & 0xF0) | (value & 0x0F); 
}

//Read the 4 bits of PORTB
char read_on_PORTB()
{
	char c=0;
	c = ((P2IN & 0b00110000) >> 2); 
	c |= ((P1IN &0b00001000) >> 2) | (P1IN &0b00000001);
	return c;
	//Format the 4 bits readed to have a 8 bits sequence like "0000XXXX" (X are the bits readed) 
}

uint16_t convert_temperature(uint16_t temp)
{
	return (char) (((temp*420)/1024)-278); //Convert ADC temperature on Celsius and cast it on 8 bits.
}

interrupt(ADC10_VECTOR) ADC_out(void) {
}

//Read ADC temperature value
interrupt(TIMER0_A0_VECTOR) Timer_A0(void) {
	temp = ADC10MEM;
}
