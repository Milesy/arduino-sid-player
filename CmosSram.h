#ifndef CmosSram_h
#define CmosSram_h

#include "Arduino.h"
#include "ShiftRegister.h"

class CmosSram {
  public:
    CmosSram(int x);
    void write(byte bytes[255]);
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
    int cePin = 6;
    int oePin = 7;
    int wePin = 8;
    long nextAddress = 0;
    long getCurrentAddress();
    void resetAddress();
    void enableAddressSelection();
    void selectNextAddress(boolean isWrite);
    void startWrite();
    void endWrite();
    void startRead();
    void endRead();
};

#endif
