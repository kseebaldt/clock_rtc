#include "BcdDriver.h"

#define IS_SET(byte,bit) (((byte) & (1UL << (bit))) >> (bit))

BcdDriver::BcdDriver(uint8_t a, uint8_t b, uint8_t c, uint8_t d, int numDigits, ...) {
  _a = a;
  _b = b;
  _c = c;
  _d = d;

  _delay = 1;
  _currentDigit = 0;
  _value = 0;

  _numDigits = numDigits;

  va_list pinList;
  va_start(pinList, numDigits);

  _digitPins = (uint8_t *) malloc(numDigits * sizeof(uint8_t));
  for (int i = 0; i < numDigits; ++i) {
    _digitPins[i] = va_arg(pinList, int);
  }
  va_end(pinList);
}

uint16_t BcdDriver::getValue() const {
  return _value;
}

void BcdDriver::setValue(uint16_t value) {
  _value = value;
}

uint16_t BcdDriver::getDelay() const {
  return _delay;
}

void BcdDriver::setDelay(uint16_t delay) {
  _delay = delay;
}

void BcdDriver::initPins() {
  arduino.pinMode(_a, OUTPUT);
  arduino.pinMode(_b, OUTPUT);
  arduino.pinMode(_c, OUTPUT);
  arduino.pinMode(_d, OUTPUT);

  for (int i = 0; i < _numDigits; ++i) {
    arduino.pinMode(_digitPins[i], OUTPUT);
  }
}

#include <stdio.h>

void BcdDriver::display() {
  uint8_t digit = (_value / (int)pow(10, _currentDigit)) % 10;
  displayNumber(digit, _currentDigit);
  _currentDigit = (_currentDigit + 1) % _numDigits;
  arduino.delay(_delay);
}

/* PRIVATE METHODS */

void BcdDriver::clearDigits() {
  for (int i = 0; i < 4; ++i) {
    arduino.digitalWrite(_digitPins[i], HIGH);
  }
}

void BcdDriver::displayNumber(uint8_t number, uint8_t digit) {
  clearDigits();

  arduino.digitalWrite(_a, IS_SET(number, 0));
  arduino.digitalWrite(_b, IS_SET(number, 1));
  arduino.digitalWrite(_c, IS_SET(number, 2));
  arduino.digitalWrite(_d, IS_SET(number, 3));

  arduino.digitalWrite(_digitPins[digit], LOW);
}
