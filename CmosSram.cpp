#include "Arduino.h"
#include "CmosSram.h"

CmosSram::CmosSram(int x) : 
  address("Address bus", addressSerialPin, addressClockPin, addressResetPin, addressPinCount),
  data("Data bus", dataSerialPin, dataClockPin, dataResetPin, dataPinCount) {
    int cePin = 6;
    int oePin = 7;
    int wePin = 8;

    pinMode(cePin, OUTPUT);
    pinMode(oePin, OUTPUT);
    pinMode(wePin, OUTPUT);
}

void CmosSram::write() {
    Serial.println("Configuring SRAM for write enable.");
    // Can I do away with the CE and OE pins? Only WE changes.
    digitalWrite(cePin, LOW);
    digitalWrite(oePin, LOW);
    digitalWrite(wePin, LOW);
}

void CmosSram::read() {
    Serial.println("Configuring SRAM for write enable.");
    // Can I do away with the CE and OE pins? Only WE changes.
    digitalWrite(cePin, LOW);
    digitalWrite(oePin, LOW);
    digitalWrite(wePin, HIGH);
}
