#include "Arduino.h"
#include "ShiftRegister.h"
#include <math.h>

ShiftRegister::ShiftRegister(String p_name, int p_serialPin, int p_clockPin, int p_resetPin, int p_pinCount) {
    name = p_name;
    serialPin = p_serialPin;
    clockPin = p_clockPin;
    resetPin = p_resetPin;
    pinCount = p_pinCount;

    pinMode(serialPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(resetPin, OUTPUT);

    Serial.println("Setting reset pin HIGH.");
    digitalWriteWithDebug(resetPin, HIGH);

    if (DEBUG == true) {
        test();   
    }
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

    Serial.print("po2 [");
    Serial.print(po2);
    Serial.print("]\n");
    
    return po2;
}

void ShiftRegister::reset() {
    Serial.println("Resetting register. LOW to HIGH.");
    digitalWriteWithDebug(resetPin, LOW);
    digitalWriteWithDebug(resetPin, HIGH);
}

void ShiftRegister::clock() {
    Serial.print("^");
    digitalWriteWithDebug(clockPin, HIGH);
    digitalWriteWithDebug(clockPin, LOW);
}

void ShiftRegister::digitalWriteWithDebug(int pin, int value) {
    digitalWrite(pin, value);

    if ((DEBUG == true || TEST == true) && DEBUG_DELAY > 0) {
        delay(DEBUG_DELAY);
    }
}

void ShiftRegister::write(long data) {
    String sShifting = "Shifting [";
    sShifting = sShifting + pinCount;
    sShifting = sShifting + "] bits of [";
    sShifting = sShifting + data;
    sShifting = sShifting + "]";

    Serial.println(sShifting);

    Serial.print("Writing Bits: ");

    // shift bits for expected number of pins.
    for (int i = 0; i < pinCount; i++) {  
        int bit = (data >> ((pinCount -1) - i)) & 1; 

        Serial.print(bit);

        if (bit == 1) {
            digitalWriteWithDebug(serialPin, HIGH);
        } else {
            digitalWriteWithDebug(serialPin, LOW);
        }

        clock();
    }

    Serial.print("\n");
}
