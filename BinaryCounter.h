#ifndef BinaryCounter_h
#define BinaryCounter_h

#include "CmosSram.h"

class BinaryCounter {
  public:
      BinaryCounter(int p_clockPin, int p_resetPin); // Include max count size?
      void clock();
      void reset();
    
  private:
      int clockPin;
      int resetPin;
};

#endif
