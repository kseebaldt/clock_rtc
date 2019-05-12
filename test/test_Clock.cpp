#define private public

#include <Clock.h>
#include <unity.h>

#include <stdio.h>

namespace Test_Clock {

    void test_start(void) {
        Clock clock;

        TEST_ASSERT(!clock.rtc.isrunning());

        clock.start();

        TEST_ASSERT_EQUAL(2019, clock.now().year());
        TEST_ASSERT(clock.rtc.isrunning());
    }

    void test_setTime(void) {
        Clock clock;

        DateTime time = DateTime(2019, 5, 12, 3, 45, 56);

        clock.setDateTime(time);

        DateTime currentTime = clock.now();

        TEST_ASSERT_EQUAL(2019, currentTime.year());
        TEST_ASSERT_EQUAL(5, currentTime.month());
        TEST_ASSERT_EQUAL(12, currentTime.day());
        TEST_ASSERT_EQUAL(3, currentTime.hour());
        TEST_ASSERT_EQUAL(45, currentTime.minute());
        TEST_ASSERT_EQUAL(56, currentTime.second());
    }

    void test_time_1digithour(void) {
        Clock clock;

        clock.setDateTime(DateTime(2019, 5, 12, 3, 45, 56));

        TEST_ASSERT_EQUAL(345, clock.time());
    }

    void test_time_2digithour(void) {
        Clock clock;

        clock.setDateTime(DateTime(2019, 5, 12, 12, 45, 56));

        TEST_ASSERT_EQUAL(1245, clock.time());
    }

    void test_date_1digitmonth(void) {
        Clock clock;

        clock.setDateTime(DateTime(2019, 5, 12, 12, 45, 56));

        TEST_ASSERT_EQUAL(512, clock.date());
    }

    void test_date_2digitmonth(void) {
        Clock clock;

        clock.setDateTime(DateTime(2019, 11, 12, 12, 45, 56));

        TEST_ASSERT_EQUAL(1112, clock.date());
    }

    void test_date_1digitday(void) {
        Clock clock;

        clock.setDateTime(DateTime(2019, 5, 8, 12, 45, 56));

        TEST_ASSERT_EQUAL(508, clock.date());
    }

    void test_year(void) {
        Clock clock;

        clock.setDateTime(DateTime(2019, 5, 8, 12, 45, 56));

        TEST_ASSERT_EQUAL(2019, clock.year());
    }

    void runTests() {
        RUN_TEST(test_start);
        RUN_TEST(test_setTime);
        RUN_TEST(test_time_1digithour);
        RUN_TEST(test_time_2digithour);
        RUN_TEST(test_date_1digitmonth);
        RUN_TEST(test_date_2digitmonth);
        RUN_TEST(test_date_1digitday);
        RUN_TEST(test_year);
    }
}
