#include "Arduino.h"
#include "Sid.h"

Sid::Sid(CmosSram *p_sram) : 
  addressCounter(addressClockPin, addressResetPin) {
    sram = p_sram;
}

void Sid::playSramContents() {
    // Select SID address. Binary counter
    // Read byte.
    // CS  
    sram->read();    
}

