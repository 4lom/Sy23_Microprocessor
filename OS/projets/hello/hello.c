/*
    hello.c
 */
 
/**
 * \file
 *         hello blink RED led and GREEN led
 * \author
 *         Michel Doussot <michel.doussot@utt.fr>
 */ 



#include "contiki.h"
#include "dev/leds.h"

/* -------------------------------------------------------------------------- */
PROCESS(hello_process, "Hello");
AUTOSTART_PROCESSES(&hello_process);

static struct etimer et;

PROCESS_THREAD(hello_process, ev, data)
{
  PROCESS_BEGIN();
  while(1) {
	leds_toggle(LEDS_ALL);  
    etimer_set(&et, CLOCK_SECOND/8);
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
  }
  PROCESS_END();
}
/*---------------------------------------------------------------------------*/

