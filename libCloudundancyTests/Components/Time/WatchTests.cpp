#include "pch.h"
#include "libCloudundancy/Components/Time/Watch.h"
#include "libCloudundancyTests/Components/Time/MetalMock/CRTWatchMock.h"

TESTS(WatchTests)
FACTS(MonthDayYearToDateString_ReturnsExpectedDateString)
FACTS(YearMonthDayToDateString_ReturnsExpectedDateString)
FACTS(FastDateTimeNow_ReturnsCurrentDateTimeInISO8601Format)
FACTS(DateTimeNowHoursMinutesForFileNames_ReturnsYYYYDashMMDashDDUnderscoreHHDashMM)
FACTS(SecondsSinceMidnight_ReturnsCurrentSecondsSinceMidnight)
EVIDENCE

Watch _watch;
CRTWatchMock* _crtWatchMock = nullptr;

STARTUP
{
   _watch._crtWatch.reset(_crtWatchMock = new CRTWatchMock);
}

TEST4X4(MonthDayYearToDateString_ReturnsExpectedDateString,
   size_t month, size_t day, size_t year, const string& expectedDateString,
   1, 1, 1900, "01-01-1900",
   1, 2, 1901, "01-02-1901",
   2, 3, 1902, "02-03-1902",
   12, 31, 2018, "12-31-2018")
{
   const string dateString = Watch::MonthDayYearToDateString(month, day, year);
   ARE_EQUAL(expectedDateString, dateString);
}

TEST4X4(YearMonthDayToDateString_ReturnsExpectedDateString,
   unsigned month, unsigned day, int year, const string& expectedDateString,
   1, 1, 1900, "01-01-1900",
   1, 2, 1901, "01-02-1901",
   2, 3, 1902, "02-03-1902",
   12, 31, 2018, "12-31-2018")
{
   const date::year_month_day yearMonthDay{ date::year(year), date::month(month), date::day(day) };
   //
   const string dateString = Watch::YearMonthDayToDateString(yearMonthDay);
   //
   ARE_EQUAL(expectedDateString, dateString);
}

using C20 = array<char, 20>;
TEST7X7(FastDateTimeNow_ReturnsCurrentDateTimeInISO8601Format,
   const C20& expectedReturnValue, int tm_year, int tm_mon, int tm_mday, int tm_hour, int tm_min, int tm_sec,
   C20{ "1900-01-01 00:00:00" }, 0, 0, 1, 0, 0, 0,
   C20{ "1901-02-03 04:05:06" }, 1, 1, 3, 4, 5, 6,
   C20{ "1970-01-01 00:00:00" }, 70, 0, 1, 0, 0, 0,
   C20{ "2000-01-01 00:00:00" }, 100, 0, 1, 0, 0, 0,
   C20{ "2038-01-01 00:00:00" }, 138, 0, 1, 0, 0, 0,
   C20{ "9999-12-31 23:59:59" }, 8099, 11, 31, 23, 59, 59)
{
   tm tmValue{};
   tmValue.tm_year = tm_year;
   tmValue.tm_mon = tm_mon;
   tmValue.tm_mday = tm_mday;
   tmValue.tm_hour = tm_hour;
   tmValue.tm_min = tm_min;
   tmValue.tm_sec = tm_sec;
   _crtWatchMock->TmNowMock.Return(tmValue);
   //
   const array<char, 20> dateTimeNow = _watch.FastDateTimeNow();
   //
   METALMOCK(_crtWatchMock->TmNowMock.CalledOnce());
   STD_ARRAYS_ARE_EQUAL(expectedReturnValue, dateTimeNow);
}

TEST6X6(DateTimeNowHoursMinutesForFileNames_ReturnsYYYYDashMMDashDDUnderscoreHHDashMM,
   const char* expectedReturnValue, int tm_year, int tm_mon, int tm_mday, int tm_hour, int tm_min,
   "1900-01-01_00-00", 0, 0, 1, 0, 0,
   "1901-02-03_04-05", 1, 1, 3, 4, 5,
   "1970-01-01_00-00", 70, 0, 1, 0, 0,
   "2000-01-01_00-00", 100, 0, 1, 0, 0,
   "2038-01-01_00-00", 138, 0, 1, 0, 0,
   "9999-12-31_23-59", 8099, 11, 31, 23, 59)
{
   tm tmValue{};
   tmValue.tm_year = tm_year;
   tmValue.tm_mon = tm_mon;
   tmValue.tm_mday = tm_mday;
   tmValue.tm_hour = tm_hour;
   tmValue.tm_min = tm_min;
   _crtWatchMock->TmNowMock.Return(tmValue);
   //
   const string dateTimeNowMinutes = _watch.DateTimeNowHoursMinutesForFileNames();
   //
   METALMOCK(_crtWatchMock->TmNowMock.CalledOnce());
   ARE_EQUAL(expectedReturnValue, dateTimeNowMinutes);
}

TEST4X4(SecondsSinceMidnight_ReturnsCurrentSecondsSinceMidnight,
   unsigned expectedSecondsSinceMidnight, int tm_hour, int tm_min, int tm_sec,
   0u, 0, 0, 0,
   1u, 0, 0, 1,
   2u, 0, 0, 2,
   60u, 0, 1, 0,
   120u, 0, 2, 0,
   3600u, 1, 0, 0,
   7200u, 2, 0, 0,
   11u * 60u * 60u + 12u * 60u + 13u, 11, 12, 13,
   86399u, 23, 59, 59)
{
   tm tmNow;
   tmNow.tm_hour = tm_hour;
   tmNow.tm_min = tm_min;
   tmNow.tm_sec = tm_sec;
   _crtWatchMock->TmNowMock.Return(tmNow);
   //
   const unsigned secondsSinceMidnight = _watch.SecondsSinceMidnight();
   //
   METALMOCK(_crtWatchMock->TmNowMock.CalledOnce());
   ARE_EQUAL(expectedSecondsSinceMidnight, secondsSinceMidnight);
}

RUN_TESTS(WatchTests)
