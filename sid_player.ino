#include "ShiftRegister.h"

int addressSerialPin = 0;
int addressClockPin = 1;
int addressResetPin = 2;
int addressPinCount = 8; // 19

int dataSerialPin = 1;
int dataClockPin = 1;
int dataResetPin = 1;
int dataPinCount = 19;

void setup() {
    initialiseSerial();
    Serial.println("in setup.");
    ShiftRegister address("Address bus", addressSerialPin, addressClockPin, addressResetPin, addressPinCount);
    // ShiftRegister data(1, 1, 1);
    address.write(255);
}

void initialiseSerial() {
    Serial.begin(9600);
    while(!Serial);
}

void loop() {
}
