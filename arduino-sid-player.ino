#include "CmosSram.h"

void setup() {
    pinMode(9, OUTPUT);
    byte byteRange[8] = {
      0x1,
      0x2,
      0x4,
      0x8,
      0x10,
      0x20,
      0x40,
      0x80
    };
    
    initialiseSerial();
    Serial.println("in setup.");
	  CmosSram sram(1);

    sram.write(byteRange);

    flashFinish();
    
    sram.read();
}

void initialiseSerial() {
    Serial.begin(9600);
    while(!Serial);
}

void flashFinish() {
    digitalWrite(9, HIGH);
    delay(200);
    digitalWrite(9, LOW);
    delay(200);
    digitalWrite(9, HIGH);
    delay(200);
    digitalWrite(9, LOW);
    delay(200);
    digitalWrite(9, HIGH);
    delay(200);
    digitalWrite(9, LOW);
    delay(200);
}

void loop() {
}
