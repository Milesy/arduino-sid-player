#include "CmosSram.h"
#include "Sid.h"
#include "SdReader.h"
#include <avr/pgmspace.h>
  
void setup() {
    initialiseSerial();
    CmosSram sram(1);
    Sid sid(&sram);
    SdReader sdReader(10);

    //char fileName[] = "monty_~1.dmp";
    
    char fileName[] = "comman~1.dmp";
    
    sdReader.openFile(fileName);

    if (!sdReader.isOpened()) {
        Serial.println("No file opened, unable to continue");
        return;
    }
    
    Serial.println("Waiting for 3 seconds before writing.");
    delay(3000);

    sram.reset();
  
    long counter = 0;
    long maxBytes = 50000;
    
    while (sdReader.hasNext()) {
        byte readByte = sdReader.readByte();  
        //Serial.print(">>>> [");
        //Serial.print(counter);
        //Serial.print("]\n");
        sram.writeByte(readByte);
        counter++;
    }
    
    sram.disableInputOnDataBus();
    
    Serial.println("Waiting for 3 seconds before reading.");
    delay(3000);
    
    sid.playSramContents();
}

void initialiseSerial() {
    Serial.begin(9600);
    while(!Serial);
}

void loop() {
}
