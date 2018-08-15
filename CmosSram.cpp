#include "Arduino.h"
#include "CmosSram.h"

CmosSram::CmosSram(int x) : 
  address("Address bus", addressSerialPin, addressClockPin, addressResetPin, addressPinCount),
  data("Data bus", dataSerialPin, dataClockPin, dataResetPin, dataPinCount) {
    // Can this be removed?
    int cePin = 6;
    int oePin = 7;
    int wePin = 8;

    pinMode(cePin, OUTPUT);
    pinMode(oePin, OUTPUT);
    pinMode(wePin, OUTPUT);
}

void CmosSram::write(byte bytes[]) {
    resetAddress();

    int byteCounter = 0;
    
    for (int i = 0; i < 4; i++) {
        selectNextAddress(true);    
        startWrite();
        data.write(bytes[byteCounter]);
        endWrite();
        delay(2000);
        data.reset();
        address.reset();
        
        if (byteCounter == 7) {
            byteCounter == 0;
        }
        else {
            byteCounter++;
        }
    }
}

void CmosSram::read() {
    resetAddress();

    for (int i = 0; i < 4; i++) {
        selectNextAddress(false);    
        startRead();
        Serial.println("Initiated read");
        endRead();
        delay(2000);
        address.reset();
    }
}

void CmosSram::enableAddressSelection() {
    digitalWrite(oePin, HIGH);
    digitalWrite(cePin, HIGH);
    digitalWrite(wePin, HIGH);
}

void CmosSram::startWrite() {
    digitalWrite(cePin, LOW);
    digitalWrite(wePin, LOW);
}

void CmosSram::endWrite() {
    digitalWrite(wePin, HIGH);
    digitalWrite(cePin, HIGH);
}

void CmosSram::startRead() {
    // WE# is already high from address selection.
    digitalWrite(cePin, LOW);
    digitalWrite(oePin, LOW);
}

void CmosSram::endRead() {
    digitalWrite(cePin, HIGH);
    digitalWrite(oePin, HIGH);
}

void CmosSram::selectNextAddress(boolean forWrite) {
    long currentAddress = getCurrentAddress();
    Serial.print("Selecting Address No [");
    Serial.print(currentAddress);
    Serial.print("] for ");

    if (forWrite == true) {
        Serial.print("WRITE");  
    }
    else {
        Serial.print("READ");
    }
        
    Serial.print("\n");
    enableAddressSelection();
    address.write(currentAddress);
}

long CmosSram::getCurrentAddress() {
    long currentAddress = nextAddress;
    nextAddress++;

    return currentAddress;
}

void CmosSram::resetAddress() {
    nextAddress = 0;
}
