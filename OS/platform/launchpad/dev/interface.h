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

#ifndef __INTERFACE_H
#define __INTERFACE_H

// mapping port A 8 bits
// port 2
#define PA0	0x01
#define PA1	0x02
#define PA2	0x04
#define PA3	0x08
// port 1
#define PA4	0x10
#define PA5	0x20
#define PA6	0x40
#define PA7	0x80

// mapping port B 4 bits
// port 1
#define PB0	0x01
#define PB1	0x08
// port 2
#define PB2	0x10
#define PB3	0x20

#define PORTA 0
#define PORTB 1


void setdirport(unsigned char,unsigned char);
void writeport(unsigned char,unsigned char);
unsigned char readport(unsigned char);

#endif /* __INTERFACE_H */
/** @} */
