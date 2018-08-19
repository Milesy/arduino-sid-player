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

    byte constantlyFlippingBytes[8] = {
      0xAA,
      0x55,
      0xAA,
      0x55,
      0xAA,
      0x55,
      0xAA,
      0x55
    };
    
    initialiseSerial();
    Serial.println("in setup.");
    CmosSram sram(1);

    Serial.println("Waiting for 3 seconds before writing.");
    delay(3000);
    //sram.write(byteRange);
    sram.write(constantlyFlippingBytes); // write 01010101 and 10101010 to see pulses on single data bus line.

    Serial.println("Waiting for 3 seconds before reading.");
    //flashFinish();
    delay(3000);
    
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
