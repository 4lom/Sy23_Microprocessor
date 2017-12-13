#include "port.h"

const int ledspin[] = {P2_0,P2_1,P2_2,P2_3,P1_4,P1_5,P1_6,P1_7};
int compteur = 0;

Port leds = Port(ledspin,0xff,8); 

volatile unsigned char valeur;

void setup() {
  leds.writeport(compteur);
}

void loop() {
  
  delay(1000);
  if(compteur < 100) {
    compteur++;
  } else {
    compteur = 0; 
  }
  leds.writeport(compteur);    
}

