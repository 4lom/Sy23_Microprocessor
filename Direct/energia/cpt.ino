#include "port.h"
#include <stdint.h>

const int ledspin[] = {P2_0, P2_1, P2_2, P2_3, P1_4, P1_5, P1_6, P1_7};
const int interspin[] = {P1_0, P1_3, P2_4, P2_5};
const int frequenceDivider = 0;
char unit_counter = 0;
char ten_counter = 0;
char unit_temp = 0;
char ten_temp = 0;
int unit_show = 1;

int P1DIR;
int P2DIR;

uint_16 read_ADC();
uint_16 convert_temperature(uint_16);

Port leds;
Port inters:

char to_segment(char value) {
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

//interrupt(TIMER0_A0_VECTOR) time_out(void) {
void time_out(void) {
  if ((inters.readport() & 0x01) == 0) {
    if(frequenceDivider == 1000000) {
      if(unite_counter >= 9 ) {
        if(ten_counter >= 9 ) {
          ten_counter = 0;
        } else  {
          ten_counter+=1;
        }
        unite_counter = 0;
      } else  {
        unite_counter+=1;
      }
      frequenceDivider = 0;
    } else {
      frequenceDivider += 1;
    }
    
    if(unit_show == 0) {
      leds.writeport(to_segment(ten_counter) | 0b00001000);
      unit_show = 1;
    } else {
      leds.writeport(to_segment(unit_counter));
      unit_show = 0;
    }
  } else {
    uint_16 temp = read_ADC();
    uint_temp = (char) temp;
    ten_temp = (char) (temp >> 4);
    if(unit_show == 0) {
      leds.writeport(to_segment(ten_temp) | 0b00001000);
      unit_show = 1;
    } else {
      leds.writeport(to_segment(unit_temp));
      unit_show = 0;
    }

  }
}




void setup() {
  WDTCTL = WDTPW + WDTHOLD;
  BCSCTL1 = CALBC1_1MHZ;
  BCSCTL2 = CALDC0_1MHZ;
  BCSCTL2 |= DIVS_1;
  P1DIR |= 0xff;
  P2DIR |= 0x0f;

  leds = Port(ledspin, PS1DIR, 8);
  inters = PORT(interspin, P2DIR, 4);
  // timer
    CCTL0 = CCIE;
  CCR0 = 32768;
  TACTL = TASSEL_2 + MC_1;
  // ADC
  ADC10CTL1 = ADC10SSEL_2 + ADC10DIV_1 + INCH_1° + CONSEQ_1;

  eint();
  
  // valeur = inters.readport() | 0xa0;
  // leds.writeport(valeur);
}

void loop() {
  delay(1000);
  //valeur = leds.readport();
  //leds.writeport(valeur);
}

uint_16 convert_temperature(uint_16 temp) {
  return ((temp*420)/1024)-278;
}

uint_16 read_ADC() {
  return convert_temperature(ADC10MEM & 0x03FF);
}


int main() {
  setup();
  loop();
}
