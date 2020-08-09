#include "pch.h"
#include "libCloudundancy/Components/Time/Watch.h"
#include "libCloudundancyTests/Components/Time/MetalMock/CRTWatchMock.h"

TESTS(WatchTests)
FACTS(MonthDayYearToDateString_ReturnsExpectedDateString)
FACTS(DateTimeNowHoursMinutesForFileNames_ReturnsYYYYDashMMDashDDUnderscoreHHDashMM)
FACTS(SecondsSinceMidnight_ReturnsCurrentSecondsSinceMidnight)
FACTS(DaysBetweenDates_RetursnTheNumberOfDaysBetweenTwoDates)
FACTS(SecondsToHHMMSS_ReturnsExpected)
EVIDENCE

Watch _watch;
CRTWatchMock* _crtWatchMock = nullptr;

STARTUP
{
   _watch._crtWatch.reset(_crtWatchMock = new CRTWatchMock);
}

TEST4X4(MonthDayYearToDateString_ReturnsExpectedDateString,
   int month, int day, int year, const string& expectedDateString,
   1, 1, 1900, "01-01-1900",
   1, 2, 1901, "01-02-1901",
   2, 3, 1902, "02-03-1902",
   12, 31, 2018, "12-31-2018")
{
   const string dateString = Watch::MonthDayYearToDateString(month, day, year);
   ARE_EQUAL(expectedDateString, dateString);
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
	const string dateTimeNowHoursMinutes = _watch.DateTimeNowHoursMinutesForFileNames();
	//
   METALMOCK(_crtWatchMock->TmNowMock.CalledOnce());
   ARE_EQUAL(expectedReturnValue, dateTimeNowHoursMinutes);
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
   11u*60u*60u + 12u*60u + 13u, 11, 12, 13,
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

TEST3X3(DaysBetweenDates_RetursnTheNumberOfDaysBetweenTwoDates,
   const date::year_month_day& date1, const date::year_month_day& date2, int expectedReturnValue,
   date::year_month_day{}, date::year_month_day{}, 0,
   date::year_month_day(date::year(2000), date::month(1), date::day(3)), date::year_month_day(date::year(2000), date::month(1), date::day(1)), -2,
   date::year_month_day(date::year(2000), date::month(1), date::day(2)), date::year_month_day(date::year(2000), date::month(1), date::day(1)), -1,
   date::year_month_day(date::year(2000), date::month(1), date::day(1)), date::year_month_day(date::year(2000), date::month(1), date::day(1)), 0,
   date::year_month_day(date::year(2000), date::month(1), date::day(1)), date::year_month_day(date::year(2000), date::month(1), date::day(2)), 1,
   date::year_month_day(date::year(2000), date::month(1), date::day(1)), date::year_month_day(date::year(2000), date::month(1), date::day(3)), 2,
   date::year_month_day(date::year(2000), date::month(1), date::day(1)), date::year_month_day(date::year(2000), date::month(2), date::day(1)), 31,
   date::year_month_day(date::year(2000), date::month(1), date::day(1)), date::year_month_day(date::year(2001), date::month(1), date::day(1)), 366,
   date::year_month_day(date::year(2001), date::month(1), date::day(1)), date::year_month_day(date::year(2002), date::month(1), date::day(1)), 365)
{
   const int daysBetweenDates = _watch.DaysBetweenDates(date1, date2);
   ARE_EQUAL(expectedReturnValue, daysBetweenDates);
}

TEST2X2(SecondsToHHMMSS_ReturnsExpected,
   unsigned seconds, const string& expectedReturnValue,
   0, "00:00:00",
   1, "00:00:01",
   59, "00:00:59",
   60, "00:01:00",
   61, "00:01:01",
   119, "00:01:59",
   120, "00:02:00",
   59 * 60 + 59, "00:59:59",
   60 * 60, "01:00:00",
   99 * 60 * 60 + 59 * 60 + 59, "99:59:59")
{
   const string hhmmss = _watch.SecondsToHHMMSS(seconds);
   ARE_EQUAL(expectedReturnValue, hhmmss);
}

RUN_TESTS(WatchTests)
