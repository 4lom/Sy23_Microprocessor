#ifndef compteur_h
#define compteur_h

class Compteur {
  private:
    int in;
    int out;
    const int freqDiv = 0;
    char unit = 0;
    char ten = 0;
    bool unit_show = true;
  public:
   void time_out(void); 
   void display();
   char to_segment(char);
};

#endif
