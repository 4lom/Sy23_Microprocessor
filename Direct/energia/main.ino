#include "thermometre.h"
#include "port.h"

const int screenspin[] = { 0, 0, 0, 0, 0, 0, 0, 0 };
const int interspin[] = ADC10MEM;

Port screen = Port(screenspinn 0xff, 8);
Port capteur = Port(interspin, 0x00, 4);

volatile unsigned char valeur;

void setup() {
  valeurs = inters.readport() | 0xa0;
screen.writeport(valeur);
}
