#define private public

#include <Clock.h>
#include <unity.h>

#include <stdio.h>

namespace Test_Clock {

    void test_start(void) {
        Clock clock;

        TEST_ASSERT(!clock._rtc.isrunning());

        clock.init();

        TEST_ASSERT_EQUAL(2019, clock.now().year());
        TEST_ASSERT(clock._rtc.isrunning());
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

    void test_display_mode(void) {
        Clock clock;

        clock.setDateTime(DateTime(2019, 5, 8, 12, 45, 56));

        TEST_ASSERT_EQUAL(1245, clock.displayValue());
        
        clock.nextMode();
        TEST_ASSERT_EQUAL(508, clock.displayValue());

        clock.nextMode();
        TEST_ASSERT_EQUAL(2019, clock.displayValue());

        clock.nextMode();
        TEST_ASSERT_EQUAL(1245, clock.displayValue());
    }

    void test_increment_hour(void) {
        Clock clock;

        clock.setDateTime(DateTime(2019, 5, 8, 12, 45, 56));

        clock.incrementHour();
        TEST_ASSERT_EQUAL(1345, clock.displayValue());
    }

    void test_increment_hour_rollover(void) {
        Clock clock;

        clock.setDateTime(DateTime(2019, 5, 8, 23, 45, 56));

        clock.incrementHour();
        TEST_ASSERT_EQUAL(45, clock.displayValue());

        clock.setMode(DATE);
        TEST_ASSERT_EQUAL(508, clock.displayValue());
    }

     void test_increment_minute(void) {
        Clock clock;

        clock.setDateTime(DateTime(2019, 5, 8, 12, 45, 56));

        clock.incrementMinute();
        TEST_ASSERT_EQUAL(1246, clock.displayValue());
    }

    void test_increment_minute_rollover(void) {
        Clock clock;

        clock.setDateTime(DateTime(2019, 5, 8, 12, 59, 56));

        clock.incrementMinute();
        TEST_ASSERT_EQUAL(1200, clock.displayValue());
    }

    void test_increment_month(void) {
        Clock clock;

        clock.setDateTime(DateTime(2019, 5, 8, 12, 45, 56));
        clock.setMode(DATE);

        clock.incrementMonth();
        TEST_ASSERT_EQUAL(608, clock.displayValue());
    }

    void test_increment_month_rollover(void) {
        Clock clock;

        clock.setDateTime(DateTime(2019, 12, 8, 23, 45, 56));
        clock.setMode(DATE);

        clock.incrementMonth();
        TEST_ASSERT_EQUAL(108, clock.displayValue());

        clock.setMode(YEAR);
        TEST_ASSERT_EQUAL(2019, clock.displayValue());
    }

    void test_increment_day(void) {
        Clock clock;

        clock.setDateTime(DateTime(2019, 5, 8, 12, 45, 56));
        clock.setMode(DATE);

        clock.incrementDay();
        TEST_ASSERT_EQUAL(509, clock.displayValue());
    }

    void test_increment_day_rollover_jan(void) {
        Clock clock;

        clock.setDateTime(DateTime(2019, 1, 31, 23, 45, 56));
        clock.setMode(DATE);

        clock.incrementDay();
        TEST_ASSERT_EQUAL(101, clock.displayValue());
    }

    void test_increment_day_rollover_feb(void) {
        Clock clock;

        clock.setDateTime(DateTime(2019, 2, 28, 23, 45, 56));
        clock.setMode(DATE);

        clock.incrementDay();
        TEST_ASSERT_EQUAL(201, clock.displayValue());
    }

    void test_increment_day_rollover_feb_leapyear(void) {
        Clock clock;

        clock.setDateTime(DateTime(2020, 2, 28, 23, 45, 56));
        clock.setMode(DATE);

        clock.incrementDay();
        TEST_ASSERT_EQUAL(229, clock.displayValue());

        clock.incrementDay();
        TEST_ASSERT_EQUAL(201, clock.displayValue());
    }

    void test_increment_year(void) {
        Clock clock;

        clock.setDateTime(DateTime(2019, 5, 8, 12, 45, 56));
        clock.setMode(YEAR);

        clock.incrementYear();
        TEST_ASSERT_EQUAL(2020, clock.displayValue());
    }

    void test_decrement_year(void) {
        Clock clock;

        clock.setDateTime(DateTime(2019, 5, 8, 12, 45, 56));
        clock.setMode(YEAR);

        clock.decrementYear();
        TEST_ASSERT_EQUAL(2018, clock.displayValue());
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
        RUN_TEST(test_display_mode);
        RUN_TEST(test_increment_hour);
        RUN_TEST(test_increment_hour_rollover);
        RUN_TEST(test_increment_minute);
        RUN_TEST(test_increment_minute_rollover);
        RUN_TEST(test_increment_month);
        RUN_TEST(test_increment_month_rollover);
        RUN_TEST(test_increment_day);
        RUN_TEST(test_increment_day_rollover_jan);
        RUN_TEST(test_increment_day_rollover_feb);
        RUN_TEST(test_increment_day_rollover_feb_leapyear);
        RUN_TEST(test_increment_year);
        RUN_TEST(test_decrement_year);
    }
}
