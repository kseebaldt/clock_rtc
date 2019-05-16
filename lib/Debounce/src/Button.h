#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "ArduinoWrapper.h"

class Button;
typedef void (*buttonCallback_t)(Button& button);

class Button {
    public:
        Button(uint8_t pin, uint16_t debounceDelay = 50);
        void init();
        void tick();

        uint8_t state() const { return _state; }
        bool isLongPress() const { return _isLongPress; }

        void setCallback(buttonCallback_t callback, uint16_t repeatTime = 0);
        void setRepeatTime(uint16_t repeatTime);

    private:
        uint8_t _pin;
        uint8_t _state;
        uint8_t _lastState;
        unsigned long _lastDebounceTime = 0;
        uint16_t _debounceDelay;
        unsigned long _lastCallBackTime = 0;
        buttonCallback_t _callback = NULL;
        uint16_t _repeatTime;
        bool _isLongPress = false;
};

#endif
