#define private public

#include <Timer.h>
#include <unity.h>

extern unsigned long _fake_millis;

namespace Test_Timer {

    void test_displayValue_returnsMinutesSeconds(void) {
        Timer timer;
        timer.setSecondsRemaining(921);

        TEST_ASSERT_EQUAL(1521, timer.displayValue());
    }

    void test_tick_decrementsTimeRemaingingWhenStarted(void) {
        Timer timer;
        timer.setSecondsRemaining(921);

        _fake_millis = 0;
        timer.start();

        _fake_millis = 1500;
        timer.tick();

        TEST_ASSERT_EQUAL(1520, timer.displayValue());
    }

    void test_tick_doesNotDecrementIfTimerIsNotStarted(void) {
        Timer timer;
        timer.setSecondsRemaining(921);

        _fake_millis = 1500;
        timer.tick();

        TEST_ASSERT_EQUAL(1521, timer.displayValue());
    }

    void runTests() {
        RUN_TEST(test_displayValue_returnsMinutesSeconds);
        RUN_TEST(test_tick_decrementsTimeRemaingingWhenStarted);
        RUN_TEST(test_tick_doesNotDecrementIfTimerIsNotStarted);
    }
}
