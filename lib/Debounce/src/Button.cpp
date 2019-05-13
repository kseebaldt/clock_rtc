#include "Button.h"

Button::Button(uint8_t pin, uint16_t debounceDelay) {
    _pin = pin;
    _debounceDelay = debounceDelay;
    _state = HIGH;
    _lastState = HIGH;
    _lastDebounceTime = 0;
}

void Button::init() {
    arduino.pinMode(_pin, INPUT_PULLUP);
}

void Button::setCallback(buttonCallback_t callback, uint16_t repeatTime) {
    _callback = callback;
    _repeatTime = repeatTime;
}

void Button::tick() {
    unsigned long now = arduino.millis();

    int reading = arduino.digitalRead(_pin);

    if (reading != _lastState) {
        _lastDebounceTime = now;
    }

    if ((now - _lastDebounceTime) > _debounceDelay) {
        if (reading != _state) {
            _state = reading;
            _lastCallBackTime = 0;
        }
    }

    if (_state == LOW && _callback != NULL) {
        if (_lastCallBackTime == 0 ||
            (_repeatTime != 0 && now - _lastCallBackTime >= _repeatTime)) {
            _callback(*this);
            _lastCallBackTime = now;
        }
    }

    _lastState = reading;
}