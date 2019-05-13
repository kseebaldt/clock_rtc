#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "ArduinoWrapper.h"

class Button {
    public:
        Button(uint8_t pin, long debounceDelay = 50);
        void init();
        void tick();

        uint8_t state() const { return _state; }
    private:
        uint8_t _pin;
        int _state;
        int _lastState;
        long _lastDebounceTime = 0;
        long _debounceDelay;
};

#endif
