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

    digitalWrite(chipSelectPin->pinNumber, HIGH);
    digitalWrite(resetPin->pinNumber, HIGH);

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
    //delay(100);
    enable();

    //Serial.print("[");
    //Serial.print(name);
    //Serial.print("] ");
    
    //Serial.print("Writing: ");
    //Serial.print(data);
    //Serial.print("\n");

    if (name.equals("Address bus")) {
        byte byte2 = (data >> 16) & 0xFF;
        byte byte1 = (data >> 8) & 0xFF;
        byte byte0 = (data >> 0) & 0xFF;

        SPI.transfer(byte2);
        SPI.transfer(byte1);
        SPI.transfer(byte0);
        
    }
    else {
        byte byte0 = (data >> 0) & 0xFF;
      
        SPI.transfer(byte0);
    }
    
    //delay(500);
    
    //delay(1);
    disable();
    //delay(1);
}

void SpiShiftRegister::printByte(byte b) {
    int size = 8;

    // MSB to LSB: 1 = 00000001
    for (int i = 8; i > 0; i--) {  
        Serial.print(bitRead(b, i));
    }
}
