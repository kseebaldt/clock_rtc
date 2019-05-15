#ifndef _MODE_H_
#define _MODE_H_

#include <stdint.h>

class Mode {
    public:
    virtual uint16_t displayValue() = 0;
    virtual uint8_t displayFlags() = 0;
    virtual void button1() = 0;
    virtual void button2() = 0;
    virtual void button3() = 0;
    virtual void switch1(bool state) = 0;
};

#endif