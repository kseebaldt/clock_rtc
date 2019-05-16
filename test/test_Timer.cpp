#define private public

#include <Timer.h>
#include <unity.h>

extern unsigned long _fake_millis;

namespace Test_Timer {

static bool _called = false;
static bool _alarmState = false;

    void callback(bool state) {
        _called = true;
        _alarmState = state;
    }

    void test_displayValue_returnsMinutesSeconds(void) {
        Timer timer;
        timer.reset();

        timer.setSecondsRemaining(921);

        TEST_ASSERT_EQUAL(1521, timer.displayValue());
    }

    void test_tick_decrementsTimeRemainingWhenStarted(void) {
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

   void test_tick_stopsAtZero(void) {
        Timer timer;
        timer.reset();
        
        timer.setSecondsRemaining(1);

        _fake_millis = 1;
        timer.setRunning(true);
        timer.tick();

        _fake_millis = 1001;
        timer.tick();

        TEST_ASSERT_EQUAL(0, timer.displayValue());

        _fake_millis = 2001;
        timer.tick();

        TEST_ASSERT_EQUAL(0, timer.displayValue());
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

    void test_button3_startsAndStopsTimer(void) {
        Timer timer;
        timer.reset();

        timer.setSecondsRemaining(300);
        timer.setRunning(false);

        timer.button3();
        TEST_ASSERT(timer.isRunning());

        timer.button3();
        TEST_ASSERT(!timer.isRunning());
    }

     void test_button3_doesNotStartTimerIfAtZero(void) {
        Timer timer;
        timer.reset();

        timer.setSecondsRemaining(0);
        timer.setRunning(false);

        timer.button3();
        TEST_ASSERT(!timer.isRunning());
    }

    void test_button3Long_resetsTimer(void) {
        Timer timer;
        timer.reset();

        timer.setSecondsRemaining(300);
        timer.setRunning(false);

        timer.button3Long();
        TEST_ASSERT_EQUAL(0, timer.secondsRemaining());
        TEST_ASSERT(!timer.isRunning());
    }

    void test_alarmCallbackCalledWhenTimerReachesZero(void) {
        Timer timer;
        timer.reset();
        
        timer.setSecondsRemaining(5);
        timer.setAlarmCallback(callback);

        _fake_millis = 1;
        _called = false;
        timer.setRunning(true);
        timer.tick();

        timer.tick();
        TEST_ASSERT(!_called);

        _fake_millis = 5001;
        timer.tick();
        TEST_ASSERT(_called);
        TEST_ASSERT(_alarmState);

        _called = false;
        _fake_millis = 5002;
        timer.tick();
        TEST_ASSERT(!_called);
    }

    void test_alarmCallback_whenReset_CallsCallbackIfRunning(void) {
        Timer timer;
        timer.reset();
        
        timer.setSecondsRemaining(5);
        timer.setAlarmCallback(callback);

        _fake_millis = 1;
        _called = false;
        timer.setRunning(true);
        timer.tick();

        timer.tick();
        TEST_ASSERT(!_called);

        _fake_millis = 5001;
        timer.tick();
        TEST_ASSERT(_called);
        TEST_ASSERT(_alarmState);

        _called = false;
        timer.button3();
        timer.tick();
        TEST_ASSERT(_called);
        TEST_ASSERT(!_alarmState);
    }

    void test_alarmCallback_whenStopped_CallsCallbackIfRunning(void) {
        Timer timer;
        timer.reset();
        
        timer.setSecondsRemaining(5);
        timer.setAlarmCallback(callback);

        _fake_millis = 1;
        _called = false;
        timer.setRunning(true);
        timer.tick();

        timer.tick();
        TEST_ASSERT(!_called);

        _fake_millis = 5001;
        timer.tick();
        TEST_ASSERT(_called);
        TEST_ASSERT(_alarmState);

        _called = false;
        timer.button3();
        timer.tick();
        TEST_ASSERT(_called);
        TEST_ASSERT(!_alarmState);
    }    

    void runTests() {
        RUN_TEST(test_displayValue_returnsMinutesSeconds);
        RUN_TEST(test_tick_decrementsTimeRemainingWhenStarted);
        RUN_TEST(test_tick_stopsAtZero);
        RUN_TEST(test_tick_doesNotDecrementIfTimerIsNotStarted);
        RUN_TEST(test_button1_incrementsTimerBy5Minutes);
        RUN_TEST(test_button2_incrementsTimerBy1Minute);
        RUN_TEST(test_button3_startsAndStopsTimer);
        RUN_TEST(test_button3_doesNotStartTimerIfAtZero);
        RUN_TEST(test_button3Long_resetsTimer);
        RUN_TEST(test_alarmCallbackCalledWhenTimerReachesZero);
        RUN_TEST(test_alarmCallback_whenReset_CallsCallbackIfRunning);
        RUN_TEST(test_alarmCallback_whenStopped_CallsCallbackIfRunning);
    }
}
