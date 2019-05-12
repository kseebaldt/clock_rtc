#include <Arduino.h>

#include "BcdDriver.h"
#include "Clock.h"

BcdDriver driver(A3, A0, A1, A2, 4, 8, 9, 10, 12);
Clock clock;

void setup() {
  clock.start();

  driver.initPins();
}

void loop() {
  driver.setValue(clock.time());
  driver.display();
}