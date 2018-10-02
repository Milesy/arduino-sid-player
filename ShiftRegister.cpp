#include <Servo.h>

#include "Arduino.h"
#include "ShiftRegister.h"
#include <math.h>

ShiftRegister::ShiftRegister(String p_name, ArduinoPin *p_serialPin, ArduinoPin *p_clockPin, ArduinoPin *p_resetPin, int p_pinCount) {
    name = p_name;
    serialPin = p_serialPin;
    clockPin = p_clockPin;
    resetPin = p_resetPin;
    pinCount = p_pinCount;

    pinMode(serialPin->pinNumber, OUTPUT);
    pinMode(clockPin->pinNumber, OUTPUT);
    pinMode(resetPin->pinNumber, OUTPUT);

    //Serial.println("Setting reset pin HIGH.");
    digitalWrite(resetPin, HIGH);
}

void ShiftRegister::reset() {
    volatile uint8_t *port = resetPin->port;
    //Serial.print("^");
    *port &= ~_BV(resetPin->physicalPin); // LOW
    *port |= _BV(resetPin->physicalPin);  // HIGH
}

void ShiftRegister::clock() {
    volatile uint8_t *port = clockPin->port;
    //Serial.print("^");
    *port |= _BV(clockPin->physicalPin);  
    *port &= ~_BV(clockPin->physicalPin);
}

void ShiftRegister::write(long data) {
    //Serial.print("[");
    //Serial.print(name);
    //Serial.print("]");
    
    //Serial.print("Writing Bits: ");

    int lastBit = -1;
    long skippedBits = 0;
    
    for (int i = 0; i < pinCount; i++) {  
        int bit = (data >> ((pinCount -1) - i)) & 1; 

        volatile uint8_t *port = serialPin->port;

        if (bit != lastBit) {
            if (bit == 1) {
                *port |= _BV(serialPin->physicalPin);          
            } 
            else {
                *port &= ~_BV(serialPin->physicalPin);
            }
        }
        else {
            skippedBits++;
        }

        lastBit = bit;
        
        clock();
    }
    
    //Serial.print("\n");
}
