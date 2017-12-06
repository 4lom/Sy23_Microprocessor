#include <Energia.h>
#include "thermometre.h"

Thermo::Thermo() {
      t = Port(tspin, PS1DIR, 8);
      inters = PORT(interspin, P2DIR, 4);
}

void Thermo::time_out(void) {
  if((inters.readport() & 0x01) != 0) {
    uint_16 temp = read_ADC();
    uint_temp = (char) temp;
    ten = (char) (temp >> 4);
    if (!unit_show){
      t.writeport(to_segment(ten) | 0b00001000);
      unit_show = true;
    } else {
      t.writeport(to_segment(unit));
      unit_show = false;
    }
  }
}

void Thermo::display(){

}


uint_16 Thermo::convert_temp(uint_16 temp) {
  return ((temp*420)/1024)-278;
}

uint_16 Thermo::read_ADC() {
  return convert_temp(ADC10MEM & 0x03FF);
}

char Thermo::to_segment(char value) {
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
