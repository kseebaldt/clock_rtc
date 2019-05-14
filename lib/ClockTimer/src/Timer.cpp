#include "Timer.h"

void Timer::init() {
    reset();
}

void Timer::setRunning(bool running) {
    _running = running;
}

uint16_t Timer::secondsRemaining() { 
    return (_timeRemaining + 500) / 1000;
}

void Timer::setSecondsRemaining(uint16_t seconds) {
    _timeRemaining = seconds * 1000;
}

void Timer::reset() {
    _timeRemaining = 0;
    _running = false;
    _lastTick = 0;
}

void Timer::tick() {
    if (_running) {
        unsigned long now = arduino.millis();
        if (_lastTick != 0) {
            _timeRemaining -= (now - _lastTick);
        }
        _lastTick = now;
    }
}

void Timer::increment(uint8_t minutes) {
    _timeRemaining += minutes * 60 * 1000;
}

uint16_t Timer::displayValue() {
    uint8_t seconds = secondsRemaining() % 60;
    uint8_t minutes = secondsRemaining() / 60;
    return minutes * 100 + seconds;
}

void Timer::button1() {
    increment(1);
}

void Timer::button2() {
    increment(5);
}

void Timer::button3() {
    reset();
}

void Timer::switch1(bool state) {
    setRunning(state);
}
