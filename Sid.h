#ifndef Sid_h
#define Sid_h

#include "CmosSram.h"
#include "BinaryCounter.h"

class Sid {
  public:
      Sid(CmosSram *p_sram);
      void playSramContents();
    
  private:
      void selectNextAddress();
      long getCurrentAddress();
      void chipSelect();
      int addressClockPin = 11;
      int addressResetPin = 12;
      int chipSelectPin = 9;
      int addressCount = 26;
      int nextAddress = 0;
      BinaryCounter addressCounter;
      CmosSram *sram;
};

#endif
