#include "SdReader.h"
#include <SD.h>
#include <SPI.h>

SdReader::SdReader(int p_chipSelectPin) {
    chipSelectPin = p_chipSelectPin;
 
    Serial.println("[SD] Initialising.");
    initialised = SD.begin(chipSelectPin);
   
    if (initialised) {
        Serial.println("[SD] Card initialised.");
        root = SD.open("/");
    }
    else {
        Serial.println("[SD] Card initialising failed.");
    }
    
}

void SdReader::openFile(const char* fileName) {
    opened = false;
    
    if (initialised) {
        Serial.print("[SD] Opening [");        
        Serial.print(fileName);
        Serial.print("]\n");
        file = SD.open(fileName);

        if (file) {
            Serial.println("[SD] File is open.");
            Serial.print("[SD] Size (bytes): ");
            Serial.print(file.size());
            Serial.print("\n");
            
            opened = true;
        }
        else {
            Serial.println("[SD] File is not open.");
            opened = false;
        }
    }
}

bool SdReader::hasNext() {
    if (opened) {
        return file.available(); 
    }
    else {
        return false;
    }
}

bool SdReader::isOpened() {
    return opened;
}

byte SdReader::readByte() {
    return file.read();
}

void SdReader::closeFile() {
    if (opened) {
        Serial.println("[SD] Closing file.");
        file.close(); 
    }
}

long SdReader::getOpenedFileSize() {
    if (opened) {
        return file.size(); 
    }
    else {
        return -1;
    }
}

// Utility at the moment, not used.
void SdReader::listFiles() {
    Serial.println("[SD] Listing files.");
    
    bool finished = false;
    
    while(!finished) {
        File entry =  root.openNextFile();

        if (entry) {
            Serial.print("[SD] ");
            Serial.print(entry.name());
            Serial.print("\n");

            break;
        }
        else {
            Serial.println("[SD] No more files.");
            finished = true;
        }
    } 
    
}
