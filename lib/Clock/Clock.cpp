#include "Clock.h"

void Clock::start() {
    rtc.begin();

    if (! rtc.isrunning()) {
        rtc.adjust(DateTime(2019, 5, 12, 0, 0, 0));
    }
}

void Clock::setDateTime(const DateTime& dt) {
    rtc.adjust(dt);
}

uint16_t Clock::time() {
    DateTime now = rtc.now();
    return now.hour() * 100 + now.minute();
}

uint16_t Clock::date() {
    DateTime now = rtc.now();
    return now.month() * 100 + now.day();
}

uint16_t Clock::year() {
    return rtc.now().year();
}


DateTime Clock::now() {
    return rtc.now();
}