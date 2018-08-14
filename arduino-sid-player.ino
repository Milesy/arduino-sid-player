#include "CmosSram.h"

void setup() {
    initialiseSerial();
    Serial.println("in setup.");
	  CmosSram sram(1);
}

void initialiseSerial() {
    Serial.begin(9600);
    while(!Serial);
}

void loop() {
}
