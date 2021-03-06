#include <unity.h>

namespace Test_BcdDriver {
    void runTests(void);
}

namespace Test_Clock {
    void runTests(void);
}

namespace Test_Timer {
    void runTests(void);
}

namespace Test_Button {
    void runTests(void);
}

void process() {
    UNITY_BEGIN();

    Test_BcdDriver::runTests();
    Test_Button::runTests();
    Test_Clock::runTests();
    Test_Timer::runTests();

    UNITY_END();
}

#ifdef ARDUINO

#include <Arduino.h>
void setup() {
    // NOTE!!! Wait for >2 secs
    // if board doesn't support software reset via Serial.DTR/RTS
    delay(2000);

    process();
}

void loop() {
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
    delay(500);
}

#else

int main(int argc, char **argv) {
    process();
    return 0;
}

#endif