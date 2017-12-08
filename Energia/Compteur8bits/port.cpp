#include <Energia.h>
#include "port.h"

Port::Port() {
  nbits = 0;
}


Port::Port(const int *p,unsigned char dir,int n) {
  nbits = n;
  for(int i=0;i<nbits;i+=1) {
       bitsport[i] = p[i];
  }
  setdir(dir);
}

void Port::setdir(unsigned char dir) {
  unsigned char pindir;
  for(int i=0;i<nbits;i+=1) {
   pindir = (dir >> i) & 1;
   pinMode(bitsport[i], pindir);
  }
}


void Port::writeport(unsigned char v) {
   unsigned char pinvalue;
   for(int i=0;i<nbits;i+=1) {
    pinvalue = (v>> i) & 1;
    digitalWrite(bitsport[i], pinvalue);
   } 
}


unsigned char Port::readport() {
  unsigned char pinvalue,portvalue=0;
  for(int i=0;i<nbits;i+=1) {
    pinvalue = digitalRead(bitsport[i]);
    portvalue |= (pinvalue & 1) << i;
  } 
  return portvalue;
}

Port Port::operator |=(const unsigned char mask) {
        unsigned char v=readport();
        v |= mask;
        writeport(v);  
	return *this;
}

Port Port::operator &=(const unsigned char mask) {
        unsigned char v=readport();
        v &= mask;        
        writeport(v);  
	return *this;
}

Port Port::operator ^=(const unsigned char mask) {
        unsigned char v=readport();
        v ^= mask;        
        writeport(v); 
	return *this;
}


void Port::writetosegment(unsigned char c) {
  unsigned char seg;
  switch(c) {
    case 1:
      seg = 0b01100000;
    case 2:
      seg = 0b10110101;
    case 3:
      seg = 0b11110100;
    case 4:
      seg = 0b01100110;
    case 5:
      seg =  0b11010110;
    case 6:
      seg = 0b110110111;
    case 7:
      seg =  0b01110000;
    case 8: 
      seg = 0b11110111;
    case 9:
      seg = 0b11110110;
    default:
      seg = 0b11110011;
  }
  this->writeport(seg);
}
