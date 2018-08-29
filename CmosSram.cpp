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

    pinMode(tranceiverOePin, OUTPUT);
}
// need to call write with one byte? and reset address outside?

void CmosSram::write(byte PROGMEM bytes[]) {
    
}



void CmosSram::disableInputOnDataBus() {
    Serial.println("Disabling input on data bus");
    delay(5000);
    digitalWrite(tranceiverOePin, HIGH);  
}

void CmosSram::writeByte(long byteToWrite) {
    selectNextAddress(true);    
    startWrite();
    // Shift register interface takes a long because its capable of more than 8 bits (addresses)
    data.write(byteToWrite);
    endWrite();
    delay(1000);
    data.reset();
    address.reset();
}

void CmosSram::enableAddressSelection() {
    digitalWrite(oePin, HIGH);
    digitalWrite(cePin, HIGH);
    digitalWrite(wePin, HIGH);
}

void CmosSram::startWrite() {
    digitalWrite(cePin, LOW);
    digitalWrite(wePin, LOW);
    delayOneCycle();
}

void CmosSram::endWrite() {
    digitalWrite(wePin, HIGH);
    digitalWrite(cePin, HIGH);
}

void CmosSram::startRead() {
    // WE# is already high from address selection.
    digitalWrite(cePin, LOW);
    digitalWrite(oePin, LOW);
    delayOneCycle();
    delay(2000);
}

void CmosSram::endRead() {
    digitalWrite(cePin, HIGH);
    digitalWrite(oePin, HIGH);
}

void CmosSram::selectNextAddress(boolean forWrite) {
    long currentAddress = getCurrentAddress();
    Serial.print("[SRAM] Selecting Address No [");
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

boolean CmosSram::hasNext() {
    return nextAddress < 1000; // Needs to be the actual size we wrote.
}

void CmosSram::readNextByte() {
    selectNextAddress(false);
    Serial.print("[SRAM] Reading byte from address [");
    Serial.print(nextAddress-1);
    Serial.print("]\n");      
}
    

void CmosSram::delayOneCycle() {
    __asm__("nop\n\t");
}

long CmosSram::getCurrentAddress() {
    long currentAddress = nextAddress;
    nextAddress++;

    return currentAddress;
}

void CmosSram::resetAddress() {
    nextAddress = 1;
}
