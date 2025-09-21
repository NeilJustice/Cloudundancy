#include "pch.h"
#include "libCloudundancy/Components/Time/CRTWatch.h"
#include "libCloudundancy/Components/Time/Watch.h"
#include "libCloudundancyTests/Components/Time/MetalMock/CRTWatchMock.h"

TESTS(WatchTests)
AFACT(DefaultConstructor_NewsCRTWatch)
FACTS(DateTimeNow_ReturnsLocalDateTimeNow)
FACTS(DateTimeNowForFileNames_ReturnsYYYYDashMMDashDDTHHDashMMDashSS)
AFACT(TMNow_ReturnstmNow__CodeCoverage)
EVIDENCE

class WatchSelfMocked : public Metal::Mock<Utils::Watch>
{
public:
   METALMOCK_NONVOID0_CONST(tm, TMNow)
};
unique_ptr<WatchSelfMocked> _watchSelfMocked;
Utils::CRTWatchMock* _crtWatchMock = nullptr;

STARTUP
{
   _watchSelfMocked = make_unique<WatchSelfMocked>();
   // Constant Components
   _watchSelfMocked->_crtWatch.reset(_crtWatchMock = new Utils::CRTWatchMock);
}

TEST(DefaultConstructor_NewsCRTWatch)
{
   Utils::Watch watch;
   // Constant Components
   DELETE_TO_ASSERT_NEWED(watch._crtWatch);
}

TEST2X2(DateTimeNow_ReturnsLocalDateTimeNow,
   const tm& tmNow, const string& expectedReturnValue,
   Tm(0, 1, 0, 0, 0, 0), "1900-01-01 12:00:00 AM",
   Tm(1, 2, 1, 1, 1, 1), "1901-02-02 01:01:01 AM",
   Tm(2, 3, 2, 11, 11, 11), "1902-03-03 11:11:11 AM",
   Tm(11, 31, 99, 23, 59, 59), "1999-12-31 11:59:59 PM",
   Tm(0, 1, 100, 0, 0, 0), "2000-01-01 12:00:00 AM",
   Tm(1, 3, 101, 4, 5, 6), "2001-02-03 04:05:06 AM")
{
   _watchSelfMocked->TMNowMock.Return(tmNow);
   //
   const string dateTimeNow = _watchSelfMocked->DateTimeNow();
   //
   METALMOCK(_watchSelfMocked->TMNowMock.CalledOnce());
   ARE_EQUAL(expectedReturnValue, dateTimeNow);
}

TEST7X7(DateTimeNowForFileNames_ReturnsYYYYDashMMDashDDTHHDashMMDashSS,
   const string& expectedReturnValue, int tm_year, int tm_mon, int tm_mday, int tm_hour, int tm_min, int tm_sec,
   "1900-01-01T00-00-00"s, 0, 0, 1, 0, 0, 0,
   "1901-02-03T04-05-01"s, 1, 1, 3, 4, 5, 1,
   "1970-01-01T00-00-15"s, 70, 0, 1, 0, 0, 15,
   "2000-01-01T00-00-30"s, 100, 0, 1, 0, 0, 30,
   "2038-01-01T00-00-45"s, 138, 0, 1, 0, 0, 45,
   "9999-12-31T23-59-59"s, 8099, 11, 31, 23, 59, 59)
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
   const string dateTimeNowMinutes = _watchSelfMocked->DateTimeNowForFileNames();
   //
   METALMOCK(_crtWatchMock->TmNowMock.CalledOnce());
   ARE_EQUAL(expectedReturnValue, dateTimeNowMinutes);
}

TEST(TMNow_ReturnstmNow__CodeCoverage)
{
   Utils::Watch watch;
   //
   const tm tmNow = watch.TMNow();
   //
   IS_NOT_DEFAULT_VALUE(tmNow);
}

static constexpr tm Tm(int tmMonth, int tmMonthDay, int tmYear, int tmHour, int tmMin, int tmSec)
{
   tm tmNow{};
   tmNow.tm_sec = tmSec;
   tmNow.tm_min = tmMin;
   tmNow.tm_hour = tmHour;
   tmNow.tm_mday = tmMonthDay;
   tmNow.tm_mon = tmMonth;
   tmNow.tm_year = tmYear;
   tmNow.tm_wday = 0;
   tmNow.tm_yday = 0;
   tmNow.tm_isdst = 0;
   return tmNow;
}

RUN_TESTS(WatchTests)
