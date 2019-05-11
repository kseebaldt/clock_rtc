#include <Arduino.h>

#include "BcdDriver.h"

// #include <Arduino.h>
// #include <RTClib.h>

BcdDriver driver(A3, A0, A1, A2, 4, 8, 9, 10, 12);

void setup() {
  driver.initPins();
  
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
}