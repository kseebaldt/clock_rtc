#include "RtcWrapper.h"

#ifndef ARDUINO

static DateTime current;

DateTime::DateTime (uint32_t t) {
    yOff = 0;
    m = 1;
    d = 1;
    hh = 1;
    mm = 1;
    ss = 1;
}

DateTime::DateTime (uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t min, uint8_t sec) {
    if (year >= 2000)
        year -= 2000;
    yOff = year;
    m = month;
    d = day;
    hh = hour;
    mm = min;
    ss = sec;
}

DateTime::DateTime (const DateTime& copy):
  yOff(copy.yOff),
  m(copy.m),
  d(copy.d),
  hh(copy.hh),
  mm(copy.mm),
  ss(copy.ss)
{}

    boolean RtcWrapper::begin(void) {
        return true;
    }

    void RtcWrapper::adjust(const DateTime& dt) {
        current = dt;
    }

    uint8_t RtcWrapper::isrunning(void) {
        return current.year() != 2000;
    }

    DateTime RtcWrapper::now() {
        return current;
    }

#endif
