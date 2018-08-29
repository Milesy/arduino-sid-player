#include "Arduino.h"
#include "Sid.h"

Sid::Sid(CmosSram *p_sram) : 
  addressCounter(addressClockPin, addressResetPin) {
    sram = p_sram;
    pinMode(chipSelectPin, OUTPUT);
    digitalWrite(chipSelectPin, HIGH);  
}

void Sid::playSramContents() {
    Serial.println("[SID] Playing contents of SRAM onto SID.");
    // Select SID address. Binary counter
    delay(5000);
    sram->resetAddress();
    while(sram->hasNext()) {
        selectNextAddress();
        sram->readNextByte();
        chipSelect();
    }  
}

void Sid::selectNextAddress() {
    long currentAddress = getCurrentAddress();
    Serial.print("[SID] Selecting Address No [");
    Serial.print(currentAddress);
    Serial.print("]\n");

    if (currentAddress == 1) {
        addressCounter.reset();    
    }
    
    addressCounter.clock();
}

long Sid::getCurrentAddress() {
    long currentAddress = nextAddress;
    nextAddress++;

    if (nextAddress > addressCount) {
        nextAddress = 1;
    }
    
    return currentAddress;
}

void Sid::chipSelect() {
    digitalWrite(chipSelectPin, LOW);
    digitalWrite(chipSelectPin, HIGH);
}

