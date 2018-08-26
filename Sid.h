#ifndef Sid_h
#define Sid_h

#include "CmosSram.h"
#include "BinaryCounter.h"

class Sid {
  public:
      Sid(CmosSram *p_sram);
      void playSramContents();
    
  private:
      int addressClockPin = 0;
      int addressResetPin = 0;
      int chipSelectPin = 0;
      BinaryCounter addressCounter;
      CmosSram *sram;
};

#endif
