#include "Arduino.h"
#include <Adafruit_NeoPixel.h>

// Acquired from looking at the arduino to STM pin mapping
// https://github.com/stm32duino/Arduino_Core_STM32/blob/master/variants/STM32F4xx/F446R(C-E)T/variant_generic.h
// NOTE: Arduino layer in platformio supports CMSIS mapping of MCU registers
// Thus, all the low level code we write will be directly portable to the Arduino environment in platformio

#define LED 29 // status LED
#define NEO_PIN 19 // neopixel data pin (fed into level shifter)
#define NEO_COUNT 73 // number of pixels on the strip
#define SHIFTER_OE 20 // output enable for level shifter

// This config worked for the neopixels I have laying around
// Will need to change depending on the variant used
Adafruit_NeoPixel strip(NEO_COUNT, NEO_PIN, NEO_RGB + NEO_KHZ800);

int ledState = 0;
void setup() {
	Serial2.begin(9600);
	pinMode(LED, OUTPUT); // status LED output
	pinMode(SHIFTER_OE, OUTPUT); // output enable for the voltage translator
	digitalWrite(SHIFTER_OE, HIGH); // enable is active high
	strip.begin();
	strip.clear();
	strip.setBrightness(50);
	strip.show();

}

// just tests red green blue function within each neopixels
// takes LED index as input
void testNeoRGB(int pixel) {
	strip.setPixelColor(pixel, 0, 0, 127);
	strip.show();
	delay(200);
	strip.setPixelColor(pixel, 0, 127, 0);
	strip.show();
	delay(200);
	strip.setPixelColor(pixel, 127, 0, 0);
	strip.show();
	delay(200);
}

void loop() {
	for (int i = 0; i < NEO_COUNT; i++) {
		testNeoRGB(i);
		strip.clear();
		strip.show();
	}
	ledState = !ledState;
	digitalWrite(LED, ledState);
}
