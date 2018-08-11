#include "Arduino.h"
#include "ShiftRegister.h"

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
}

void ShiftRegister::reset() {
    Serial.println("Resetting register. LOW to HIGH.");
    digitalWriteWithDebug(resetPin, LOW);
    digitalWriteWithDebug(resetPin, HIGH);
}

void ShiftRegister::clock() {
    Serial.println("Clocking bit. HIGH to LOW.");
    digitalWriteWithDebug(clockPin, HIGH);
    digitalWriteWithDebug(clockPin, LOW);
}

void ShiftRegister::digitalWriteWithDebug(int pin, int value) {
    digitalWrite(pin, value);

    if (DEBUG == true && DEBUG_DELAY > 0) {
        delay(DEBUG_DELAY);
    }
}

void ShiftRegister::write(word data) {
    String sShifting = "Shifting [";
    sShifting = sShifting + pinCount;
    sShifting = sShifting + "] bits of word [";
    sShifting = sShifting + data;
    sShifting = sShifting + "]";

    Serial.println(sShifting);

    // shift bits for expected number of pins.
    for (int i = 0; i < pinCount; i++) {  
        int bit = (data >> ((pinCount -1) - i)) & 1; 

        String sWriting = "Writing Bit: ";
        String sData = sWriting + bit;

        Serial.println(sData);

        if (bit == 1) {
            digitalWriteWithDebug(serialPin, HIGH);
        } else {
            digitalWriteWithDebug(serialPin, LOW);
        }

        clock();
    }
}
