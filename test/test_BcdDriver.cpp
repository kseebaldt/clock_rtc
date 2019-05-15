#include <BcdDriver.h>
#include <unity.h>

#include <stdio.h>
#include "DisplayFlags.h"

extern uint8_t _fake_pinModes[20];

namespace Test_BcdDriver {

    void reset() {
        for (int i = 0; i < 14; ++i) {
            arduino.digitalWrite(i, 99);
        }
    }

    void test_initPins(void) {
        BcdDriver driver(1, 2, 3, 4, 5, 6, 4, 10, 11, 12, 13);

        driver.initPins();

        TEST_ASSERT_EQUAL(OUTPUT, _fake_pinModes[1]);
        TEST_ASSERT_EQUAL(OUTPUT, _fake_pinModes[2]);
        TEST_ASSERT_EQUAL(OUTPUT, _fake_pinModes[3]);
        TEST_ASSERT_EQUAL(OUTPUT, _fake_pinModes[4]);
        TEST_ASSERT_EQUAL(OUTPUT, _fake_pinModes[10]);
        TEST_ASSERT_EQUAL(OUTPUT, _fake_pinModes[11]);
        TEST_ASSERT_EQUAL(OUTPUT, _fake_pinModes[12]);
        TEST_ASSERT_EQUAL(OUTPUT, _fake_pinModes[13]);
    }

    void test_display_0(void) {
        BcdDriver driver(1, 2, 3, 4, 5, 6, 1, 9);

        driver.setValue(0);
        driver.display();

        TEST_ASSERT_EQUAL(LOW, arduino.digitalRead(1));
        TEST_ASSERT_EQUAL(LOW, arduino.digitalRead(2));
        TEST_ASSERT_EQUAL(LOW, arduino.digitalRead(3));
        TEST_ASSERT_EQUAL(LOW, arduino.digitalRead(4));
    }

    void test_display_1(void) {
        BcdDriver driver(1, 2, 3, 4, 5, 6, 1, 9);

        driver.setValue(1);
        driver.display();

        TEST_ASSERT_EQUAL(HIGH, arduino.digitalRead(1));
        TEST_ASSERT_EQUAL(LOW, arduino.digitalRead(2));
        TEST_ASSERT_EQUAL(LOW, arduino.digitalRead(3));
        TEST_ASSERT_EQUAL(LOW, arduino.digitalRead(4));
    }

    void test_display_2(void) {
        BcdDriver driver(1, 2, 3, 4, 5, 6, 1, 9);

        driver.setValue(2);
        driver.display();

        TEST_ASSERT_EQUAL(LOW, arduino.digitalRead(1));
        TEST_ASSERT_EQUAL(HIGH, arduino.digitalRead(2));
        TEST_ASSERT_EQUAL(LOW, arduino.digitalRead(3));
        TEST_ASSERT_EQUAL(LOW, arduino.digitalRead(4));
    }

    void test_display_3(void) {
        BcdDriver driver(1, 2, 3, 4, 5, 6, 1, 9);

        driver.setValue(3);
        driver.display();

        TEST_ASSERT_EQUAL(HIGH, arduino.digitalRead(1));
        TEST_ASSERT_EQUAL(HIGH, arduino.digitalRead(2));
        TEST_ASSERT_EQUAL(LOW, arduino.digitalRead(3));
        TEST_ASSERT_EQUAL(LOW, arduino.digitalRead(4));
    }

    void test_display_4(void) {
        BcdDriver driver(1, 2, 3, 4, 5, 6, 1, 9);

        driver.setValue(4);
        driver.display();

        TEST_ASSERT_EQUAL(LOW, arduino.digitalRead(1));
        TEST_ASSERT_EQUAL(LOW, arduino.digitalRead(2));
        TEST_ASSERT_EQUAL(HIGH, arduino.digitalRead(3));
        TEST_ASSERT_EQUAL(LOW, arduino.digitalRead(4));
    }

    void test_display_5(void) {
        BcdDriver driver(1, 2, 3, 4, 5, 6, 1, 9);

        driver.setValue(5);
        driver.display();

        TEST_ASSERT_EQUAL(HIGH, arduino.digitalRead(1));
        TEST_ASSERT_EQUAL(LOW, arduino.digitalRead(2));
        TEST_ASSERT_EQUAL(HIGH, arduino.digitalRead(3));
        TEST_ASSERT_EQUAL(LOW, arduino.digitalRead(4));
    }

    void test_display_6(void) {
        BcdDriver driver(1, 2, 3, 4, 5, 6, 1, 9);

        driver.setValue(6);
        driver.display();

        TEST_ASSERT_EQUAL(LOW, arduino.digitalRead(1));
        TEST_ASSERT_EQUAL(HIGH, arduino.digitalRead(2));
        TEST_ASSERT_EQUAL(HIGH, arduino.digitalRead(3));
        TEST_ASSERT_EQUAL(LOW, arduino.digitalRead(4));
    }

    void test_display_7(void) {
        BcdDriver driver(1, 2, 3, 4, 5, 6, 1, 9);

        driver.setValue(7);
        driver.display();

        TEST_ASSERT_EQUAL(HIGH, arduino.digitalRead(1));
        TEST_ASSERT_EQUAL(HIGH, arduino.digitalRead(2));
        TEST_ASSERT_EQUAL(HIGH, arduino.digitalRead(3));
        TEST_ASSERT_EQUAL(LOW, arduino.digitalRead(4));
    }

    void test_display_8(void) {
        BcdDriver driver(1, 2, 3, 4, 5, 6, 1, 9);

        driver.setValue(8);
        driver.display();

        TEST_ASSERT_EQUAL(LOW, arduino.digitalRead(1));
        TEST_ASSERT_EQUAL(LOW, arduino.digitalRead(2));
        TEST_ASSERT_EQUAL(LOW, arduino.digitalRead(3));
        TEST_ASSERT_EQUAL(HIGH, arduino.digitalRead(4));
    }

    void test_display_9(void) {
        BcdDriver driver(1, 2, 3, 4, 5, 6, 1, 9);

        driver.setValue(9);
        driver.display();

        TEST_ASSERT_EQUAL(HIGH, arduino.digitalRead(1));
        TEST_ASSERT_EQUAL(LOW, arduino.digitalRead(2));
        TEST_ASSERT_EQUAL(LOW, arduino.digitalRead(3));
        TEST_ASSERT_EQUAL(HIGH, arduino.digitalRead(4));
    }

    void test_display_multiDigit(void) {
        BcdDriver driver(1, 2, 3, 4, 5, 6, 2, 10, 11);
        driver.setValue(12);

        driver.display();

        TEST_ASSERT_EQUAL(HIGH, arduino.digitalRead(1));
        TEST_ASSERT_EQUAL(LOW, arduino.digitalRead(2));
        TEST_ASSERT_EQUAL(LOW, arduino.digitalRead(3));
        TEST_ASSERT_EQUAL(LOW, arduino.digitalRead(4));

        TEST_ASSERT_EQUAL(LOW, arduino.digitalRead(10));
        TEST_ASSERT_EQUAL(HIGH, arduino.digitalRead(11));

        driver.display();

        TEST_ASSERT_EQUAL(LOW, arduino.digitalRead(1));
        TEST_ASSERT_EQUAL(HIGH, arduino.digitalRead(2));
        TEST_ASSERT_EQUAL(LOW, arduino.digitalRead(3));
        TEST_ASSERT_EQUAL(LOW, arduino.digitalRead(4));

        TEST_ASSERT_EQUAL(HIGH, arduino.digitalRead(10));
        TEST_ASSERT_EQUAL(LOW, arduino.digitalRead(11));

        driver.display();

        TEST_ASSERT_EQUAL(HIGH, arduino.digitalRead(1));
        TEST_ASSERT_EQUAL(LOW, arduino.digitalRead(2));
        TEST_ASSERT_EQUAL(LOW, arduino.digitalRead(3));
        TEST_ASSERT_EQUAL(LOW, arduino.digitalRead(4));

        TEST_ASSERT_EQUAL(LOW, arduino.digitalRead(10));
        TEST_ASSERT_EQUAL(HIGH, arduino.digitalRead(11));
    }

    void test_displayFlags_none(void) {
        BcdDriver driver(1, 2, 3, 4, 5, 6, 4, 9, 10, 11, 12);

        driver.setDisplayFlags(DISPLAY_NONE);

        // DP1
        driver.display();
        TEST_ASSERT_EQUAL(LOW, arduino.digitalRead(5));
        TEST_ASSERT_EQUAL(LOW, arduino.digitalRead(6));

        // DP2
        driver.display();
        TEST_ASSERT_EQUAL(LOW, arduino.digitalRead(5));

        // DP3
        driver.display();
        TEST_ASSERT_EQUAL(LOW, arduino.digitalRead(5));

        // DP4
        driver.display();
        TEST_ASSERT_EQUAL(LOW, arduino.digitalRead(5));
    }

    void test_displayFlags_dp1(void) {
        BcdDriver driver(1, 2, 3, 4, 5, 6, 4, 9, 10, 11, 12);

        driver.setDisplayFlags(DISPLAY_DP1);

        // DP1
        driver.display();
        TEST_ASSERT_EQUAL(HIGH, arduino.digitalRead(5));
        TEST_ASSERT_EQUAL(LOW, arduino.digitalRead(6));

        // DP2
        driver.display();
        TEST_ASSERT_EQUAL(LOW, arduino.digitalRead(5));

        // DP3
        driver.display();
        TEST_ASSERT_EQUAL(LOW, arduino.digitalRead(5));

        // DP4
        driver.display();
        TEST_ASSERT_EQUAL(LOW, arduino.digitalRead(5));
    }

    void test_displayFlags_dp2(void) {
        BcdDriver driver(1, 2, 3, 4, 5, 6, 4, 9, 10, 11, 12);

        driver.setDisplayFlags(DISPLAY_DP2);

        // DP1
        driver.display();
        TEST_ASSERT_EQUAL(LOW, arduino.digitalRead(5));
        TEST_ASSERT_EQUAL(LOW, arduino.digitalRead(6));

        // DP2
        driver.display();
        TEST_ASSERT_EQUAL(HIGH, arduino.digitalRead(5));

        // DP3
        driver.display();
        TEST_ASSERT_EQUAL(LOW, arduino.digitalRead(5));

        // DP4
        driver.display();
        TEST_ASSERT_EQUAL(LOW, arduino.digitalRead(5));
    }

    void test_displayFlags_dp3(void) {
        BcdDriver driver(1, 2, 3, 4, 5, 6, 4, 9, 10, 11, 12);

        driver.setDisplayFlags(DISPLAY_DP3);

        // DP1
        driver.display();
        TEST_ASSERT_EQUAL(LOW, arduino.digitalRead(5));
        TEST_ASSERT_EQUAL(LOW, arduino.digitalRead(6));

        // DP2
        driver.display();
        TEST_ASSERT_EQUAL(LOW, arduino.digitalRead(5));

        // DP3
        driver.display();
        TEST_ASSERT_EQUAL(HIGH, arduino.digitalRead(5));

        // DP4
        driver.display();
        TEST_ASSERT_EQUAL(LOW, arduino.digitalRead(5));
    }

    void test_displayFlags_dp4(void) {
        BcdDriver driver(1, 2, 3, 4, 5, 6, 4, 9, 10, 11, 12);

        driver.setDisplayFlags(DISPLAY_DP4);

        // DP1
        driver.display();
        TEST_ASSERT_EQUAL(LOW, arduino.digitalRead(5));
        TEST_ASSERT_EQUAL(LOW, arduino.digitalRead(6));

        // DP2
        driver.display();
        TEST_ASSERT_EQUAL(LOW, arduino.digitalRead(5));

        // DP3
        driver.display();
        TEST_ASSERT_EQUAL(LOW, arduino.digitalRead(5));

        // DP4
        driver.display();
        TEST_ASSERT_EQUAL(HIGH, arduino.digitalRead(5));
    }

    void test_displayFlags_l1_l2(void) {
        BcdDriver driver(1, 2, 3, 4, 5, 6, 4, 9, 10, 11, 12);

        driver.setDisplayFlags(DISPLAY_L1_L2);

        driver.display();
        TEST_ASSERT_EQUAL(HIGH, arduino.digitalRead(6));
    }

    void test_displayFlags_all(void) {
        BcdDriver driver(1, 2, 3, 4, 5, 6, 4, 9, 10, 11, 12);

        driver.setDisplayFlags(DISPLAY_DP1 | DISPLAY_DP2 | DISPLAY_DP3 | DISPLAY_DP4 | DISPLAY_L1_L2);

        // DP1
        driver.display();
        TEST_ASSERT_EQUAL(HIGH, arduino.digitalRead(5));
        TEST_ASSERT_EQUAL(HIGH, arduino.digitalRead(6));

        // DP2
        driver.display();
        TEST_ASSERT_EQUAL(HIGH, arduino.digitalRead(5));

        // DP3
        driver.display();
        TEST_ASSERT_EQUAL(HIGH, arduino.digitalRead(5));

        // DP4
        driver.display();
        TEST_ASSERT_EQUAL(HIGH, arduino.digitalRead(5));
    }

    void runTests() {
        reset();
        RUN_TEST(test_initPins);
        reset();
        RUN_TEST(test_display_0);
        reset();
        RUN_TEST(test_display_1);
        reset();
        RUN_TEST(test_display_2);
        reset();
        RUN_TEST(test_display_3);
        reset();
        RUN_TEST(test_display_4);
        reset();
        RUN_TEST(test_display_5);
        reset();
        RUN_TEST(test_display_6);
        reset();
        RUN_TEST(test_display_7);
        reset();
        RUN_TEST(test_display_8);
        reset();
        RUN_TEST(test_display_9);
        reset();
        RUN_TEST(test_display_multiDigit);
        reset();
        RUN_TEST(test_displayFlags_none);
        reset();
        RUN_TEST(test_displayFlags_dp1);
        reset();
        RUN_TEST(test_displayFlags_dp2);
        reset();
        RUN_TEST(test_displayFlags_dp3);
        reset();
        RUN_TEST(test_displayFlags_dp4);
        reset();
        RUN_TEST(test_displayFlags_l1_l2);
        reset();
        RUN_TEST(test_displayFlags_all);
    }
}
