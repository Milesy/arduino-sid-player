#ifndef CmosSram_h
#define CmosSram_h

#include "Arduino.h"
#include "ShiftRegister.h"

class CmosSram {
  public:
    CmosSram(int x);
    void write(byte bytes[255]);
    boolean hasNext();
    void readNextByte();
    void reset();
    void resetAddress();
    void writeByte(long data);
    void disableInputOnDataBus();
    void startRead();
    void endRead();
    
  private:
    // GPIO Pins
    int addressSerialPin = 0;
    int addressClockPin = 1;
    int addressResetPin = 2;
    int dataSerialPin = 3;
    int dataClockPin = 4;
    int dataResetPin = 5;
    int tranceiverOePin = A0;
    int cePin = 6;
    int oePin = 7;
    int wePin = 8;

    int addressPinCount = 19;
    int dataPinCount = 8;
    ShiftRegister address;
    ShiftRegister data;
    long nextAddress = 0;
    long byteCount = 0;
    long getCurrentAddress();
    void enableAddressSelection();
    void selectNextAddress(boolean isWrite);
    void startWrite();
    void endWrite();
    void delayOneCycle();
};

#endif
