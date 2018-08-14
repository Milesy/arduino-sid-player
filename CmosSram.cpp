#include "Arduino.h"
#include "CmosSram.h"

CmosSram::CmosSram(int x) : 
  address("Address bus", addressSerialPin, addressClockPin, addressResetPin, addressPinCount),
  data("Data bus", dataSerialPin, dataClockPin, dataResetPin, dataPinCount) {
    
}

void CmosSram::write() {
  
}

void CmosSram::read() {

}
