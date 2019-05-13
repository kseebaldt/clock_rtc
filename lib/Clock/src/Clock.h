#ifndef _CLOCK_H_
#define _CLOCK_H_

#include "RtcWrapper.h"

enum ClockMode {
    TIME,
    DATE,
    YEAR
};

class Clock {
    public:
        void start();
        void setDateTime(const DateTime& dt);
        DateTime now();

        uint16_t time();
        uint16_t date();
        uint16_t year();

        uint16_t displayValue();

        ClockMode mode() const       { return _mode; }
        void setMode(ClockMode mode);
        void nextMode();

        void increment();
        void decrement();

    private:
        ClockMode _mode = TIME;
        RtcWrapper _rtc;
};

#endif
