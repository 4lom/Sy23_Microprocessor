#include "port.h"
#include <stdint.h>

const int ledspin[] = {P2_0,P2_1,P2_2,P2_3,P1_4,P1_5,P1_6,P1_7};



Port leds = Port(ledspin,0xff,8); 

//Temperature value
volatile unsigned char valeur;

//Boolean which determine if the future digit show is the unit or the ten.
bool unit_show = true;

uint16_t convert_temperature(uint16_t temp)
{
	//Convert ADC temperature on Celsius and cast it on 8 bits.
    return (char) ((temp*420)/1024); 
}

void display_7seg(uint16_t temp) {

	char unit_to_show = 0;
	char ten_to_show  = 0;
	
	//Convert the temperature to Celsius
	uint16_t temperature = convert_temperature(temp);
	//Extract the unit digit
	unit_to_show = (unsigned char)(temperature%10);
	//Extract the ten digit 
	ten_to_show  = (unsigned char)(((uint32_t)temperature*(uint32_t)0xCCCD) >> 16) >> 3;
	
	//Select if it is the unit digit to show or the ten digit.
	if(unit_show == false)
	{
		//write to the 7 segments of port A, passing the flag that the number is not the unit digit.
		leds.writetosegment(ten_to_show, false);
		unit_show = true;
	}
	else
	{
		//write to the 7 segments of port A, passing no flag is equal to passing that the number is the unit digit.
        leds.writetosegment(unit_to_show);
		unit_show = false;
	}
}

void setup() {
  //analogReference(INTERNAL2V5);
  
}

void loop() {
   delay(10);
   //read the temperature value 
   uint16_t t = analogRead(A10);
   
   //Display temperature on the 7 segments
   display_7seg(t);
}
