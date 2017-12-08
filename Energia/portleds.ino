#include "port.h"

const int ledspin[] = {P2_0, P2_1, P2_2, P2_3, P1_4, P1_5, P1_6, P1_7};
const int interspin[] = {P1_0, P1_3, P2_4, P2_5};

Port leds = Port(ledspin, 0xff, 8);
Port inters = Port(interspin, 0x00, 4);

volatile unsigned char valeur;

void setup() {
  valeur = inters.readport() | 0xa0;
  leds.writeport(valeur);
}

void loop() {
  delay(1000);
  valeur = leds.readport();
  leds.writeport(valeur);
}
