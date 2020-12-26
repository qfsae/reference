#include "Arduino.h"

#define LED 24

void setup() {
	Serial2.begin(9600);
//	pinMode(LED, OUTPUT);
}

void loop() {
	Serial2.write('A');
	delay(100);
}
