#include "Arduino.h"
#include "Sid.h"

Sid::Sid(CmosSram *p_sram) : 
  addressCounter(addressClockPin, addressResetPin) {
    sram = p_sram;
    pinMode(chipSelectPin, OUTPUT);
    digitalWrite(chipSelectPin, HIGH);  

    Serial.println("[SID] Resetting address bus.");
    addressCounter.reset();    
}

void Sid::playSramContents() {
    Serial.println("[SID] Playing contents of SRAM onto SID.");
    delay(5000);
    sram->resetAddress();
    
    while(sram->hasNext()) {
        selectNextAddress();
        sram->readNextByte();
        sram->startRead();
        chipSelect();
        sram->endRead();
        delayMicroseconds(500);
    }  

    Serial.println("[SID] Finished playing contents of SRAM onto SID.");
}

void Sid::selectNextAddress() {
    long currentAddress = getCurrentAddress();
    //Serial.print("[SID] Selecting Address No [");
    //Serial.print(currentAddress);
    //Serial.print("]\n");

    if (currentAddress == 1) {
        addressCounter.reset();    
    }
    
    addressCounter.clock();
}

long Sid::getCurrentAddress() {
    long currentAddress = nextAddress;
    nextAddress++;

    if (nextAddress >= addressCount) {
        nextAddress = 0;
    }
    
    return currentAddress;
}

void Sid::chipSelect() {
    //Serial.println("[SID] chip select.");
    digitalWrite(chipSelectPin, LOW);
    digitalWrite(chipSelectPin, HIGH);
}
