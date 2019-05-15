#include <Arduino.h>

#include "BcdDriver.h"
#include "Mode.h"

#include "Clock.h"
#include "Timer.h"

#include "Button.h"

BcdDriver driver(A0, A3, A2, A1, 10, 9, 4, 8, 13, 12, 11);
Clock clock;
Timer timer;

Button button1 = Button(4);
Button button2 = Button(3);
Button button3 = Button(2);
Button toggleSwitch = Button(6);
Button modeSwitch = Button(5);

Mode *currentMode;

void button1Callback(Button& button) {
  currentMode->button1();
}

void button2Callback(Button& button) {
  currentMode->button2();
}

void button3Callback(Button& button) {
  currentMode->button3();
}

void toggleSwitchCallback(Button& button) {
  currentMode->switch1(button.state() == LOW);
}

void modeSwitchCallback(Button& button) {
  if (button.state() == LOW) {
      currentMode = (Mode *)&clock;
  } else {
      currentMode = (Mode *)&timer;
  }
}

void setup() {
  clock.init();
  timer.init();

  currentMode = (Mode *)&clock;

  button1.init();
  button2.init();
  button3.init();
  toggleSwitch.init();
  modeSwitch.init();

  button1.setCallback(button1Callback, 250);
  button2.setCallback(button2Callback, 250);
  button3.setCallback(button3Callback);
  toggleSwitch.setCallback(toggleSwitchCallback);

  driver.initPins();
}

void loop() {
  timer.tick();

  button1.tick();
  button2.tick();
  button3.tick();
  toggleSwitch.tick();
  modeSwitch.tick();

  if (modeSwitch.state() == LOW) {
      currentMode = (Mode *)&timer;
  } else {
      currentMode = (Mode *)&clock;
  }

  driver.setValue(currentMode->displayValue());
  driver.setDisplayFlags(currentMode->displayFlags());
  driver.display();
}
