/**
 * \addtogroup launchpad-platform
 *
 * @{
 */

/*
 * Copyright (c) 2013, Michel Doussot http://www.utt.fr
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/*
 * \file
 *         A simple ADC-implementation
 * \author
 *         Michel Doussot <michel.doussot@utt.fr>
 */


#include "contiki.h"
#include "interface.h"

#include "interface.h"
#include "portsmap.h"


void setdirport(unsigned char port, unsigned char masque) {
  unsigned char i,mask,numport;
  unsigned char *pport;
  for(i=0,mask=1;i<tailleport[port];i+=1,mask<<=1) {
	  numport = portmap[port][i].port;
	  pport = portdir[numport];
	  if (mask & masque) {
		  *pport |= portmap[port][i].bit;
	  }
	  else {
		  *pport &= ~portmap[port][i].bit;
	  }
  }
}


void writeport(unsigned char port,unsigned char masque) {		
  unsigned char i,mask,numport;
  unsigned char *pport;
  for(i=0,mask=1;i<tailleport[port];i+=1,mask<<=1) {
	  numport = portmap[port][i].port;
	  pport = portout[numport];
	  if (mask & masque) {
		  *pport |= portmap[port][i].bit;
	  }
	  else {
		  *pport &= ~portmap[port][i].bit;
	  }
  }
}

unsigned char readport(unsigned char port) {
	
  unsigned char value=0;
  unsigned char i,mask,numport;
  unsigned char *pport;
  for(i=0,mask=1;i<tailleport[port];i+=1,mask<<=1) {
	  numport = portmap[port][i].port;
	  pport = portin[numport];
	  if (*pport & portmap[port][i].bit) {
		  value |= mask;
	  }
  }  
 return value;
	
}

/*--------------------------------------------------------------------------*/
/** @} */
