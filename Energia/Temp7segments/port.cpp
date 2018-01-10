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


void Port::writetosegment(unsigned char c, bool is_unit = true) {
  unsigned char seg = to_segments(c);
  if(!is_unit)
  {
	seg |= 0b00001000;
  }
  this->writeport(seg);
}

char Port::to_segments(char value)
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
