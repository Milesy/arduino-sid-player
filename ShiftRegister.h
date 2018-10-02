#ifndef ShiftRegister_h
#define ShiftRegister_h

#include "ArduinoPin.h"

class ShiftRegister {
  public:
    ShiftRegister(String p_name, ArduinoPin *p_serialPin, ArduinoPin *p_clockPin, ArduinoPin *p_resetPin, int p_pinCount);
    void reset();
    void write(long data);
    void test();
  
  private:
    String name;
    ArduinoPin *serialPin;
    ArduinoPin *clockPin;
    ArduinoPin *resetPin;
    int pinCount;
    long DEBUG_DELAY = 500;
    boolean DEBUG = false;
    boolean TEST = false;
    void clock();
    long powerOfTwo(int exp);
    long maxShiftRegisterValue(int pinCount);
};

#endif
