#include "SdReader.h"
#include <SD.h>
#include <SPI.h>

SdReader::SdReader(int p_chipSelectPin) {
    chipSelectPin = p_chipSelectPin;
 
    Serial.println("Initialising.");
    initialised = SD.begin(chipSelectPin);
   
    if (initialised) {
        Serial.println("Card initialised.");
        root = SD.open("/");
        listFiles();
    }
    else {
        Serial.println("Card initialising failed.");
    }
    
}

void SdReader::openFile(const char* fileName) {
    opened = false;
    
    if (initialised) {
        Serial.print("Opening [");        
        Serial.print(fileName);
        Serial.print("]\n");
        file = SD.open(fileName);

        if (file) {
            Serial.println("File is open.");
            opened = true;
        }
        else {
            Serial.println("File is not open.");
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
        Serial.println("Closing file.");
        file.close(); 
    }
}

void SdReader::listFiles() {
    Serial.println("Listing files.");
    
    bool finished = false;
    
    while(!finished) {
        File entry =  root.openNextFile();

        if (entry) {
            Serial.print(entry.name());
            Serial.print("\n");

            break;
        }
        else {
            Serial.println("No more files.");
            finished = true;
        }
    } 
    
}
