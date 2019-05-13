#include "Clock.h"

void Clock::start() {
    _rtc.begin();

    if (! _rtc.isrunning()) {
        _rtc.adjust(DateTime(2019, 5, 12, 0, 0, 0));
    }
}

void Clock::setDateTime(const DateTime& dt) {
    _rtc.adjust(dt);
}

uint16_t Clock::time() {
    DateTime now = _rtc.now();
    return now.hour() * 100 + now.minute();
}

uint16_t Clock::date() {
    DateTime now = _rtc.now();
    return now.month() * 100 + now.day();
}

uint16_t Clock::year() {
    return _rtc.now().year();
}

DateTime Clock::now() {
    return _rtc.now();
}

void Clock::setMode(ClockMode mode) {
    _mode = mode;
}

void Clock::nextMode() {
    switch (_mode)
    {
    case TIME:
        _mode = DATE;
        break;
    case DATE:
        _mode = YEAR;
        break;
    case YEAR:
        _mode = TIME;
        break;
    }
}

uint16_t Clock::displayValue() {
    switch (_mode)
    {
    case TIME:
        return time();
    case DATE:
        return date();
    case YEAR:
        return year();
    default:
        return time();
    }
}

void Clock::increment() {
    switch (_mode)
    {
    case TIME:
        _rtc.adjust(_rtc.now() + TimeSpan(0, 0, 1, 0));
        break;
    case DATE:
        _rtc.adjust(_rtc.now() + TimeSpan(1, 0, 0, 0));
        break;
    case YEAR:
        DateTime now = _rtc.now();
        _rtc.adjust(DateTime(now.year() + 1, now.month(), now.day(), now.hour(), now.minute(), now.second()));
        break;
    }
}

void Clock::decrement() {
    switch (_mode)
    {
    case TIME:
        _rtc.adjust(_rtc.now() + TimeSpan(0, 0, -1, 0));
        break;
    case DATE:
        _rtc.adjust(_rtc.now() + TimeSpan(-1, 0, 0, 0));
        break;
    case YEAR:
        DateTime now = _rtc.now();
        _rtc.adjust(DateTime(now.year() - 1, now.month(), now.day(), now.hour(), now.minute(), now.second()));
        break;
    }
}
