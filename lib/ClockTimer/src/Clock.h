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
        void init();
        void setDateTime(const DateTime& dt);
        DateTime now();

        uint16_t time();
        uint16_t date();
        uint16_t year();

        ClockMode mode() const       { return _mode; }
        void setMode(ClockMode mode);
        void nextMode();

        void incrementHour();
        void incrementMinute();
        void incrementMonth();
        void incrementDay();
        void incrementYear();
        void decrementYear();

        virtual uint16_t displayValue();
        virtual uint8_t displayFlags();
        virtual void button1();
        virtual void button2();
        virtual void button3();
        virtual void switch1(bool state);

    private:
        ClockMode _mode = TIME;
        RtcWrapper _rtc;
};

#endif
