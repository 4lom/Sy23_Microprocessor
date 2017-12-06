#include "compteur.h"
#include <stdint.h>

void Compteur::time_out(void) {
  if((in & 0x01) == 0) {
    if(freqDiv == 1000000) {
      if(unite >= 9) {
        if(ten >= 9) {
          ten = 0;
        } else {
          ten += 1;
        }
        unite = 0;
      } else {
        unit += 1;
      }
      freqDiv = 0;
    } else {
      freqDiv += 1; 
    }
  }  
}
void Compteur::display() {
  if(!unit_show) {
    out.writeport(to_segment(ten) | 0b00001000);
    unit_show = true;
  } else {
    out.writeport(to_segment(unit));
    unit_show = false;
  }
}

char Compteur::to_segment(char value) {
  switch(value) {
    case 1:
      return 0b01100001;
    case 2:
      return 0b10110101;
    case 3: 
      return 0b11110100;
    case 4:
      return 0b01100110;
    case 5:
      return 0b11010110;
    case 6:
      return 0b11010111;
    case 7:
      return 0b01110000;
    case 8:
      return 0b11110111;
    case 9:
      return 0b11110110;
    default :
      return 0b11110011; 
  }
}
