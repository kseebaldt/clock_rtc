#ifndef _TIMER_H_
#define _TIMER_H_

#include "Mode.h"
#include "ArduinoWrapper.h"

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

        virtual uint16_t displayValue();
        virtual uint8_t displayFlags();
        virtual void button1();
        virtual void button2();
        virtual void button3();
        virtual void switch1(bool state);        

    private:
        bool _running;
        unsigned long _timeRemaining;
        unsigned long _lastTick;
};

#endif
