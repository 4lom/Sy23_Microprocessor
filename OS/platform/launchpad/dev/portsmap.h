/*
   interface.h
*/

#ifndef __PORTS_AB_H
#define __PORTS_AB_H

#define PORT1 1
#define PORT2 2

#define TAILLEPORTA	8
#define TAILLEPORTB	4

typedef struct {
	unsigned char bit;
	unsigned char port;
} tbitport;

unsigned char *portdir[] = { 0, (unsigned char*)&P1DIR, (unsigned char*)&P2DIR };
unsigned char *portin[] = { 0, (unsigned char*)&P1IN, (unsigned char*)&P2IN };
unsigned char *portout[] = { 0, (unsigned char*)&P1OUT, (unsigned char*)&P2OUT };

const tbitport portmap[2][8] = { { {PA0 , PORT2} , {PA1, PORT2} , {PA2, PORT2} , {PA3, PORT2} , 
                                   {PA4, PORT1} , {PA5, PORT1} , {PA6, PORT1} , {PA7, PORT1} } ,
                                  { {PB0 , PORT1} , {PB1 , PORT1} , {PB2 , PORT2} , {PB3 , PORT2} ,
                                    { 0, 0 } , { 0, 0 } ,{ 0, 0 } , { 0, 0 }}
                                };
                                
const unsigned char tailleport[2] = { TAILLEPORTA, TAILLEPORTB };                                

#endif
