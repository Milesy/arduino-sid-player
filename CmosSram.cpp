#include "Arduino.h"
#include "CmosSram.h"

CmosSram::CmosSram(int x) : 
  address("Address bus", addressSerialPin, addressClockPin, addressResetPin, addressPinCount),
  data("Data bus", dataSerialPin, dataClockPin, dataResetPin, dataPinCount) {
    pinMode(cePin, OUTPUT);
    pinMode(oePin, OUTPUT);
    pinMode(wePin, OUTPUT);
    pinMode(tranceiverOePin, OUTPUT);
}

void CmosSram::disableInputOnDataBus() {
    Serial.println("[Buffer] Disabling input on data bus.");
    delay(5000);
    digitalWrite(tranceiverOePin, HIGH);  
}

void CmosSram::writeByte(long byteToWrite) {
    selectNextAddress(true);    
    startWrite();
    data.write(byteToWrite);
    endWrite();
    data.reset();
    address.reset();
    byteCount++;
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
}

void CmosSram::endRead() {
    digitalWrite(cePin, HIGH);
    digitalWrite(oePin, HIGH);
}

void CmosSram::selectNextAddress(boolean forWrite) {
    long currentAddress = getCurrentAddress();
    enableAddressSelection();
    address.write(currentAddress);
}

boolean CmosSram::hasNext() {
    return nextAddress < byteCount; 
}

void CmosSram::readNextByte() {
    selectNextAddress(false);    
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
    nextAddress = 0;
}

void CmosSram::reset() {
    resetAddress();
    byteCount = 0;
}
