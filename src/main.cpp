#include <Arduino.h>
#include <TimerOne.h>

#include "BcdDriver.h"
#include "Mode.h"

#include "Clock.h"
#include "Timer.h"

#include "Button.h"

#define BUZZER_PIN 7

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
  if (button.isLongPress()) {
    currentMode->button3Long();
  } else {
    currentMode->button3(); 
  }
}

void toggleSwitchCallback(Button& button) {
  currentMode->switch1(button.state() == LOW);
}

bool _alarmPlaying;

void alarmInterrupt(void) {
  if (_alarmPlaying) {
    noTone(BUZZER_PIN);
    _alarmPlaying = false;
  } else {
    tone(BUZZER_PIN, 1000);
    _alarmPlaying = true;
  }
}

void alarmCallback(bool alarmOn) {
  if (alarmOn) {
    Timer1.attachInterrupt(alarmInterrupt);
  } else {
    Timer1.detachInterrupt();
    noTone(BUZZER_PIN);
  }
}

void setup() {
  Timer1.initialize(1000000);

  clock.init();
  timer.init();

  clock.setAlarmCallback(alarmCallback);
  timer.setAlarmCallback(alarmCallback);

  currentMode = (Mode *)&clock;

  button1.init();
  button2.init();
  button3.init();
  toggleSwitch.init();
  modeSwitch.init();

  button1.setCallback(button1Callback, 250);
  button2.setCallback(button2Callback, 250);
  button3.setCallback(button3Callback, 1000);
  toggleSwitch.setCallback(toggleSwitchCallback);

  driver.initPins();
}

void loop() {
  timer.tick();
  clock.tick();

  button1.tick();
  button2.tick();
  button3.tick();
  toggleSwitch.tick();
  modeSwitch.tick();

  currentMode->switch1(toggleSwitch.state() == LOW);
  if (modeSwitch.state() == LOW) {
      currentMode = (Mode *)&timer;
  } else {
      currentMode = (Mode *)&clock;
  }

  driver.setValue(currentMode->displayValue());
  driver.setDisplayFlags(currentMode->displayFlags());
  driver.display();
}
