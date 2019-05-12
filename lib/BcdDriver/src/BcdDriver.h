#ifndef _BCDDRIVER_H_
#define _BCDDRIVER_H_

#include "ArduinoWrapper.h"

class BcdDriver {
    public:
        BcdDriver(uint8_t a, uint8_t b, uint8_t c, uint8_t d, int numDigits, ...);

        uint16_t getDelay() const;
        uint16_t getValue() const;

        void setDelay(uint16_t delay);
        void setValue(uint16_t value);

        void initPins();
        void display();

    private:
        uint8_t _a;
        uint8_t _b;
        uint8_t _c;
        uint8_t _d;

        uint16_t _value;
        
        uint16_t _delay;

        uint8_t _numDigits;
        uint8_t *_digitPins;

        uint8_t _currentDigit;

        void displayNumber(uint8_t number, uint8_t digit);
        void clearDigits();
};

#endif /* _BCDDRIVER_H_ */
