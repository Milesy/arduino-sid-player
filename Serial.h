class ShiftRegister {
  public:
    ShiftRegister(int p_serialPin, int p_clockPin, int p_resetPin);
    void reset();
    void write(word data);
  
  private:
    int serialPin;
    int clockPin;
    int resetPin;

};
