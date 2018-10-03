#include <Servo.h>

#include "Arduino.h"
#include "SpiShiftRegister.h"
#include <math.h>

SpiShiftRegister::SpiShiftRegister(String p_name, ArduinoPin *p_chipSelectPin, ArduinoPin *p_resetPin, int p_pinCount) {
    name = p_name;
    chipSelectPin = p_chipSelectPin;
    resetPin = p_resetPin;
    pinCount = p_pinCount;

    pinMode(chipSelectPin->pinNumber, OUTPUT);
    pinMode(resetPin->pinNumber, OUTPUT);

    //digitalWrite(chipSelectPin->pinNumber, HIGH);
    //digitalWrite(resetPin->pinNumber, HIGH);

    settings = SPISettings(250000, MSBFIRST, SPI_MODE0);
}

void SpiShiftRegister::reset() {
    volatile uint8_t *port = resetPin->port;
    *port &= ~_BV(resetPin->physicalPin); // LOW
    *port |= _BV(resetPin->physicalPin);  // HIGH
}

void SpiShiftRegister::enable() {
    SPI.beginTransaction(settings);
    
    volatile uint8_t *port = chipSelectPin->port; 
    *port &= ~_BV(chipSelectPin->physicalPin); // LOW
}

void SpiShiftRegister::disable() {
    volatile uint8_t *port = chipSelectPin->port;
    *port |= _BV(chipSelectPin->physicalPin); // HIGH
    SPI.endTransaction();
}

void SpiShiftRegister::write(long data) {
    enable();

    Serial.print("[");
    Serial.print(name);
    Serial.print("] ");
    
    Serial.print("Writing: ");
    Serial.print(data);
    Serial.print("\n");

    delay(500);
    
    delay(1);
    disable();
    delay(1);
}
