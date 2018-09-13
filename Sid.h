#ifndef Sid_h
#define Sid_h

#include "CmosSram.h"
#include "BinaryCounter.h"

class Sid {
  public:
      Sid(CmosSram *p_sram);
      void playSramContents();
    
  private:
      // GPIO Pins
      int addressClockPin = 11;
      int addressResetPin = 12;
      int chipSelectPin = 9;
      
      void selectNextAddress();
      long getCurrentAddress();
      void chipSelect();
      int addressCount = 25;
      int nextAddress = 0;
      BinaryCounter addressCounter;
      CmosSram *sram;
};

#endif
