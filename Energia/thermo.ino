
int port_in[] = { ADC10MEM };
int port_out[] = { P2_0, P2_1, P2_2, P2_3, P1_4, P1_5, P1_6, P1_7 };

Port p_out = Port(port_out, 0xff, 8);
Port p_in = Port(port_in, 0x00, 1);

volatile unsigned char value;

void setup() {
  valeur = p_in.readport() | 0xa0;
  p_out.writeport(valeur);
}

void loop() {
  delay(1000);
  valeur =  p_out.readport();
  p_out.writeport(valeur);

}
