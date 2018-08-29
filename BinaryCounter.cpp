#include "Arduino.h"
#include "BinaryCounter.h"

/**
 * Using CD74HC4040 implementation.
 */
BinaryCounter::BinaryCounter(int p_clockPin, int p_resetPin) {
    clockPin = p_clockPin;
    resetPin = p_resetPin;
  
    pinMode(clockPin, OUTPUT);
    pinMode(resetPin, OUTPUT);

    digitalWrite(clockPin, HIGH);
    digitalWrite(resetPin, LOW);
}

void BinaryCounter::clock() {
    digitalWrite(clockPin, LOW);
    digitalWrite(clockPin, HIGH);
}

void BinaryCounter::reset() {
    digitalWrite(resetPin, HIGH);
    digitalWrite(resetPin, LOW);   
}
