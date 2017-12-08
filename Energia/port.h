#ifndef port_h
#define port_h

#define Nbits 8

class Port {
  private :
    int bitsport[Nbits];
    int nbits;
  public :
    Port(const int *, unsigned char, int);
    Port();
    void setdir(unsigned char);
    void writeport(unsigned char);
    unsigned char readport();

};
#endif
