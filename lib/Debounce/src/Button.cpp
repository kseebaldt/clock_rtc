#include "Button.h"

Button::Button(uint8_t pin, long debounceDelay) {
    _pin = pin;
    _debounceDelay = debounceDelay;
    _state = HIGH;
}

void Button::init() {
    arduino.pinMode(_pin, INPUT_PULLUP);
}

void Button::tick() {
  int reading = arduino.digitalRead(_pin);

  if (reading != _lastState) {
    _lastDebounceTime = arduino.millis();
  }

  if ((arduino.millis() - _lastDebounceTime) > _debounceDelay) {
    if (reading != _state) {
      _state = reading;

    //   if (_state == LOW) {
        
    //   }
    }
  }

  _lastState = reading;
}