#include "CmosSram.h"
#include "Sid.h"
#include "SdReader.h"
#include <avr/pgmspace.h>
  
void setup() {
    initialiseSerial();
    CmosSram sram(1);
    Sid sid(&sram);
    SdReader sdReader(10);

    char fileName[] = "OCEAN_~1.DMP";
    
    sdReader.openFile(fileName);

    if (!sdReader.isOpened()) {
        Serial.println("[SID Player] No file opened, unable to continue.");
        return;
    }
    
    Serial.println("[SID Player] Waiting for 3 seconds before writing.");
    delay(3000);

    sram.reset();
  
    long counter = 0;
    long maxBytes = 15000;
    long fileSize = sdReader.getOpenedFileSize();

    double percentage;
    int percentageRound;
    
    while (sdReader.hasNext()) {
        byte readByte = sdReader.readByte();  
        sram.writeByte(readByte);
        
        percentage = (double) (counter * 100.f) / fileSize;
        percentageRound = (int) (percentage + 0.5);

        if (counter % 40000 == 0) {
            Serial.print("[SID Player] Load [");
            Serial.print(percentageRound);
            Serial.print("%]\n");             
        }
        
        counter++;
    }
    
    sram.disableInputOnDataBus();
    
    Serial.println("[SID Player] Waiting for 3 seconds before reading.");
    delay(3000);
    
    sid.playSramContents();
}

void initialiseSerial() {
    Serial.begin(9600);
    while(!Serial);
}

void loop() {
}
