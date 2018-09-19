#ifndef ArduinoPin_h
#define ArduinoPin_h

struct ArduinoPin {
  int pinNumber;
  volatile uint8_t *port;
  volatile uint8_t physicalPin;
};

#endif
