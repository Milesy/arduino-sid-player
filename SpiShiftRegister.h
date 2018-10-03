#ifndef SpiShiftRegister_h
#define SpiShiftRegister_h

#include <SPI.h>
#include "ArduinoPin.h"

class SpiShiftRegister {
  public:
    SpiShiftRegister(String p_name, ArduinoPin *p_chipSelectPin, ArduinoPin *p_resetPin, int p_pinCount);
    void reset();
    void write(long data);
    void enable();
    void disable();
  
  private:
    String name;
    ArduinoPin *chipSelectPin;
    ArduinoPin *resetPin;
    int pinCount;
    SPISettings settings;
    void printByte(byte b);
};

#endif
