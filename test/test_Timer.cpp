#define private public

#include <Timer.h>
#include <unity.h>

extern unsigned long _fake_millis;

namespace Test_Timer {

    void test_displayValue_returnsMinutesSeconds(void) {
        Timer timer;
        timer.reset();

        timer.setSecondsRemaining(921);

        TEST_ASSERT_EQUAL(1521, timer.displayValue());
    }

    void test_tick_decrementsTimeRemaingingWhenStarted(void) {
        Timer timer;
        timer.reset();
        
        timer.setSecondsRemaining(921);

        _fake_millis = 1;
        timer.setRunning(true);
        timer.tick();

        _fake_millis = 1500;
        timer.tick();

        TEST_ASSERT_EQUAL(1520, timer.displayValue());
    }

    void test_tick_doesNotDecrementIfTimerIsNotStarted(void) {
        Timer timer;
        timer.reset();

        timer.setSecondsRemaining(921);

        _fake_millis = 1500;
        timer.tick();

        TEST_ASSERT_EQUAL(1521, timer.displayValue());
    }

    void test_button1_incrementsTimerBy5Minutes(void) {
        Timer timer;
        timer.reset();

        timer.setSecondsRemaining(0);

        timer.button1();

        TEST_ASSERT_EQUAL(500, timer.displayValue());
    }

    void test_button2_incrementsTimerBy1Minute(void) {
        Timer timer;
        timer.reset();

        timer.setSecondsRemaining(0);

        timer.button2();

        TEST_ASSERT_EQUAL(100, timer.displayValue());
    }

    void test_button3_resetsTimer(void) {
        Timer timer;
        timer.reset();

        timer.setSecondsRemaining(300);

        timer.button3();

        TEST_ASSERT_EQUAL(0, timer.displayValue());
    }

    void runTests() {
        RUN_TEST(test_displayValue_returnsMinutesSeconds);
        RUN_TEST(test_tick_decrementsTimeRemaingingWhenStarted);
        RUN_TEST(test_tick_doesNotDecrementIfTimerIsNotStarted);
        RUN_TEST(test_button1_incrementsTimerBy5Minutes);
        RUN_TEST(test_button2_incrementsTimerBy1Minute);
        RUN_TEST(test_button3_resetsTimer);
    }
}
