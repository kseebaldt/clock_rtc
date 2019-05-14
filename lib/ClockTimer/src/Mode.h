#include <stdint.h>

class Mode {
    virtual uint16_t displayValue() = 0;
    virtual void button1() = 0;
    virtual void button2() = 0;
    virtual void button3() = 0;
    virtual void switch1() = 0;
};
