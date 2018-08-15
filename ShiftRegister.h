#ifndef ShiftRegister_h
#define ShiftRegister_h

#include "Arduino.h"

class ShiftRegister {
  public:
    ShiftRegister(String p_name, int p_serialPin, int p_clockPin, int p_resetPin, int p_pinCount);
    void reset();
    void write(long data);
    void test();
  
  private:
    String name;
    int serialPin;
    int clockPin;
    int resetPin;
    int pinCount;
    long DEBUG_DELAY = 0;
    boolean DEBUG = false;
    boolean TEST = false;
    void clock();
    // move this into my own class?
    void digitalWriteWithDebug(int pin, int value);
    long powerOfTwo(int exp);
    long maxShiftRegisterValue(int pinCount);
};

#endif
