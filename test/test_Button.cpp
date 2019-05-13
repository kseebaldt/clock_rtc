#define private public

#include <Button.h>
#include <unity.h>

#include "ArduinoWrapper.h"

extern uint8_t _fake_pinModes[20];
extern unsigned long _fake_millis;

int _callCount = 0;

namespace Test_Button {

    void callme(Button& button) {
        ++_callCount;
    }

    void test_init(void) {
        Button button = Button(5);

        button.init();

        TEST_ASSERT_EQUAL(INPUT_PULLUP, _fake_pinModes[5]);
    }

    void test_tick_does_not_change_state_before_delay(void) {
        Button button = Button(5);
        button.init();

        _fake_millis = 0;
        arduino.digitalWrite(5, LOW);
        button.tick();

        _fake_millis = 50;
        button.tick();

        TEST_ASSERT_EQUAL(HIGH, button.state());
    }

    void test_tick_changes_state_after_delay(void) {
        Button button = Button(5);
        button.init();

        _fake_millis = 0;
        arduino.digitalWrite(5, LOW);
        button.tick();

        _fake_millis = 51;
        button.tick();

        TEST_ASSERT_EQUAL(LOW, button.state());
    }

    void test_tick_does_not_revert_state_before_delay(void) {
        Button button = Button(5);
        button.init();

        _fake_millis = 0;
        arduino.digitalWrite(5, LOW);
        button.tick();

        _fake_millis = 51;
        button.tick();

        TEST_ASSERT_EQUAL(LOW, button.state());

        arduino.digitalWrite(5, HIGH);
        _fake_millis = 60;
        button.tick();

        _fake_millis = 110;
        button.tick();

        TEST_ASSERT_EQUAL(LOW, button.state());
    }

    void test_tick_reverts_state_after_delay(void) {
        Button button = Button(5);
        button.init();

        _fake_millis = 0;
        arduino.digitalWrite(5, LOW);
        button.tick();

        _fake_millis = 51;
        button.tick();

        TEST_ASSERT_EQUAL(LOW, button.state());

        arduino.digitalWrite(5, HIGH);
        _fake_millis = 60;
        button.tick();

        _fake_millis = 111;
        button.tick();

        TEST_ASSERT_EQUAL(HIGH, button.state());
    }

    void test_tick_calls_callback_after_delay(void) {
        _callCount = 0;

        Button button = Button(5);
        button.init();
        button.setCallback(&callme);

        _fake_millis = 0;
        arduino.digitalWrite(5, LOW);
        button.tick();

        _fake_millis = 51;
        button.tick();

        TEST_ASSERT_EQUAL(1, _callCount);
    }

    void test_tick_calls_callback_again_after_repeatTime(void) {
        _callCount = 0;

        Button button = Button(5);
        button.init();
        button.setCallback(&callme, 100);

        _fake_millis = 0;
        arduino.digitalWrite(5, LOW);
        button.tick();

        _fake_millis = 51;
        button.tick();

        _fake_millis = 151;
        button.tick();

        _fake_millis = 152;
        button.tick();

        TEST_ASSERT_EQUAL(2, _callCount);
    }    

    void runTests() {
        RUN_TEST(test_init);
        RUN_TEST(test_tick_does_not_change_state_before_delay);
        RUN_TEST(test_tick_changes_state_after_delay);
        RUN_TEST(test_tick_does_not_revert_state_before_delay);
        RUN_TEST(test_tick_reverts_state_after_delay);
        RUN_TEST(test_tick_calls_callback_after_delay);
        RUN_TEST(test_tick_calls_callback_again_after_repeatTime);
    }
}
