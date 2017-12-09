/*
    ports.c
 */
 
/**
 * \file
 *         interface 8 bits et 4 bits digilent
 * \author
 *         Michel Doussot <michel.doussot@utt.fr>
 */ 



#include "contiki.h"
#include "dev/interface.h"

/* -------------------------------------------------------------------------- */
PROCESS(ports_process, "Ports");
AUTOSTART_PROCESSES(&ports_process);

static struct etimer et;
unsigned char value;

PROCESS_THREAD(ports_process, ev, data)
{
  PROCESS_BEGIN();
  setdirport(PORTA,PA0|PA1|PA2|PA3|PA4|PA5|PA6|PA7);
  setdirport(PORTB,0);
  writeport(PORTA,0);  
  while(1) {
	value=readport(PORTB);
	writeport(PORTA,value); 
    etimer_set(&et, CLOCK_SECOND/10);
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
  }
  PROCESS_END();
}
/*---------------------------------------------------------------------------*/

