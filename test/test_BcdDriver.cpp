#include <BcdDriver.h>
#include <unity.h>

#include <stdio.h>

extern uint8_t _fake_pinModes[20];

void reset() {
    for (int i = 0; i < 14; ++i) {
        arduino.digitalWrite(i, 99);
    }
}

void test_initPins(void) {
    BcdDriver driver(1, 2, 3, 4, 4, 10, 11, 12, 13);

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
    BcdDriver driver(1, 2, 3, 4, 1, 9);

    driver.setValue(0);
    driver.display();

    TEST_ASSERT_EQUAL(LOW, arduino.digitalRead(1));
    TEST_ASSERT_EQUAL(LOW, arduino.digitalRead(2));
    TEST_ASSERT_EQUAL(LOW, arduino.digitalRead(3));
    TEST_ASSERT_EQUAL(LOW, arduino.digitalRead(4));
}

void test_display_1(void) {
    BcdDriver driver(1, 2, 3, 4, 1, 9);

    driver.setValue(1);
    driver.display();

    TEST_ASSERT_EQUAL(HIGH, arduino.digitalRead(1));
    TEST_ASSERT_EQUAL(LOW, arduino.digitalRead(2));
    TEST_ASSERT_EQUAL(LOW, arduino.digitalRead(3));
    TEST_ASSERT_EQUAL(LOW, arduino.digitalRead(4));
}

void test_display_2(void) {
    BcdDriver driver(1, 2, 3, 4, 1, 9);

    driver.setValue(2);
    driver.display();

    TEST_ASSERT_EQUAL(LOW, arduino.digitalRead(1));
    TEST_ASSERT_EQUAL(HIGH, arduino.digitalRead(2));
    TEST_ASSERT_EQUAL(LOW, arduino.digitalRead(3));
    TEST_ASSERT_EQUAL(LOW, arduino.digitalRead(4));
}

void test_display_3(void) {
    BcdDriver driver(1, 2, 3, 4, 1, 9);

    driver.setValue(3);
    driver.display();

    TEST_ASSERT_EQUAL(HIGH, arduino.digitalRead(1));
    TEST_ASSERT_EQUAL(HIGH, arduino.digitalRead(2));
    TEST_ASSERT_EQUAL(LOW, arduino.digitalRead(3));
    TEST_ASSERT_EQUAL(LOW, arduino.digitalRead(4));
}

void test_display_4(void) {
    BcdDriver driver(1, 2, 3, 4, 1, 9);

    driver.setValue(4);
    driver.display();

    TEST_ASSERT_EQUAL(LOW, arduino.digitalRead(1));
    TEST_ASSERT_EQUAL(LOW, arduino.digitalRead(2));
    TEST_ASSERT_EQUAL(HIGH, arduino.digitalRead(3));
    TEST_ASSERT_EQUAL(LOW, arduino.digitalRead(4));
}

void test_display_5(void) {
    BcdDriver driver(1, 2, 3, 4, 1, 9);

    driver.setValue(5);
    driver.display();

    TEST_ASSERT_EQUAL(HIGH, arduino.digitalRead(1));
    TEST_ASSERT_EQUAL(LOW, arduino.digitalRead(2));
    TEST_ASSERT_EQUAL(HIGH, arduino.digitalRead(3));
    TEST_ASSERT_EQUAL(LOW, arduino.digitalRead(4));
}

void test_display_6(void) {
    BcdDriver driver(1, 2, 3, 4, 1, 9);

    driver.setValue(6);
    driver.display();

    TEST_ASSERT_EQUAL(LOW, arduino.digitalRead(1));
    TEST_ASSERT_EQUAL(HIGH, arduino.digitalRead(2));
    TEST_ASSERT_EQUAL(HIGH, arduino.digitalRead(3));
    TEST_ASSERT_EQUAL(LOW, arduino.digitalRead(4));
}

void test_display_7(void) {
    BcdDriver driver(1, 2, 3, 4, 1, 9);

    driver.setValue(7);
    driver.display();

    TEST_ASSERT_EQUAL(HIGH, arduino.digitalRead(1));
    TEST_ASSERT_EQUAL(HIGH, arduino.digitalRead(2));
    TEST_ASSERT_EQUAL(HIGH, arduino.digitalRead(3));
    TEST_ASSERT_EQUAL(LOW, arduino.digitalRead(4));
}

void test_display_8(void) {
    BcdDriver driver(1, 2, 3, 4, 1, 9);

    driver.setValue(8);
    driver.display();

    TEST_ASSERT_EQUAL(LOW, arduino.digitalRead(1));
    TEST_ASSERT_EQUAL(LOW, arduino.digitalRead(2));
    TEST_ASSERT_EQUAL(LOW, arduino.digitalRead(3));
    TEST_ASSERT_EQUAL(HIGH, arduino.digitalRead(4));
}

void test_display_9(void) {
    BcdDriver driver(1, 2, 3, 4, 1, 9);

    driver.setValue(9);
    driver.display();

    TEST_ASSERT_EQUAL(HIGH, arduino.digitalRead(1));
    TEST_ASSERT_EQUAL(LOW, arduino.digitalRead(2));
    TEST_ASSERT_EQUAL(LOW, arduino.digitalRead(3));
    TEST_ASSERT_EQUAL(HIGH, arduino.digitalRead(4));
}

void test_display_multiDigit(void) {
    BcdDriver driver(1, 2, 3, 4, 2, 10, 11);
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

void process() {
    UNITY_BEGIN();

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