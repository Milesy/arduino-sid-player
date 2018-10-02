#ifndef CmosSram_h
#define CmosSram_h

#include "Arduino.h"
#include "SpiShiftRegister.h"
#include "ArduinoPin.h"

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

    const ArduinoPin addressChipSelectPin = [&] {
        // Pin A3 / PORTF(PF4);
        ArduinoPin pin;
        pin.pinNumber = A3;
        pin.port = &PORTF;
        pin.physicalPin = PF4;
        return pin;
    }();

    const ArduinoPin addressResetPin = [&] {
        // Pin 2 / PORTD(PD1);
        ArduinoPin pin;
        pin.pinNumber = 2;
        pin.port = &PORTD;
        pin.physicalPin = PD1;
        return pin;
    }();
  
    const ArduinoPin dataChipSelectPin = [&] {
        // Pin A4 / PORTF(PF1);
        ArduinoPin pin;
        pin.pinNumber = A4;
        pin.port = &PORTF;
        pin.physicalPin = PF1;
        return pin;
    }();

    const ArduinoPin dataResetPin = [&] {
        // Pin 5 / PORTC(PC6);
        ArduinoPin pin;
        pin.pinNumber = 5;
        pin.port = &PORTC;
        pin.physicalPin = PC6;
        return pin;
    }();
    
    int tranceiverOePin = A0;
    int cePin = 6;
    int oePin = 7;
    int wePin = 8;

    int addressPinCount = 19;
    int dataPinCount = 8;
    SpiShiftRegister address;
    SpiShiftRegister data;
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
