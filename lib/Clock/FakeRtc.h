#ifndef _FAKERTC_H_
#define _FAKERTC_H_

#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

typedef bool boolean;

class DateTime {
public:
    DateTime (uint32_t t = 0);
    DateTime (uint16_t year, uint8_t month, uint8_t day,
                uint8_t hour = 0, uint8_t min = 0, uint8_t sec = 0);
    DateTime (const DateTime& copy);
    DateTime (const char* date, const char* time);
    uint16_t year() const       { return 2000 + yOff; }
    uint8_t month() const       { return m; }
    uint8_t day() const         { return d; }
    uint8_t hour() const        { return hh; }
    uint8_t minute() const      { return mm; }
    uint8_t second() const      { return ss; }

protected:
    uint8_t yOff, m, d, hh, mm, ss;
};

#endif // _RTCLIB_H_