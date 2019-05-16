#include "Timer.h"
#include "DisplayFlags.h"

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

void Timer::setAlarmCallback(timerAlarmCallback_t callback) {
    _alarmCallback = callback;
}

void Timer::reset() {
    _timeRemaining = 0;
    _lastTick = 0;

    if (_alarmRunning && _alarmCallback != NULL) {
        _alarmRunning = false;
        _alarmCallback(false);
    }    
}

void Timer::tick() {
    if (_running) {
        unsigned long now = arduino.millis();
        if (_lastTick != 0 && _timeRemaining > 0) {
            _timeRemaining -= (now - _lastTick);
            if (_timeRemaining < 0) {
                _timeRemaining = 0;
            }
        }
        _lastTick = now;
    }

    if (_running && _alarmCallback != NULL && !_alarmRunning && _timeRemaining <= 0) {
        _alarmRunning = true;
        _alarmCallback(true);
    }

    if (_alarmRunning && !_running && _alarmCallback != NULL) {
        _alarmRunning = false;
        _alarmCallback(false);
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

uint8_t Timer::displayFlags() {
    return DISPLAY_L1_L2;
}

void Timer::button1() {
    increment(5);
}

void Timer::button2() {
    increment(1);
}

void Timer::button3() {
    _running = !_running;
}

void Timer::button3Long() {
    reset();
}

void Timer::switch1(bool state) {
}
