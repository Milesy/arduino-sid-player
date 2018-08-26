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

void CmosSram::write(byte bytes[]) {
    resetAddress();

    long data = 1;
    auto sizea = (sizeof(bytes));
    auto sizeb = (sizeof(bytes[0]));
    auto size = (sizeof(bytes) / sizeof(bytes[0]));

    Serial.print("A [");
    Serial.print(sizea);
    Serial.print("] bytes.\n");

    Serial.print("B [");
    Serial.print(sizeb);
    Serial.print("] bytes.\n");
    
    Serial.print("Writing [");
    Serial.print(size);
    Serial.print("] bytes.\n");
    
    for (int i = 0; i < 8; i++) {
        //writeByte(255); // Light up all the pins at address 1.
        writeByte(bytes[i]); // Light up one pin at a time.
    }
    
    disableInputOnDataBus();
}

void CmosSram::disableInputOnDataBus() {
    Serial.println("Disabling input on data bus");
    delay(5000);
    digitalWrite(tranceiverOePin, HIGH);  
}

// Won't allow me to call variable data?
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

void CmosSram::read() {
    resetAddress();

    for (int i = 0; i < 8; i++) {
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
