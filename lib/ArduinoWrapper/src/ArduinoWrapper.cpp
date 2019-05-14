#include "ArduinoWrapper.h"

ArduinoWrapper arduino;

#ifdef ARDUINO

void ArduinoWrapper::pinMode(uint8_t pin, uint8_t mode) {
    ::pinMode(pin, mode);
}

void ArduinoWrapper::digitalWrite(uint8_t pin, uint8_t val) {
    ::digitalWrite(pin, val);
}

int ArduinoWrapper::digitalRead(uint8_t pin) {
    return ::digitalRead(pin);
}

void ArduinoWrapper::delay(unsigned long millis) {
    ::delay(millis);
}

unsigned long ArduinoWrapper::millis(void) {
    return ::millis();
}

#else

uint8_t _fake_pinModes[20] = {0};
uint8_t _fake_pinValues[20] = {0};

unsigned long _fake_millis = 0;

void ArduinoWrapper::pinMode(uint8_t pin, uint8_t mode) {
    _fake_pinModes[pin] = mode;
}

void ArduinoWrapper::digitalWrite(uint8_t pin, uint8_t val) {
    _fake_pinValues[pin] = val;
}

int ArduinoWrapper::digitalRead(uint8_t pin) {
    return _fake_pinValues[pin];
}

void ArduinoWrapper::delay(unsigned long millis) {
}

unsigned long ArduinoWrapper::millis(void) {
    return _fake_millis;
}

#endif