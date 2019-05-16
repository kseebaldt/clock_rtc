#define private public

#include <Clock.h>
#include <unity.h>

#include <stdio.h>

#include "DisplayFlags.h"

namespace Test_Clock {

static bool _called = false;
static bool _alarmState = false;

    void callback(bool state) {
        _called = true;
        _alarmState = state;
    }

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

    void test_setAlarm_writesToNvram(void) {
        Clock clock;

        clock.setAlarm(12, 45);

        TEST_ASSERT_EQUAL(12, clock._rtc.readnvram(0));
        TEST_ASSERT_EQUAL(45, clock._rtc.readnvram(1));
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

    void test_display_TimeMode(void) {
        Clock clock;

        clock.setDateTime(DateTime(2019, 5, 8, 12, 45, 56));

        TEST_ASSERT_EQUAL(1245, clock.displayValue());
    }

    void test_display_DateMode(void) {
        Clock clock;

        clock.setDateTime(DateTime(2019, 5, 8, 12, 45, 56));
        clock.setMode(DATE);

        TEST_ASSERT_EQUAL(508, clock.displayValue());
    }

    void test_display_YearMode(void) {
        Clock clock;

        clock.setDateTime(DateTime(2019, 5, 8, 12, 45, 56));
        clock.setMode(YEAR);

        TEST_ASSERT_EQUAL(2019, clock.displayValue());
    }

    void test_display_AlarmMode(void) {
        Clock clock;

        clock.setDateTime(DateTime(2019, 5, 8, 12, 45, 56));
        clock.setAlarm(11, 23);
        clock.setMode(ALARM);

        TEST_ASSERT_EQUAL(1123, clock.displayValue());
    }

    void test_nextMode(void) {
        Clock clock;

        TEST_ASSERT_EQUAL(TIME, clock.mode());

        clock.nextMode();
        TEST_ASSERT_EQUAL(DATE, clock.mode());

        clock.nextMode();
        TEST_ASSERT_EQUAL(YEAR, clock.mode());

        clock.nextMode();
        TEST_ASSERT_EQUAL(ALARM, clock.mode());

        clock.nextMode();
        TEST_ASSERT_EQUAL(TIME, clock.mode());
    }

    void test_displayFlags_time_showsL1L2OnEvenSeconds(void) {
        Clock clock;

        clock.setDateTime(DateTime(2019, 5, 8, 12, 45, 56));

        TEST_ASSERT_EQUAL(DISPLAY_L1_L2, clock.displayFlags());
    }

    void test_displayFlags_time_showsNoneOnOddSeconds(void) {
        Clock clock;

        clock.setDateTime(DateTime(2019, 5, 8, 12, 45, 57));

        TEST_ASSERT_EQUAL(DISPLAY_NONE, clock.displayFlags());
    }

    void test_displayFlags_date_showsDP2(void) {
        Clock clock;

        clock.setDateTime(DateTime(2019, 5, 8, 12, 45, 56));
        clock.setMode(DATE);

        TEST_ASSERT_EQUAL(DISPLAY_DP2, clock.displayFlags());
    }

    void test_displayFlags_year_showsNone(void) {
        Clock clock;

        clock.setDateTime(DateTime(2019, 5, 8, 12, 45, 56));
        clock.setMode(YEAR);

        TEST_ASSERT_EQUAL(DISPLAY_NONE, clock.displayFlags());
    }

    void test_displayFlags_alarm_showsL1L2(void) {
        Clock clock;

        clock.setDateTime(DateTime(2019, 5, 8, 12, 45, 56));
        clock.setMode(ALARM);

        TEST_ASSERT_EQUAL(DISPLAY_L1_L2, clock.displayFlags());
    }

    void test_displayFlags_alarmActivated_addsDP4(void) {
        Clock clock;

        clock.setDateTime(DateTime(2019, 5, 8, 12, 45, 56));
        clock.setMode(ALARM);
        clock.switch1(true);

        TEST_ASSERT_EQUAL(DISPLAY_L1_L2 | DISPLAY_DP4, clock.displayFlags());
    }

    void test_button1_TimeMode_incrementsHour(void) {
        Clock clock;

        clock.setDateTime(DateTime(2019, 5, 8, 12, 45, 56));

        clock.button1();
        TEST_ASSERT_EQUAL(1345, clock.displayValue());
    }

    void test_button1_TimeMode_incrementsHourRollover(void) {
        Clock clock;

        clock.setDateTime(DateTime(2019, 5, 8, 23, 45, 56));

        clock.button1();
        TEST_ASSERT_EQUAL(45, clock.displayValue());

        clock.setMode(DATE);
        TEST_ASSERT_EQUAL(508, clock.displayValue());
    }

     void test_button2_TimeMode_incrementsMinute(void) {
        Clock clock;

        clock.setDateTime(DateTime(2019, 5, 8, 12, 45, 56));

        clock.button2();
        TEST_ASSERT_EQUAL(1246, clock.displayValue());
    }

    void test_button2_TimeMode_incrementsMinuteRollover(void) {
        Clock clock;

        clock.setDateTime(DateTime(2019, 5, 8, 12, 59, 56));

        clock.button2();
        TEST_ASSERT_EQUAL(1200, clock.displayValue());
    }

    void test_button1_DateMode_incrementsMonth(void) {
        Clock clock;

        clock.setDateTime(DateTime(2019, 5, 8, 12, 45, 56));
        clock.setMode(DATE);

        clock.button1();
        TEST_ASSERT_EQUAL(608, clock.displayValue());
    }

    void test_button1_DateMode_incrementsMonthRollover(void) {
        Clock clock;

        clock.setDateTime(DateTime(2019, 12, 8, 23, 45, 56));
        clock.setMode(DATE);

        clock.button1();
        TEST_ASSERT_EQUAL(108, clock.displayValue());

        clock.setMode(YEAR);
        TEST_ASSERT_EQUAL(2019, clock.displayValue());
    }

    void test_button2_DateMode_incrementsDay(void) {
        Clock clock;

        clock.setDateTime(DateTime(2019, 5, 8, 12, 45, 56));
        clock.setMode(DATE);

        clock.button2();
        TEST_ASSERT_EQUAL(509, clock.displayValue());
    }

    void test_button2_DateMode_incrementsDayRollover_jan(void) {
        Clock clock;

        clock.setDateTime(DateTime(2019, 1, 31, 23, 45, 56));
        clock.setMode(DATE);

        clock.button2();
        TEST_ASSERT_EQUAL(101, clock.displayValue());
    }

    void test_button2_DateMode_incrementsDayRollover_feb(void) {
        Clock clock;

        clock.setDateTime(DateTime(2019, 2, 28, 23, 45, 56));
        clock.setMode(DATE);

        clock.button2();
        TEST_ASSERT_EQUAL(201, clock.displayValue());
    }

    void test_button2_DateMode_incrementsDayRollover_feb_leapyear(void) {
        Clock clock;

        clock.setDateTime(DateTime(2020, 2, 28, 23, 45, 56));
        clock.setMode(DATE);

        clock.button2();
        TEST_ASSERT_EQUAL(229, clock.displayValue());

        clock.button2();
        TEST_ASSERT_EQUAL(201, clock.displayValue());
    }

    void test_button1_YearMode_incrementsYear(void) {
        Clock clock;

        clock.setDateTime(DateTime(2019, 5, 8, 12, 45, 56));
        clock.setMode(YEAR);

        clock.button1();
        TEST_ASSERT_EQUAL(2020, clock.displayValue());
    }

    void test_button2_YearMode_decrementsYear(void) {
        Clock clock;

        clock.setDateTime(DateTime(2019, 5, 8, 12, 45, 56));
        clock.setMode(YEAR);

        clock.button2();
        TEST_ASSERT_EQUAL(2018, clock.displayValue());
    }

    void test_button1_AlarmMode_incrementsHour(void) {
        Clock clock;

        clock.setAlarm(12, 45);
        clock.setMode(ALARM);

        clock.button1();
        TEST_ASSERT_EQUAL(1345, clock.displayValue());
    }

    void test_button1_AlarmMode_incrementsHourRollover(void) {
        Clock clock;

        clock.setAlarm(23, 45);
        clock.setMode(ALARM);

        clock.button1();
        TEST_ASSERT_EQUAL(45, clock.displayValue());

        clock.setMode(DATE);
        TEST_ASSERT_EQUAL(508, clock.displayValue());
    }

     void test_button2_AlarmMode_incrementsMinute(void) {
        Clock clock;

        clock.setAlarm(12, 45);
        clock.setMode(ALARM);

        clock.button2();
        TEST_ASSERT_EQUAL(1246, clock.displayValue());
    }

    void test_button2_AlarmMode_incrementsMinuteRollover(void) {
        Clock clock;

        clock.setAlarm(12, 59);
        clock.setMode(ALARM);

        clock.button2();
        TEST_ASSERT_EQUAL(1200, clock.displayValue());
    }

    void test_switch1_setsAlarmActivated(void) {
        Clock clock;
        
        clock.switch1(true);
        TEST_ASSERT(clock.alarmActivated());

        clock.switch1(false);
        TEST_ASSERT(!clock.alarmActivated());
    }

    void test_alarmCallback_whenActivated_CallsCallbackAtAlarmTimeOnlyOnce(void) {
        Clock clock;

        clock.setDateTime(DateTime(2019, 5, 8, 12, 45, 59));
        clock.setAlarm(12, 46);
        clock.setAlarmCallback(callback);
        clock.switch1(true);

        _called = false;
        clock.tick();
        TEST_ASSERT(!_called);

        clock.setDateTime(DateTime(2019, 5, 8, 12, 46, 00));
        clock.tick();
        TEST_ASSERT(_called);
        TEST_ASSERT(_alarmState);

        _called = false;
        clock.tick();
        TEST_ASSERT(!_called);
    }

    void test_alarmCallback_whenDeactivated_CallsCallbackIfRunning(void) {
        Clock clock;

        clock.setDateTime(DateTime(2019, 5, 8, 12, 46, 00));
        clock.setAlarm(12, 46);
        clock.setAlarmCallback(callback);
        clock.switch1(true);

        clock.tick();
        TEST_ASSERT(_called);
        TEST_ASSERT(_alarmState);

        _called = false;
        clock.switch1(false);
        clock.tick();
        TEST_ASSERT(_called);
        TEST_ASSERT(!_alarmState);
    }

    void runTests() {
        RUN_TEST(test_start);
        RUN_TEST(test_setTime);
        RUN_TEST(test_setAlarm_writesToNvram);
        RUN_TEST(test_time_1digithour);
        RUN_TEST(test_time_2digithour);
        RUN_TEST(test_date_1digitmonth);
        RUN_TEST(test_date_2digitmonth);
        RUN_TEST(test_date_1digitday);
        RUN_TEST(test_year);
        RUN_TEST(test_display_TimeMode);
        RUN_TEST(test_display_DateMode);
        RUN_TEST(test_display_YearMode);
        RUN_TEST(test_display_AlarmMode);

        RUN_TEST(test_nextMode);
        RUN_TEST(test_displayFlags_time_showsL1L2OnEvenSeconds);
        RUN_TEST(test_displayFlags_time_showsNoneOnOddSeconds);
        RUN_TEST(test_displayFlags_date_showsDP2);
        RUN_TEST(test_displayFlags_year_showsNone);
        RUN_TEST(test_displayFlags_alarm_showsL1L2);
        RUN_TEST(test_displayFlags_alarmActivated_addsDP4);
        
        RUN_TEST(test_button1_TimeMode_incrementsHour);
        RUN_TEST(test_button1_TimeMode_incrementsHourRollover);
        RUN_TEST(test_button2_TimeMode_incrementsMinute);
        RUN_TEST(test_button2_TimeMode_incrementsMinuteRollover);
        RUN_TEST(test_button1_DateMode_incrementsMonth);
        RUN_TEST(test_button1_DateMode_incrementsMonthRollover);
        RUN_TEST(test_button2_DateMode_incrementsDay);
        RUN_TEST(test_button2_DateMode_incrementsDayRollover_jan);
        RUN_TEST(test_button2_DateMode_incrementsDayRollover_feb);
        RUN_TEST(test_button2_DateMode_incrementsDayRollover_feb_leapyear);
        RUN_TEST(test_button1_YearMode_incrementsYear);
        RUN_TEST(test_button2_YearMode_decrementsYear);
        RUN_TEST(test_button1_AlarmMode_incrementsHour);
        RUN_TEST(test_button1_AlarmMode_incrementsHourRollover);
        RUN_TEST(test_button2_AlarmMode_incrementsMinute);
        RUN_TEST(test_button2_AlarmMode_incrementsMinuteRollover);
        RUN_TEST(test_switch1_setsAlarmActivated);

        RUN_TEST(test_alarmCallback_whenActivated_CallsCallbackAtAlarmTimeOnlyOnce);
        RUN_TEST(test_alarmCallback_whenDeactivated_CallsCallbackIfRunning);
    }
}
