#ifndef thermometre_h
#define thermometre_h
#include <stdint>

class Thermo {
  private :
    // in 
    const int tpin[] = {};
    // out
    const int interspin[] = {};
    char unit = 0;
    char ten = 0;
    bool unit_show = true;
    Port t;
    Port inters:

  public :
    void Thermo(); 
    void time_out(void);
    void display();
    char to_segment(char);
    uint_16 convert_temp(uint_16 temp);
    uint_16 read_ADV();
};

#endif

