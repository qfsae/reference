#include "Arduino.h"

// Acquired from looking at the arduino to STM pin mapping
// https://github.com/stm32duino/Arduino_Core_STM32/blob/master/variants/Generic_F446Rx/variant.h
#define LED A8

int ledState = 0;

void setup() {
	Serial2.begin(9600);
	pinMode(LED, OUTPUT);
}

void loop() {
	Serial2.write('A');
	delay(100);
	ledState = !ledState;
	digitalWrite(LED, ledState);
}
