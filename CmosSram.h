#ifndef CmosSram_h
#define CmosSram_h

#include "Arduino.h"
#include "ShiftRegister.h"

class CmosSram {
  public:
    CmosSram(int x);
    void write();
    void read();
  
  private:
    int addressSerialPin = 0;
    int addressClockPin = 1;
    int addressResetPin = 2;
    int addressPinCount = 19;
    int dataSerialPin = 3;
    int dataClockPin = 4;
    int dataResetPin = 5;
    int dataPinCount = 8;
    ShiftRegister address;
    ShiftRegister data;
};

#endif
