#include <msp430.h>
#include <legacymsp430.h>
// msp430g2553

void write_on_PORTA(char value);
char read_on_PORTB();
uint_16 read_ADC();
uint_16 convert_temperature(uint_16);


//Counter which divide the timer frequency
int frequencedivider 	= 0;

//Unit and tenth counter
char unite_counter 		= 0;
char ten_counter			= 0;

char unit_temp = 0;
char ten_temp = 0;

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

interrupt(TIMER0_A0_VECTOR) time_out(void) {
	if((read_on_PORTB() & 0x01) == 0)
	{
		if(frequencedivider == 1000000)
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
		if(unit_show == 0)
		{
			write_on_PORTA(to_segments(ten_counter) | 0b00001000);
			unit_show = 1;
		}
		else
		{
			write_on_PORTA(to_segments(unite_counter));
			unit_show = 0;
		}
	}
	else
	{
		uint_16 temp = read_ADC();
		unit_temp = (char) temp;
		ten_temp = (char) (temp >> 4);
		if(unit_show == 0)
		{
			write_on_PORTA(to_segments(ten_temp) | 0b00001000);
			unit_show = 1;
		}
		else
		{
			write_on_PORTA(to_segments(unit_temp));
			unit_show = 0;
		}
		
	}
}

int main(void)
{
	WDTCTL = WDTPW + WDTHOLD;
	BCSCTL1 = CALBC1_1MHZ;
	DCOCTL = CALDCO_1MHZ;
	BCSCTL2 |= DIVS_1;
	P1DIR |= 0xFF;
	P1OUT = 0x00;
	P2DIR |= 0x0F;
	P2OUT = 0x00;
	
	//timer
	CCTL0 = CCIE;
	CCR0 = 32768;
	TACTL = TASSEL_2 + MC_1;
	
	//ADC
	ADC10CTL1 = ADC10SSEL_2 + ADC10DIV_1 + INCH_10 + CONSEQ_1;
		
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
	char c = ((P2IN & 0b00110000) >> 2); 
	c |= ((P1IN &0b00001000) >> 2) | (P1IN &0b00000001); //Format the 4 bits readed to have a 8 bits sequence like "0000XXXX" (X are the bits readed) 
	return c;
}

uint_16 convert_temperature(uint_16 temp)
{
	return ((temp*420)/1024)-278; //read the 9 bits value of the ADC.
}

//Read ADC temperature value
uint_16 read_ADC()
{
	return convert_temperature(ADC10MEM & 0x03FF); //read the 9 bits value of the ADC.
}