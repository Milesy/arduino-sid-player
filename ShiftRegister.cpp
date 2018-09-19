#include <Servo.h>

#include "Arduino.h"
#include "ShiftRegister.h"
#include <math.h>

ShiftRegister::ShiftRegister(String p_name, ArduinoPin *p_serialPin, ArduinoPin *p_clockPin, int p_resetPin, int p_pinCount) {
    name = p_name;
    serialPin = p_serialPin;
    clockPin = p_clockPin;
    resetPin = p_resetPin;
    pinCount = p_pinCount;

    pinMode(serialPin->pinNumber, OUTPUT);
    pinMode(clockPin->pinNumber, OUTPUT);
    pinMode(resetPin, OUTPUT);

    //Serial.println("Setting reset pin HIGH.");
    digitalWrite(resetPin, HIGH);
}

void ShiftRegister::test() {
    Serial.print("Performing shift register test for [");
    Serial.print(name);
    Serial.print("]\n");
    
    long max = maxShiftRegisterValue(pinCount);
    write(max);
}

// for 8 pins calculate ((2^8)-1) = 255 = 11111111 which allows me to send a HIGH bit to each pin.    
long ShiftRegister::maxShiftRegisterValue(int pinCount) {
    return powerOfTwo(pinCount) - 1;
}

long ShiftRegister::powerOfTwo(int exp) {
    long po2 = (long)2 << (exp - 1);
    
    return po2;
}

void ShiftRegister::reset() {
    //Serial.println("Resetting register. LOW to HIGH.");
    digitalWrite(resetPin, LOW);
    digitalWrite(resetPin, HIGH);
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
    
    for (int i = 0; i < pinCount; i++) {  
        int bit = (data >> ((pinCount -1) - i)) & 1; 

        volatile uint8_t *port = serialPin->port;
        
        if (bit == 1) {
            *port |= _BV(serialPin->physicalPin);  
            
        } else {
            *port &= ~_BV(serialPin->physicalPin);
        }

        clock();
    }

    //Serial.print("\n");
}
