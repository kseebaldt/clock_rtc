#ifndef _TIMER_H_
#define _TIMER_H_

#include "Mode.h"
#include "ArduinoWrapper.h"

typedef void (*timerAlarmCallback_t)(bool state);

class Timer : Mode {
    public:
        void init();

        bool isRunning() const { return _running; }
        void setRunning(bool);
        void reset();
        void tick();
        void increment(uint8_t minutes = 1);

        uint16_t secondsRemaining();
        void setSecondsRemaining(uint16_t seconds);

        void setAlarmCallback(timerAlarmCallback_t callback);

        virtual uint16_t displayValue();
        virtual uint8_t displayFlags();
        virtual void button1();
        virtual void button2();
        virtual void button3();
        virtual void button3Long();
        virtual void switch1(bool state);        

    private:
        bool _running;
        bool _alarmRunning = false;
        unsigned long _timeRemaining;
        unsigned long _lastTick;
        timerAlarmCallback_t _alarmCallback = NULL;
};

#endif
