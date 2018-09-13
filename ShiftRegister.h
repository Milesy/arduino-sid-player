#ifndef ShiftRegister_h
#define ShiftRegister_h

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
    long DEBUG_DELAY = 500;
    boolean DEBUG = false;
    boolean TEST = false;
    void clock();
    long powerOfTwo(int exp);
    long maxShiftRegisterValue(int pinCount);
};

#endif
