#include <Energia.h>
#include "port.h"

Port::Port() {
  nbits = 0;
}

Port::Port(const int *p, unsigned char dir, int n) {
  nbits = n;
  for(int i = 0; i < nbits; i++) {
    bitsport[i] = p[i];
  }
  setdir(dir);
}

void Port::setdir(unsigned char dir) {
  unsigned char pindir;
  for(int i = 0; i < nbits; i++) {
    pindir = (dir >> i) & 1;
    pinMode(bitsport[i], pindir);
  }
}

void Port::writeport(unsigned char v) {
  unsigned char pinvalue, portvalue = 0;
  for(int i = 0; i < nbits; i++) {
    pinvalue = digitalRead(bitsport[i]);
    portvalue |= (pinvalue & 1) << i;
  }
  return portvalue;
}
