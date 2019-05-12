#include <Arduino.h>

#include "BcdDriver.h"

BcdDriver driver(A3, A0, A1, A2, 4, 8, 9, 10, 12);

void setup() {
  driver.initPins();
  
  driver.setValue(1234);
}

void loop() {
  driver.display();
}