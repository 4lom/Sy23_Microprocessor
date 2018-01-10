#include "contiki.h"
#include "dev/interface.h"

/* -------------------------------------------------------------------------- */
PROCESS(chrono_process, "chrono");
AUTOSTART_PROCESSES(&chrono_process);

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


static struct etimer et;
unsigned char ten_counter = 0;
unsigned char unit_counter = 0;

int div_clock = 0;
char unit_show = 0;
char is_lock = 0;

volatile unsigned char flags = 0x00;

PROCESS_THREAD(chrono_process, ev, data)
{
  PROCESS_BEGIN();
  setdirport(PORTA,PA0|PA1|PA2|PA3|PA4|PA5|PA6|PA7);
  setdirport(PORTB,0);
  writeport(PORTA,0);  
  while(1) 
  {	
  	flags = readport(PORTB);
	if((flags & 0x1) == 0x1) //Search the lock flag value
	{
		is_lock = 1;
	}
	else if((flags & 0x2) == 0x2) //Search the reset flag value
	{
		//reset counter
		is_lock = 1;
		unit_counter = 0;
		ten_counter = 0;
	}
	else
	{
		is_lock = 0;
	}
	
	//If the clock is not locked
	if(is_lock == 0)
	{
		//Each 50 loop the counter is incremented
		if(div_clock == 50)
		{
			//Increment to 9 max (1 to 9 + 0 = 10)
			if(unit_counter >= 9)
			{
				ten_counter = 1;
				unit_counter = 0;
			}
			else
			{	if(ten_counter == 1)
				{
					ten_counter = 0;
				}
				else
				{
					unit_counter++;
				}
			}
			div_clock = 0;
		}
		else
		{
			div_clock++;
		}
	}	
	
	//Alternate the digit displayed
	if(unit_show == 0)
	{
		writeport(PORTA,to_segments(ten_counter) | 0b00001000);
		unit_show = 1;
	}
	else
	{
		writeport(PORTA,to_segments(unit_counter));
		unit_show = 0;
	}
	
	etimer_set(&et, CLOCK_SECOND/100);
	PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
  }
  PROCESS_END();
}
/*---------------------------------------------------------------------------*/

