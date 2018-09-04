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
        //Serial.println("selectNextAddress");
        selectNextAddress();
        //delay(10000);

        //Serial.println("readNextByte");
        sram->readNextByte();
        //delay(10000);
        
        //Serial.println("startRead");
        sram->startRead();
        //delay(10000);

        //Serial.println("chipSelect");
        chipSelect();
        //delay(10000);
        
        //Serial.println("endRead");
        sram->endRead();

        delay(50);
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
        nextAddress = 0;
    }
    
    return currentAddress;
}

void Sid::chipSelect() {
    Serial.println("[SID] chip select.");
    digitalWrite(chipSelectPin, LOW);
    delay(1);
    digitalWrite(chipSelectPin, HIGH);
}
