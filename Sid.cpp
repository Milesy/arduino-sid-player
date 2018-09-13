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
    // Select SID address. Binary counter
    delay(5000);
    sram->resetAddress();
    
    while(sram->hasNext()) {
        selectNextAddress();
        sram->readNextByte();
        sram->startRead();
        chipSelect();
        sram->endRead();
        //delay(0.5);
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

    if (nextAddress >= addressCount) {
        nextAddress = 0;
    }
    
    return currentAddress;
}

void Sid::chipSelect() {
    //Serial.println("[SID] chip select.");
    digitalWrite(chipSelectPin, LOW);
    delay(0.3);
    digitalWrite(chipSelectPin, HIGH);
}
