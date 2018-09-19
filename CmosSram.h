#ifndef CmosSram_h
#define CmosSram_h

#include "Arduino.h"
#include "ShiftRegister.h"
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
    const ArduinoPin addressSerialPin = [&] {
        // Pin 0 / PORTD(PD2);
        ArduinoPin pin;
        pin.pinNumber = 0;
        pin.port = &PORTD;
        pin.physicalPin = PD2;
        return pin;
    }();

    const ArduinoPin addressClockPin = [&] {
        // Pin 1 / PORTD(PD3);
        ArduinoPin pin;
        pin.pinNumber = 1;
        pin.port = &PORTD;
        pin.physicalPin = PD3;
        return pin;
    }();
    
    int addressResetPin = 2;

    const ArduinoPin dataSerialPin = [&] {
        // Pin 3 / PORTD(PD0);
        ArduinoPin pin;
        pin.pinNumber = 3;
        pin.port = &PORTD;
        pin.physicalPin = PD0;
        return pin;
    }();
    
    const ArduinoPin dataClockPin = [&] {
        // Pin 4 / PORTD(PD2);
        ArduinoPin pin;
        pin.pinNumber = 4;
        pin.port = &PORTD;
        pin.physicalPin = PD4;
        return pin;
    }();
    
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
