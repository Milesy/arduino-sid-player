#ifndef SdReader_h
#define Sd_h

#include "Arduino.h"
#include <SD.h>
#include <SPI.h>

class SdReader {
  public:
      SdReader(int p_chipSelectPin);
      void openFile(const char* fileName);
      bool hasNext();
      byte readByte();
      void closeFile();
      boolean isOpened();
      long getOpenedFileSize();
    
  private:
      File root;
      File file;
      int chipSelectPin;
      bool initialised;
      bool volumeInitialised;
      bool opened;
      void listFiles();
};

#endif
