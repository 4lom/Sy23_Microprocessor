#include <msp430.h>
#include <legacymsp430.h>
#include <stdint.h>
// msp430g2553

void write_on_PORTA(char value);
char read_on_PORTB();
uint16_t read_ADC();
uint16_t convert_temperature(uint16_t);


//Counter which divide the timer frequency
int frequencedivider 	= 0;

//Unit and tenth counter
char unite_counter 	= 0;
char ten_counter	= 0;


volatile uint16_t temp;
char unit_temp 		= 0;
char ten_temp 		= 0;

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
		//uint16_t temp = read_ADC();
		write_on_PORTA(temp);
		unit_temp = (char) (temp%10);
		ten_temp = (char) (temp/10);
		if(unit_show == 0)
		{
			//write_on_PORTA(ten_temp);
			//write_on_PORTA(to_segments(ten_temp) | 0b00001000);
			unit_show = 1;
		}
		else
		{
			//write_on_PORTA(unit_temp);
			//write_on_PORTA(to_segments(unit_temp));
			unit_show = 0;
		}
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
	P1DIR |= (BIT7 | BIT6 | BIT5 | BIT4 | ~BIT3 | BIT2 | BIT1 | ~BIT0);//0b11110110;
	P1OUT = 0x00;
	P2DIR |= 0b11001111;
	P2OUT = 0x0F;	
	
	// interruption sur valeur CCR0
	CCTL0 = CCIE | OUTMOD_4; // OUT0 for ADC10

	//ADC
	ADC10CTL0 = SREF_1 | ADC10SHT_3 | REFON | ADC10ON | ADC10IE;
	ADC10CTL1 = ADC10SSEL_0 | ADC10DIV_0 | INCH_10 | SHS_2 | CONSEQ_2;	
	ADC10CTL0 |= ENC ;
	
	//timer
	CCR0 = 512;
	TACTL = TASSEL_2 | MC_1 | TACLR;
	
	//ADC
/*
	ADC10CTL0 = ADC10ON + ADC10SHT1 + ADC10IE;
	ADC10CTL1 = INCH_10;// + CONSEQ_1;
*/
		
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
	return ((temp*420)/1024);//-278; //read the 9 bits value of the ADC.
}

//Read ADC temperature value
interrupt(ADC10_VECTOR) ADC_out(void) {
	//write_on_PORTA(read_ADC() & 0x03FF);
	//write_on_PORTA(0xFF);
	temp = ADC10MEM;
}

uint16_t read_ADC()
{
	write_on_PORTA(ADC10MEM);
	return ADC10MEM;
	//return convert_temperature(ADC10MEM); //read the 9 bits value of the ADC.
}
