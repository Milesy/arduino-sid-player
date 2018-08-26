#include "Arduino.h"
#include "BinaryCounter.h"

BinaryCounter::BinaryCounter(int p_clockPin, int p_resetPin) {
    clockPin = p_clockPin;
    resetPin = p_resetPin;

    pinMode(clockPin, OUTPUT);
    pinMode(resetPin, OUTPUT);
}

void BinaryCounter::clock() {
    digitalWrite(clockPin, HIGH);
    digitalWrite(clockPin, LOW);
}

void BinaryCounter::reset() {
    digitalWrite(resetPin, HIGH);
    digitalWrite(resetPin, LOW);   
}

