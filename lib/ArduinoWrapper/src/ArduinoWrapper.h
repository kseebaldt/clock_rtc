#ifndef ARDUINOWRAPPER_H
#define ARDUINOWRAPPER_H

#ifdef ARDUINO
    #include "Arduino.h"
#else
    #include "FakeArduino.h"
#endif

class ArduinoWrapper {
    public:
        void pinMode(uint8_t, uint8_t);
        void digitalWrite(uint8_t, uint8_t);
        int digitalRead(uint8_t);
        void delay(unsigned long);
   
    private:
        struct FakeArduino;
};

extern ArduinoWrapper arduino;

#endif /* ARDUINOWRAPPER_H */
