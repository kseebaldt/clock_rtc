#ifndef _CLOCK_H_
#define _CLOCK_H_

#include "RtcWrapper.h"

class Clock {
    public:
        void start();
        void setDateTime(const DateTime& dt);
        DateTime now();

        uint16_t time();
        uint16_t date();
        uint16_t year();

    private:
        RtcWrapper rtc;
};

#endif
