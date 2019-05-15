#include "Clock.h"
#include "DisplayFlags.h"

void Clock::init() {
    _rtc.begin();

    if (! _rtc.isrunning()) {
        _rtc.adjust(DateTime(2019, 5, 12, 0, 0, 0));
    }
}

void Clock::setDateTime(const DateTime& dt) {
    _rtc.adjust(dt);
}

void Clock::setAlarm(uint8_t hour, uint8_t minute) {
    _alarmHour = hour;
    _alarmMinute = minute;
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

uint16_t Clock::alarm() {
    return _alarmHour * 100 + _alarmMinute;
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
        _mode = ALARM;
        break;
    case ALARM:
        _mode = TIME;
        break;
    }
}

void Clock::incrementHour() {
    DateTime now = _rtc.now();
    if (now.hour() == 23) {
        _rtc.adjust(DateTime(now.year(), now.month(), now.day(), 
                0, now.minute(), now.second()));
    } else {
        _rtc.adjust(DateTime(now.year(), now.month(), now.day(), 
                now.hour() + 1, now.minute(), now.second()));
    }
}

void Clock::incrementMinute() {
    DateTime now = _rtc.now();
    if (now.minute() == 59) {
        _rtc.adjust(DateTime(now.year(), now.month(), now.day(), 
                now.hour(), 0, now.second()));
    } else {
        _rtc.adjust(DateTime(now.year(), now.month(), now.day(), 
                now.hour(), now.minute() + 1, now.second()));
    }
}

void Clock::incrementMonth() {
     DateTime now = _rtc.now();
    if (now.month() == 12) {
        _rtc.adjust(DateTime(now.year(), 1, now.day(), 
                now.hour(), now.minute(), now.second()));
    } else {
        _rtc.adjust(DateTime(now.year(), now.month() + 1, now.day(), 
                now.hour(), now.minute(), now.second()));
    }
}

void Clock::incrementDay() {
    DateTime now = _rtc.now();

    DateTime next = now + TimeSpan(1, 0, 0, 0);
    if (next.month() == now.month()) {
        _rtc.adjust(next);
    } else {
        _rtc.adjust(DateTime(now.year(), now.month(), 1,
                now.hour(), now.minute(), now.second()));
    }
}

void Clock::incrementYear() {
    DateTime now = _rtc.now();
    _rtc.adjust(DateTime(now.year() + 1, now.month(), now.day(), 
                now.hour(), now.minute(), now.second()));
}

void Clock::decrementYear() {
    DateTime now = _rtc.now();
    _rtc.adjust(DateTime(now.year() - 1, now.month(), now.day(), 
                now.hour(), now.minute(), now.second()));
}

void Clock::incrementAlarmHour() {
    _alarmHour = (_alarmHour + 1) % 24;
}

void Clock::incrementAlarmMinute() {
    _alarmMinute = (_alarmMinute + 1) % 60;
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
    case ALARM:
        return alarm();
    default:
        return time();
    }
}

uint8_t Clock::displayFlags() {
    switch (_mode)
    {
    case TIME:
        return _rtc.now().second() % 2 == 0 ? DISPLAY_L1_L2 : DISPLAY_NONE;
    case DATE:
        return DISPLAY_DP2;
    case ALARM:
        return DISPLAY_L1_L2;
    case YEAR:
    default:
        return DISPLAY_NONE;
    }
}

void Clock::button1() {
    switch (_mode)
    {
    case TIME:
        incrementHour();
        break;
    case DATE:
        incrementMonth();
        break;
    case YEAR:
        incrementYear();
        break;
    case ALARM:
        incrementAlarmHour();
        break;
    }
}

void Clock::button2() {
    switch (_mode)
    {
    case TIME:
        incrementMinute();
        break;
    case DATE:
        incrementDay();
        break;
    case YEAR:
        decrementYear();
        break;
    case ALARM:
        incrementAlarmMinute();
        break;
    }
}

void Clock::button3() {
    nextMode();
}

void Clock::switch1(bool state) {
    _alarmOn = state;
}
