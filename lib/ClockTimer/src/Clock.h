#ifndef _CLOCK_H_
#define _CLOCK_H_

#include "RtcWrapper.h"

enum ClockMode {
    TIME,
    DATE,
    YEAR,
    ALARM
};

typedef void (*alarmCallback_t)(bool state);

class Clock {
    public:
        void init();
        void setDateTime(const DateTime& dt);
        void setAlarm(uint8_t hour, uint8_t minute);
        DateTime now();
        bool alarmActivated() const { return _alarmActivated; }

        void tick();

        uint16_t time();
        uint16_t date();
        uint16_t year();
        uint16_t alarm();        

        ClockMode mode() const       { return _mode; }
        void setMode(ClockMode mode);
        void nextMode();

        void setAlarmCallback(alarmCallback_t callback);

        virtual uint16_t displayValue();
        virtual uint8_t displayFlags();
        virtual void button1();
        virtual void button2();
        virtual void button3();
        virtual void switch1(bool state);

    private:
        ClockMode _mode = TIME;
        bool _alarmActivated;
        bool _alarmRunning = false;
        RtcWrapper _rtc;
        alarmCallback_t _alarmCallback = NULL;

        uint8_t alarmHour();
        uint8_t alarmMinute();
        void setAlarmHour(uint8_t hour);
        void setAlarmMinute(uint8_t minute);

        void incrementHour();
        void incrementMinute();
        void incrementMonth();
        void incrementDay();
        void incrementYear();
        void decrementYear();
        void incrementAlarmHour();
        void incrementAlarmMinute();
};

#endif
